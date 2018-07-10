#ifndef _DEDITOR_MOTOX_PACKAGE_OBSTACLES_H_
#define _DEDITOR_MOTOX_PACKAGE_OBSTACLES_H_

#include "Task/AutomaticMerge/FileAdapter.h"

namespace deditor
{
	namespace motox
	{
		class PackageObstacles
		{
		public:
			PackageObstacles(const wxString& mergeFile,
				const std::vector<wxString>& meshFiles,
				const std::vector<wxString>& combineFiles, 
				const std::vector<wxString>& breakableFiles);

			void package(const wxString& filepath) const;

		private:
			void packageMeshes(std::ofstream& fout) const;
			void packageCombines(std::ofstream& fout) const;
			void packageBreakables(std::ofstream& fout) const;

		private:
			automatic_merge::FileAdapter m_merged;

			const std::vector<wxString>& m_meshFiles;
			const std::vector<wxString>& m_combineFiles;
			const std::vector<wxString>& m_breakableFiles;

		}; // PackageObstacles
	}
}

#endif // _DEDITOR_MOTOX_PACKAGE_OBSTACLES_H_