// #include "DemoRotateTriangle.h"
// 
// using namespace FEDITOR::SOFT_RENDER;
// 
// DemoRotateTriangle::DemoRotateTriangle(Blackboard* bb)
// {
// 
// }
// 
// void DemoRotateTriangle::init()
// {
// 
// }
// 
// void DemoRotateTriangle::draw()
// {
// 	//////////////////////////////////////////////////////////////////////////
// 
// 	static float angle_y = 0;
// 
// 	if (++angle_y >= 360) angle_y = 0;
// 
// 	f3Matrix4X4 mt_rot;
// 	mt_rot.buildYRotation(angle_y * TRANS_DEG_TO_RAD);
// 	f3Transform::transformMatrix(m_renderList, mt_rot, f3Transform::TRANSFORM_LOCAL_TO_TRANS);
// 
// 	f3Transform::modelToWorld(m_renderList, f3Vec4(0.0f, 0.0f, 0.0f, 1.0f), f3Transform::TRANSFORM_TRANS_ONLY);
// 
// 	m_f3camera.buildMatrixEuler(f3Camera4::CAM_ROT_SEQ_ZYX);
// 	f3Transform::worldToCamera(m_f3camera, m_renderList);
// 
// 	f3Transform::cameraToPerspective(m_f3camera, m_renderList);
// 
// 	f3Transform::perspectiveToScreen(m_f3camera, m_renderList);
// 
// 	//////////////////////////////////////////////////////////////////////////
// 
// 	f3Transform::modelToWorld(m_frame, f3Vec4(0.0f, 0.0f, 0.0f, 1.0f), f3Transform::TRANSFORM_LOCAL_TO_TRANS);
// 
// 	m_f3camera.buildMatrixEuler(f3Camera4::CAM_ROT_SEQ_ZYX);
// 	f3Transform::worldToCamera(m_f3camera, m_frame);
// 
// 	f3Transform::cameraToPerspective(m_f3camera, m_frame);
// 
// 	f3Transform::perspectiveToScreen(m_f3camera, m_frame);
// 
// 	//////////////////////////////////////////////////////////////////////////
// 
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	gluOrtho2D(
// 		m_camera.xOffset, 
// 		m_camera.xOffset + m_viewSize.viewWidth * m_camera.scale, 
// 		m_camera.yOffset,
// 		m_camera.yOffset + m_viewSize.viewHeight * m_camera.scale
// 		);
// 
// 	// 	glEnable(GL_ALPHA_TEST);
// 	// 	glAlphaFunc(GL_GREATER, 0);
// 
// 	glEnable(GL_BLEND);
// 	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
// 	glEnable(GL_DEPTH_TEST);
// 
// 	f3Render::draw(m_frame, true, 0.1f);
// 	f3Render::draw(m_renderList, true, 0.8f);
// 
// 	//	glDisable(GL_ALPHA_TEST);
// 
// 	glDisable(GL_BLEND);
// 	glDisable(GL_DEPTH_TEST);
// 
// 	// 	static long last_time = clock();
// 	// 	std::cout << clock() - last_time << std::endl;
// 	// 	last_time = clock();
// 
// 	//	if (cost < 30) Sleep(30 - cost);
// }