#ifndef _DEDITOR_TEXTURE_EDIT_MESH_BUILDER_H_
#define _DEDITOR_TEXTURE_EDIT_MESH_BUILDER_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace texture_edit
	{
		class MeshBuilder
		{
		public:
			MeshBuilder(const wxgui::Image& image,
				const std::vector<std::vector<f2Vec2> >& loops);

			void storeToTextFile(const wxString& filepath) const;
			
		private:
			void build(int width, int height, 
				const std::vector<std::vector<f2Vec2> >& loops);

		private:
			wxString m_imagePath;

			std::vector<f2Vec2> m_vertices;
			std::vector<f2Vec2> m_texCoords;

		}; // MeshBuilder
	}
}

#endif // _DEDITOR_TEXTURE_EDIT_MESH_BUILDER_H_