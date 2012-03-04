#include <stdio.h>
#include <string.h>
#include "org_xkit_demo_jni_HelloJNI.h"

_Bool vm_initialize(JNIEnv *env);

_Bool vm_finalize(JNIEnv *env);

void foo_test(char *greeting);

JNIEXPORT jboolean
JNICALL Java_org_xkit_demo_jni_HelloJNI_initNative(JNIEnv *env, jobject obj)
{
	return vm_initialize(env);
}

JNIEXPORT jboolean
JNICALL Java_org_xkit_demo_jni_HelloJNI_finalizeNative(JNIEnv *env, jobject obj)
{
	return vm_finalize(env);
}

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

JNIEXPORT void JNICALL
Java_org_xkit_demo_jni_HelloJNI_call(JNIEnv *env, jobject obj) {
	(*m_pJVM) -> AttachCurrentThread(m_pJVM, (void **) &env, NULL);

	char *hello = "Hello, I'm from C layer";

	(*env) -> CallVoidMethod(env, m_jni, m_vmSayHello, (*env) -> NewStringUTF(env, hello));
}

_Bool vm_initialize(JNIEnv *env)
{
	m_class = (*env) -> FindClass(env, "org/xkit/demo/jni/HelloJNI");

	jmethodID construction_id = (*env) -> GetMethodID(env, m_class, "<init>", "()V");

	m_vmSayHello = (*env) -> GetMethodID(env, m_class, "vmSayHello", "(Ljava/lang/String;)V");

	m_jni = (*env) -> NewObject(env, m_class, construction_id);

	(*env) -> GetJavaVM(env, &m_pJVM);

	return 1;
}

_Bool vm_finalize(JNIEnv *env)
{
	(*m_pJVM) -> DetachCurrentThread(m_pJVM);

	(*m_pJVM) -> DestroyJavaVM(m_pJVM);

	return 1;
}

/*
 * just for test
 */
void foo_test(char *greeting)
{
	printf("%s", greeting);
}
