#include "GameState.h"
#include <chrono>
#include <iostream>

// 1/60 * 10⁶
#define UPDATE_TIME 16667
using namespace std::chrono;

void GameState::Run(){
	high_resolution_clock::time_point currentTime 
				= high_resolution_clock::now();
	
	auto elapsedTime 
				= currentTime - previousTime;

	

	lag += duration_cast<microseconds> ( currentTime - previousTime ).count();
	previousTime = currentTime;
	while (lag >= UPDATE_TIME)
	{
		std::cout << lag << " ";
		Update();
		lag -= UPDATE_TIME;	
	}

	Render((double) lag / (double) UPDATE_TIME);
}

GameState::~GameState(){

}