#ifndef _D2D_CAMERA_H_
#define _D2D_CAMERA_H_

namespace d2d
{
	class Camera
	{
	public:
		static void translate(float x, float y);
		static void zoomIn();
		static void zoomOut();

	private:
		static float m_scale;

	}; // Camera
}

#endif // _D2D_CAMERA_H_