require("animation")
local texture_atlas = class("texture_atlas", "animation")
local json = require('json')

local cache = {}

function texture_atlas:texture_atlas(name)
    self.name = name
    self.config = json.load("./Contents/resource/" .. name .. ".json")
    if cache["local:" .. name .. ".png"] == nil then
        cache["local:" .. name .. ".png"] = SamEngine.Texture.FromLocation("local:" .. name .. ".png")
    end
    self.totalframe = #self.config.frames
    for _, config in ipairs(self.config.frames) do
        if config.rotated then
            table.insert(self.textures, SamEngine.Texture.FromTexture(cache["local:" .. name .. ".png"], config.frame.x, config.frame.y, config.frame.w, config.frame.h, config.rotated, config.spriteSourceSize.x, config.spriteSourceSize.h - config.frame.w - config.spriteSourceSize.y, config.spriteSourceSize.w, config.spriteSourceSize.h))
        else
            table.insert(self.textures, SamEngine.Texture.FromTexture(cache["local:" .. name .. ".png"], config.frame.x, config.frame.y, config.frame.w, config.frame.h, config.rotated, config.spriteSourceSize.x, config.spriteSourceSize.h - config.frame.h - config.spriteSourceSize.y, config.spriteSourceSize.w, config.spriteSourceSize.h))
        end
    end
end