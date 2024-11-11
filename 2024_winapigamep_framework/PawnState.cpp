#include "pch.h"
#include "PawnState.h"

void PawnState::Enter()
{
	__super::Enter();

	cout << "Pawn State Enter" << endl;
}

void PawnState::UpdateState()
{
	__super::UpdateState();
}

void PawnState::Exit()
{
	cout << "Pawn State Exit" << endl;
	__super::Exit();
}
