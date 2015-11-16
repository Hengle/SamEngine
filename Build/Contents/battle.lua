require("player")
require("enemy")
require("background")
require("foreground")

local battle = class("battle")

function battle:battle()
	self.background = new("background")
	self.foreground = new("foreground")
	self.player = new("player")
	self.list_enemy = {}
	self.move_offset = 0 -- 偏移量
	self.move_dst = 0 -- 人物和小兵的距離
	self.enemy_in_attack_area = 0 --小兵在攻擊區域 0  不在 1 在
	self.player_attack_state = 0 -- 0 沒有攻擊，1 右邊攻擊，-1 左邊攻擊
	self.player_be_attacked = 0 -- 0表示沒有被攻擊，1表示被攻擊了，
	self.player_change_face = 0 -- 改變人物的朝向
	self.player_left_face = -1
	self.player_right_face = 1
	self.enemy_left_face = 1
	self.enemy_right_face = -1
	self.enemy_move_dst = 0
	self.insert_enemy_time = 0
	self.last_attack_time  = 0
	self.attack_pause_time_index = 0 --攻擊延時
	self.attack_pause = 0 --攻擊停頓
	self.enemy_id  = 0
end

function battle:add_enemy(facing)
	self.enemy_id = self.enemy_id + 1
	if facing == self.enemy_left_face then
		table.insert(self.list_enemy, new("enemy", facing , self.move_offset , self.enemy_id))
	else
		table.insert(self.list_enemy, new("enemy", facing , Game.ScreenWidth + self.move_offset , self.enemy_id))
	end
end

function battle:player_attack(facing)
	local max_position = Game.config.right_attack_area
	local dst_index = -1
	local dst_enemy = nil
	local dst
	for index, enemy in ipairs(self.list_enemy) do
		if facing == -enemy.facing then
			dst = math.abs(enemy.position - Game.battle.player.position)
			if dst <= max_position and enemy.is_dead == false  then
				dst_index = index
				dst_enemy = enemy
				max_position = dst
			end
		end
	end
	if dst_enemy then
		dst_enemy:be_attacked()
		dst_enemy.index = dst_index
	end
	self.player_attack_state = 0
end
function battle:remove(id)
	for index, enemy in ipairs(self.list_enemy) do
		if enemy and enemy.enemy_id == id then
			table.remove(self.list_enemy, index)
			trace(string.format("remove.index:%d", index))
		end
	end
end
function battle:player_before_attack(facing)
	self.player_attack_state = facing
	local max_position = Game.config.right_attack_area
	local dst_enemy = nil
	local dst
	for index, enemy in ipairs(self.list_enemy) do
		if facing == -enemy.facing then
			dst = math.abs(enemy.position - Game.battle.player.position)
			if dst <= max_position and enemy.is_dead == false then
				dst_enemy = enemy
				max_position = dst
			end
		end
	end
	if dst_enemy then
		self.enemy_in_attack_area = 1
		self.player.attack_miss = 0
		self.player.move_distance = max_position - Game.config.player_attack_dst
		trace(string.format("player_before_attack.index:%d", dst_enemy.index))
	else
		self.enemy_in_attack_area = 0
		self.player.attack_miss = 1
		self.player.move_distance = Game.config.player_attack_miss_move_dst
	end
end

function battle:enemy_attack()
	for _, enemy in ipairs(self.list_enemy) do
		if enemy.state:is("attack")==false then
			enemy.move_dst = Game.config.move_distance
		end
		--self.attack_pause = 1
	end
	self.player:be_attacked()
end

function battle:draw()
	self.background:draw()
	self.player:draw()
	for _, enemy in ipairs(self.list_enemy) do
		enemy:draw()
	end
	self.foreground:draw()
end

function battle:attack_pause()
	if Game.config.attack_pause_delay ~= 0  and self.attack_pause == 1  then
		self.attack_pause_time_index = self.attack_pause_time_index + 1
		if Game.config.attack_pause_time > self.attack_pause_time_index and self.attack_pause_time_index  % Game.config.attack_pause_delay ~= 0 then
			return true
		end
	end
	
	if self.attack_pause_time_index >= Game.config.attack_pause_time then
		self.attack_pause_time_index = 0
		self.attack_pause = 0
	end
	return false
end

function battle:enemy_nudge_f()
	for i, enemy in ipairs(self.list_enemy) do
		for j, enemy1 in ipairs(self.list_enemy) do
			if (enemy1.is_dead == false and enemy1.is_thrower == false) then
				for k, enemy2 in ipairs(self.list_enemy) do
					if (((j ~= k) and enemy2.is_dead == false) and enemy2.is_thrower == false) then
						if enemy1.facing == self.enemy_left_face then
							if ((enemy1.position < enemy2.position) and ((enemy2.position - enemy1.position) < 64)) then
								enemy1.position = enemy2.position - 64;
							elseif ((enemy1.position > enemy2.position) and ((enemy1.position - enemy2.position) < 64)) then
								enemy1.position = enemy2.position + 64;
							end
						end
					end
				end
			end
		end
	end
end
function battle:update(now, delta)
	if self.insert_enemy_time % 30 == 0 and #self.list_enemy < 2 then
		local random = math.random(-100,100)
		if random > 0 then
			if math.abs(random) % 3 == 0 then
				self:add_enemy(1)
			end
		else
			if math.abs(random) % 3 == 0 then
				self:add_enemy(-1)
			end
		end
	end
	if #self.list_enemy > 0 then
		--self:enemy_nudge_f()
	end
	self.insert_enemy_time = self.insert_enemy_time + 1
	self.background:update(delta)
	self:deal_palyer_attack_miss()
	if Game.battle.player.state.is("idle") then
		self:deal_palyer_face()--處理計算一下離人物最近的一個小兵的朝向
	end
	self.player:update(now, delta)
	for _, enemy in ipairs(self.list_enemy) do
		enemy:update(now, delta)
	end
	self.foreground:update(delta)
end

function battle:deal_palyer_attack_miss()
	local dst_enemy = nil
	local min_position = 0
	if self.player.attack_miss == 2 and self.enemy_in_attack_area == 0 then
		for _, enemy in ipairs(self.list_enemy) do
			if enemy and math.abs(enemy.position - Game.battle.player.position) < min_position or min_position == 0 then

				if enemy.facing == self.enemy_left_face then
					min_position = math.abs(enemy.position - Game.battle.player.position)
					
				else
					min_position = math.abs(Game.battle.player.position - enemy.position)
				end
				if min_position - Game.config.player_attack_miss_move_dst - 350 < Game.config.enemy_attack_dst then
					dst_enemy = enemy					
				end
			end
		end
		if dst_enemy and dst_enemy.active_attack == 0 and dst_enemy.facing == -self.player.facing then
			dst_enemy.active_attack = 1
			dst_enemy.state:ready()
		end
	end
end

function battle:deal_palyer_face()
	local dst_enemy = nil
	local min_position = 0
	for _, enemy in ipairs(self.list_enemy) do
		if enemy and math.abs(enemy.position - Game.battle.player.position) < min_position or min_position == 0 then
			dst_enemy = enemy
			if enemy.facing == self.enemy_left_face then
				min_position = math.abs(enemy.position - Game.battle.player.position)
			else
				min_position = math.abs(Game.battle.player.position - enemy.position)
			end
		end
	end
	if dst_enemy then
		self.player_change_face = -dst_enemy.facing
	end
end