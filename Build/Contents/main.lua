package.path = "F:/SamEngine/Build/Contents/?.lua;F:/SamEngine/Build/Contents/?/?.lua;F:/SamEngine/Build/Contents/?/init.lua;F:/SamEngine/Build/Contents/?.lua;F:/SamEngine/Build/Contents/lib/?.lua;F:/SamEngine/Build/Contents/lib/?/?.lua;F:/SamEngine/Build/Contents/lib/?/init.lua;F:/SamEngine/Build/Contents/lib/?.lua"
package.cpath = ""

require('mobdebug').start()

Game = {}

function trace(message, ...)
    if message == nil then return end
    if type(message) == "string" then
        SamEngine.Log.Debug(message .. "\n")
    elseif type(message) == "userdata" then
        SamEngine.Log.Debug(getmetatable(message).___type .. "\n")
    else
        SamEngine.Log.Debug(type(message) .. "\n")
    end
    trace(...)
end

function Game.Initialize()
    SamEngine.IO:SetLocationPlaceholder("git", "http://leafnsand.com/")
    SamEngine.IO:SetLocationPlaceholder("local", "storage://F:/SamEngine/Build/Contents/resource/")
    SamEngine.Window:SetMouseInputCallback(MouseCallback)
    SamEngine.Window:SetKeyboardInputCallback(KeyboardCallback)
    SamEngine.Window:SetTitle("One Finger Death Paunch")

    Game.Character = {}
    
    SamEngine.TextureLoader.LoadFromLocation("local:tex_a.png", function(id)
        if id == SamEngine.InvalidResourceID then
            trace("invalid resource")
        end
        Game.Character.Texture_A = { 
            SamEngine.Texture(id, 0, 0, 0x48, 0x94),
            SamEngine.Texture(id, 0x48, 0, 0x48, 140),
            SamEngine.Texture(id, 0x90, 0, 0x90, 0x84),
            SamEngine.Texture(id, 0x120, 0, 100, 0x88),
            SamEngine.Texture(id, 0x184, 0, 0x58, 0x80),
            SamEngine.Texture(id, 0x1dc, 0, 0x70, 0x98),
            SamEngine.Texture(id, 0x24c, 0, 0x5c, 0x84),
            SamEngine.Texture(id, 680, 0, 0x6c, 0x84),
            SamEngine.Texture(id, 0x314, 0, 0x58, 0x90),
            SamEngine.Texture(id, 0x36c, 0, 0x74, 0x88),
            SamEngine.Texture(id, 0x3e0, 0, 0x74, 140),
            SamEngine.Texture(id, 0x454, 0, 0x70, 0x88),
            SamEngine.Texture(id, 0, 0x98, 0x7c, 0x94),
            SamEngine.Texture(id, 0x7c, 0x98, 0x7c, 0x90),
            SamEngine.Texture(id, 0xf8, 0x98, 0x7c, 0x90),
            SamEngine.Texture(id, 0x174, 0x98, 0x7c, 0x90), 
            SamEngine.Texture(id, 0x1f0, 0x98, 0x7c, 0x88),
            SamEngine.Texture(id, 620, 0x98, 0x7c, 0x98),
            SamEngine.Texture(id, 0x2e8, 0x98, 0x7c, 0x84),
            SamEngine.Texture(id, 0x364, 0x98, 0x84, 0x84),
            SamEngine.Texture(id, 0x3e8, 0x98, 0x7c, 0x88),
            SamEngine.Texture(id, 0x464, 0x98, 0x7c, 0x88),
            SamEngine.Texture(id, 0x4e0, 0x98, 0x80, 0x94),
            SamEngine.Texture(id, 0x560, 0x98, 0x80, 0x84),
            SamEngine.Texture(id, 0, 0x130, 0x84, 0x7c),
            SamEngine.Texture(id, 0x84, 0x130, 0x88, 0x84),
            SamEngine.Texture(id, 0x10c, 0x130, 0x7c, 140),
            SamEngine.Texture(id, 0x188, 0x130, 0x68, 140),
            SamEngine.Texture(id, 0x1f0, 0x130, 0xf8, 120),
            SamEngine.Texture(id, 0x2e8, 0x130, 180, 0x7c),
            SamEngine.Texture(id, 0x39c, 0x130, 160, 0x80),
            SamEngine.Texture(id, 0x43c, 0x130, 0x94, 0x94), 
            SamEngine.Texture(id, 0x4d0, 0x130, 0x84, 140),
            SamEngine.Texture(id, 0x554, 0x130, 0x98, 0x90),
            SamEngine.Texture(id, 0x5ec, 0x130, 0xbc, 0x74),
            SamEngine.Texture(id, 0x6a8, 0x130, 140, 0x74),
            SamEngine.Texture(id, 0, 0x1c4, 180, 140),
            SamEngine.Texture(id, 180, 0x1c4, 0x5c, 160),
            SamEngine.Texture(id, 0x110, 0x1c4, 0x88, 0x7c),
            SamEngine.Texture(id, 0x198, 0x1c4, 80, 0x80),
            SamEngine.Texture(id, 0x1e8, 0x1c4, 0x68, 0x84),
            SamEngine.Texture(id, 0x250, 0x1c4, 140, 0x90),
            SamEngine.Texture(id, 0x2dc, 0x1c4, 0x40, 140),
            SamEngine.Texture(id, 0x31c, 0x1c4, 0x7c, 0xa4),
            SamEngine.Texture(id, 920, 0x1c4, 0x40, 0xa4),
            SamEngine.Texture(id, 0x3d8, 0x1c4, 0xa8, 0x80),
            SamEngine.Texture(id, 0x480, 0x1c4, 0x70, 160),
            SamEngine.Texture(id, 0x4f0, 0x1c4, 160, 0x70), 
            SamEngine.Texture(id, 0, 0x268, 0x90, 0x90),
            SamEngine.Texture(id, 0x90, 0x268, 160, 0x84),
            SamEngine.Texture(id, 0x130, 0x268, 0xa8, 160),
            SamEngine.Texture(id, 0x1d8, 0x268, 0x94, 0x90),
            SamEngine.Texture(id, 620, 0x268, 0x94, 0x80),
            SamEngine.Texture(id, 0x300, 0x268, 0x98, 0x80),
            SamEngine.Texture(id, 920, 0x268, 0x9c, 0x9c),
            SamEngine.Texture(id, 0x434, 0x268, 0xb8, 140),
            SamEngine.Texture(id, 0x4ec, 0x268, 0xac, 0x94),
            SamEngine.Texture(id, 0x598, 0x268, 0x94, 160),
            SamEngine.Texture(id, 0x62c, 0x268, 0xc4, 0x94),
            SamEngine.Texture(id, 0x6f0, 0x268, 0xa4, 0x94),
            SamEngine.Texture(id, 0, 0x308, 80, 0x9c),
            SamEngine.Texture(id, 80, 0x308, 0x40, 140),
            SamEngine.Texture(id, 0x90, 0x308, 0x74, 0x80),
            SamEngine.Texture(id, 260, 0x308, 0x5c, 0x94), 
            SamEngine.Texture(id, 0x160, 0x308, 140, 0x80),
            SamEngine.Texture(id, 0x1ec, 0x308, 0x4c, 0x94),
            SamEngine.Texture(id, 0x238, 0x308, 0x74, 0x9c),
            SamEngine.Texture(id, 0x2ac, 0x308, 0x68, 0x84),
            SamEngine.Texture(id, 0x314, 0x308, 0x68, 140),
            SamEngine.Texture(id, 0x37c, 0x308, 80, 0x88),
            SamEngine.Texture(id, 0x3cc, 0x308, 0x54, 0x94),
            SamEngine.Texture(id, 0x420, 0x308, 0x54, 0xac),
            SamEngine.Texture(id, 0, 0x3b4, 0x60, 0x90),
            SamEngine.Texture(id, 0x60, 0x3b4, 0x88, 0x98),
            SamEngine.Texture(id, 0xe8, 0x3b4, 0x5c, 0x9c),
            SamEngine.Texture(id, 0x144, 0x3b4, 0x4c, 160),
            SamEngine.Texture(id, 400, 0x3b4, 0x74, 0x7c),
            SamEngine.Texture(id, 0x204, 0x3b4, 0x58, 0xc4),
            SamEngine.Texture(id, 0x25c, 0x3b4, 0x98, 0x88),
            SamEngine.Texture(id, 0x2f4, 0x3b4, 0x68, 0x90), 
            SamEngine.Texture(id, 860, 0x3b4, 100, 0x98),
            SamEngine.Texture(id, 960, 0x3b4, 0x7c, 0x94),
            SamEngine.Texture(id, 0x43c, 0x3b4, 0x80, 0x98),
            SamEngine.Texture(id, 0x4bc, 0x3b4, 0x88, 160),
            SamEngine.Texture(id, 0, 0x478, 0x74, 0x94),
            SamEngine.Texture(id, 0x74, 0x478, 0x88, 0x7c),
            SamEngine.Texture(id, 0xfc, 0x478, 0x6c, 0x80),
            SamEngine.Texture(id, 360, 0x478, 0x4c, 0x84),
            SamEngine.Texture(id, 0x1b4, 0x478, 0x7c, 140),
            SamEngine.Texture(id, 560, 0x478, 120, 140),
            SamEngine.Texture(id, 680, 0x478, 0x7c, 0x98),
            SamEngine.Texture(id, 0x324, 0x478, 0x84, 120),
            SamEngine.Texture(id, 0x3a8, 0x478, 0x7c, 140),
            SamEngine.Texture(id, 0x424, 0x478, 0x60, 160),
            SamEngine.Texture(id, 0x484, 0x478, 0xa4, 0x88),
            SamEngine.Texture(id, 0x528, 0x478, 80, 0xb8), 
            SamEngine.Texture(id, 0, 0x530, 220, 0x94),
            SamEngine.Texture(id, 220, 0x530, 0xcc, 0xac),
            SamEngine.Texture(id, 0x1a8, 0x530, 0x44, 0x90),
            SamEngine.Texture(id, 0x1ec, 0x530, 260, 140),
            SamEngine.Texture(id, 0x2f0, 0x530, 0x124, 0x88),
            SamEngine.Texture(id, 0x414, 0x530, 0xcc, 0xac),
            SamEngine.Texture(id, 0x4e0, 0x530, 0x44, 0x90),
            SamEngine.Texture(id, 0x524, 0x530, 260, 140),
            SamEngine.Texture(id, 0x628, 0x530, 180, 0x74),
            SamEngine.Texture(id, 0x6dc, 0x530, 0xcc, 0xac),
            SamEngine.Texture(id, 0x578, 0x478, 0xc0, 0x90),
            SamEngine.Texture(id, 0x638, 0x478, 0xd4, 0x80),
            SamEngine.Texture(id, 0, 0x5dc, 0xa4, 0xc0),
            SamEngine.Texture(id, 0xa4, 0x5dc, 0x94, 160),
            SamEngine.Texture(id, 0x138, 0x5dc, 140, 0xac),
            SamEngine.Texture(id, 0x1c4, 0x5dc, 0x80, 0xa4), 
            SamEngine.Texture(id, 580, 0x5dc, 0xd4, 0x74),
            SamEngine.Texture(id, 0x318, 0x5dc, 0x68, 0x90),
            SamEngine.Texture(id, 0x380, 0x5dc, 260, 0x9c),
            SamEngine.Texture(id, 0x484, 0x5dc, 0xac, 0xa8),
            SamEngine.Texture(id, 0x530, 0x5dc, 0xa4, 0x90),
            SamEngine.Texture(id, 0x5d4, 0x5dc, 0xbc, 0xb8),
            SamEngine.Texture(id, 0x690, 0x5dc, 0xe4, 0x9c),
            SamEngine.Texture(id, 0x544, 0x3b4, 0xe4, 0x84)
        }
    end)

    SamEngine.TextureLoader.LoadFromLocation("local:tex_b.png", function(id)
        if id == SamEngine.InvalidResourceID then
            trace("invalid resource")
        end
        Game.Character.Texture_B = {
            SamEngine.Texture(id, 0, 0, 0x90, 0x90),
            SamEngine.Texture(id, 0x90, 0, 0xa4, 0x80),
            SamEngine.Texture(id, 0x134, 0, 0xb0, 120),
            SamEngine.Texture(id, 0x1e4, 0, 0xac, 120),
            SamEngine.Texture(id, 0x290, 0, 0x98, 0x80),
            SamEngine.Texture(id, 0x328, 0, 160, 0xac),
            SamEngine.Texture(id, 0x3c8, 0, 0x9c, 0x70),
            SamEngine.Texture(id, 0x464, 0, 0x88, 120),
            SamEngine.Texture(id, 0x4ec, 0, 0x84, 0x88),
            SamEngine.Texture(id, 0x570, 0, 140, 0x84),
            SamEngine.Texture(id, 0x5fc, 0, 0xb0, 0x80),
            SamEngine.Texture(id, 0x6ac, 0, 0xb0, 0x80),
            SamEngine.Texture(id, 0, 0xac, 0xbc, 0x94),
            SamEngine.Texture(id, 0xbc, 0xac, 0xb8, 0x94),
            SamEngine.Texture(id, 0x174, 0xac, 0xb8, 0x94),
            SamEngine.Texture(id, 0x22c, 0xac, 180, 0x94), 
            SamEngine.Texture(id, 0x2e0, 0xac, 0xb8, 0x88),
            SamEngine.Texture(id, 920, 0xac, 0xb8, 0x88),
            SamEngine.Texture(id, 0x450, 0xac, 0x9c, 0x80),
            SamEngine.Texture(id, 0x4ec, 0xac, 0x9c, 0x80),
            SamEngine.Texture(id, 0x588, 0xac, 0x94, 140),
            SamEngine.Texture(id, 0x61c, 0xac, 0x90, 140),
            SamEngine.Texture(id, 0x6ac, 0xac, 0x9c, 0x80),
            SamEngine.Texture(id, 0x748, 0xac, 0x94, 0x80),
            SamEngine.Texture(id, 0, 320, 0xa4, 120),
            SamEngine.Texture(id, 0xa4, 320, 220, 0x80),
            SamEngine.Texture(id, 0x180, 320, 180, 0x88),
            SamEngine.Texture(id, 0x234, 320, 0xec, 0x7c),
            SamEngine.Texture(id, 800, 320, 0x98, 0x90),
            SamEngine.Texture(id, 0x3b8, 320, 0xd8, 0x60),
            SamEngine.Texture(id, 0x490, 320, 180, 120),
            SamEngine.Texture(id, 0x544, 320, 220, 0x74), 
            SamEngine.Texture(id, 0x620, 320, 0xc0, 0xa4),
            SamEngine.Texture(id, 0x6e0, 320, 0xa4, 0x94),
            SamEngine.Texture(id, 0x784, 320, 0xec, 60),
            SamEngine.Texture(id, 0x870, 320, 0xd4, 0x68),
            SamEngine.Texture(id, 0, 0x1e4, 0xd4, 0x80),
            SamEngine.Texture(id, 0xd4, 0x1e4, 0x90, 0x90),
            SamEngine.Texture(id, 0x164, 0x1e4, 160, 100),
            SamEngine.Texture(id, 0x204, 0x1e4, 180, 0x5c),
            SamEngine.Texture(id, 0x2b8, 0x1e4, 0xcc, 0x80),
            SamEngine.Texture(id, 900, 0x1e4, 0xbc, 0x88),
            SamEngine.Texture(id, 0x440, 0x1e4, 140, 140),
            SamEngine.Texture(id, 0x4cc, 0x1e4, 0xc4, 0xc4),
            SamEngine.Texture(id, 0x590, 0x1e4, 0x98, 0x84),
            SamEngine.Texture(id, 0x628, 0x1e4, 260, 0x54),
            SamEngine.Texture(id, 0x72c, 0x1e4, 0x90, 0xb0),
            SamEngine.Texture(id, 0x7bc, 0x1e4, 0x94, 0xa4), 
            SamEngine.Texture(id, 0, 680, 0xb0, 0x9c),
            SamEngine.Texture(id, 0xb0, 680, 0xec, 0x84),
            SamEngine.Texture(id, 0x19c, 680, 0xd4, 0x90),
            SamEngine.Texture(id, 0x270, 680, 0xf8, 0x94),
            SamEngine.Texture(id, 0x368, 680, 0x100, 0x70),
            SamEngine.Texture(id, 0x468, 680, 0xd0, 0x68),
            SamEngine.Texture(id, 0x538, 680, 0xcc, 0x80),
            SamEngine.Texture(id, 0x604, 680, 0xc4, 0x90),
            SamEngine.Texture(id, 0x6c8, 680, 0xe8, 0x80),
            SamEngine.Texture(id, 0x7b0, 680, 0xe0, 0x90),
            SamEngine.Texture(id, 0x890, 680, 0xd0, 160),
            SamEngine.Texture(id, 0x960, 680, 240, 140),
            SamEngine.Texture(id, 0, 840, 0x68, 0x90),
            SamEngine.Texture(id, 140, 840, 0x80, 140),
            SamEngine.Texture(id, 0xe8, 840, 0x9c, 0x60),
            SamEngine.Texture(id, 0x184, 840, 120, 0x94), 
            SamEngine.Texture(id, 0x1fc, 840, 0xb8, 0x5c),
            SamEngine.Texture(id, 0x2b4, 840, 0x98, 0x90),
            SamEngine.Texture(id, 0x34c, 840, 0xd4, 0x9c),
            SamEngine.Texture(id, 0x420, 840, 0x60, 0x6c),
            SamEngine.Texture(id, 0x480, 840, 0x70, 0x90),
            SamEngine.Texture(id, 0x4f0, 840, 0x80, 0x70),
            SamEngine.Texture(id, 0x570, 840, 0x90, 0x94),
            SamEngine.Texture(id, 0x600, 840, 0x60, 0xb0),
            SamEngine.Texture(id, 0, 0x3f8, 0x9c, 0x90),
            SamEngine.Texture(id, 0x9c, 0x3f8, 0xc4, 0x7c),
            SamEngine.Texture(id, 0x160, 0x3f8, 0x94, 100),
            SamEngine.Texture(id, 500, 0x3f8, 0x90, 0x94),
            SamEngine.Texture(id, 0x284, 0x3f8, 0xac, 0x68),
            SamEngine.Texture(id, 0x330, 0x3f8, 0x70, 0xa4),
            SamEngine.Texture(id, 0x3a0, 0x3f8, 0xcc, 0x54),
            SamEngine.Texture(id, 0x46c, 0x3f8, 0xa8, 0x84), 
            SamEngine.Texture(id, 0x514, 0x3f8, 0xcc, 0x88),
            SamEngine.Texture(id, 0x5e0, 0x3f8, 180, 0x90),
            SamEngine.Texture(id, 0x694, 0x3f8, 180, 0x84),
            SamEngine.Texture(id, 0x748, 0x3f8, 0xf4, 0x9c),
            SamEngine.Texture(id, 0, 0x49c, 200, 0x7c),
            SamEngine.Texture(id, 200, 0x49c, 0xc0, 0x6c),
            SamEngine.Texture(id, 0x188, 0x49c, 0xd4, 0x74),
            SamEngine.Texture(id, 0x25c, 0x49c, 0x80, 0x88),
            SamEngine.Texture(id, 0x2dc, 0x49c, 0x80, 0x88),
            SamEngine.Texture(id, 860, 0x49c, 0x6c, 0x9c),
            SamEngine.Texture(id, 0x3c8, 0x49c, 0xb8, 0x90),
            SamEngine.Texture(id, 0x480, 0x49c, 0xd4, 0x68),
            SamEngine.Texture(id, 0x554, 0x49c, 140, 140),
            SamEngine.Texture(id, 0x5e0, 0x49c, 0xc4, 0x98),
            SamEngine.Texture(id, 0x6a4, 0x49c, 0x108, 0xac),
            SamEngine.Texture(id, 0x7ac, 0x49c, 100, 140), 
            SamEngine.Texture(id, 0, 0x548, 0x14c, 0xac),
            SamEngine.Texture(id, 0x14c, 0x548, 0x11c, 140),
            SamEngine.Texture(id, 0x268, 0x548, 320, 0x90),
            SamEngine.Texture(id, 0x3a8, 0x548, 0x120, 0xe8),
            SamEngine.Texture(id, 0x4c8, 0x548, 320, 0x88),
            SamEngine.Texture(id, 0x608, 0x548, 0x120, 0x70),
            SamEngine.Texture(id, 0x728, 0x548, 0x15c, 140),
            SamEngine.Texture(id, 0x884, 0x548, 0x124, 140),
            SamEngine.Texture(id, 0, 0x630, 0x170, 0xac),
            SamEngine.Texture(id, 0x170, 0x630, 0x128, 0xa8),
            SamEngine.Texture(id, 0x298, 0x630, 300, 0xe4),
            SamEngine.Texture(id, 0x3c4, 0x630, 360, 120),
            SamEngine.Texture(id, 0x52c, 0x630, 340, 0xc0),
            SamEngine.Texture(id, 0x680, 0x630, 0x124, 120),
            SamEngine.Texture(id, 0x7a4, 0x630, 260, 0xb0),
            SamEngine.Texture(id, 0x8a8, 0x630, 260, 0x98), 
            SamEngine.Texture(id, 0, 0x714, 0x150, 140),
            SamEngine.Texture(id, 0x150, 0x714, 0xe4, 0x80),
            SamEngine.Texture(id, 0x234, 0x714, 0x120, 0x7c),
            SamEngine.Texture(id, 0x354, 0x714, 260, 0xb0),
            SamEngine.Texture(id, 0x458, 0x714, 0x150, 140),
            SamEngine.Texture(id, 0x5a8, 0x714, 360, 0xbc),
            SamEngine.Texture(id, 0x710, 0x714, 0xf4, 0xac),
            SamEngine.Texture(id, 0x804, 0x714, 0x174, 0x98)
        }
    end)

    SamEngine.TextureLoader.LoadFromLocation("local:tex_c.png", function(id)
        if id == SamEngine.InvalidResourceID then
            trace("invalid resource")
        end
        Game.Character.Texture_C = {
            SamEngine.Texture(id, 0, 0, 0x74, 0x94),
            SamEngine.Texture(id, 0x74, 0, 0x7c, 140),
            SamEngine.Texture(id, 240, 0, 0x80, 0x84),
            SamEngine.Texture(id, 0x170, 0, 0x44, 140),
            SamEngine.Texture(id, 0x1b4, 0, 0x4c, 0x90),
            SamEngine.Texture(id, 0x200, 0, 0x5c, 160),
            SamEngine.Texture(id, 0x25c, 0, 0x7c, 0x84),
            SamEngine.Texture(id, 0x2d8, 0, 0x6c, 0x84),
            SamEngine.Texture(id, 0x344, 0, 0x58, 0x90),
            SamEngine.Texture(id, 0x39c, 0, 0x74, 0x88),
            SamEngine.Texture(id, 0x410, 0, 0x7c, 140),
            SamEngine.Texture(id, 0x48c, 0, 0x7c, 140),
            SamEngine.Texture(id, 0, 160, 0x90, 140),
            SamEngine.Texture(id, 0x90, 160, 0x7c, 140),
            SamEngine.Texture(id, 0x10c, 160, 0x90, 140),
            SamEngine.Texture(id, 0x19c, 160, 0x7c, 140), 
            SamEngine.Texture(id, 0x218, 160, 0x7c, 0x88),
            SamEngine.Texture(id, 660, 160, 0x84, 0x88),
            SamEngine.Texture(id, 0x318, 160, 0x7c, 0x84),
            SamEngine.Texture(id, 0x394, 160, 0x80, 0x84),
            SamEngine.Texture(id, 0x414, 160, 0x7c, 0x88),
            SamEngine.Texture(id, 0x490, 160, 0x7c, 0x88),
            SamEngine.Texture(id, 0x50c, 160, 0x7c, 0x84),
            SamEngine.Texture(id, 0x588, 160, 0x7c, 0x84),
            SamEngine.Texture(id, 0, 300, 120, 0x7c),
            SamEngine.Texture(id, 120, 300, 0x98, 0x84),
            SamEngine.Texture(id, 0x110, 300, 0x7c, 140),
            SamEngine.Texture(id, 0x18c, 300, 0x68, 140),
            SamEngine.Texture(id, 500, 300, 0xa8, 0x74),
            SamEngine.Texture(id, 0x29c, 300, 180, 0x7c),
            SamEngine.Texture(id, 0x350, 300, 0xd8, 0x7c),
            SamEngine.Texture(id, 0x428, 300, 0xac, 0x84), 
            SamEngine.Texture(id, 0x4d4, 300, 140, 0x98),
            SamEngine.Texture(id, 0x560, 300, 0x68, 0x90),
            SamEngine.Texture(id, 0x5c8, 300, 0x88, 0x74),
            SamEngine.Texture(id, 0x650, 300, 0xac, 0x74),
            SamEngine.Texture(id, 0, 0x1c4, 0xb8, 140),
            SamEngine.Texture(id, 0xb8, 0x1c4, 0x5c, 0x90),
            SamEngine.Texture(id, 0x114, 0x1c4, 0x74, 0x80),
            SamEngine.Texture(id, 0x188, 0x1c4, 0x68, 0x80),
            SamEngine.Texture(id, 0x1f0, 0x1c4, 0x68, 0x84),
            SamEngine.Texture(id, 600, 0x1c4, 0xa8, 0x90),
            SamEngine.Texture(id, 0x300, 0x1c4, 0x54, 140),
            SamEngine.Texture(id, 0x354, 0x1c4, 0x6c, 0xa4),
            SamEngine.Texture(id, 960, 0x1c4, 0x40, 0x98),
            SamEngine.Texture(id, 0x400, 0x1c4, 0xa8, 0x80),
            SamEngine.Texture(id, 0x4a8, 0x1c4, 0x88, 160),
            SamEngine.Texture(id, 0x530, 0x1c4, 0xb8, 0x68), 
            SamEngine.Texture(id, 0, 0x268, 180, 0x80),
            SamEngine.Texture(id, 180, 0x268, 0xa4, 0x80),
            SamEngine.Texture(id, 0x158, 0x268, 180, 0x84),
            SamEngine.Texture(id, 0x20c, 0x268, 0xa8, 140),
            SamEngine.Texture(id, 0x2b4, 0x268, 0x94, 0x88),
            SamEngine.Texture(id, 840, 0x268, 160, 0x74),
            SamEngine.Texture(id, 0x3e8, 0x268, 160, 140),
            SamEngine.Texture(id, 0x488, 0x268, 180, 120),
            SamEngine.Texture(id, 0x53c, 0x268, 0x98, 140),
            SamEngine.Texture(id, 0x5d4, 0x268, 0x94, 140),
            SamEngine.Texture(id, 0x668, 0x268, 0xb0, 0x94),
            SamEngine.Texture(id, 0x718, 0x268, 0xbc, 0x88),
            SamEngine.Texture(id, 0, 0x2fc, 80, 0x90),
            SamEngine.Texture(id, 80, 0x2fc, 0x70, 0x90),
            SamEngine.Texture(id, 0xc0, 0x2fc, 0x60, 0x7c),
            SamEngine.Texture(id, 0x120, 0x2fc, 0x70, 0x94), 
            SamEngine.Texture(id, 400, 0x2fc, 0x9c, 120),
            SamEngine.Texture(id, 0x22c, 0x2fc, 80, 0x90),
            SamEngine.Texture(id, 0x27c, 0x2fc, 0x68, 0x9c),
            SamEngine.Texture(id, 740, 0x2fc, 0x4c, 0x7c),
            SamEngine.Texture(id, 0x330, 0x2fc, 0x6c, 140),
            SamEngine.Texture(id, 0x39c, 0x2fc, 0x70, 0x88),
            SamEngine.Texture(id, 0x40c, 0x2fc, 100, 0x9c),
            SamEngine.Texture(id, 0x470, 0x2fc, 0x48, 0xa4),
            SamEngine.Texture(id, 0, 0x3a0, 0x4c, 160),
            SamEngine.Texture(id, 0x4c, 0x3a0, 0x88, 0x84),
            SamEngine.Texture(id, 0xd4, 0x3a0, 0x68, 140),
            SamEngine.Texture(id, 0x13c, 0x3a0, 80, 0x98),
            SamEngine.Texture(id, 0x18c, 0x3a0, 0x80, 140),
            SamEngine.Texture(id, 0x20c, 0x3a0, 0x54, 0x98),
            SamEngine.Texture(id, 0x260, 0x3a0, 0x84, 0x70),
            SamEngine.Texture(id, 740, 0x3a0, 0x54, 0x88), 
            SamEngine.Texture(id, 0x338, 0x3a0, 0x7c, 0x9c),
            SamEngine.Texture(id, 0x3b4, 0x3a0, 0x5c, 0x9c),
            SamEngine.Texture(id, 0x410, 0x3a0, 120, 0x88),
            SamEngine.Texture(id, 0x488, 0x3a0, 0x5c, 0x9c),
            SamEngine.Texture(id, 0, 0x440, 0x7c, 0x80),
            SamEngine.Texture(id, 0x7c, 0x440, 0x80, 0x7c),
            SamEngine.Texture(id, 0xfc, 0x440, 0x84, 0x84),
            SamEngine.Texture(id, 0x180, 0x440, 0x7c, 140),
            SamEngine.Texture(id, 0x1fc, 0x440, 80, 0x84),
            SamEngine.Texture(id, 0x24c, 0x440, 0x84, 0x88),
            SamEngine.Texture(id, 720, 0x440, 0x74, 140),
            SamEngine.Texture(id, 0x344, 0x440, 140, 0x70),
            SamEngine.Texture(id, 0x3d0, 0x440, 80, 0x88),
            SamEngine.Texture(id, 0x420, 0x440, 0x88, 140),
            SamEngine.Texture(id, 0x4a8, 0x440, 140, 0x94),
            SamEngine.Texture(id, 0x534, 0x440, 0x48, 0x84), 
            SamEngine.Texture(id, 0, 0x4d4, 0x11c, 140),
            SamEngine.Texture(id, 0x11c, 0x4d4, 0xbc, 140),
            SamEngine.Texture(id, 0x1d8, 0x4d4, 0x10c, 140),
            SamEngine.Texture(id, 740, 0x4d4, 0xb0, 0xd4),
            SamEngine.Texture(id, 0x394, 0x4d4, 0x100, 160),
            SamEngine.Texture(id, 0x494, 0x4d4, 0xd4, 0x84),
            SamEngine.Texture(id, 0x568, 0x4d4, 0x70, 200),
            SamEngine.Texture(id, 0x5d8, 0x4d4, 0x40, 0xd0),
            SamEngine.Texture(id, 0x618, 0x4d4, 300, 0x84),
            SamEngine.Texture(id, 0, 0x5a8, 160, 140),
            SamEngine.Texture(id, 160, 0x5a8, 0xd0, 0xc4),
            SamEngine.Texture(id, 0x170, 0x5a8, 0x124, 0x98),
            SamEngine.Texture(id, 660, 0x5a8, 0x120, 0x90),
            SamEngine.Texture(id, 0x3b4, 0x5a8, 0x94, 0xa8),
            SamEngine.Texture(id, 0x448, 0x5a8, 0xe0, 0x94),
            SamEngine.Texture(id, 0x528, 0x5a8, 0xec, 0x80), 
            SamEngine.Texture(id, 0x614, 0x5a8, 0xd8, 0x74),
            SamEngine.Texture(id, 0x6ec, 0x5a8, 0xb8, 140),
            SamEngine.Texture(id, 0, 0x66c, 0x108, 0xa8),
            SamEngine.Texture(id, 0x108, 0x66c, 0x108, 140),
            SamEngine.Texture(id, 0x210, 0x66c, 280, 0xcc),
            SamEngine.Texture(id, 0x328, 0x66c, 0x134, 0x7c),
            SamEngine.Texture(id, 0x45c, 0x66c, 0xcc, 0x9c),
            SamEngine.Texture(id, 0x528, 0x66c, 0x160, 0x80)
        }
    end)
    
    SamEngine.TextureLoader.LoadFromLocation("local:tex_idle.png", function(id)
        if id == SamEngine.InvalidResourceID then
            trace("invalid resource")
        end
        Game.Character.Texture_Idle = {
            SamEngine.Texture(id, 0, 0, 0x68, 0x84),
            SamEngine.Texture(id, 0x68, 0, 0x6c, 0x84),
            SamEngine.Texture(id, 0xd4, 0, 0x68, 0x84),
            SamEngine.Texture(id, 0, 0x84, 0x7c, 0x80),
            SamEngine.Texture(id, 0x7c, 0x84, 0x7c, 0x80),
            SamEngine.Texture(id, 0xf8, 0x84, 0x7c, 0x80),
            SamEngine.Texture(id, 0, 260, 0x60, 0x84),
            SamEngine.Texture(id, 0x60, 260, 100, 0x84),
            SamEngine.Texture(id, 0xc4, 260, 0x70, 120),
            SamEngine.Texture(id, 0, 0x188, 120, 160),
            SamEngine.Texture(id, 120, 0x188, 0x84, 0x98),
            SamEngine.Texture(id, 0xfc, 0x188, 0x90, 0x94),
            SamEngine.Texture(id, 0, 0x228, 0x90, 0x84),
            SamEngine.Texture(id, 0x90, 0x228, 0x90, 0x94),
            SamEngine.Texture(id, 0x120, 0x228, 0x90, 0x90)
        }
        Game.Character.Texture_Idle_Config = {
            {
                { frame = 0, duration = 5 },
                { frame = 1, duration = 5 },
                { frame = 2, duration = 5 },
                { frame = 0, duration = 5 },
                { frame = 1, duration = 30 },
                { frame = 2, duration = 5 },
                { frame = 3, duration = 120 }
            },
            {
                { frame = 0, duration = 4 },
                { frame = 1, duration = 6 },
                { frame = 2, duration = 8 },
                { frame = 1, duration = 10 },
                { frame = 0, duration = 12 },
                { frame = 1, duration = 14 },
                { frame = 2, duration = 16 },
                { frame = 1, duration = 18 },
                { frame = 3, duration = 120 }
            },
            {
                { frame = 0, duration = 6 }, 
                { frame = 1, duration = 6 }, 
                { frame = 2, duration = 60 }, 
                { frame = 1, duration = 10 }, 
                { frame = 0, duration = 10 }, 
                { frame = 3, duration = 120 }
            },
            {
                { frame = 0, duration = 10 }, 
                { frame = 1, duration = 10 }, 
                { frame = 2, duration = 10 }, 
                { frame = 3, duration = 120 }
            },
            {
                { frame = 0, duration = 5 }, 
                { frame = 1, duration = 5 }, 
                { frame = 2, duration = 5 }, 
                { frame = 3, duration = 120 }
            }
        }
        local function shuffle(list)
            local indices = {}
            for i = 1, #list do
                indices[#indices+1] = i
            end
            local shuffled = {}
            for i = 1, #list do
                local index = math.random(#indices)
                local value = list[indices[index]]
                table.remove(indices, index)
                shuffled[#shuffled+1] = value
            end
            return shuffled
        end
        Game.Character.AttackArray = shuffle{1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11}
        Game.Character.CurrenAttackIndex = 1
        Game.Character.Style = math.random(#Game.Character.Texture_Idle_Config)
        Game.Character.CurrentIndex = 1
        Game.Character.Attack = -1
        Game.Character.FrameDuration = Game.Character.Texture_Idle_Config[Game.Character.Style][Game.Character.CurrentIndex].duration
        Game.Character.Image = SamEngine.Image(Game.Character.Texture_Idle[Game.Character.Texture_Idle_Config[Game.Character.Style][Game.Character.CurrentIndex].frame + 1])
    end)
end

function Game.Finalize()
    SamEngine.Window:SetMouseInputCallback(nil)
    SamEngine.Window:SetKeyboardInputCallback(nil)
end

function Game.Tick(count, delta)
    if Game.Character.Image ~= nil then
        if Game.Character.Attack == -1 then
            if Game.Character.FrameDuration > 0 then
                Game.Character.FrameDuration = Game.Character.FrameDuration - 1
                Game.Character.Image.texture = Game.Character.Texture_Idle[Game.Character.Texture_Idle_Config[Game.Character.Style][Game.Character.CurrentIndex].frame + 1]
            end
            if Game.Character.FrameDuration == 0 then
                Game.Character.CurrentIndex = Game.Character.CurrentIndex + 1
                if Game.Character.CurrentIndex == #Game.Character.Texture_Idle_Config[Game.Character.Style] + 1 then
                    Game.Character.CurrentIndex = 1
                end
                Game.Character.FrameDuration = Game.Character.Texture_Idle_Config[Game.Character.Style][Game.Character.CurrentIndex].duration
            end
        else
            if Game.Character.AttackFrame == 0 then
                Game.Character.Image.texture = Game.Character.Texture_A[Game.Character.Attack]
            elseif Game.Character.AttackFrame == 10 then
                Game.Character.Image.texture = Game.Character.Texture_B[Game.Character.Attack]
            elseif Game.Character.AttackFrame == 20 then
                Game.Character.Image.texture = Game.Character.Texture_C[Game.Character.Attack]
                Game.Character.CurrentIndex = 1
                Game.Character.Attack = -1
                Game.Character.FrameDuration = Game.Character.Texture_Idle_Config[Game.Character.Style][Game.Character.CurrentIndex].duration
            end
            Game.Character.AttackFrame = Game.Character.AttackFrame + 1
        end
    end
end

function Game.Draw()
    SamEngine.Graphics.Clear()
    if Game.Character.Image ~= nil then
        Game.Character.Image:Draw()
    end
end

function KeyboardCallback(type, isPress)

end

function MouseCallback(type, isPress)
    if type == SamEngine.MouseType.LEFT and isPress == true and Game.Character.Attack == -1 then
        if Game.Character.Texture_A ~= nil and Game.Character.Texture_B ~= nil and Game.Character.Texture_C ~= nil then
            Game.Character.Attack = Game.Character.Style * Game.Character.AttackArray[Game.Character.CurrenAttackIndex]
            Game.Character.CurrenAttackIndex = Game.Character.CurrenAttackIndex + 1
            if Game.Character.CurrenAttackIndex == #Game.Character.AttackArray + 1 then
                Game.Character.CurrenAttackIndex = 1
            end
            Game.Character.AttackFrame = 0
        end
    end
end