#include "pch.h"
#include "PawnState.h"

void PawnState::Enter()
{
	__super::Enter();

	cout << "Pawn State Enter";
}

void PawnState::UpdateState()
{
	__super::UpdateState();
}

void PawnState::Exit()
{
	cout << "Pawn State Exit";
	__super::Exit();
}
