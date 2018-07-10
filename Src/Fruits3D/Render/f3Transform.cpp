#include "f3Transform.h"
#include "f3Camera.h"
#include "f3RenderList.h"
#include "f3Object.h"

using namespace F3D;

void f3Transform::transformMatrix(f3RenderList4V1& renderlist, const f3Matrix4X4& mt, uint32_t type)
{
	switch (type)
	{
	case TRANSFORM_LOCAL_ONLY:
		for (size_t i = 0, n = renderlist.m_poly_ptrs.size(); i < n; ++i)
		{
			f3Poly4V1* poly = renderlist.m_poly_ptrs[i];
			if (!f3Poly4V1::isPolyValid(poly)) continue;

			for (size_t j = 0; j < 3; ++j)
			{
				f3Vec4 tmp;
				f3Mul(poly->m_vlist[j], mt, &tmp);
				poly->m_vlist[j] = tmp;
			}
		}
		for (size_t i = 0, n = renderlist.m_line_ptrs.size(); i < n; ++i)
		{
			f3Line4* line = renderlist.m_line_ptrs[i];
			for (size_t j = 0; j < 2; ++j)
			{
				f3Vec4 tmp;
				f3Mul(line->m_vlist[j], mt, &tmp);
				line->m_vlist[j] = tmp;
			}
		}
		break;
	case TRANSFORM_TRANS_ONLY:
		for (size_t i = 0, n = renderlist.m_poly_ptrs.size(); i < n; ++i)
		{
			f3Poly4V1* poly = renderlist.m_poly_ptrs[i];
			if (!f3Poly4V1::isPolyValid(poly)) continue;

			for (size_t j = 0; j < 3; ++j)
			{
				f3Vec4 tmp;
				f3Mul(poly->m_tvlist[j], mt, &tmp);
				poly->m_tvlist[j] = tmp;
			}
		}
		for (size_t i = 0, n = renderlist.m_line_ptrs.size(); i < n; ++i)
		{
			f3Line4* line = renderlist.m_line_ptrs[i];
			for (size_t j = 0; j < 2; ++j)
			{
				f3Vec4 tmp;
				f3Mul(line->m_tvlist[j], mt, &tmp);
				line->m_tvlist[j] = tmp;
			}
		}
		break;
	case TRANSFORM_LOCAL_TO_TRANS:
		for (size_t i = 0, n = renderlist.m_poly_ptrs.size(); i < n; ++i)
		{
			f3Poly4V1* poly = renderlist.m_poly_ptrs[i];
			if (!f3Poly4V1::isPolyValid(poly)) continue;

			for (size_t j = 0; j < 3; ++j)
			{
				f3Mul(poly->m_vlist[j], mt, &poly->m_tvlist[j]);
			}
		}
		for (size_t i = 0, n = renderlist.m_line_ptrs.size(); i < n; ++i)
		{
			f3Line4* line = renderlist.m_line_ptrs[i];
			for (size_t j = 0; j < 2; ++j)
			{
				f3Mul(line->m_vlist[j], mt, &line->m_tvlist[j]);
			}
		}
		break;
	}
}

void f3Transform::transformMatrix(f3Object4V1& object, const f3Matrix4X4& mt, uint32_t type, bool transform_basis)
{
	switch (type)
	{
	case TRANSFORM_LOCAL_ONLY:
		for (size_t i = 0, n = object.m_vlist_local.size(); i < n; ++i)
		{
			f3Vec4 tmp;
			f3Mul(object.m_vlist_local[i], mt, &tmp);
			object.m_vlist_local[i] = tmp;
		}
		break;
	case TRANSFORM_TRANS_ONLY:
		for (size_t i = 0, n = object.m_vlist_trans.size(); i < n; ++i)
		{
			f3Vec4 tmp;
			f3Mul(object.m_vlist_trans[i], mt, &tmp);
			object.m_vlist_trans[i] = tmp;
		}
		break;
	case TRANSFORM_LOCAL_TO_TRANS:
		for (size_t i = 0, n = object.m_vlist_trans.size(); i < n; ++i)
		{
			f3Mul(object.m_vlist_local[i], mt, &object.m_vlist_trans[i]);
		}
		break;
	}

	if (transform_basis)
	{
		f3Vec4 tmp;
		f3Mul(object.m_ux, mt, &tmp);
		object.m_ux = tmp;
		f3Mul(object.m_uy, mt, &tmp);
		object.m_uy = tmp;
		f3Mul(object.m_uz, mt, &tmp);
		object.m_uz = tmp;
	}
}

void f3Transform::modelToWorld(f3Object4V1& object, uint32_t coord_select/* = TRANSFORM_LOCAL_TO_TRANS*/, bool use_matrix/* = false*/)
{
	if (use_matrix)
	{
		f3Matrix4X4 mt;
		mt.set(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			object.m_world_pos.x, object.m_world_pos.y, object.m_world_pos.z, 1
			);
		transformMatrix(object, mt, coord_select, false);
	}
	else
	{
		if (coord_select == TRANSFORM_LOCAL_TO_TRANS) {
			for (size_t i = 0, n = object.m_vlist_local.size(); i < n; ++i)
				f3Add(object.m_vlist_local[i], object.m_world_pos, &object.m_vlist_trans[i]);
		} else {
			for (size_t i = 0, n = object.m_vlist_trans.size(); i < n; ++i)
				f3Add(object.m_vlist_trans[i], object.m_world_pos, &object.m_vlist_trans[i]);
		}
	}
}

void f3Transform::modelToWorld(f3RenderList4V1& renderlist, const f3Vec4& world_pos, uint32_t coord_select/* = TRANSFORM_LOCAL_TO_TRANS*/, bool use_matrix/* = false*/)
{
	if (use_matrix)
	{
		f3Matrix4X4 mt;
		mt.set(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			world_pos.x, world_pos.y, world_pos.z, 1
			);
		transformMatrix(renderlist, mt, coord_select);
	}
	else
	{
		if (coord_select == TRANSFORM_LOCAL_TO_TRANS) {
			for (size_t i = 0, n = renderlist.m_poly_ptrs.size(); i < n; ++i)
			{
				f3Poly4V1* poly = renderlist.m_poly_ptrs[i];
				if (!f3Poly4V1::isPolyValid(poly)) continue;

				for (size_t j = 0; j < 3; ++j)
					f3Add(poly->m_vlist[j], world_pos, &poly->m_tvlist[j]);
			}
			for (size_t i = 0, n = renderlist.m_line_ptrs.size(); i < n; ++i)
			{
				f3Line4* line = renderlist.m_line_ptrs[i];
				for (size_t j = 0; j < 2; ++j)
					f3Add(line->m_vlist[j], world_pos, &line->m_tvlist[j]);
			}
		} 
		else 
		{
			for (size_t i = 0, n = renderlist.m_poly_ptrs.size(); i < n; ++i)
			{
				f3Poly4V1* poly = renderlist.m_poly_ptrs[i];
				if (!f3Poly4V1::isPolyValid(poly)) continue;

				for (size_t j = 0; j < 3; ++j)
					f3Add(poly->m_tvlist[j], world_pos, &poly->m_tvlist[j]);
			}
			for (size_t i = 0, n = renderlist.m_line_ptrs.size(); i < n; ++i)
			{
				f3Line4* line = renderlist.m_line_ptrs[i];
				for (size_t j = 0; j < 2; ++j)
					f3Add(line->m_vlist[j], world_pos, &line->m_tvlist[j]);
			}
		}
	}
}

void f3Transform::worldToCamera(const f3Camera4& cam, f3Object4V1& object)
{
// 	//////////////////////////////////////////////////////////////////////////
// 	cam.buildMatrixEuler(f3Camera4::CAM_ROT_SEQ_ZYX);
// 	transformMatrix(object, cam.m_mt_camera, TRANSFORM_TRANS_ONLY, true);
// 	//////////////////////////////////////////////////////////////////////////

	for (size_t i = 0, n = object.m_vlist_trans.size(); i < n; ++i)
	{
		f3Vec4 tmp;
		f3Mul(object.m_vlist_trans[i], cam.m_mt_camera, &tmp);
		object.m_vlist_trans[i] = tmp;
	}
}

void f3Transform::worldToCamera(const f3Camera4& cam, f3RenderList4V1& renderlist)
{
// 	//////////////////////////////////////////////////////////////////////////
// 	cam.buildMatrixEuler(f3Camera4::CAM_ROT_SEQ_ZYX);
// 	transformMatrix(renderlist, cam.m_mt_camera, TRANSFORM_TRANS_ONLY);
// 	//////////////////////////////////////////////////////////////////////////

	for (size_t i = 0, n = renderlist.m_poly_ptrs.size(); i < n; ++i)
	{
		f3Poly4V1* poly = renderlist.m_poly_ptrs[i];
		if (!f3Poly4V1::isPolyValid(poly)) continue;

		for (size_t j = 0; j < 3; ++j)
		{
			f3Vec4 tmp;
			f3Mul(poly->m_tvlist[j], cam.m_mt_camera, &tmp);
			poly->m_tvlist[j] = tmp;
		}
	}
	for (size_t i = 0, n = renderlist.m_line_ptrs.size(); i < n; ++i)
	{
		f3Line4* line = renderlist.m_line_ptrs[i];
		for (size_t j = 0; j < 2; ++j)
		{
			f3Vec4 tmp;
			f3Mul(line->m_tvlist[j], cam.m_mt_camera, &tmp);
			line->m_tvlist[j] = tmp;
		}
	}
}

void f3Transform::cameraToPerspective(const f3Camera4& cam, f3Object4V1& object)
{
	for (size_t i = 0, n = object.m_vlist_trans.size(); i < n; ++i)
	{
		const float z = object.m_vlist_trans[i].z;		
		object.m_vlist_trans[i].x = cam.m_view_dist * object.m_vlist_trans[i].x / z;
		object.m_vlist_trans[i].y = cam.m_view_dist * object.m_vlist_trans[i].y * cam.m_aspect_ratio / z;
	}
}

void f3Transform::cameraToPerspective(const f3Camera4& cam, f3RenderList4V1& renderlist)
{
	for (size_t i = 0, n = renderlist.m_poly_ptrs.size(); i < n; ++i)
	{
		f3Poly4V1* poly = renderlist.m_poly_ptrs[i];
		if (!f3Poly4V1::isPolyValid(poly)) continue;

		for (size_t j = 0; j < 3; ++j)
		{
			const float z = poly->m_tvlist[j].z;
			poly->m_tvlist[j].x = cam.m_view_dist * poly->m_tvlist[j].x / z;
			poly->m_tvlist[j].y = cam.m_view_dist * poly->m_tvlist[j].y * cam.m_aspect_ratio / z;
		}
	}
	for (size_t i = 0, n = renderlist.m_line_ptrs.size(); i < n; ++i)
	{
		f3Line4* line = renderlist.m_line_ptrs[i];
		for (size_t j = 0; j < 2; ++j)
		{
			const float z = line->m_tvlist[j].z;
			line->m_tvlist[j].x = cam.m_view_dist * line->m_tvlist[j].x / z;
			line->m_tvlist[j].y = cam.m_view_dist * line->m_tvlist[j].y * cam.m_aspect_ratio / z;
		}
	}
}

void f3Transform::perspectiveToScreen(const f3Camera4& cam, f3Object4V1& object)
{
	const float alpha = 0.5f * cam.m_viewport_w - 0.5f,
		beta = 0.5f * cam.m_viewport_h - 0.5f;
	for (size_t i = 0, n = object.m_vlist_trans.size(); i < n; ++i)
	{
		object.m_vlist_trans[i].x = alpha + alpha * object.m_vlist_trans[i].x;
		object.m_vlist_trans[i].y = beta - beta * object.m_vlist_trans[i].y;
	}
}

void f3Transform::perspectiveToScreen(const f3Camera4& cam, f3RenderList4V1& renderlist)
{
	const float alpha = 0.5f * cam.m_viewport_w - 0.5f,
		beta = 0.5f * cam.m_viewport_h - 0.5f;

	for (size_t i = 0, n = renderlist.m_poly_ptrs.size(); i < n; ++i)
	{
		f3Poly4V1* poly = renderlist.m_poly_ptrs[i];
		if (!f3Poly4V1::isPolyValid(poly)) continue;

		for (size_t j = 0; j < 3; ++j)
		{
			poly->m_tvlist[j].x = alpha + alpha * poly->m_tvlist[j].x;
			poly->m_tvlist[j].y = beta - beta * poly->m_tvlist[j].y;
		}
	}
	for (size_t i = 0, n = renderlist.m_line_ptrs.size(); i < n; ++i)
	{
		f3Line4* line = renderlist.m_line_ptrs[i];
		for (size_t j = 0; j < 2; ++j)
		{
			line->m_tvlist[j].x = alpha + alpha * line->m_tvlist[j].x;
			line->m_tvlist[j].y = beta - beta * line->m_tvlist[j].y;
		}
	}
}

void f3Transform::cameraToScreen(const f3Camera4& cam, f3Object4V1& object)
{
	const float alpha = 0.5f * cam.m_viewport_w - 0.5f,
		beta = 0.5f * cam.m_viewport_h - 0.5f;
	for (size_t i = 0, n = object.m_vlist_trans.size(); i < n; ++i)
	{
		const float z = object.m_vlist_trans[i].z;		
		object.m_vlist_trans[i].x = cam.m_view_dist * object.m_vlist_trans[i].x / z;
		object.m_vlist_trans[i].y = cam.m_view_dist * object.m_vlist_trans[i].y * cam.m_aspect_ratio / z;

		object.m_vlist_trans[i].x = alpha + object.m_vlist_trans[i].x;
		object.m_vlist_trans[i].y = beta - object.m_vlist_trans[i].y;
	}
}

void f3Transform::cameraToScreen(const f3Camera4& cam, f3RenderList4V1& renderlist)
{
	const float alpha = 0.5f * cam.m_viewport_w - 0.5f,
		beta = 0.5f * cam.m_viewport_h - 0.5f;

	for (size_t i = 0, n = renderlist.m_poly_ptrs.size(); i < n; ++i)
	{
		f3Poly4V1* poly = renderlist.m_poly_ptrs[i];
		if (!f3Poly4V1::isPolyValid(poly)) continue;

		for (size_t j = 0; j < 3; ++j)
		{
			const float z = poly->m_tvlist[j].z;
			poly->m_tvlist[j].x = cam.m_view_dist * poly->m_tvlist[j].x / z;
			poly->m_tvlist[j].y = cam.m_view_dist * poly->m_tvlist[j].y * cam.m_aspect_ratio / z;

			poly->m_tvlist[j].x = alpha + poly->m_tvlist[j].x;
			poly->m_tvlist[j].y = beta - poly->m_tvlist[j].y;
		}
	}
	for (size_t i = 0, n = renderlist.m_line_ptrs.size(); i < n; ++i)
	{
		f3Line4* line = renderlist.m_line_ptrs[i];
		for (size_t j = 0; j < 2; ++j)
		{
			const float z = line->m_tvlist[j].z;
			line->m_tvlist[j].x = cam.m_view_dist * line->m_tvlist[j].x / z;
			line->m_tvlist[j].y = cam.m_view_dist * line->m_tvlist[j].y * cam.m_aspect_ratio / z;

			line->m_tvlist[j].x = alpha + line->m_tvlist[j].x;
			line->m_tvlist[j].y = beta - line->m_tvlist[j].y;
		}
	}
}