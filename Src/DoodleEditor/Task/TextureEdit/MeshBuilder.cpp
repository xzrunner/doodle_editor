#include "MeshBuilder.h"

using namespace deditor::texture_edit;

MeshBuilder::MeshBuilder(const wxgui::Image& image,
						 const std::vector<std::vector<f2Vec2> >& loops)
{
	m_imagePath = image.filepath();
	build(image.width(), image.height(), loops);
}

void MeshBuilder::storeToTextFile(const wxString& filepath) const
{
	std::ofstream fout(filepath.fn_str());

	fout << m_imagePath << '\n';

	fout << m_vertices.size() << '\n';

	for (size_t i = 0, n = m_vertices.size(); i < n; ++i)
		fout << m_vertices[i] << " ";
	fout << '\n';

	for (size_t i = 0, n = m_texCoords.size(); i < n; ++i)
		fout << m_texCoords[i] << " ";
	fout << '\n';

	fout.close();
}

void MeshBuilder::build(int width, int height, 
						const std::vector<std::vector<f2Vec2> >& loops)
{
	m_vertices.clear();
	m_texCoords.clear();

	const float hWidth = width * 0.5f,
		hHeight = height * 0.5f;

	for (size_t i = 0, n = loops.size(); i < n; ++i)
	{
		std::vector<f2Vec2> tris;
		wxgui::Math::triangulatePolygon(loops[i], tris);
		for (size_t j = 0, m = tris.size(); j < m; ++j)
		{
			m_vertices.push_back(tris[j]);

			float tx = (tris[j].x + hWidth) / width;
			float ty = (tris[j].y + hHeight) / height;
			m_texCoords.push_back(f2Vec2(tx, ty));
		}
	}
}