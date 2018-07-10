#ifndef _FEDITOR_TRIS_FILE_ADAPTER_H_
#define _FEDITOR_TRIS_FILE_ADAPTER_H_
#include "TextFileAdapter.h"

namespace FEDITOR
{
	class TriangleShape;

	class TrisFileAdapter : public TextFileAdapter
	{
	public:
		~TrisFileAdapter();

		virtual void load(const std::string& filename);

	public:
		struct Layer
		{
			f2Colorf color;
			std::vector<TriangleShape*> shapes;
		};

	public:
		std::vector<Layer*> m_layers;

	}; // TrisFileAdapter
}

#endif // _FEDITOR_TRIS_FILE_ADAPTER_H_