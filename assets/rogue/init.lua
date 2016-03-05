local rogue = {}

map = require(assetdir .. "rogue/map")
require(assetdir .. "rogue/player")

function rogue.init()
	print("Rogue!")

	map.create(1024, 1024, 30)
end

function rogue.update()

end

function rogue.keydown(key)
	if key == "Up" then
		map.player:move(0, -1)
	end
	if key == "Down" then
		map.player:move(0, 1)
	end
	if key == "Left" then
		map.player:move(-1, 0)
	end
	if key == "Right" then
		map.player:move(1, 0)
	end
end

function rogue.keyup(key)

end

function rogue.render()
	clear()
	map.render()
end

return rogue
