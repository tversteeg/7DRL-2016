function newStats() return {
	strength = 10;
	defence = 10;
	max_health = 100;
	health = 100;
} end

function newHuman(t) return {
	stats = newStats();
	tribe = t;
	x = 1;
	y = 1;
} end
