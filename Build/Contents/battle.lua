require("player")
require("enemy")
require("background")
require("foreground")

local battle = class("battle")

function battle:battle()
    self.background = new("background")
    self.foreground = new("foreground")
    self.player = new("player")
    self.enemy = { new("enemy", 1), new("enemy", -1) }
end

function battle:draw()
    self.background:draw()
    self.player:draw()
    for _, enemy in ipairs(self.enemy) do
        enemy:draw()
    end
    self.foreground:draw()
end

function battle:update(now, delta)
    self.background:update(delta)
    self.player:update(now, delta)
    for _, enemy in ipairs(self.enemy) do
        enemy:update(now, delta)
    end
    self.foreground:update(delta)
end