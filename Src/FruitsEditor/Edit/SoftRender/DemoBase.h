#ifndef _FEDITOR_SOFT_RENDER_DEMO_BASE_H_
#define _FEDITOR_SOFT_RENDER_DEMO_BASE_H_
#include "Fruits3D/Fruits3D.h"

namespace FEDITOR
{
	namespace SOFT_RENDER
	{
		class Blackboard;

		class DemoBase
		{
		public:
			DemoBase(Blackboard* bb);
			virtual ~DemoBase();

			virtual void init() = 0;
			virtual void draw() = 0;

			F3D::f3Camera4& getCamera();

		protected:
			F3D::f3Camera4 m_camera;	

		}; // DemoBase
	}
}

#endif // _FEDITOR_SOFT_RENDER_DEMO_BASE_H_