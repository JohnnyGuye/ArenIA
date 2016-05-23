-- Constants
MAX_WALL_RANGE = 200
STEPS = 5

START_X = 0
CELL_SIZE = 100

init = false

function main()
	
	--[[if not init then
		init = true
		RANGE_X,RANGE_Z = getTerrainSize()
		print (RANGE_X .. " " .. RANGE_Z)
		for x = 1, RANGE_Z-100, CELL_SIZE do
			strin = ""
			for z = 1, RANGE_X-100, CELL_SIZE do
				if isAWall(x,z) then
					strin = strin .. "#"
				else
					strin = strin .. "."
				end
		
			end
			print(strin)
			move()
		end
	end]]--
	--move()
	--print("robot default debug")
	
	-- Check if a wall is nearby
	angle = math.rad(getRobotAngle())
	x,z = getPosition()

	print(x .. ", " .. z)
	for i=0,MAX_WALL_RANGE, MAX_WALL_RANGE/STEPS do
		

		dz = z + i * math.cos(angle)
		dx = x + i * math.sin(angle)

		--print(x .. ", " .. z .. ", " .. dx .. ", " ..dz .. ", " .. math.deg(angle))
		if (isAWall(dx,dz)) then
			turnRobot(math.random(0,360))
		end
	end

	move()
	fire()
end