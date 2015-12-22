#include "DummyGameState.h"

int main()
{
	DummyGameState gs;
	gs.Init();
	while (true)
	{
		gs.Run();
	}
	return 0;
}