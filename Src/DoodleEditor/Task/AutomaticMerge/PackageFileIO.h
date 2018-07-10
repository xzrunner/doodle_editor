#ifndef _DEDITOR_AUTOMATIC_MERGE_PACKAGE_FILE_IO_H_
#define _DEDITOR_AUTOMATIC_MERGE_PACKAGE_FILE_IO_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace automatic_merge
	{
		class StagePanel;
		class FileAdapter;

		class PackageFileIO
		{
		public:
			PackageFileIO(bool hasBoundInfo);
			PackageFileIO(StagePanel* stagePanel, bool hasBoundInfo);
			~PackageFileIO();

			void storeToFile(const wxString& filepath) const;
			void storeToFile(std::ofstream& fout) const;
			void storeToFileOrder(std::ofstream& fout, const std::vector<wxString>& order) const;

			void loadFromTextFile(const wxString& filepath);

			static void storeToFileInOrder();

		private:
			static void storeBoundaryInfo(std::ofstream& fout, const wxString& filepath);

			static void storePolygonInfo(std::ofstream& fout, const wxString& filepath);
			static void storeCircleInfo(std::ofstream& fout, const wxString& filepath);

		private:
			StagePanel* m_stagePanel;

			bool m_hasBoundInfo;

			FileAdapter* m_adapter;

		}; // PackageFileIO
	}
}

#endif // _DEDITOR_AUTOMATIC_MERGE_PACKAGE_FILE_IO_H_