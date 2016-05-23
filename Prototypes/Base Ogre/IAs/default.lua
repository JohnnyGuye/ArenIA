-- Constants
MAX_WALL_RANGE = 2500
STEPS = 200

START_X = 0
CELL_SIZE = 100

init = false

function main()
	print("WAT THE FUCK")
	
	--print("robot default debug")
	
	-- Check if a wall is nearby
	--[[angle = math.rad(getRobotAngle())
	x,z = getPosition()

	print(x .. ", " .. z)
	for i=1500,MAX_WALL_RANGE, MAX_WALL_RANGE/STEPS do
		

		dz = z + i * math.cos(angle)
		dx = x + i * math.sin(angle)

		--print(x .. ", " .. z .. ", " .. dx .. ", " ..dz .. ", " .. math.deg(angle))
		if (isAWall(450,i)) then
			turnRobot(math.random(0,360))
		end
	end

	move()
	fire()]]--
end