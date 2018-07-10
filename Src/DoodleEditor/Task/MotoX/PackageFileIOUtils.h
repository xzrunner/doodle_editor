#ifndef _DEDITOR_MOTOX_PACKAGE_FILE_IO_UTILS_H_
#define _DEDITOR_MOTOX_PACKAGE_FILE_IO_UTILS_H_

#include "Task/AutomaticMerge/FileAdapter.h"

namespace deditor
{
	namespace motox
	{
		class PackageFileIOUtils
		{
		public:
			PackageFileIOUtils(wxgui::MultiSpritesImpl* spritesImpl, 
				const automatic_merge::FileAdapter& merged, float gridWidth);
			PackageFileIOUtils(wxgui::MultiSpritesImpl* spritesImpl, 
				const automatic_merge::FileAdapter& merged, float gridWidth, 
				float leftmost, float rightmost);

			void storeToFileSingleLayer(const wxString& filepath, 
				const std::vector<wxgui::ISprite*>& sprites);
			void loadFromFileSingleLayer(const wxString& filepath);

			void storeToFileMultiLayers(const wxString& filepath,
				const std::vector<wxgui::Layer*>& layers);
			void loadFromFileMultiLayers(const wxString& filepath);

		private:
			typedef std::vector<wxgui::ISprite*> Grid;
			typedef std::vector<Grid> Grids;

			void initAllDataRegion(const std::vector<wxgui::ISprite*>& sprites);
			void initAllDataRegion(const std::vector<wxgui::Layer*>& layers);
			void dataRegionCombine(const std::vector<wxgui::ISprite*>& sprites);

			void initGrids(const std::vector<wxgui::ISprite*>& sprites,
				Grids& internal, Grids& intersect);

			void storeHeader(std::ofstream& fout);
			void storeData(std::ofstream& fout, const Grids& internal, const Grids& intersect);
			void storeData(std::ofstream& fout, const std::vector<wxgui::Layer*>& layers);
			void storeData(std::ofstream& fout, const std::vector<wxgui::ISprite*>& sprites);
			void storeDataCompress(std::ofstream& fout, const std::vector<wxgui::ISprite*>& sprites);
			static int compressAngle(float angle);
			static unsigned int compressType(wxgui::ISprite* sprite);

			void loadHeader(std::ifstream& fin);
			void loadData(std::ifstream& fin, Grids& internal, Grids& intersect);
			void loadData(std::ifstream& fin, std::vector<Grids>& internals, 
				std::vector<Grids>& intersects);
			void loadData(std::ifstream& fin, std::vector<wxgui::ISprite*>& sprites);

			void addToStagePanel(const Grids& internal, const Grids& intersect);

		private:
			static const int SPRITE_X_MIRROR	= 0x1;
			static const int SPRITE_Y_MIRROR	= 0x2;
			static const int NO_SCALE			= 0x4;

		private:
			wxgui::MultiSpritesImpl* m_spritesImpl;

			const automatic_merge::FileAdapter& m_merged;

			float m_gridWidth;
			float m_leftmost, m_rightmost;

		}; // PackageFileIOUtils
	}
}

#endif // _DEDITOR_MOTOX_PACKAGE_FILE_IO_UTILS_H_