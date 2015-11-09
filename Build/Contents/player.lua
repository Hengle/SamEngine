require('texture_atlas')
local fsm = require('fsm')

local player = class("player")

function player:player()
    self.facing = 1
    self.animations = {
        idle = new("texture_atlas", "player_idle"),
        run = new("texture_atlas", "player_run"),
        before_attack = new("texture_atlas", "player_before_attack"),
        attack = new("texture_atlas", "player_attack"),
        after_attack = new("texture_atlas", "player_after_attack"),
    }
    self.animations.idle.loop = true
    self.animations.idle.callback = function() end
    self.animations.run.callback = function() end
    self.animations.before_attack.callback = function() self.state:attack() end
    self.animations.attack.callback = function() Game.battle:player_attack(self.facing) self.state:recovery() end
    self.animations.after_attack.callback = function() self.state:reset() end
    self.state = fsm.create({
        initial = "idle",
        events = {
            { name = "run", from = "idle", to = "run" },
            { name = "ready", from = { "idle", "run", "after_attack" }, to = "before_attack" },
            { name = "attack", from = "before_attack", to = "attack" },
            { name = "recovery", from = "attack", to = "after_attack" },
            { name = "reset", from = "after_attack", to = "idle" },
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
    end
end

function player:attack_right()
    if self.state:can('ready') then
        self.facing = 1
        self.state:ready()
    end
end

function player:update(now, delta)
    self.current_animation:update(delta)
end

function player:draw()
    self.current_animation.image.x = Game.ScreenWidth / 2
    self.current_animation.image.scaleX = self.facing
    self.current_animation:draw()
end