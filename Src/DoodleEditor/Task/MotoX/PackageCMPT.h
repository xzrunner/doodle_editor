#ifndef _DEDITOR_MOTOX_PACKAGE_CMPT_H_
#define _DEDITOR_MOTOX_PACKAGE_CMPT_H_

#include <wxGUI/wxGUI.h>
#include <wx/dir.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;

		class PackageCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			PackageCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel);

		protected:
			virtual wxSizer* initLayout();

		private:
			void onPackageLevels(wxCommandEvent& event);
			void onPackageObstacles(wxCommandEvent& event);
			void onPackageMotorbike(wxCommandEvent& event);
			void onPackageHeader(wxCommandEvent& event);

			void onPackageTrackChains(const wxString& filepath);
			void onPackageSurface(const wxString& filepath);
			void onPackageTiles(const wxString& filepath);
			void onPackageObstacles(const wxString& filepath);

			void filterObstacleFiles(const wxString& dlg,
				std::vector<wxString>& meshFiles,
				std::vector<wxString>& combineFiles, 
				std::vector<wxString>& breakableFiles);

			static wxString createDstFilepath(const wxString& srcPath, 
				const wxString& filename);

		private:
			class DirTraverser : public wxDirTraverser
			{
			public:
				DirTraverser(wxArrayString& files) 
					: m_files(files) {}

				virtual wxDirTraverseResult OnFile(const wxString& filename)
				{
					m_files.Add(filename);
					return wxDIR_CONTINUE;
				}

				virtual wxDirTraverseResult OnDir(const wxString& dirname)
				{
					if (wxFileName(dirname).GetFullName() == wxT(".svn"))
						return wxDIR_IGNORE;
					else
						return wxDIR_CONTINUE;
				}

			private:
				wxArrayString& m_files;

			}; // DirTraverser

			class DirCurrTraverser : public wxDirTraverser
			{
			public:
				DirCurrTraverser(wxArrayString& files) 
					: m_files(files) {}

				virtual wxDirTraverseResult OnFile(const wxString& filename)
				{
					m_files.Add(filename);
					return wxDIR_CONTINUE;
				}

				virtual wxDirTraverseResult OnDir(const wxString& dirname)
				{
					return wxDIR_IGNORE;
				}

			private:
				wxArrayString& m_files;

			}; // DirCurrTraverser

			class FindMotoXTraverser : public wxDirTraverser
			{
			public:
				FindMotoXTraverser(wxString& file) 
					: m_file(file) {}

				virtual wxDirTraverseResult OnFile(const wxString& filename)
				{
					if (filename.find(TILES_FILTER) == wxNOT_FOUND)
						return wxDIR_CONTINUE;
					else
					{
						m_file = filename;
						return wxDIR_STOP;
					}
				}

				virtual wxDirTraverseResult OnDir(const wxString& dirname)
				{
					return wxDIR_CONTINUE;
				}

			private:
				wxString& m_file;

			}; // FindMotoXTraverser

		private:
			static const wxString TRACK_FILTER;
			static const wxString SURFACE_FILTER;
			static const wxString TILES_FILTER;
			static const wxString OBSTACLE_FILTER;

			static const wxString SURFACE_MERGED_FILE;
			static const wxString TILES_MERGED_FILE;
			static const wxString OBSTACLE_MERGED_FILE;
			static const wxString OBSTACLE_INFO_FILE;

		}; // PackageCMPT
	}
}

#endif // _DEDITOR_MOTOX_PACKAGE_CMPT_H_