#ifndef _DEDITOR_MOTOX_PACKAGE_MOTORBIKE_H_
#define _DEDITOR_MOTOX_PACKAGE_MOTORBIKE_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class PackageMotorbike
		{
		public:

			void package(const wxString& modelingPath) const;

		private:
			void packMergedAndBounding(std::ofstream& fout) const;
			void packPlayerInfo(std::ofstream& fout) const;
			void packMotorbikeInfo(std::ofstream& fout,
				const wxString& modelingPath) const;

		private:
			static const wxString MERGE_FILE;
			static const wxString ACTOR_FILE;
			static const wxString OUTPUT_FILE;

			static const wxString IMAGE_FILE_PATH[];

		}; // PackageMotorbike
	}
}

#endif // _DEDITOR_MOTOX_PACKAGE_MOTORBIKE_H_