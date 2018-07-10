#include "Camera.h"

#include <GLES/gl.h>

using namespace d2d;

float Camera::m_scale = 1.0f;

void Camera::translate(float x, float y)
{
	glTranslatef(x / m_scale, y / m_scale, 0.0f);
}

void Camera::zoomIn()
{
	m_scale *= 1.05f;
	glScalef(1.05f, 1.05f, 0.0f);
}

void Camera::zoomOut()
{
	m_scale *= 0.95f;
	glScalef(0.95f, 0.95f, 0.0f);
}