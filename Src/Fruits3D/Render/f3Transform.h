#ifndef _F3D_RENDER_TRANSFORM_H_
#define _F3D_RENDER_TRANSFORM_H_
#include "../Tools/Tools.h"
#include "../Tools/f3Types.h"

namespace F3D
{
	class f3Camera4;
	class f3RenderList4V1;
	class f3Object4V1;

	class f3Transform
	{
	public:
		static const uint32_t TRANSFORM_LOCAL_ONLY		= 0;
		static const uint32_t TRANSFORM_TRANS_ONLY		= 1;
		static const uint32_t TRANSFORM_LOCAL_TO_TRANS	= 2;

	public:
		static void transformMatrix(f3RenderList4V1& renderlist, const f3Matrix4X4& mt, uint32_t type);
		static void transformMatrix(f3Object4V1& object, const f3Matrix4X4& mt, uint32_t type, bool transform_basis);

		static void modelToWorld(f3Object4V1& object, uint32_t coord_select = TRANSFORM_LOCAL_TO_TRANS, bool use_matrix = false);
		static void modelToWorld(f3RenderList4V1& renderlist, const f3Vec4& world_pos, uint32_t coord_select = TRANSFORM_LOCAL_TO_TRANS, bool use_matrix = false);

		static void worldToCamera(const f3Camera4& cam, f3Object4V1& object);
		static void worldToCamera(const f3Camera4& cam, f3RenderList4V1& renderlist);

		static void cameraToPerspective(const f3Camera4& cam, f3Object4V1& object);
		static void cameraToPerspective(const f3Camera4& cam, f3RenderList4V1& renderlist);

		static void perspectiveToScreen(const f3Camera4& cam, f3Object4V1& object);
		static void perspectiveToScreen(const f3Camera4& cam, f3RenderList4V1& renderlist);

		static void cameraToScreen(const f3Camera4& cam, f3Object4V1& object);
		static void cameraToScreen(const f3Camera4& cam, f3RenderList4V1& renderlist);

	}; // f3Transform
}

#endif // _F3D_RENDER_TRANSFORM_H_