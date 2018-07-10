#ifndef _FEDITOR_SIMULATE_CLOTH_REGULAR_GRIDS_H_
#define _FEDITOR_SIMULATE_CLOTH_REGULAR_GRIDS_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	namespace SIMULATE_CLOTH
	{
		class Model;

		class RegularGrids
		{
		public:
			RegularGrids(Model& model);

			void loadFromFile(const std::string& filename);

			void build();

			void update();

		private:
			void initParams();
			void buildGround();
			void buildBodies();
			void buildNodes();
			void buildJoints();
			void buildDeformationSprite();
			void updateDeformationSprite();

		private:
			Model& m_model;

			size_t m_rowCount, m_colCount;
			float m_halfNodeEdge;
			bool m_isBoundStatic, isConnectCenter;
			float m_totWidth, m_totHeight;

		}; // RegularGrids
	}
}

#endif // _FEDITOR_SIMULATE_CLOTH_REGULAR_GRIDS_H_