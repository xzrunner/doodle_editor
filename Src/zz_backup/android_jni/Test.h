#include "common/config.h"

#ifdef D2D_ANDROID_JNI

#ifndef _D2D_ANDROID_JNI_TEST_H_
#define _D2D_ANDROID_JNI_TEST_H_

#include <GLES/gl.h>

void init();
void resize(GLint w, GLint h);
void render();

#endif // _D2D_ANDROID_JNI_TEST_H_

#endif // D2D_ANDROID_JNI
