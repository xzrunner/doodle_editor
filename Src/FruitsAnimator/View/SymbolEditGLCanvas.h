#ifndef _FRUITS_ANIMATOR_SYMBOL_EDIT_GL_CANVAS_H_
#define _FRUITS_ANIMATOR_SYMBOL_EDIT_GL_CANVAS_H_
#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class Symbol;

	class SymbolEditGLCanvas : public wxgui::GLCanvas
	{
	public:
		enum e_DrawMode
		{
			DrawInTexture,
			DrawInPixels
		};

		struct RenderSetting
		{
			bool drawPixelBound;
			bool drawOriginalSymbol;

			RenderSetting()
			{
				drawPixelBound = true;
				drawOriginalSymbol = true;
			}
		};

	public:
		SymbolEditGLCanvas(wxgui::EditPanel* parent, Symbol* symbol);

		void setDrawMode(e_DrawMode mode);

		wxgui::RawPixels* getRawPixels();
		wxgui::RawPixels::PixelBuf& getSelectedPixels();

		RenderSetting& getRenderSetting();

	protected:
		virtual void initGL();
		virtual void onDraw();

	private:
		Symbol* m_symbol;

		e_DrawMode m_drawMode;

		wxgui::RawPixels::PixelBuf m_selectedPixels;

		RenderSetting m_renderSetting;

	}; // SymbolEditGLCanvas
}

#endif // _FRUITS_ANIMATOR_SYMBOL_EDIT_GL_CANVAS_H_