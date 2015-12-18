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

function Game.Initialize()
	SamEngine.IO:SetLocationPlaceholder("git", "http://leafnsand.com/")
	SamEngine.IO:SetLocationPlaceholder("local", "storage:///Users/xavierjiang/Documents/SamEngine/Build/Contents/resource/")
    
    local atlas = SamEngine.SpineAtlas("local:raptor.atlas")
    local data = SamEngine.SpineSkeletonData("local:raptor.json", atlas)
    Game.spine = SamEngine.Spine(data)
    Game.spine:SetAnimation(0, "walk", true)
    Game.spine.x = 640
    Game.spine.scaleX = 0.5
    Game.spine.scaleY = 0.5
end

function Game.Finalize()

end

function Game.Tick(now, delta)
    Game.spine:Update(delta)
end

function Game.Draw()
	SamEngine.Graphics.Clear()
    Game.spine:Draw()
end