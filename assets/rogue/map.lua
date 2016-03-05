require(assetdir .. "rogue/tribe")
require(assetdir .. "rogue/human")
require(assetdir .. "rogue/player")

local map = {}

NUM_TRIBES = 3
NUM_HUMANS_PER_TRIBE = 10

ROOM_MAX_SIZE = 5
ROOM_MIN_SIZE = 3

map.tiles = {}
map.tribes = {}
map.player = {}

function roomcollides(room1, room2)
	if room1.x > room2.x + room2.width then
		return false
	elseif room1.y > room2.y + room2.height then
		return false
	elseif room1.x + room1.width < room2.x then
		return false
	elseif room1.y + room1.height < room2.y then
		return false
	else
		return true
	end
end

function relaxrooms(room_list)
	for i = 1, #room_list do
		room_list[i].dx = math.floor(math.random(0, 1)) * 2 - 1
		room_list[i].dy = math.floor(math.random(0, 1)) * 2 - 1
	end

	relaxed = true
	for i = 1, #room_list do
		for j = 1, #room_list do
			if i ~= j then
				while roomcollides(room_list[i], room_list[j]) do
					room_list[i].x = room_list[i].x + room_list[i].dx
					room_list[i].y = room_list[i].y + room_list[i].dy
					relaxed = false
				end
			end
		end
	end

	return relaxed
end

function createroomcluster(x, y, rooms)
	room_list = {}
	for i = 1, rooms do
		room = {}
		room.width = math.random(ROOM_MIN_SIZE, ROOM_MAX_SIZE)
		room.height = math.random(ROOM_MIN_SIZE, ROOM_MAX_SIZE)
		room.x = math.floor(map.width / 2) - math.random(room.width)
		room.y = math.floor(map.height / 2) - math.random(room.height)

		room.relax_width = math.random(room.width, ROOM_MAX_SIZE)
		room.relax_height = math.random(room.height, ROOM_MAX_SIZE)
		room_list[i] = room
	end

	while not relaxrooms(room_list) do end

	for i = 1, rooms do
		room = room_list[i]
		for y = 1, room.height do
			for x = 1, room.width do
				rx = x + room.x
				ry = y + room.y
				if rx >= 1 and rx < map.width and ry >= 1 and ry < map.height then
					map.tiles[y + room.y][x + room.x] = '%'
				end
			end
		end
	end
end

function map.create(width, height, rooms)	map.width = width
	map.height = height

	for y = 1, map.height do
		map.tiles[y] = {}
		for x = 1, map.width do
			map.tiles[y][x] = '.'
		end
	end

	createroomcluster(math.floor(map.width / 2), math.floor(map.height / 2), rooms)

	for i = 1, NUM_TRIBES do
		tribe = newTribe()
		for j = 1, NUM_HUMANS_PER_TRIBE do
			tribe:addhuman()
		end

		map.tribes[i] = tribe
	end

	map.player = newPlayer(map.tribes[1])
end

function map.render(xpos, ypos)
	max_width = map.width
	if max_width > getwidth() - 1 then
		max_width = getwidth() - 1
	end
	max_height = map.height
	if max_height > getheight() - 1 then
		max_height = getheight() - 1
	end

	for y = 0, max_height do
		for x = 1, max_width do
			c = map.tiles[y + 1][x]
			if c == '%' then
				drawchar(x, y, string.byte(c), 128, 12, 12)
			elseif c == '.' then
				drawchar(x, y, string.byte(c), 0, 255, 0)
			end
		end
	end
end

return map
