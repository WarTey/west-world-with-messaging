#include "Drunkard.h"

bool Drunkard::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}

void Drunkard::Update()
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}

bool Drunkard::Drunk() const
{
	if (m_iDrunk > AlcoholLevel) return true;

	return false;
}

bool Drunkard::Rested() const
{
	if (m_iDrunk == 0) return true;

	return false;
}
