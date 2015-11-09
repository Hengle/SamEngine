require("player")
require("enemy")
require("background")
require("foreground")

local battle = class("battle")

function battle:battle()
    self.background = new("background")
    self.foreground = new("foreground")
    self.player = new("player")
    self.left_enemy = {new("enemy", 1)}
    self.right_enemy = {new("enemy", -1)}
end

function battle:add_left_enemy()
    table.insert(self.left_enemy, new("enemy", 1))
end

function battle:add_right_enemy()
    table.insert(self.right_enemy, new("enemy", -1))
end

function battle:player_attack(facing)
    if facing == 1 then
        local max_position = 0
        local dst_index = -1
        local dst_enemy = nil
        for index, enemy in ipairs(self.right_enemy) do
            if enemy.position > max_position then
                dst_index = index
                dst_enemy = enemy
                max_position = enemy.position
            end
        end
        if dst_enemy then
            dst_enemy:be_attacked()
--            table.remove(self.right_enemy, dst_index)
        end
    else
        local max_position = 0
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
--            table.remove(self.left_enemy, dst_index)
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
    if #self.left_enemy == 0 then
        self:add_left_enemy()
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