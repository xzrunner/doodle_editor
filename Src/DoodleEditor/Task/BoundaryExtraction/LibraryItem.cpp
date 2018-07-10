#include "LibraryItem.h"

using namespace deditor::boundary_extraction;

LibraryItem::~LibraryItem()
{
	clearUserData(true);
}

void LibraryItem::clearUserData(bool deletePtr)
{
	if (m_userData)
	{
		std::vector<wxgui::IShape*>* shapes 
			= static_cast<std::vector<wxgui::IShape*>*>(m_userData);
		for_each(shapes->begin(), shapes->end(), DeletePointerFunctor<wxgui::IShape>());
		shapes->clear();
		if (deletePtr)
			delete shapes, m_userData = NULL;
	}
}

float LibraryItem::getWidth() const
{
	return 0;
}

float LibraryItem::getHeight() const
{
	return 0;
}