#include "LibrarySkeletonList.h"
#include "SkeletonEditDialog.h"
#include "StagePanel.h"
#include "LibraryPanel.h"
#include "Dataset/Symbol.h"

using namespace FRUITS_ANIMATOR;

LibrarySkeletonList::LibrarySkeletonList(wxWindow* parent, LibraryPanel* library)
	: wxgui::VerticalImageList(parent, LibraryPanel::SKELETON_LIST_NAME)
{
	m_library = library;
}

void LibrarySkeletonList::loadFromTextFile(std::ifstream& fin)
{
	clear();

	std::string flag;
	size_t size;
	fin >> flag >> size;
	if (size == 0) return;

	std::vector<WholeSkeleton::Node*> nodes;
	std::vector<WholeSkeleton::Body*> bodies;
	loadDataFromSymbolList(nodes, bodies);

	for (size_t i = 0; i < size; ++i)
	{
		WholeSkeleton* skeleton = new WholeSkeleton;
		skeleton->loadFromTextFile(fin, nodes, bodies);
		insert(skeleton);
	}
}

void LibrarySkeletonList::storeToTextFile(std::ofstream& fout) const
{
	if (m_items.empty())
	{
		fout << "skeleton 0" << '\n';
		return;
	}

	std::vector<WholeSkeleton::Node*> nodes;
	std::vector<WholeSkeleton::Body*> bodies;
	loadDataFromSymbolList(nodes, bodies);

	fout << "skeleton " << m_items.size() << '\n';
	for (size_t i = 0, n = m_items.size(); i < n; ++i)
	{
		WholeSkeleton* skeleton = static_cast<WholeSkeleton*>(m_items[i]);
		skeleton->storeToTextFile(fout, nodes, bodies);
	}
}

WholeSkeleton* LibrarySkeletonList::getSkeleton(int index) const
{
	if (index < 0 || index >= m_items.size()) return NULL;
	else return static_cast<WholeSkeleton*>(m_items[index]);
}

int LibrarySkeletonList::getIndex(WholeSkeleton* skeleton) const
{
	return STLTools::getArrayIndex(m_items, static_cast<wxgui::ListItem*>(skeleton));
}

void LibrarySkeletonList::setStagePanel(StagePanel* stagePanel)
{
	m_stagePanel = stagePanel;
}

void LibrarySkeletonList::onListDoubleClicked(wxCommandEvent& event)
{
 	SkeletonEditDialog dlg(this, static_cast<WholeSkeleton*>(m_items[event.GetInt()]), m_library);
 	dlg.ShowModal();
 	m_stagePanel->resetCanvas();
}

void LibrarySkeletonList::loadDataFromSymbolList(std::vector<WholeSkeleton::Node*>& nodes,
												 std::vector<WholeSkeleton::Body*>& bodies) const
{
	int index = 0;
	while (true)
	{
		Symbol* symbol = m_library->getSymbol(index++);
		if (!symbol) break;

		WholeSkeleton::Body* body = symbol->getSkeletonBody();
		if (body)
		{
			bodies.push_back(body);

			const std::vector<WholeSkeleton::Node*>& src = body->getNodes();
			copy(src.begin(), src.end(), back_inserter(nodes));
		}
	}
}