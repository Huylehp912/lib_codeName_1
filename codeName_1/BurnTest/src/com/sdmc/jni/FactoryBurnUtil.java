package com.sdmc.jni;

import com.sdmc.jni.FactoryBurn.BurnPermissionException;

public abstract class FactoryBurnUtil {
	
	public abstract int writeEthMAC(String ethMac)throws BurnPermissionException;
	
	public abstract String readEthMAC();
	
	public abstract boolean writeChipID(String chipID) throws BurnPermissionException;
	
	public abstract String readChipID(int len);
	
	public abstract String readChipID();
	
	public abstract int writeDeviceSN(String sn)throws BurnPermissionException;
	
	public abstract String readDeviceSN();

	public abstract int writeDeviceSN(String sn, int len)throws BurnPermissionException;
	
	public abstract String readDeviceSN(int snLen);
	
	public abstract int writeS2AC(final String acStr)throws BurnPermissionException;
    
	public abstract String readS2AC();

	public abstract int writeS2SN(final String snStr)throws BurnPermissionException;
    
	public abstract String readS2SN();

	public abstract int writeS2ChipID(final String cid)throws BurnPermissionException;
    
    public abstract String readS2ChipID();
	
    public abstract boolean checkRecoveryButton();
    
    public abstract int DDRTest(int testCount);
    
    @Deprecated
	public abstract int writeWiFiMAC(String wifiMAC)throws BurnPermissionException;
    
    @Deprecated
    public abstract String readWiFiMAC(String wifiModelType);
	
    @Deprecated
	public abstract boolean checkHDCPFileValid(String keyFilePath) throws BurnPermissionException;
	
    @Deprecated
	public abstract int getHDCPKeyUsedNum(String keyFilePath);
	
    @Deprecated
	public abstract int getHDCPKeyUnusedNum(String keyFilePath);
	
    @Deprecated
	public abstract int writeHDCPKey(String keyFilePath)throws BurnPermissionException;
	
    @Deprecated
	public abstract boolean isHDCPBurned();
	
    @Deprecated
	public abstract boolean writeDongleSecureKey(String secureKey)throws BurnPermissionException;
	
    @Deprecated
	public abstract String readDongleSecureKey(int len) throws BurnPermissionException;
	
    @Deprecated
	public abstract int writeMACID(String MACID)throws BurnPermissionException;
	
    @Deprecated
	public abstract String readMACID();
	
    @Deprecated
	public abstract String readDeviceID();
	
    @Deprecated
	public abstract int writeDeviceID(String deviceID);
}
