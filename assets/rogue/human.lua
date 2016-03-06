function newStats() return {
	strength = 10;
	defence = 10;
	max_health = 100;
	health = 100;
} end

function newHuman(t) return {
	map = t.map;
	stats = newStats();
	tribe = t;
	x = 1;
	y = 0;

	endturn = function(self)
	end;

	render = function(self)
		drawchar(self._.x, self._.y, string.byte("$"), self.tribe.color[0], self.tribe.color[1], self.tribe.color[2])
	end;

	move = function(self, x, y)
		newx = self.x + x
		newy = self.y + y

		if newx < 1 or newy < 1 then
			return
		end

		self.x = newx
		self.y = newy
	end;

	getx = function(self)
		return self.x
	end;

	gety = function(self)
		return self.y
	end;
} end
