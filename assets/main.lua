rogue = require(assetdir .. "rogue")

state = "Menu"
game = nil

menu_items = {"Play", "Config"}
menu_len = 2
menu_selected = 1

function renderselectionmenu(width, height)
	clear()
	drawstring(width / 2 - math.floor(string.len("Ancestral Roots") / 2), 8, "Ancestral Roots", 255, 0, 0)
	for i = 1, menu_len do
		local color = {127, 127, 127}
		if menu_selected == i then
			color = {255, 255, 255}
		end
		drawstring(width / 2 - math.floor(string.len(menu_items[i]) / 2), 12 + i * 4, menu_items[i], color[1], color[2], color[3])
	end

	for i = 1, width - 2 do
		drawchar(i, 1, string.byte("="), 64, 64, 64)
		drawchar(i, height - 1, string.byte("="), 64, 64, 64)
	end
	for i = 1, height - 1 do
		drawchar(1, i, string.byte("#"), 64, 64, 64)
		drawchar(width - 2, i, string.byte("#"), 64, 64, 64)
	end
end

function keydown(keycode)
	if state == "Menu" then
		if keycode == "Down" then
			if menu_selected < menu_len then
				menu_selected = menu_selected + 1
			end
		elseif keycode == "Up" then
			if menu_selected > 1 then
				menu_selected = menu_selected - 1
			end
		elseif keycode == "Return" then
			if menu_items[menu_selected] == "Play" then
				state = "Game"
				game = rogue
				game.init()
			end
		end
	elseif state == "Game" then
		game.keydown(keycode)
	end
end

function keyup(keycode)
	if state == "Game" then
		game.keyup(keycode)
	end
end

function setup()
	math.randomseed(os.time())
end

function update()
	local width = getwidth()
	if math.fmod(width, 2) == 1 then
		width = width - 1
	end
	local height = getheight()
	if math.fmod(height, 2) == 1 then
		height = height - 1
	end

	if state == "Menu" then
		renderselectionmenu(width, height)
	elseif state == "Game" then
		game.update()
	end
end

function render()
	if state == "Game" then
		game.render()
	end
end
