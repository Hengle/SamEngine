local background = class("background")

function background:background()
	self.speed = { 0, 0, 0, 0 }
	self.layer = {}
	self.imagePoint = {}
	for i = 1, 4 do
        self.layer[i] = SamEngine.Image(SamEngine.Texture.FromLocation("local:background" .. i .. ".png"))
        self.imagePoint[i] = self.layer[i].x
	end
end

function background:update(delta)
	for i, image in ipairs(self.layer) do
		self.imagePoint[i] = self.imagePoint[i] - self.speed[i]
		if self.imagePoint[i] + image.width <= Game.ScreenWidth then
			self.imagePoint[i] = 0
		end
	end
end

function background:draw()
	for index, image in ipairs(self.layer) do
		if self.imagePoint[index] ~= nil then
			image.x = -(image.width - Game.ScreenWidth )/2   + self.imagePoint[index] - Game.battle.move_offset
		end
		image:Draw()
	end
end