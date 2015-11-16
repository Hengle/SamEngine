package.path = "./Contents/?.lua;./Contents/?/?.lua;./Contents/?/init.lua;./Contents/?.lua;./Contents/lib/?.lua;./Contents/lib/?/?.lua;./Contents/lib/?/init.lua;./Contents/lib/?.lua"
package.cpath = "./Contents/clib/?.dll"

require('mobdebug').start()
require('class')
require('config')
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
	SamEngine.IO:SetLocationPlaceholder("local", "storage://./Contents/resource/")
	SamEngine.Window:SetMouseInputCallback(Game.MouseCallback)
	SamEngine.Window:SetKeyboardInputCallback(Game.KeyboardCallback)
	SamEngine.Window:SetTitle("Demo")
	
	Game.battle = new("battle")
    Game.config = new ("config")
	Game.index = 0
    
    --Game.spine = SamEngine.Spine("./Contents/resource/raptor.json", "./Contents/resource/raptor.atlas")
    --Game.spine:SetAnimation(0, "walk", true)
    --Game.spine.x = 640
    --Game.spine.scaleX = 0.5
    --Game.spine.scaleY = 0.5
end

function Game.Finalize()
	SamEngine.Window:SetMouseInputCallback(nil)
	SamEngine.Window:SetKeyboardInputCallback(nil)
end

function Game.Tick(now, delta)
--    Game.spine:Update(delta)
        
	Game.index = Game.index + 1
	if Game.index % 20  ~= 0 then
		--return
	end
	Game.index = 0
	Game.battle:update(now, delta)
end

function Game.Draw()
	SamEngine.Graphics.Clear()
	Game.battle:draw()
--    Game.spine:Draw()
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