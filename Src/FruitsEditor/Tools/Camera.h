#ifndef _FEDITOR_CAMERA_H_
#define _FEDITOR_CAMERA_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	class Camera
	{
	public:
		Camera(float scale = 1.0f);

		void onScale(float newScale, float cx, float cy);

		f2Vec2 transPosScrToPoj(int x, int y, int viewHeight) const;

		void setCenter(const f2Vec2& p, int viewWidth, int viewHeight);

		float getScale() const;
		float getLeft() const;
		float getLow() const;

	private:
		void reset(float scale = 1.0f);

	private:
		float m_xOffset, m_yOffset;
		float m_scale;

	}; // Camera

	inline Camera::Camera(float scale/* = 1.0f*/) 
	{ 
		reset(scale); 
	}

	inline void Camera::onScale(float newScale, float cx, float cy) 
	{
		m_xOffset = cx * m_scale + m_xOffset - cx * newScale;
		m_yOffset = cy * m_scale + m_yOffset - cy * newScale;
		m_scale = newScale;
	}

	inline f2Vec2 Camera::transPosScrToPoj(int x, int y, int viewHeight) const 
	{
		f2Vec2 p;
		const int view_x = x, view_y = viewHeight - y;
		p.x = view_x * m_scale + m_xOffset;
		p.y = view_y * m_scale + m_yOffset;
		return p;
	}

	inline void Camera::setCenter(const f2Vec2& p, int viewWidth, int viewHeight)
	{
		m_xOffset = p.x - viewWidth * 0.5f * m_scale;
		m_yOffset = p.y - viewHeight * 0.5f * m_scale;
	}

	inline float Camera::getScale() const
	{
		return m_scale;
	}

	inline float Camera::getLeft() const
	{
		return m_xOffset;
	}

	inline float Camera::getLow() const
	{
		return m_yOffset;
	}

	inline void Camera::reset(float scale/* = 1.0f*/) 
	{
		m_xOffset = m_yOffset = 0.0f;
		m_scale = scale;
	}
}

#endif // _FEDITOR_CAMERA_H_