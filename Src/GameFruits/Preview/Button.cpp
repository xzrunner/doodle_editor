#include "Button.h"
#include "Scene.h"
#include "MainDialog.h"

using namespace GAME_FRUITS::PREVIEW;

Button::Button(MainDialog* main, wxBitmap* bitmap, int x, int y)
{
	m_main = main;
	m_bitmap = bitmap;
	m_x = x;
	m_y = y;

	m_isDownChangeScene = false;
	m_toScene = NULL;

	m_isDownScaleSize = true;
	m_scaledBmp = NULL;
	m_isDrawScaled = false;

	m_isDownChangeImage = true;
	m_anotherBmp = NULL;
	m_isDrawAnother = false;
}

void Button::addChangeSceneAction(bool isDownChange, GAME_FRUITS::Scene* toScene)
{
	m_isDownChangeScene = isDownChange;
	m_toScene = toScene;
}

void Button::addScaleSizeAction(bool isDownChange, float scale)
{
	m_isDownScaleSize = isDownChange;
	wxImage image = m_bitmap->ConvertToImage();
	image.Rescale(image.GetWidth() * scale, image.GetHeight() * scale);
	m_scaledBmp = new wxBitmap(image);
}

void Button::addChangeImageAction(bool isDownChange, const wxString& bmpPath)
{
	m_isDownChangeImage = isDownChange;
	wxImage image;
	image.LoadFile(bmpPath);
	m_anotherBmp = new wxBitmap(image);
}

void Button::onPaint(wxDC& dc) const
{
	if (m_isDrawScaled && m_scaledBmp)
		dc.DrawBitmap(
		*m_scaledBmp,
		m_x - m_scaledBmp->GetWidth() * 0.5f,
		m_y - m_scaledBmp->GetHeight() * 0.5f
		);
	else if (m_isDrawAnother && m_anotherBmp)
		dc.DrawBitmap(
		*m_anotherBmp,
		m_x - m_bitmap->GetWidth() * 0.5f,
		m_y - m_bitmap->GetHeight() * 0.5f
		);
	else
		dc.DrawBitmap(
		*m_bitmap,
		m_x - m_bitmap->GetWidth() * 0.5f,
		m_y - m_bitmap->GetHeight() * 0.5f
		);
}

void Button::onMouseDown(int x, int y)
{
	if (m_isDownChangeScene && m_toScene && isContain(x, y))
		m_main->loadFromScene(m_toScene);
	if (m_isDownScaleSize && m_scaledBmp && isContain(x, y))
	{
		m_isDrawScaled = true;
		m_main->Refresh();
	}
	if (m_isDownChangeImage && m_anotherBmp && isContain(x, y))
	{
		m_isDrawAnother = true;
		m_main->Refresh();
	}
}

void Button::onMouseUp(int x, int y)
{
	if (!m_isDownChangeScene && isContain(x, y) && m_toScene)
		m_main->loadFromScene(m_toScene);
	if (m_scaledBmp)
	{
		m_isDrawScaled = false;
		m_main->Refresh();
	}
	if (m_anotherBmp)
	{
		m_isDrawAnother = false;
		m_main->Refresh();
	}
}

bool Button::isContain(int x, int y) const
{
	const float hWidth = m_bitmap->GetWidth() * 0.5f,
		hHeight = m_bitmap->GetHeight() * 0.5f;
	return abs(x - m_x) < hWidth && abs(y - m_y) < hHeight;
}

