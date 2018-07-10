#include "Actor.h"

using namespace ebuilder::preview;

Actor::Actor(const wxgui::ImageSprite& sprite)
	: Item(e_actor, sprite)
{
}