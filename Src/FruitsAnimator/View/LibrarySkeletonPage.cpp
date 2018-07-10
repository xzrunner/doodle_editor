#include "LibrarySkeletonPage.h"
#include "LibrarySkeletonList.h"
#include "SkeletonEditDialog.h"
#include "StagePanel.h"
#include "Dataset/WholeSkeleton.h"

using namespace FRUITS_ANIMATOR;

LibrarySkeletonPage::LibrarySkeletonPage(wxWindow* parent, LibraryPanel* library)
	: ILibraryPage(parent)
	, m_stagePanel(NULL)
	, m_library(library)
{
	initLayout();

	wxSizer* sizer = GetSizer();
	m_skeletonList = new LibrarySkeletonList(this, library);
	sizer->Add(m_skeletonList, 1, wxEXPAND);
	SetSizer(sizer);
}

void LibrarySkeletonPage::loadFromTextFile(std::ifstream& fin)
{
	m_skeletonList->loadFromTextFile(fin);
}

void LibrarySkeletonPage::storeToTextFile(std::ofstream& fout) const
{
	m_skeletonList->storeToTextFile(fout);
}

void LibrarySkeletonPage::traverse(IVisitor& visitor) const
{
}

WholeSkeleton* LibrarySkeletonPage::getSkeleton(int index) const
{
	return m_skeletonList->getSkeleton(index);
}

int LibrarySkeletonPage::getIndex(WholeSkeleton* skeleton) const
{
	return m_skeletonList->getIndex(skeleton);
}

void LibrarySkeletonPage::setStagePanel(StagePanel* stagePanel)
{
	m_stagePanel = stagePanel;
	m_skeletonList->setStagePanel(stagePanel);
}

void LibrarySkeletonPage::clear()
{
	m_skeletonList->clear();
}

void LibrarySkeletonPage::onAddPress(wxCommandEvent& event)
{
	WholeSkeleton* skeleton = new WholeSkeleton;
	m_skeletonList->insert(skeleton);

	SkeletonEditDialog dlg(this, skeleton, m_library);
	dlg.ShowModal();
	m_stagePanel->resetCanvas();
}

void LibrarySkeletonPage::onDelPress(wxCommandEvent& event)
{
	m_skeletonList->remove();
}