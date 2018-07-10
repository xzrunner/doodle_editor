#include "KeysContentWidget.h"
#include "KeysPanel.h"
#include "Utility.h"
#include "Dataset/KeyFrame.h"
#include "Dataset/Layer.h"
#include "Dataset/LayersMgr.h"
#include <wx/dcbuffer.h>

using namespace FRUITS_ANIMATOR;

BEGIN_EVENT_TABLE(KeysContentWidget, wxPanel)
	EVT_PAINT(KeysContentWidget::onPaint)
	EVT_ERASE_BACKGROUND(KeysContentWidget::onEraseBackground)
	EVT_SIZE(KeysContentWidget::onSize)
	EVT_MOUSE_EVENTS(KeysContentWidget::onMouse)

	EVT_MENU(Menu_CreateClassicTween, KeysContentWidget::onCreateClassicTween)
	EVT_MENU(Menu_DeleteClassicTween, KeysContentWidget::onDeleteClassicTween)
	EVT_MENU(Menu_InsertFrame, KeysContentWidget::onInsertFrame)
	EVT_MENU(Menu_DeleteFrame, KeysContentWidget::onDeleteFrame)
	EVT_MENU(Menu_InsertKeyFrame, KeysContentWidget::onInsertKeyFrame)
	EVT_MENU(Menu_DeleteKeyFrame, KeysContentWidget::onDeleteKeyFrame)

	EVT_UPDATE_UI(Menu_CreateClassicTween, KeysContentWidget::onUpdateCreateClassicTween)
	EVT_UPDATE_UI(Menu_DeleteClassicTween, KeysContentWidget::onUpdateDeleteClassicTween)
	EVT_UPDATE_UI(Menu_InsertFrame, KeysContentWidget::onUpdateInsertFrame)
	EVT_UPDATE_UI(Menu_DeleteFrame, KeysContentWidget::onUpdateDeleteFrame)
	EVT_UPDATE_UI(Menu_InsertKeyFrame, KeysContentWidget::onUpdateInsertKeyFrame)
	EVT_UPDATE_UI(Menu_DeleteKeyFrame, KeysContentWidget::onUpdateDeleteKeyFrame)
END_EVENT_TABLE()

LanguageEntry KeysContentWidget::entries[] =
{
	{ "������ͳ����", "Create Classic Tween" },
	{ "ɾ����ͳ����", "Delete Classic Tween" },
	{ "����֡", "Insert Frame" },
	{ "ɾ��֡", "Delete Frame" },
	{ "����ؼ�֡", "Insert Key Frame" },
	{ "ɾ���ؼ�֡", "Delete Key Frame" }
};

KeysContentWidget::KeysContentWidget(KeysPanel* parent, int id, LayersMgr* layersMgr)
	: wxPanel(parent, id, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
	m_parent = parent;
	m_layersMgr = layersMgr;
}

void KeysContentWidget::onSize(wxSizeEvent& event)
{
	Refresh();
}

void KeysContentWidget::onPaint(wxPaintEvent& event)
{
	wxBufferedPaintDC dc(this);

	drawBackground(dc);
	drawLayersDataBg(dc);
	drawSelected(dc);
	drawLayersDataFlag(dc);
	drawCurrPosFlag(dc);
}

void KeysContentWidget::onEraseBackground(wxEraseEvent& event)
{

}

void KeysContentWidget::onMouse(wxMouseEvent& event)
{
	if (event.LeftDown() || event.RightDown())
	{
		int row = event.GetY() / FRAME_GRID_HEIGHT,
			col = event.GetX() / FRAME_GRID_WIDTH;
		if (row < m_layersMgr->size() && col < MAX_FRAME_COUNT)
			m_parent->setSelectPos(row, col);
		else
			m_parent->setSelectPos(-1, -1);
	}

	if (event.RightDown())
	{
		wxMenu menu;

		menu.Append(Menu_CreateClassicTween, entries[Menu_CreateClassicTween].text[currLanguage]);
		menu.Append(Menu_DeleteClassicTween, entries[Menu_DeleteClassicTween].text[currLanguage]);
		menu.AppendSeparator();
		menu.Append(Menu_InsertFrame, entries[Menu_InsertFrame].text[currLanguage]);
		menu.Append(Menu_DeleteFrame, entries[Menu_DeleteFrame].text[currLanguage]);
		menu.AppendSeparator();
		menu.Append(Menu_InsertKeyFrame, entries[Menu_InsertKeyFrame].text[currLanguage]);
		menu.Append(Menu_DeleteKeyFrame, entries[Menu_DeleteKeyFrame].text[currLanguage]);

		PopupMenu(&menu, event.GetX(), event.GetY());
	}
}

KeyFrame* KeysContentWidget::queryKeyFrameByPos() const
{
	int row, col;
	m_parent->getSelectPos(row, col);
	if (row == -1 || col == -1) 
		return NULL;

	Layer* layer = m_layersMgr->getLayer(m_layersMgr->size() - row - 1);
	if (!layer) return NULL;
	else return layer->getCurrKeyFrame(col + 1);
}

void KeysContentWidget::drawBackground(wxBufferedPaintDC& dc)
{
	// background
	dc.SetPen(wxPen(LIGHT_GRAY));
	dc.SetBrush(wxBrush(LIGHT_GRAY));
	dc.DrawRectangle(GetSize());

	const size_t size = m_layersMgr->size();
	const float width = FRAME_GRID_WIDTH * MAX_FRAME_COUNT,
		height = FRAME_GRID_HEIGHT * size;

	// white grids
	dc.SetPen(*wxWHITE_PEN);
	dc.SetBrush(*wxWHITE_BRUSH);
 	dc.DrawRectangle(0, 0, width, height);

	// 5 times gray grids
	dc.SetPen(wxPen(LIGHT_GRAY));
	dc.SetBrush(wxBrush(LIGHT_GRAY));
	for (size_t i = 1; i <= MAX_FRAME_COUNT; ++i)
	{
		if (i % 5 == 0)
		{
			const float x = FRAME_GRID_WIDTH * (i - 1);
			dc.DrawRectangle(x, 0, FRAME_GRID_WIDTH, height);
		}
	}

	// grid lines
	dc.SetPen(wxPen(MEDIUM_GRAY));
	for (size_t i = 0; i <= size; ++i)
	{
		const float y = FRAME_GRID_HEIGHT * i;
		dc.DrawLine(0, y, width, y);
	}
	for (size_t i = 0; i <= MAX_FRAME_COUNT; ++i)
	{
		const float x = FRAME_GRID_WIDTH * i;
		dc.DrawLine(x, 0, x, height);
	}
}

void KeysContentWidget::drawLayersDataBg(wxBufferedPaintDC& dc)
{
	for (size_t i = 0, n = m_layersMgr->size(); i < n; ++i)
	{
		size_t storeIndex = n - i - 1;
		const std::map<int, KeyFrame*>& frames = m_layersMgr->getLayer(storeIndex)->getAllFrames();
		std::map<int, KeyFrame*>::const_iterator itr;
		// during
		for (itr = frames.begin(); itr != frames.end(); ++itr)
		{
			std::map<int, KeyFrame*>::const_iterator next = itr;
			++next;
			float x = FRAME_GRID_WIDTH * (itr->first - 1),
				y = FRAME_GRID_HEIGHT * i;
			float width = FRAME_GRID_WIDTH + 1,
				height = FRAME_GRID_HEIGHT + 1;
			if (next != frames.end())
				width = std::max(FRAME_GRID_WIDTH * (next->first - itr->first), FRAME_GRID_WIDTH) + 1;
			dc.SetPen(*wxBLACK_PEN);
			//			dc.SetBrush(*wxWHITE_BRUSH);
			dc.SetBrush(wxColour(255, 255, 255, 128));
			dc.DrawRectangle(x, y, width, height);
		}
		// Classic Tween
		for (itr = frames.begin(); itr != frames.end(); ++itr)
		{
			if (itr->second->hasClassicTween())
			{
				std::map<int, KeyFrame*>::const_iterator next = itr;
				++next;
				if (next != frames.end())
				{
					float x = FRAME_GRID_WIDTH * (itr->first - 1.0f),
						y = FRAME_GRID_HEIGHT * i;
					float width = FRAME_GRID_WIDTH * (next->first - itr->first) + 1,
						height = FRAME_GRID_HEIGHT + 1;

					dc.SetPen(*wxBLACK_PEN);
					dc.SetBrush(wxBrush(CLASSIC_TWEEN_COLOR));
					dc.DrawRectangle(x, y, width, height);
				}
			}
		}
	}
}

void KeysContentWidget::drawLayersDataFlag(wxBufferedPaintDC& dc)
{
	for (size_t i = 0, n = m_layersMgr->size(); i < n; ++i)
	{
		size_t storeIndex = n - i - 1;
		const std::map<int, KeyFrame*>& frames = m_layersMgr->getLayer(storeIndex)->getAllFrames();
		std::map<int, KeyFrame*>::const_iterator itr;
		// key frame start (circle)
		for (itr = frames.begin(); itr != frames.end(); ++itr)
		{
			float x = FRAME_GRID_WIDTH * (itr->first - 0.5f),
				y = FRAME_GRID_HEIGHT * (i + 1) - KEY_FRAME_CIRCLE_Y_OFFSET;
			dc.SetPen(*wxBLACK_PEN);
			if (itr->second->isEmpty()) dc.SetBrush(*wxWHITE_BRUSH);
			else dc.SetBrush(*wxBLACK_BRUSH);
			dc.DrawCircle(x, y, KEY_FRAME_CIRCLE_RADIUS);
		}
		// key frame end (rect)
		for (itr = frames.begin(); itr != frames.end(); ++itr)
		{
			if (itr == frames.begin()) continue;

			std::map<int, KeyFrame*>::const_iterator prev = itr;
			--prev;
			if (prev->first == itr->first - 1) continue;

			float x = FRAME_GRID_WIDTH * (itr->first - 1 - 0.5f) - FRAME_END_RECT_WIDTH * 0.5f,
				y = FRAME_GRID_HEIGHT * (i + 1) - KEY_FRAME_RECT_Y_OFFSET - FRAME_END_RECT_HEIGHT * 0.5f;
			dc.SetPen(*wxBLACK_PEN);
			dc.SetBrush(*wxWHITE_BRUSH);
			dc.DrawRectangle(x, y, FRAME_END_RECT_WIDTH, FRAME_END_RECT_HEIGHT);
		}
	}
}

void KeysContentWidget::drawCurrPosFlag(wxBufferedPaintDC& dc)
{
	const float x = FRAME_GRID_WIDTH * (m_parent->getCurrPos() - 0.5f);
	dc.SetPen(DARK_RED);
	dc.DrawLine(x, 0, x, FRAME_GRID_HEIGHT * m_layersMgr->size());
}

void KeysContentWidget::drawSelected(wxBufferedPaintDC& dc)
{
	int row, col;
	m_parent->getSelectPos(row, col);
	if (row != -1 && col != -1)
	{
		dc.SetPen(wxPen(DARK_BLUE));
		dc.SetBrush(wxBrush(DARK_BLUE));
		dc.DrawRectangle(FRAME_GRID_WIDTH * col, FRAME_GRID_HEIGHT * row, FRAME_GRID_WIDTH, FRAME_GRID_HEIGHT);
	}
}

void KeysContentWidget::onCreateClassicTween(wxCommandEvent& event)
{
	KeyFrame* keyFrame = queryKeyFrameByPos();
	keyFrame->setClassicTween(true);
	Refresh();
}

void KeysContentWidget::onDeleteClassicTween(wxCommandEvent& event)
{
	KeyFrame* keyFrame = queryKeyFrameByPos();
	keyFrame->setClassicTween(false);
	Refresh();
}

void KeysContentWidget::onInsertFrame(wxCommandEvent& event)
{
}

void KeysContentWidget::onDeleteFrame(wxCommandEvent& event)
{
}

void KeysContentWidget::onInsertKeyFrame(wxCommandEvent& event)
{
	int row, col;
	m_parent->getSelectPos(row, col);
	if (row != -1 && col != -1)
	{
		KeyFrame* frame = new KeyFrame(col + 1);
		m_layersMgr->getLayer(m_layersMgr->size() - row - 1)->insertKeyFrame(col + 1, frame);
		m_parent->setCurrPos(col + 1);
		Refresh();
	}
}

void KeysContentWidget::onDeleteKeyFrame(wxCommandEvent& event)
{
	int row, col;
	m_parent->getSelectPos(row, col);
	m_layersMgr->getLayer(m_layersMgr->size() - row - 1)->deleteKeyFrame(col + 1);
	m_parent->setCurrPos(col + 1);
	Refresh();
}

void KeysContentWidget::onUpdateCreateClassicTween(wxUpdateUIEvent& event)
{
	KeyFrame* keyFrame = queryKeyFrameByPos();
	if (keyFrame)
	{
		if (keyFrame->hasClassicTween())
			event.Enable(false);
		else
			event.Enable(true);
	}
	else
	{
		event.Enable(false);
	}
}

void KeysContentWidget::onUpdateDeleteClassicTween(wxUpdateUIEvent& event)
{
	KeyFrame* keyFrame = queryKeyFrameByPos();
	if (keyFrame)
	{
		if (keyFrame->hasClassicTween())
			event.Enable(true);
		else
			event.Enable(false);
	}
	else
	{
		event.Enable(false);
	}
}

void KeysContentWidget::onUpdateInsertFrame(wxUpdateUIEvent& event)
{
	event.Enable(false);
}

void KeysContentWidget::onUpdateDeleteFrame(wxUpdateUIEvent& event)
{
	event.Enable(false);
}

void KeysContentWidget::onUpdateInsertKeyFrame(wxUpdateUIEvent& event)
{
//	event.Enable(false);
}

void KeysContentWidget::onUpdateDeleteKeyFrame(wxUpdateUIEvent& event)
{
	int row, col;
	m_parent->getSelectPos(row, col);
	if (row == -1 || col == -1) return;
	const bool isKey = m_layersMgr->getLayer(m_layersMgr->size() - row - 1)->isKeyFrame(col + 1);
	if (isKey) event.Enable(true);
	else event.Enable(false);
}