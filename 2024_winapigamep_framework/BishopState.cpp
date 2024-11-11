#include "pch.h"
#include "BishopState.h"

void BishopState::Enter()
{
	__super::Enter();

	cout << "Bishop State Enter" << endl;
}

void BishopState::UpdateState()
{
	__super::UpdateState();
}

void BishopState::Exit()
{
	cout << "Bishop State Exit" << endl;
	__super::Exit();
}
