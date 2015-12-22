#ifndef _DUMMY_GS_H_
#define _DUMMY_GS_H_

#include "GameState.h"

class DummyGameState :public GameState {
public:
	void HandleInput();
	void Update();
	void Render(double interpolation);

	DummyGameState();
	~DummyGameState();
private:

};


#endif