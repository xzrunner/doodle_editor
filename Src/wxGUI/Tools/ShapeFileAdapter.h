#ifndef _WX_GUI_SHAPE_FILE_ADAPTER_H_
#define _WX_GUI_SHAPE_FILE_ADAPTER_H_

#include "IFileAdapter.h"

#include <wx/colourdata.h>
#include <vector>

namespace wxgui
{
	class PolygonShape;

	class ShapeFileAdapter : public IFileAdapter
	{
	public:
		~ShapeFileAdapter();

		virtual void load(const char* filename);

	public:
		struct Layer
		{
			std::vector<PolygonShape*> polys;
			std::string name;

			~Layer();

		}; // Layer

	public:
		wxColourData m_color;

		std::vector<Layer*> m_layers;

	}; // ShapeFileAdapter
}

#endif // _WX_GUI_SHAPE_FILE_ADAPTER_H_