#include "PackageFileIO.h"
#include "StagePanel.h"
#include "FileAdapter.h"

using namespace deditor::automatic_merge;

PackageFileIO::PackageFileIO(bool hasBoundInfo)
	: m_stagePanel(NULL)
	, m_hasBoundInfo(hasBoundInfo)
	, m_adapter(NULL)
{
}

PackageFileIO::PackageFileIO(StagePanel* stagePanel, bool hasBoundInfo)
	: m_stagePanel(stagePanel)
	, m_hasBoundInfo(hasBoundInfo)
	, m_adapter(NULL)
{
}

PackageFileIO::~PackageFileIO()
{
	delete m_adapter;
}

void PackageFileIO::storeToFile(const wxString& filepath) const
{
	std::ofstream fout(filepath.fn_str(), std::ios::out | std::ios::binary);
	storeToFile(fout);
	fout.close();
}

void PackageFileIO::storeToFile(std::ofstream& fout) const
{
	if (m_stagePanel)
	{
		std::vector<wxgui::ImageSprite*> sprites;
		m_stagePanel->traverseSprites(FetchAllVisitor<wxgui::ImageSprite>(sprites));

		const int totWidth = m_stagePanel->getWidth(),
			totHeight = m_stagePanel->getHeight();
		fout.write(reinterpret_cast<const char*>(&totWidth), sizeof(int));
		fout.write(reinterpret_cast<const char*>(&totHeight), sizeof(int));

		size_t size = sprites.size();
		fout.write(reinterpret_cast<const char*>(&size), sizeof(int));
		for (size_t i = 0; i < size; ++i)
		{
			wxgui::ImageSprite* sprite = sprites[i];

			const int w = sprite->getSymbol().getWidth(),
				h = sprite->getSymbol().getHeight();

			const int left = sprite->getPosition().x - w * 0.5f,
				top = totHeight - sprite->getPosition().y - h * 0.5f,
				width = static_cast<int>(w),
				height = static_cast<int>(h);

			fout.write(reinterpret_cast<const char*>(&left), sizeof(int));
			fout.write(reinterpret_cast<const char*>(&top), sizeof(int));
			fout.write(reinterpret_cast<const char*>(&width), sizeof(int));
			fout.write(reinterpret_cast<const char*>(&height), sizeof(int));

			if (m_hasBoundInfo)
				storeBoundaryInfo(fout, sprite->getSymbol().getFilepath());
		}
	}
	else if (m_adapter)
	{
		fout.write(reinterpret_cast<const char*>(&m_adapter->m_width), sizeof(int));
		fout.write(reinterpret_cast<const char*>(&m_adapter->m_height), sizeof(int));

		size_t size = m_adapter->m_data.size();
		fout.write(reinterpret_cast<const char*>(&size), sizeof(int));
		for (size_t i = 0; i < size; ++i)
		{
			const automatic_merge::FileAdapter::Item& item = m_adapter->m_data[i];
			fout.write(reinterpret_cast<const char*>(&item.left), sizeof(int));
			fout.write(reinterpret_cast<const char*>(&item.top), sizeof(int));
			fout.write(reinterpret_cast<const char*>(&item.width), sizeof(int));
			fout.write(reinterpret_cast<const char*>(&item.height), sizeof(int));
			storeBoundaryInfo(fout, item.filepath);
		}
	}
	else
	{
		assert(0);
	}
}

void PackageFileIO::storeToFileOrder(std::ofstream& fout, 
									 const std::vector<wxString>& filepathOrder) const
{
	assert(m_adapter);

	fout.write(reinterpret_cast<const char*>(&m_adapter->m_width), sizeof(int));
	fout.write(reinterpret_cast<const char*>(&m_adapter->m_height), sizeof(int));

	size_t size = filepathOrder.size();
	fout.write(reinterpret_cast<const char*>(&size), sizeof(int));
	for (size_t i = 0; i < size; ++i)
	{
		const wxString& filepath = filepathOrder[i];
		size_t j = 0;
		for (size_t m = m_adapter->m_data.size(); j < m; ++j)
		{
			const automatic_merge::FileAdapter::Item& item = m_adapter->m_data[j];
			if (item.filepath == filepath)
			{
				fout.write(reinterpret_cast<const char*>(&item.left), sizeof(int));
				fout.write(reinterpret_cast<const char*>(&item.top), sizeof(int));
				fout.write(reinterpret_cast<const char*>(&item.width), sizeof(int));
				fout.write(reinterpret_cast<const char*>(&item.height), sizeof(int));
				storeBoundaryInfo(fout, item.filepath);

				break;
			}
		}
		assert(j != m_adapter->m_data.size());
	}
}

void PackageFileIO::loadFromTextFile(const wxString& filepath)
{
	if (m_adapter) delete m_adapter;
	m_adapter = new FileAdapter;
	m_adapter->resolve(filepath);
}

void PackageFileIO::storeBoundaryInfo(std::ofstream& fout, const wxString& filepath)
{
	wxString path = wxgui::FilenameTools::getFilePathExceptExtension(filepath);

	wxString polygonPath = path + "_" + wxgui::FileNameParser::getFileTag(wxgui::FileNameParser::e_polyline) + ".txt";
	wxString circlePath = path + "_" + wxgui::FileNameParser::getFileTag(wxgui::FileNameParser::e_circle) + ".txt";

	if (wxgui::FilenameTools::isExist(polygonPath))
	{
		int flag = 1;
		fout.write(reinterpret_cast<const char*>(&flag), sizeof(int));
		storePolygonInfo(fout, polygonPath);
	}
	else if (wxgui::FilenameTools::isExist(circlePath))
	{
		int flag = 2;
		fout.write(reinterpret_cast<const char*>(&flag), sizeof(int));
		storeCircleInfo(fout, circlePath);
	}
	else
	{
		int flag = 0;
		fout.write(reinterpret_cast<const char*>(&flag), sizeof(int));
	}
}

void PackageFileIO::storePolygonInfo(std::ofstream& fout, const wxString& filepath)
{
	std::vector<wxgui::ChainShape*> chains;
	wxgui::PolylineFileAdapter fileAdapter(chains);
	fileAdapter.load(filepath.c_str());

	size_t chainSize = chains.size();
	fout.write(reinterpret_cast<const char*>(&chainSize), sizeof(int));
	for (size_t i = 0; i < chainSize; ++i)
	{
		const std::vector<f2Vec2>& vertices = chains[i]->getVertices();
		size_t posSize = vertices.size();
		fout.write(reinterpret_cast<const char*>(&posSize), sizeof(int));
		for (size_t j = 0; j < posSize; ++j)
		{
			fout.write(reinterpret_cast<const char*>(&vertices[j].x), sizeof(float));
			fout.write(reinterpret_cast<const char*>(&vertices[j].y), sizeof(float));
		}
	}

	for_each(chains.begin(), chains.end(), DeletePointerFunctor<wxgui::ChainShape>());
}

void PackageFileIO::storeCircleInfo(std::ofstream& fout, const wxString& filepath)
{
	wxgui::CircleFileAdapter fileAdapter;
	fileAdapter.load(filepath);

	int flag = -1;
	fout.write(reinterpret_cast<const char*>(&flag), sizeof(int));
	fout.write(reinterpret_cast<const char*>(&fileAdapter.m_width), sizeof(int));
}