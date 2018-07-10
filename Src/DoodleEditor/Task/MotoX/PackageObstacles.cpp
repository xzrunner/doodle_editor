#include "PackageObstacles.h"

using namespace deditor::motox;

PackageObstacles::PackageObstacles(const wxString& mergeFile,
								   const std::vector<wxString>& meshFiles,
								   const std::vector<wxString>& combineFiles, 
								   const std::vector<wxString>& breakableFiles)
	: m_meshFiles(meshFiles)
	, m_combineFiles(combineFiles)
	, m_breakableFiles(breakableFiles)
{
	m_merged.resolve(mergeFile);
}

void PackageObstacles::package(const wxString& filepath) const
{
	std::ofstream fout(filepath.fn_str(), std::ios::out | std::ios::binary);
	packageMeshes(fout);
	packageCombines(fout);
	packageBreakables(fout);
	fout.close();
}

void PackageObstacles::packageMeshes(std::ofstream& fout) const
{
	size_t size = m_meshFiles.size();
	fout.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
	for (size_t i = 0; i < size; ++i)
	{
		wxgui::MeshFileAdapter adapter;
		adapter.load(m_meshFiles[i].c_str());

		int id = -1;
		for (size_t j = 0, m = m_merged.m_data.size(); j < m; ++j)
		{
			if (m_merged.m_data[j].filepath == adapter.m_imagePath)
			{
				id = j;
				break;
			}
		}
		assert(id != -1);

		fout.write(reinterpret_cast<const char*>(&id), sizeof(int));

		size_t pSize = adapter.m_vertices.size();
		fout.write(reinterpret_cast<const char*>(&pSize), sizeof(size_t));
		for (size_t j = 0; j < pSize; ++j)
		{
			fout.write(reinterpret_cast<const char*>(&adapter.m_vertices[j].x), sizeof(float));
			fout.write(reinterpret_cast<const char*>(&adapter.m_vertices[j].y), sizeof(float));
			fout.write(reinterpret_cast<const char*>(&adapter.m_texCoords[j].x), sizeof(float));
			fout.write(reinterpret_cast<const char*>(&adapter.m_texCoords[j].y), sizeof(float));
		}

		// body bounding
		float xMin = FLOAT_MAX, xMax = -FLOAT_MAX,
			yMin = FLOAT_MAX, yMax = -FLOAT_MAX;
		for (size_t j = 0; j < pSize; ++j)
		{
			if (adapter.m_vertices[j].x < xMin) xMin = adapter.m_vertices[j].x;
			if (adapter.m_vertices[j].x > xMax) xMax = adapter.m_vertices[j].x;
			if (adapter.m_vertices[j].y < yMin) yMin = adapter.m_vertices[j].y;
			if (adapter.m_vertices[j].y > yMax) yMax = adapter.m_vertices[j].y;
		}

		float left = xMin, right = xMax,
			top = yMax, low = yMin;
		float xMid = (left + right) * 0.5f,
			yMid = (low + top) * 0.5f;
		for (size_t j = 0; j < pSize; ++j)
		{
			const f2Vec2& p = adapter.m_vertices[j];
			if (p.x < xMid && p.x > left) left = p.x;
			if (p.x > xMid && p.x < right) right = p.x;
// 			if (p.y < yMid && p.y > low) low = p.y;
// 			if (p.y > yMid && p.y < top) top = p.y;
		}
		fout.write(reinterpret_cast<const char*>(&left), sizeof(float));
		fout.write(reinterpret_cast<const char*>(&right), sizeof(float));
		fout.write(reinterpret_cast<const char*>(&low), sizeof(float));
		fout.write(reinterpret_cast<const char*>(&top), sizeof(float));
	}
}

void PackageObstacles::packageCombines(std::ofstream& fout) const
{
	size_t size = m_combineFiles.size();
	fout.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
	for (size_t i = 0; i < size; ++i)
	{
		wxgui::CombinationFileAdapter adapter;
		adapter.load(m_combineFiles[i].c_str());

		size_t pSize = adapter.m_data.size();
		fout.write(reinterpret_cast<const char*>(&pSize), sizeof(size_t));
		for (size_t j = 0; j < pSize; ++j)
		{
			const wxgui::CombinationFileAdapter::Entry& entry = adapter.m_data[j];
			if (wxgui::FileNameParser::isType(entry.filepath, wxgui::FileNameParser::e_image))
			{
				int id = -1;
				for (size_t k = 0, l = m_merged.m_data.size(); k < l; ++k)
				{
					if (m_merged.m_data[k].filepath == entry.filepath)
					{
						id = k;
						break;
					}
				}
				assert(id != -1);
				fout.write(reinterpret_cast<const char*>(&id), sizeof(int));
			}
			else if (wxgui::FileNameParser::isType(entry.filepath, wxgui::FileNameParser::e_mesh))
			{
				int id = -1;
				for (size_t k = 0, l = m_meshFiles.size(); k < l; ++k)
				{
					if (m_meshFiles[k] == entry.filepath)
					{
						id = k;
						break;
					}
				}
				assert(id != -1);
				id += m_merged.m_data.size();
				fout.write(reinterpret_cast<const char*>(&id), sizeof(int));
			}
			else
			{
				assert(0);
			}

			fout.write(reinterpret_cast<const char*>(&entry.pos.x), sizeof(float));
			fout.write(reinterpret_cast<const char*>(&entry.pos.y), sizeof(float));
			fout.write(reinterpret_cast<const char*>(&entry.angle), sizeof(float));
			fout.write(reinterpret_cast<const char*>(&entry.scale), sizeof(float));
		}
	}
}

void PackageObstacles::packageBreakables(std::ofstream& fout) const
{
	size_t size = m_breakableFiles.size();
	fout.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
	for (size_t i = 0; i < size; ++i)
	{
		std::ifstream fin(m_breakableFiles[i].fn_str());

		wxString spritesPath = StringTools::getLine(fin);
		if (spritesPath != wxT("NULL"))
			spritesPath = wxgui::FilenameTools::getExistFilepath(spritesPath);

		wxString meshesPath = StringTools::getLine(fin);
		if (meshesPath != wxT("NULL"))
			meshesPath = wxgui::FilenameTools::getExistFilepath(meshesPath);

		fin.close();

		if (spritesPath == wxT("NULL"))
		{
			int id = -1;
			fout.write(reinterpret_cast<const char*>(&id), sizeof(int));
		}
		else
		{
			int id = -1;
			for (size_t j = 0, m = m_combineFiles.size(); j < m; ++j)
			{
				if (m_combineFiles[j] == spritesPath)
				{
					id = j;
					break;
				}
			}
			assert(id != -1);
			fout.write(reinterpret_cast<const char*>(&id), sizeof(int));
		}

		int id = -1;
		for (size_t j = 0, m = m_combineFiles.size(); j < m; ++j)
		{
			if (m_combineFiles[j] == meshesPath)
			{
				id = j;
				break;
			}
		}
		assert(id != -1);
		fout.write(reinterpret_cast<const char*>(&id), sizeof(int));
	}
}