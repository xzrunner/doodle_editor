#include "Actor.h"

#include "behaviors/Behavior.h"

using namespace ebuilder;

Actor::Actor(wxgui::ImageSymbol* symbol)
	: wxgui::ImageSprite(symbol)
	, m_isBg(false)
	, m_layer(1)
{
	static int count = 0;
	m_name = wxT("actor") + wxString::FromDouble(count++);
}

Actor::~Actor()
{
	clearBehaviors();	
}

Actor* Actor::clone()
{
	return NULL;
}

void Actor::clearBehaviors()
{
	for_each(m_behaviors.begin(), m_behaviors.end(), DeletePointerFunctor<Behavior>());
	m_behaviors.clear();
}