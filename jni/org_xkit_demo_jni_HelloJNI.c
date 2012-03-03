#include <jni.h>
#include <stdio.h>
#include "org_xkit_demo_jni_HelloJNI.h"

JNIEXPORT void JNICALL
Java_org_xkit_demo_jni_HelloJNI_print__(JNIEnv *env, jobject obj)
{
	printf("Hello JNI!\n");
	return;
}

JNIEXPORT void JNICALL
Java_org_xkit_demo_jni_HelloJNI_print__Ljava_lang_String_2(JNIEnv *env, jobject obj, jstring msg)
{
	const char *str = (*env) -> GetStringUTFChars(env, msg, 0);
	printf("%s\n", str);
	(*env) -> ReleaseStringUTFChars(env, msg, str);
	return;
}

JNIEXPORT jstring JNICALL
Java_org_xkit_demo_jni_HelloJNI_echo(JNIEnv *env, jobject obj, jint times,
		jstring msg)
{
	const char *str = (*env) -> GetStringUTFChars(env, msg, 0);

	char tmp[strlen(str) * times];

	int i, l;
	for(i = 0, l = strlen(str); i < times; i ++)
	{
		strcpy(tmp + l * i, str);
	}

	(*env) -> ReleaseStringUTFChars(env, msg, str);

	for (i = 0, l = strlen(tmp); i < l; i++)
	{
		*(tmp + i) = (char) toupper(*(tmp + i));
	}

	return (*env) -> NewStringUTF(env, tmp);
}

JNIEXPORT jintArray JNICALL
Java_org_xkit_demo_jni_HelloJNI_draw(JNIEnv *env, jobject obj, jintArray data)
{
	int *tmp = (*env) -> GetIntArrayElements(env, data, NULL);
	int i, l = (*env) -> GetArrayLength(env, data);
	jintArray result = (*env) -> NewIntArray(env, l);

	for(i = 0; i < l; i++)
	{
		*(tmp + i) = *(tmp + i) + 2;
	}
	(*env) -> SetIntArrayRegion(env, result, 0, l, tmp);
	(*env) -> ReleaseIntArrayElements(env, data, tmp, 0);
	return result;
}
