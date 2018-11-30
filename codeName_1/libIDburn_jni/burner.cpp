#include "IDburner.h"
#include <malloc.h>
#include <string.h>
#include <jni.h>
#include <android/log.h>
#include <stdio.h>

#undef JNIEXPORT
#define JNIEXPORT extern "C"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

JNIEXPORT jint JNICALL Java_com_sdmc_jni_IDburner_readMacAddr
(JNIEnv *env, jclass thiz, jbyteArray jmacAddr)
{
	const unsigned int MAC_LENGTH = 6;
	char macAddr[MAC_LENGTH+1] = {0};
	int result = readMacAddr(macAddr);
	LOGE("read macAddr is %02x:%02x:%02x:%02x:%02x:%02x" \
			,macAddr[0], macAddr[1], macAddr[2], \
			macAddr[3], macAddr[4], macAddr[5]);
	if(result == 0) {
		env->SetByteArrayRegion(jmacAddr, 0, MAC_LENGTH, (const jbyte *) macAddr);
	} else {
		LOGE("read macAddr fail!");
	}
	return result;
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_IDburner_writeMacAddr
(JNIEnv *env, jclass thiz, jbyteArray jmacAddr)
{
	const unsigned int MAC_LENGTH = 6;
	char macAddr[MAC_LENGTH] = {0};

	jbyte *tmpMacAddr = env->GetByteArrayElements(jmacAddr, 0);
	memcpy(macAddr, tmpMacAddr, MAC_LENGTH);
	LOGE("write macAddr %02x:%02x:%02x:%02x:%02x:%02x", \
			macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);

	int result = writeMacAddr(macAddr);
	env->ReleaseByteArrayElements(jmacAddr,tmpMacAddr,0);
	return result;
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_IDburner_readUserDeviceID
  (JNIEnv *env, jclass thiz, jbyteArray juserDeviceID)
{
	char userDeviceID[37] = {0};
	int arryLen = env->GetArrayLength(juserDeviceID);
	int result = readUserDeviceID(userDeviceID);
	LOGE("read sn len is %d" , arryLen);
	LOGE("read device id %s" , userDeviceID);
	if(result == 0) {
		env->SetByteArrayRegion(juserDeviceID, 0, arryLen, (const jbyte *) userDeviceID);
		LOGE("read sn success");
	} else {
		LOGE("read sn fail");
	}
	return result;
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_IDburner_writeUserDeviceID
  (JNIEnv *env, jclass thiz, jbyteArray juserDeviceID)
{
	int arryLen = env->GetArrayLength(juserDeviceID);
	const unsigned int SN_LENGTH = 37;
	char userDeviceID[SN_LENGTH] = {0};

	LOGE("write sn len is %d" , arryLen);
	jbyte *tmpUserDeviceID = env->GetByteArrayElements(juserDeviceID, 0);
	memcpy(userDeviceID, tmpUserDeviceID, arryLen);
	LOGE("write user device id %s", userDeviceID);

	int result = writeUserDeviceID(userDeviceID);
	env->ReleaseByteArrayElements(juserDeviceID, tmpUserDeviceID, 0);
	return result;
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_IDburner_readS2Activecode
  (JNIEnv *env, jclass thiz, jbyteArray jactiveCode)
{
	const unsigned int AC_LEN = 16;
	char activeCode[AC_LEN] = {0};
	int result = readActivecode(activeCode);
	LOGE("read active code is %02x:%02x", activeCode[0], activeCode[1]);
	if(result == 0) {
		env->SetByteArrayRegion(jactiveCode, 0, AC_LEN, (const jbyte *) activeCode);
		LOGE("read active code success");
	} else {
		LOGE("read active code fail");
	}
	return result;
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_IDburner_writeS2Activecode
  (JNIEnv *env, jclass thiz, jbyteArray jactiveCode)
{
	const unsigned int AC_LEN = 16;
	char activeCode[16] = {0};
	jbyte * tmpActiveConde = env->GetByteArrayElements(jactiveCode, NULL);
	memcpy(activeCode, tmpActiveConde, AC_LEN);

	int result = writeActivecode(activeCode);
	env->ReleaseByteArrayElements(jactiveCode, tmpActiveConde, 0);
	return result;
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_IDburner_readChipID
  (JNIEnv *env, jclass thiz, jbyteArray jchipID, jint len)
{
	char chipID[8] = {0};
	int result = readChipID(chipID);
	int valueLength =
	LOGE("read chipid: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x", \
				chipID[0], chipID[1], chipID[2], chipID[3], chipID[4], chipID[5],\
				chipID[6] ,chipID[7]);
	if(result == 0) {
		env->SetByteArrayRegion(jchipID, 0, len, (jbyte *) chipID);
		LOGE("readChipID success");
	} else {
		LOGE("readChipID fail");
	}
	return result;
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_IDburner_writeChipID
  (JNIEnv *env, jclass thiz, jbyteArray jchipID)
{
	const unsigned int CHIPID_LENGTH = 8;
	char chipID[CHIPID_LENGTH] = {0};
	jbyte *tmpChipID = env->GetByteArrayElements(jchipID, 0);

	memcpy(chipID, tmpChipID, CHIPID_LENGTH);
	LOGE("wired chipid: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x", \
			chipID[0], chipID[1], chipID[2], chipID[3], chipID[4], chipID[5],\
			chipID[6] ,chipID[7]);
	int result = writeChipID(chipID);
	env->ReleaseByteArrayElements(jchipID, tmpChipID, 0);
	return result;
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_IDburner_ddrTest
   (JNIEnv *env, jclass thiz, jint jdata)
{
    int count = jdata;
	int result = ddrTest(count);
	LOGE("Java_com_sdmc_jni_IDburner_ddrTest %02x", count);
	return result;
}
