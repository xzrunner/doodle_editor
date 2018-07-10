#include "FileIO.h"
#include "StagePanel.h"

using namespace deditor::texture_edit;

void FileIO::load(std::ifstream& fin, StagePanel* editPanel)
{
	wxString imagePath = StringTools::getLine(fin);
	if (imagePath != "NULL")
		editPanel->loadTexture(imagePath);

	size_t shapeSize;
	fin >> shapeSize;
	for (size_t i = 0; i < shapeSize; ++i)
	{
		std::vector<f2Vec2> vertices;
		size_t verticesSize;
		fin >> verticesSize;
		vertices.reserve(verticesSize);
		for (size_t j = 0; j < verticesSize; ++j)
		{
			f2Vec2 pos;
			fin >> pos;
			vertices.push_back(pos);
		}
		editPanel->insertShape(new wxgui::ChainShape(vertices, true));
	}
}

void FileIO::store(std::ofstream& fout, StagePanel* editPanel)
{
	wxgui::Image* image = editPanel->getTexture();
	if (image)
		fout << image->filepath() << '\n';
	else
		fout << "NULL";

	std::vector<wxgui::ChainShape*> chains;
	editPanel->traverseShapes(FetchAllVisitor<wxgui::ChainShape>(chains));
	fout << chains.size() << '\n';
	for (size_t i = 0, n = chains.size(); i < n; ++i)
	{
		const std::vector<f2Vec2>& vertices = chains[i]->getVertices();
		fout << vertices.size() << '\n';
		for (size_t j = 0, m = vertices.size(); j < m; ++j)
			fout << vertices[j] << " ";
		fout << '\n';
	}
}