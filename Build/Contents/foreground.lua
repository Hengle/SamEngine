local foreground = class("foreground")

function foreground:foreground()
	self.speed = { 0, 0 }
	self.layer = {}
	self.imagePoint = {}
	for i = 1, 2 do
        self.layer[i] = SamEngine.Image(SamEngine.Texture.FromLocation("local:foreground" .. i .. ".png"))
        self.imagePoint[i] = self.layer[i].x
	end
end

function foreground:update(delta)
	for i, image in ipairs(self.layer) do
		self.imagePoint[i] = self.imagePoint[i] - self.speed[i]
		if self.imagePoint[i] + image.width <= Game.ScreenWidth then
			self.imagePoint[i] = 0
		end
	end
end

function foreground:draw()
	for index, image in ipairs(self.layer) do
		if self.imagePoint[index] ~= nil then
			image.x = -(image.width - Game.ScreenWidth )/2   + self.imagePoint[index] + Game.battle.move_offset
		end
		image:Draw()
	end
end