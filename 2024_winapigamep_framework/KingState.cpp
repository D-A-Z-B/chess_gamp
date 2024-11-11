#include "pch.h"
#include "KingState.h"

void KingState::Enter()
{
	__super::Enter();

	cout << "King State Enter" << endl;
}

void KingState::UpdateState()
{
	__super::UpdateState();
}

void KingState::Exit()
{
	cout << "King State Exit" << endl;
	__super::Exit();
}
