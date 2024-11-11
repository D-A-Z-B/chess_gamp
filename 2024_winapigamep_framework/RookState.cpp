#include "pch.h"
#include "RookState.h"

void RookState::Enter()
{
	__super::Enter();

	cout << "Rook State Enter" << endl;
}

void RookState::UpdateState()
{
	__super::UpdateState();
}

void RookState::Exit()
{
	__super::Exit();

	cout << "Rook State Exit" << endl;
}
