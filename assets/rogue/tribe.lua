function newTribe() return {
	color = {255, 255, 255};
	humans = {};
	humans_amount = 0;

	relations = {};

	addhuman = function(self)
		self.humans_amount = self.humans_amount + 1
		self.humans[self.humans_amount] = newHuman(self)
	end;
} end
