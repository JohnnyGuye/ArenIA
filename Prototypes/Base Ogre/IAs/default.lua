function main()
	move();

	stats = getStats()


	turnRobot(0.2);
	fire();
	x,y = getPosition()
	print(x ..", " .. y);
end