package com.sdmc.jni;

public class IDburner {

/***********************************************
	***Function: read device id from hardware
	***input:
	***  data: out data buffer, at least 24Bytes, be sure it's clean
	***return:
	***  0: on success
	***  <0: on error
	************************************************/
public static native int readUserDeviceID(byte[] userDeviceID);

/***********************************************
***Function: write device id to hardware
***input:
***  data: in data buffer, 24Bytes
***return:
***  0: on success
***  <0: on error
************************************************/
public static native int writeUserDeviceID(byte[] data);

public static native int readMacAddr(byte[] macAddr);
public static native int writeMacAddr(byte[] data);

/***********************************************
***31-37 burn AC SN ChipID for S2 .
************************************************/
public static native int readS2Activecode(byte[] ac);
public static native int writeS2Activecode(byte[] ac);
public static native int readChipID(byte[] chipID, int len);
public static native int writeChipID(byte[] chipID);
public static native int ddrTest(int count);

static {
	System.loadLibrary("idburnerjni");
}
}
