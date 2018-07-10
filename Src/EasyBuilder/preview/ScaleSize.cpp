#include "ScaleSize.h"

using namespace ebuilder::preview;

ScaleSize::ScaleSize(wxgui::ISprite* sprite, float scale)
	: m_sprite(sprite)
	, m_scale(scale)
{
}

void ScaleSize::trigger()
{
	m_sprite->setScale(m_scale);
}