#include <jni.h>
#include <stdio.h>
#include "org_xkit_demo_jni_HelloJNI.h"

JNIEXPORT void JNICALL
Java_org_xkit_demo_jni_HelloJNI_print(JNIEnv *env, jobject obj)
{
	printf("Hello JNI!\n");
	return;
}
