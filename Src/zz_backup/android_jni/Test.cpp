#include "Test.h"

#ifdef D2D_ANDROID_JNI

static float triangleCoords[] = 
{
	-0.5f, -0.25f, 0, //
	0.5f, -0.25f, 0, //
	0.0f, 0.559016994f, 0 //
};

static float angle = 0;

void init() 
{
	glClearColor(1.0f, 0.5f, 0.5f, 1.0f);
	glEnableClientState(GL_VERTEX_ARRAY);

}

void resize(GLint w, GLint h) 
{
	glViewport(0, 0, w, h);

	// make adjustments for screen ratio
	float ratio = w / (float) h;
	glMatrixMode(GL_PROJECTION); // set matrix to projection mode
	glLoadIdentity(); // reset the matrix to its default state
	glFrustumf(-ratio, ratio, -1, 1, -1, 7); // apply the projection matrix

}

void render() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set GL_MODELVIEW transformation mode
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // reset the matrix to its default state

	// When using GL_MODELVIEW, you must set the view point
	//  GLU.gluLookAt(gl, 0, 0, -5, 0f, 0f, 0f, 0f, 1.0f, 0.0f);

	// Create a rotation for the triangle
	angle += 3;
	if (angle > 360) {
		angle -= 360;
	}
	glRotatef(angle, 0.0f, 0.0f, 1.0f);

	// Draw the triangle
	glColor4f(0.63671875f, 0.76953125f, 0.22265625f, 0.0f);
	glVertexPointer(3, GL_FLOAT, 0, triangleCoords);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

#endif // D2D_ANDROID_JNI