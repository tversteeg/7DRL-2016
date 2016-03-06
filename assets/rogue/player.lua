require(assetdir .. "rogue/human")

function newPlayer(t) return {
	_ = newHuman(t);

	render = function(self)
		drawchar(self._.x, self._.y, string.byte("@"), 255, 255, 255)
	end;

	move = function(self, x, y)
		self._:move(x, y)
	end;

	getx = function(self)
		return self._.x
	end;

	gety = function(self)
		return self._.y
	end;
} end
