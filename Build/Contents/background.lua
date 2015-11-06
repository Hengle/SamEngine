local background = class("background")

function background:background()
    self.speed = { 1, 0, 0, 0 }
    self.layer = {}
    for i = 1, 4 do
        SamEngine.TextureLoader.LoadFromLocation("local:background" .. i .. ".png", function(id)
            if id ~= SamEngine.InvalidResourceID then
                self.layer[i] = SamEngine.Image(SamEngine.Texture(id))
            end
        end)
    end
end

function background:update(delta)
    for i, image in ipairs(self.layer) do
        image.x = image.x - self.speed[i]
        if image.x + image.width <= Game.ScreenWidth then
            image.x = 0
        end
    end
end

function background:draw()
    for _, image in ipairs(self.layer) do
        image:Draw()
    end
end