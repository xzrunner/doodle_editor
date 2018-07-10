#include "common/config.h"

#ifdef D2D_ANDROID_JNI

#include "Test.h"

#include <android/log.h>
#include <jni.h>

using namespace d2d;

#ifdef __cplusplus
extern "C" {
#endif

	void Java_com_zz_d2d_1jni_lib_JNIProxy_nativeSetPaths(JNIEnv* env, jclass thiz, jstring apkPath)
	{
		
	}

	void Java_com_zz_d2d_1jni_lib_JNIProxy_nativeTouchesBegin(JNIEnv* env, jclass thiz, jint id, jfloat x, jfloat y)
	{

	}

	void Java_com_zz_d2d_1jni_lib_JNIProxy_nativeTouchesEnd(JNIEnv* env, jclass thiz, jint id, jfloat x, jfloat y)
	{	

	}

	void Java_com_zz_d2d_1jni_lib_JNIProxy_nativeTouchesMove(JNIEnv* env, jclass thiz, jintArray ids, jfloatArray xs, jfloatArray ys)
	{

	}

	void Java_com_zz_d2d_1jni_lib_JNIProxy_nativeTouchesCancel(JNIEnv* env, jclass thiz, jintArray ids, jfloatArray xs, jfloatArray ys)
	{

	}

	jboolean Java_com_zz_d2d_1jni_lib_JNIProxy_nativeKeyDown(JNIEnv* env, jclass thiz, jint keyCode)
	{

	}

	void Java_com_zz_d2d_1jni_lib_JNIProxy_nativeRender(JNIEnv* env, jclass thiz)
	{
		render();
	}

	void Java_com_zz_d2d_1jni_lib_JNIProxy_nativeInit(JNIEnv* env, jclass thiz, jint w, jint h)
	{
		init();
		resize(w, h);
	}

	void Java_com_zz_d2d_1jni_lib_JNIProxy_nativeOnPause(JNIEnv* env, jclass thiz)
	{

	}

	void Java_com_zz_d2d_1jni_lib_JNIProxy_nativeOnResume(JNIEnv* env, jclass thiz)
	{

	}

#ifdef __cplusplus
}
#endif

//#endif // D2D_ANDROID_JNI

