#include "DummyGameState.h"
#include <iostream>

using namespace std;

void DummyGameState::HandleInput()
{

}

void DummyGameState::Update()
{
	cout << "=== Doing update ===" << endl;
}

void DummyGameState::Render(double interpolation)
{
	cout << "Doing render" << endl;
}

DummyGameState::DummyGameState()
{
	Init();
}

DummyGameState::~DummyGameState()
{
}