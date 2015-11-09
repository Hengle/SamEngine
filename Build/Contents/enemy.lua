require('texture_atlas')
local fsm = require('fsm')

local enemy = class("enemy")

function enemy:enemy(facing)
    self.facing = facing
    self.position = 0
    self.speed = math.random(2, 3)
    self.animations = {
        walk = new("texture_atlas", "enemy_walk"),
        before_attack = new("texture_atlas", "enemy_before_attack"),
        attack = new("texture_atlas", "enemy_attack"),
        after_attack = new("texture_atlas", "enemy_after_attack"),
        die = new("texture_atlas", "enemy_die"),
    }
    self.animations.attack.callback = function() self.state:recovery() end
    self.animations.after_attack.callback = function() self.state:reset() end
    self.animations.walk.loop = true
    self.state = fsm.create({
        initial = "walk",
        events = {
            { name = "walk", from = "before_attack", to = "before_attack" },
            { name = "ready", from = "walk", to = "before_attack" },
            { name = "attack", from = "before_attack", to = "attack" },
            { name = "recovery", from = "attack", to = "after_attack" },
            { name = "reset", from = "after_attack", to = "before_attack" },
            { name = "be_attacked", from = { "before_attack", "after_attack" }, to = "die" },
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
    self.state:be_attacked()
end

function enemy:update(now, delta)
    if self.state.current == "walk" then
        self.position = self.position + self.speed
        if self.position >= 400 then
            self.state:ready()
        end
    elseif self.state.current == "before_attack" then
        if self.position < 550 then
            self.position = self.position + self.speed
        else
            if now - self.last_attack_time > 1000 then
                self.state:attack()
                self.last_attack_time = now
            end
        end
    end
    self.current_animation:update(delta)
end

function enemy:draw()
    if self.facing == 1 then
        self.current_animation.image.x = self.position
    else
        self.current_animation.image.x = Game.ScreenWidth - self.position
    end
    self.current_animation.image.scaleX = self.facing
    self.current_animation:draw()
end