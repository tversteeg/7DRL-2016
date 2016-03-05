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

end

function rogue.keyup(key)

end

function rogue.render()
	clear()
	map.render()
end

return rogue
