require("player")
require("enemy")
require("background")
require("foreground")

local battle = class("battle")

function battle:battle()
	self.background = new("background")
	self.foreground = new("foreground")
	self.player = new("player")
	self.left_enemy = {}
	self.right_enemy = {}
	self.move_offset = 0 -- 偏移量
	self.move_dst = 0 -- 人物和小兵的距離
	self.enemy_in_attact_area = 0 --小兵在攻擊區域 0  不在 1 在
	self.player_attact_state = 0 -- 0 沒有攻擊，1 右邊攻擊，-1 左邊攻擊
end

function battle:add_left_enemy()
	table.insert(self.left_enemy, new("enemy", 1))
end

function battle:add_right_enemy()
	table.insert(self.right_enemy, new("enemy", -1))
end

function battle:player_attack(facing)
	if facing == 1 then
		local max_position = 400
		local dst_index = -1
		local dst_enemy = nil
		for index, enemy in ipairs(self.right_enemy) do
			--trace(enemy.position);
			if enemy.position > max_position then
				dst_index = index
				dst_enemy = enemy
				max_position = enemy.position
			end
		end
		if dst_enemy then
			dst_enemy:be_attacked()
			table.remove(self.right_enemy, dst_index)
		end
	else
		local max_position = 400
		local dst_enemy = nil
		for index, enemy in ipairs(self.left_enemy) do
			if enemy.position > max_position then
				dst_index = index
				dst_enemy = enemy
				max_position = enemy.position
			end
		end
		if dst_enemy then
			dst_enemy:be_attacked()
			table.remove(self.left_enemy, dst_index)
		end
	end
	self.player_attact_state = 0
end

function battle:player_before_attack(facing)
	self.player_attact_state = facing
	if facing == 1 then
		local max_position = 400
		local dst_index = -1
		local dst_enemy = nil
		for index, enemy in ipairs(self.right_enemy) do
			--trace(enemy.position);
			if enemy.position > max_position then
				dst_index = index
				dst_enemy = enemy
				max_position = enemy.position
			end
		end
		if dst_enemy then
			self.enemy_in_attact_area = 1
			self.move_dst = (Game.ScreenWidth  / 2  - dst_enemy.position + self.move_offset) + 10
		else
			self.enemy_in_attact_area = 0
			self.move_dst = 50
		end
	else
		local max_position = 400
		local dst_enemy = nil
		for index, enemy in ipairs(self.left_enemy) do
			if enemy.position > max_position then
				dst_index = index
				dst_enemy = enemy
				max_position = enemy.position
			end
		end
		if dst_enemy then
			self.enemy_in_attact_area = 1
			self.move_dst = (Game.ScreenWidth  / 2  - dst_enemy.position + self.move_offset) + 10
		else
			self.enemy_in_attact_area = 0
			self.move_dst = 50
		end
	end
end

function battle:draw()
	self.background:draw()
	self.player:draw()
	for _, enemy in ipairs(self.left_enemy) do
		enemy:draw()
	end
	for _, enemy in ipairs(self.right_enemy) do
		enemy:draw()
	end
	self.foreground:draw()
end

function battle:update(now, delta)
	if #self.left_enemy == 0  then
	--	self:add_left_enemy()
	end
	
	if #self.right_enemy == 0 then
		self:add_right_enemy()
	end
	self.background:update(delta)
	self.player:update(now, delta)
	for _, enemy in ipairs(self.left_enemy) do
		enemy:update(now, delta)
	end
	for _, enemy in ipairs(self.right_enemy) do
		enemy:update(now, delta)
	end
	self.foreground:update(delta)
end