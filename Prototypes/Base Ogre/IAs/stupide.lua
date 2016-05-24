function main()
	
	idRobots = getRobots();
	print(#idRobots)
	-- if there is still robots in da game
	if (#idRobots >= 2) then
		-- Find the enemy robot adress
		--print(idRobots[2]);
		x,y = getPosition(idRobots[2]);

		-- get our position
		myX,myY = getPosition();

		-- Compute distance to the target
		dY = y - myY;
		dH = math.sqrt( (myX - x)*(myX - x) + (myY - y)*(myY - y))

		-- Compute angle using fancy trigonometrics
		alpha = math.deg(math.acos(dY/dH))

		-- Must be usefull ...
		if (x<myX) then
			alpha = 360-alpha;
		end

		-- Find which angle we must turn using our orientation and the angle bewteen us and the target
		angleTurn =  alpha - getRobotAngle();


		--print(alpha .. ",    " .. angleTurn .. ",     " .. getRobotAngle());
		
		-- If we are too close, don't move
		if (dH > 250) then
			move();
		end

		-- Turn the robot by the computed angle
		turnRobot(angleTurn);

		-- Fire whenever it's possible
		fire();
	end

end