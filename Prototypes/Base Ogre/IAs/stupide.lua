function main()
	
	idRobots = getRobots();
	-- Find the enemy robot adress
	--print(idRobots[2]);

	x,y = getPosition(idRobots[2]);

	myX,myY = getPosition();

	dY = y - myY;
	dH = math.sqrt( (myX - x)*(myX - x) + (myY - y)*(myY - y))

	alpha = math.deg(math.acos(dY/dH))

	if (x<myX) then
		alpha = 360-alpha;
	end

	angleTurn =  alpha - getRobotAngle();

	--print(alpha .. ",    " .. angleTurn .. ",     " .. getRobotAngle());

	if (dH > 250) then
		move();
	end
	turnRobot(angleTurn);
	fire();
end