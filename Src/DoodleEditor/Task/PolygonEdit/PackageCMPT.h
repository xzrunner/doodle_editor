#ifndef _DEDITOR_POLYGON_EDIT_PACKAGE_CMPT_H_
#define _DEDITOR_POLYGON_EDIT_PACKAGE_CMPT_H_

#include "Task/AutomaticMerge/FileAdapter.h"

namespace deditor
{
	namespace polygon_edit
	{
		class StagePanel;

		class PackageCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			PackageCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel);

			static void packageToBin(const wxString& src, 
				const wxString& mergeFile, const wxString& motoxFile,
				const wxString& dst);

		protected:
			virtual wxSizer* initLayout();

		private:
			void onStoreToBinFile(wxCommandEvent& event);
			void onLoadFromBinFile(wxCommandEvent& event);
			void onLoadMergedFile(wxCommandEvent& event);
			void onLoadMotoXFile(wxCommandEvent& event);
			void onStoreToTextFile(wxCommandEvent& event);

			void onChangeTriangulateType(wxCommandEvent& event);
			void onSetGridWidth(wxSpinEvent& event);

			void triangulateAllPolygons();

			static wxgui::Layer* loadMotoXLayer(const wxString& filepath);

		private:
			class GetTotAABBVisitor : public IVisitor
			{
			public:
				GetTotAABBVisitor(f2AABB& aabb) : m_aabb(aabb) {}

				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				f2AABB& m_aabb;

			}; // GetAllBoundingVisitor

			class TriangulateVisitor : public IVisitor
			{
			public:
				TriangulateVisitor(wxgui::Math::TriangulateType type, const std::vector<f2Vec2>& lines)
					: m_type(type), m_lines(lines) {}

				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				wxgui::Math::TriangulateType m_type;
				const std::vector<f2Vec2>& m_lines;

			}; // TriangulateVisitor

		private:
			StagePanel* m_editPanel;

			wxRadioBox* m_typeChoice;
			wxSpinCtrl* m_widthSpin;

			automatic_merge::FileAdapter m_merged;

		}; // PackageCMPT
	}
}

#endif // _DEDITOR_POLYGON_EDIT_PACKAGE_CMPT_H_