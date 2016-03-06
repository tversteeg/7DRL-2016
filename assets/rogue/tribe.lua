function newTribe(m) return {
	map = m;
	color = {255, 255, 255};
	humans = {};
	humans_amount = 0;

	relations = {};

	addhuman = function(self)
		self.humans_amount = self.humans_amount + 1
		self.humans[self.humans_amount] = newHuman(self)
		return self.humans[self.humans_amount]
	end;

	endturn = function(self)
		for i = 1, self.humans_amount do
			self.humans[i]:endturn()
		end
	end;

	render = function(self)
		for i = 1, self.humans_amount do
			self.humans[i]:endturn()
		end
	end;
} end
