function main()

	--[[
	if(!init)
	{
		init = true;
		math.randomseed(os.time())
	}
	]]--
	nb = math.random(-20,20);
	move();
	stats = getStats()
	turnRobot(nb);
	fire();
end