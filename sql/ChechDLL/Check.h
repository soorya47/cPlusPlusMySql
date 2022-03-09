/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class Check */

#ifndef _Included_Check
#define _Included_Check
#ifdef __cplusplus
extern "C" {
#endif
	/*
	 * Class:     Check
	 * Method:    addRow
	 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z
	 */
	JNIEXPORT jboolean JNICALL Java_Check_addRow
	(JNIEnv*, jobject, jstring, jstring, jstring, jstring, jstring);

	/*
	 * Class:     Check
	 * Method:    removeRow
	 * Signature: (Ljava/lang/String;)Z
	 */
	JNIEXPORT jboolean JNICALL Java_Check_removeRow
	(JNIEnv*, jobject, jstring);

	/*
	 * Class:     Check
	 * Method:    updateRow
	 * Signature: (Ljava/lang/String;ILjava/lang/String;)Z
	 */
	JNIEXPORT jboolean JNICALL Java_Check_updateRow
	(JNIEnv*, jobject, jstring, jint, jstring);

	/*
	 * Class:     Check
	 * Method:    searchRow
	 * Signature: (ILjava/lang/String;)I
	 */
	JNIEXPORT jint JNICALL Java_Check_searchRow
	(JNIEnv*, jobject, jint, jstring);

#ifdef __cplusplus
}
#endif
#endif
