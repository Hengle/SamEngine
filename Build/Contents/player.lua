require('texture_atlas')
local fsm = require('fsm')

local player = class("player")

function player:player()
	self.facing = 1
	self.position = 640
	self.width = 0
	self.last_be_attack_time = 0
	self.distance = 0 --和小兵之間的距離
	self.move_distance = 0 --運行距離
	self.old_x = 0
	self.attack_pause = 0 -- 攻擊停頓
	self.attack_pause_time_index = 0 --攻擊停頓時間
	self.attack_miss = false  -- 攻擊miss
	self.animations = {
	idle = new("texture_atlas", "player_idle"),
	run = new("texture_atlas", "player_run"),
	before_attack = new("texture_atlas", "player_before_attack"),
	attack = new("texture_atlas", "player_attack"),
	after_attack = new("texture_atlas", "player_after_attack"),
	be_attack = new("texture_atlas", "player_be_attack"),
	}
	self.animations.idle.loop = true
	self.animations.idle.callback = function() end
	self.animations.run.callback = function() end
	--self.animations.before_attack.callback = function() self.state:attack() end
	self.animations.attack.callback = function()  self:attack_after() end
	self.animations.after_attack.callback = function() self.state:reset() self.attack_miss = false end
	--self.animations.be_attack.callback = function() self.state:reset() end
	self.state = fsm.create({
	initial = "idle",
	events = {
	{ name = "run", from = "idle", to = "run" },
	{ name = "ready", from = { "idle", "run", "after_attack","attack" }, to = "before_attack" },
	{ name = "attack", from = "before_attack", to = "attack" },
	{ name = "recovery", from = "attack", to = "after_attack" },
	{ name = "reset", from = {"after_attack","be_attack"}, to = "idle" },
	{ name = "be_attacked", from ={"idle","run"}, to ="be_attack" },
	},
	callbacks = {
	on_state_change = function(fsm, event, from, to)
		self.current_animation = self.animations[to]
		self.current_animation:play()
	end
	}
	})
	self.current_animation = self.animations.idle
end

function player:attack_left()
	if self.state:can('ready') then
		self.facing = -1
		self.state:ready()
		Game.battle:player_before_attack(-1)
	end
end

function player:attack_right()
	if self.state:can('ready') then
		self.facing = 1
		self.state:ready()
		Game.battle:player_before_attack(1)
	end
end
--攻擊后
function player:attack_after()
	if self.attack_miss == 1 then
		self.attack_miss = 2
	end
	self.state:recovery()
end

function player:be_attacked()
	self.move_distance = Game.config.move_distance
	self.state:be_attacked()
end

function player:attack_pause_f()
	if Game.config.attack_pause_delay ~= 0  and self.attack_pause == 1  then
		self.attack_pause_time_index = self.attack_pause_time_index + 1
		if Game.config.attack_pause_time > self.attack_pause_time_index and self.attack_pause_time_index  % Game.config.attack_pause_delay ~= 0 then
			return 1
		end
	end
	
	if self.attack_pause_time_index >= Game.config.attack_pause_time then
		self.attack_pause_time_index = 0
		self.attack_pause = 0
	end
	return 0
end


function player:update(now, delta)
	if self:attack_pause_f() == 1 then
		return
	end
	
	if self.state:is('before_attack') then
		if self.move_distance > 0 then
			local speed = Game.config.player_move_speed
			if self.move_distance < Game.config.player_move_speed then
				speed = self.move_distance
			end			
			self.move_distance = self.move_distance - speed;
			--trace(string.format("dst:%d,%d",self.move_distance,Game.config.player_move_speed))
			if self.facing == Game.battle.player_left_face then
				Game.battle.move_offset = Game.battle.move_offset - speed;
				self.position = self.position - speed
			end
			if self.facing == Game.battle.player_right_face then
				Game.battle.move_offset = Game.battle.move_offset + speed;
				self.position = self.position + speed
			end
			--trace(string.format("dst:%d,player.p:%d",Game.battle.move_offset,self.position))
		else
			if Game.battle.enemy_in_attack_area == 1 then 
				Game.battle:player_attack(self.facing)
			end
			Game.battle.attack_pause = 1
			self.state:attack()			
		end
	elseif self.state:is('be_attack') then
		-- 如果我被攻擊的時候，不能攻擊其他人，等我被攻擊的動作做完了，才能攻擊或者被攻擊
		
		if self.move_distance > 0 then
			self.move_distance = self.move_distance - Game.config.player_move_speed
			if self.facing == Game.battle.player_left_face then
				Game.battle.move_offset = Game.battle.move_offset + Game.config.player_move_speed;
				self.position = self.position + Game.config.player_move_speed
			end
			if self.facing == Game.battle.player_right_face then
				Game.battle.move_offset = Game.battle.move_offset - Game.config.player_move_speed;
				self.position = self.position - Game.config.player_move_speed
			end
		else
			if self.last_be_attack_time >= 0 then
				self.state:reset()	
				self.last_be_attack_time = 0				
			end
			self.last_be_attack_time = self.last_be_attack_time + 1
		end
		
	elseif self.state.is('idle') then
		Game.battle.player_be_attacked = 0
	end
	if self.state:is('idle') and Game.battle.player_change_face ~= self.facing then
		self.facing = Game.battle.player_change_face
	end
	
	self.current_animation:update(delta)
end

function player:draw()
	self.current_animation.image.x = self.position	- Game.battle.move_offset
	self.current_animation.image.scaleX = self.facing
	self.current_animation:draw()
end