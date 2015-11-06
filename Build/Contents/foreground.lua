local foreground = class("foreground")

function foreground:foreground()
    self.speed = { 0, 0 }
    self.layer = {}
    for i = 1, 2 do
        SamEngine.TextureLoader.LoadFromLocation("local:foreground" .. i .. ".png", function(id)
            if id ~= SamEngine.InvalidResourceID then
                self.layer[i] = SamEngine.Image(SamEngine.Texture(id))
            end
        end)
    end
end

function foreground:update(delta)
    for i, image in ipairs(self.layer) do
        image.x = image.x - self.speed[i]
        if image.x + image.width <= Game.ScreenWidth then
            image.x = 0
        end
    end
end

function foreground:draw()
    for _, image in ipairs(self.layer) do
        image:Draw()
    end
end