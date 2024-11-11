#include "pch.h"
#include "KnightState.h"

void KnightState::Enter()
{
	__super::Enter();

	cout << "Knight State Enter" << endl;
}

void KnightState::UpdateState()
{
	__super::UpdateState();
}

void KnightState::Exit()
{
	__super::Exit();

	cout << "Knight State Exit" << endl;
}
