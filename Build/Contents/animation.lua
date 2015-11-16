local animation = class("animation")

function animation:animation()
    self.time_per_frame = 1 / 60
    self.totalframe = 0
    self.image = SamEngine.Image()
    self.image.y = 180
    self.textures = {}
    self.paused = false
    self.current = 1
    self.time = 0
end

function animation:update(delta)
    if self.paused == false then
        self.time = self.time + delta
        if self.time >= self.time_per_frame then
            self:next_frame()
        end
    end
end

function animation:next_frame()
    if self.current == self.totalframe then
        if self.loop then
            self.current = 1
        end
        if self.callback then
            self.callback()
        end
    else
        self.current = self.current + 1
    end
    if self.textures[self.current] then
        self.image.texture = self.textures[self.current]
        self.image.originX = -self.image.texture.frameWidth / 2
    end
end

function animation:goto_frame(frame)
    if frame > 0 and frame <= self.totalframe then
        self.current = frame
        if self.textures[self.current] then
            self.image.texture = self.textures[self.current]
            self.image.originX = -self.image.texture.frameWidth / 2
        end
    end
end

function animation:play()
    self.current = 1
    self:resume()
end

function animation:resume()
    self.paused = false
end

function animation:pause()
    self.paused = true
end

function animation:draw()
    self.image:Draw()
end