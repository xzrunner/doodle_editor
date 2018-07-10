#ifndef _DEDITOR_MOTOX_ACTOR_EDIT_PACKAGE_IMPL_H_
#define _DEDITOR_MOTOX_ACTOR_EDIT_PACKAGE_IMPL_H_

#include "Task/AutomaticMerge/PackageFileIO.h"

namespace deditor
{
	namespace motox
	{
		class LibraryActorItem;

		class AEPackageImpl
		{
		public:
			AEPackageImpl(const LibraryActorItem& params);

			void loadFromTextFile(const wxString& filepath);
			void storeToBinaryFile(const wxString& filepath) const;

		private:
			void storeActorInfo(std::ofstream& fout) const;

		private:
			const LibraryActorItem& m_params;

			automatic_merge::PackageFileIO m_imgsPackage;

		}; // AEPackageImpl
	}
}

#endif // _DEDITOR_MOTOX_ACTOR_EDIT_PACKAGE_IMPL_H_