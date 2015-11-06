package.path = "F:/SamEngine/Build/Contents/?.lua;F:/SamEngine/Build/Contents/?/?.lua;F:/SamEngine/Build/Contents/?/init.lua;F:/SamEngine/Build/Contents/?.lua;F:/SamEngine/Build/Contents/lib/?.lua;F:/SamEngine/Build/Contents/lib/?/?.lua;F:/SamEngine/Build/Contents/lib/?/init.lua;F:/SamEngine/Build/Contents/lib/?.lua"
package.cpath = "F:/SamEngine/Build/Contents/clib/?.dll"

require('mobdebug').start()
require('class')
require('battle')
require('texture_atlas')


function trace(message, ...)
    if message == nil then return end
    if type(message) == "string" or type(message) == "number" then
        SamEngine.Log.Debug(message .. "\n")
    elseif type(message) == "userdata" then
        SamEngine.Log.Debug(getmetatable(message).___type .. "\n")
    else
        SamEngine.Log.Debug(type(message) .. "\n")
    end
    trace(...)
end

Game = {}
Game.ScreenWidth = 1280
Game.ScreenHeight = 720

function Game.Initialize()
    SamEngine.IO:SetLocationPlaceholder("git", "http://leafnsand.com/")
    SamEngine.IO:SetLocationPlaceholder("local", "storage://F:/SamEngine/Build/Contents/resource/")
    SamEngine.Window:SetMouseInputCallback(Game.MouseCallback)
    SamEngine.Window:SetKeyboardInputCallback(Game.KeyboardCallback)
    SamEngine.Window:SetTitle("Demo")
    
    Game.battle = new("battle")
end

function Game.Finalize()
    SamEngine.Window:SetMouseInputCallback(nil)
    SamEngine.Window:SetKeyboardInputCallback(nil)
end

function Game.Tick(now, delta)
    Game.battle:update(now, delta)
end

function Game.Draw()
    SamEngine.Graphics.Clear()
    Game.battle:draw()
end

function Game.KeyboardCallback(keyType, isPress)
    
end

function Game.MouseCallback(keyType, isPress)
    if isPress then
        if keyType == SamEngine.MouseType.LEFT then
            Game.battle.player:attack_left()
        else
            Game.battle.player:attack_right()
        end
    end
end