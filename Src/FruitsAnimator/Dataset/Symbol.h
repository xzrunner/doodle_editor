#ifndef _FRUITS_ANIMATOR_SYMBOL_H_
#define _FRUITS_ANIMATOR_SYMBOL_H_

#include "WholeSkeleton.h"

#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class Mesh;
	class PartSkeleton;

	class Symbol : public wxgui::Symbol
	{
	public:
		Symbol();
		Symbol(const wxString& filepath);
		virtual ~Symbol();
		
		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

// 		void loadFromModifiedData();
		void replaceBySelectedPixels(const wxgui::RawPixels::PixelBuf& selected);

		wxgui::RawPixels* getRawPixels();

		Mesh* getMesh();
		Mesh* createMesh();

		PartSkeleton* getSkeleton();
		PartSkeleton* createSkeleton();

		WholeSkeleton::Body* getSkeletonBody();
		WholeSkeleton::Body* createSkeletonBody();

	private:
		void clear();

	private:
		wxgui::RawPixels* m_pixelData;

		Mesh* m_mesh;
		PartSkeleton* m_skeleton;
		WholeSkeleton::Body* m_skeletonBody;

	}; // Symbol
}

#endif // _FRUITS_ANIMATOR_SYMBOL_H_