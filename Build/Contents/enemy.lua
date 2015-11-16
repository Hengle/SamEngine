require('texture_atlas')
local fsm = require('fsm')

local enemy = class("enemy")

function enemy:enemy(facing,position,id)
	self.enemy_id = id
	self.facing = facing
	self.position = position
	self.stop = 0 -- 0表示正常，1表示停止，2表示攻擊狀態
	self.width = 0
	self.after_attack_time_delay = 0 --攻擊回到攻擊后，需要有個延時
	self.index = 0
	self.move_dst = 0
	self.attack_pause = 0 -- 攻擊停頓
	self.attack_pause_time_index = 0 --攻擊停頓時間
	self.is_thrower = false
	self.is_dead = false
	self.active_attack = 0
	self.speed = math.random(2, 2)
	self.animations = {
	walk = new("texture_atlas", "enemy_walk"),
	before_attack = new("texture_atlas", "enemy_before_attack"),
	attack = new("texture_atlas", "enemy_attack"),
	after_attack = new("texture_atlas", "enemy_after_attack"),
	die = new("texture_atlas", "enemy_die"),
	}
	self.animations.attack.callback = function() self.state:recovery() end
	self.animations.die.callback = function() Game.battle:remove(self.enemy_id) end
	self.animations.walk.loop = true
	self.state = fsm.create({
	initial = "walk",
	events = {
	{ name = "walk", from = "before_attack", to = "before_attack" },
	{ name = "ready", from = "walk", to = "before_attack" },
	{ name = "attack", from = "before_attack", to = "attack" },
	{ name = "recovery", from = "attack", to = "after_attack" },
	{ name = "reset", from = "after_attack", to = "walk" },
	{ name = "be_attacked", from = {"walk", "before_attack", "after_attack" }, to = "die" },
	},
	callbacks = {
	on_state_change = function(fsm, event, from, to)
		self.current_animation = self.animations[to]
		self.current_animation:play()
	end
	}
	})
	self.current_animation = self.animations.walk
	self.last_attack_time = 0
end

function enemy:be_attacked()
	self.is_dead = true
	self.state:be_attacked()
end
-- 小兵攻擊
function enemy:attack(now)
	if (now - Game.battle.last_attack_time > 1500 and Game.battle.player.state:can('be_attacked') and self.facing == -Game.battle.player.facing) then
		--trace(string.format("%d,p:%d",self.position,Game.battle.player.position))
		self.state:attack()
		Game.battle:enemy_attack()
		Game.battle.last_attack_time = now
		self.active_attack = 0
	end
end

function enemy:attack_pause_f()
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


function enemy:update(now, delta)
	if self:attack_pause_f() then
		return
	end
	
	if Game.battle.player.state:is("be_attack") then
		if self.state:is("attack") or self.state:is("after_attack") then
			if self.state.current == "after_attack" then
				if self.after_attack_time_delay > 20 then
					self.state:reset()
					self.after_attack_time_delay = 0
				end
				self.after_attack_time_delay = self.after_attack_time_delay + 1
			end
		else
			if self.move_dst > 0 then
				self.move_dst = self.move_dst - Game.config.enemy_move_speed
				if Game.battle.enemy_left_face == self.facing then
					self.position = self.position - Game.config.enemy_move_speed
				else
					self.position = self.position + Game.config.enemy_move_speed
				end
			end
			
			if self.state:is("before_attack") then
				self.state:reset()
			end
			return
		end
	elseif self.state.current == "after_attack" then
		if self.after_attack_time_delay > 20 then
			self.state:reset()
			self.after_attack_time_delay = 0
		end
		self.after_attack_time_delay = self.after_attack_time_delay + 1
	end
	
	local position = 0
	
	if self.state.current == "walk" then
		if self.facing == Game.battle.enemy_left_face then
			self.position = self.position  + self.speed
			position = Game.battle.player.position - Game.config.enemy_before_attack_dst
			if self.position >= position then
				self.state:ready()
				if Game.battle.player_attack_state ~=0 and self.move_dst > 0 then
					self.move_dst = self.move_dst - self.speed;
				end
			end
		else
			self.position = self.position - self.speed
			position = Game.battle.player.position + Game.config.enemy_before_attack_dst
			if self.position <= position then
				self.state:ready()
				if Game.battle.player_attack_state ~=0 and self.move_dst > 0 then
					self.move_dst = self.move_dst - self.speed;
				end
			end
		end
	elseif self.state.current == "before_attack" then

		if Game.battle.player.attack_miss and self.active_attack == 1 then
			local dst = math.abs(self.position - Game.battle.player.position)
			if dst > Game.config.enemy_attack_dst then
				position = math.abs(self.position - Game.battle.player.position) - Game.config.enemy_attack_dst
				if position > Game.config.enemy_move_speed then
					position  =  Game.config.enemy_move_speed
				end
				if self.facing == Game.battle.enemy_left_face then
					self.position = self.position +  position
				else
					self.position = self.position -  position
				end
			else
				self:attack(now)
			end
		else
			if self.facing == Game.battle.enemy_left_face then
				if (self.position + Game.config.enemy_attack_dst + self.width/2 + Game.battle.player.width /2) < Game.battle.player.position then
					self.position = self.position + self.speed
				else
					self:attack(now)
				end
			else
				if (self.position - Game.config.enemy_attack_dst - self.width/2 - Game.battle.player.width /2)  > Game.battle.player.position then
					self.position = self.position - self.speed
				else
					self:attack(now)
				end
			end
		end
	end
	self.current_animation:update(delta)
end
function enemy:draw()
	self.current_animation.image.x = self.position - Game.battle.move_offset
	self.current_animation.image.scaleX = self.facing
	self.current_animation:draw()
end