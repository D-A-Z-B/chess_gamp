#include "pch.h"
#include "QueenState.h"

void QueenState::Enter()
{
	__super::Enter();

	cout << "Queen State Enter" << endl;
}

void QueenState::UpdateState()
{
	__super::UpdateState();
}

void QueenState::Exit()
{
	__super::Enter();

	cout << "Queen State Exit" << endl;
}
