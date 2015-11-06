require("animation")
local texture_atlas = class("texture_atlas", "animation")
local json = require('json')

function texture_atlas:texture_atlas(name)
    self.name = name
    self.config = json.load("./resource/" .. name .. ".json")
    if self.config then
        SamEngine.TextureLoader.LoadFromLocation("local:" .. self.config.meta.image, function(id)
            if id ~= SamEngine.InvalidResourceID then
                self.texture_id = id
                self:parse()
            end
        end)
    end
end

function texture_atlas:parse()
    self.totalframe = #self.config.frames
    for _, config in ipairs(self.config.frames) do
        table.insert(self.textures, SamEngine.Texture(self.texture_id, config.frame.x, config.frame.y, config.frame.w, config.frame.h))
    end
end