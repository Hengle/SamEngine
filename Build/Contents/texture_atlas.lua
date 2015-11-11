require("animation")
local texture_atlas = class("texture_atlas", "animation")
local json = require('json')

function texture_atlas:texture_atlas(name)
    self.name = name
    self.config = json.load("./Contents/resource/" .. name .. ".json")
    local texture = SamEngine.Texture.FromLocation("local:" .. name .. ".png")
    self.totalframe = #self.config.frames
    for _, config in ipairs(self.config.frames) do
        table.insert(self.textures, SamEngine.Texture.FromTexture(texture, config.frame.x, config.frame.y, config.frame.w, config.frame.h))
    end
end