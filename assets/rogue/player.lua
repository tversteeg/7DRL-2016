require(assetdir .. "rogue/human")

function newPlayer(t, m) return {
	_ = newHuman(t);
	map = m;

	move = function(self, x, y)
		newx = self._.x + x
		newy = self._.y + y

		if newx < 1 or newy < 1 then
			return false
		end

		self._.x = newx
		self._.y = newy

		return true
	end;

	getx = function(self)
		return self._.x
	end;

	gety = function(self)
		return self._.y
	end;
} end
