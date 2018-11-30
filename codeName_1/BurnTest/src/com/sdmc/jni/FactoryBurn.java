package com.sdmc.jni;


public class FactoryBurn {
	/**
     * The result of write IDs on EPROM: write success.
     */
	public static final int REC_BURNER_SUCCESS = 0;
	
	/**
     * The result of write IDs on EPROM: write faile.
     */
	public static final int ERROR_BURNER_FAILE = -1;
	
	/**
     * The result of write IDs on EPROM: id is invalid.
     */
	public static final int ERROR_IPUT_ID_INVALID = -2;
	
	/**
     * {@link #readWiFiMAC(String wifiModelType)} value: the WIFI model type is 8188CUS.
     */
	public static final String WIFI_TYPE_CUS = "type_cus";
	
	/**
     * {@link #readWiFiMAC(String wifiModelType)} value: the WIFI model type is 8188EUS.
     */
	public static final String WIFI_TYPE_EUS = "type_eus";
	
	/**
     * {@link #readWiFiMAC(String wifiModelType)} value: the WIFI model type is unknown.
     */
	public static final String WIFI_TYPE_NO_SPECIAL = "type_nospecial";
	
	private FactoryBurnUtil mFactoryBurnUtil;
	
	public FactoryBurn(){
		mFactoryBurnUtil = new FactoryBurnUtilImp();
	}

	
	/**
	 * Burn the ethernet mac to EPROM, May be either
	 * @param ethMac The valid mac to burn.
	 * @return {@link #REC_BURNER_SUCCESS},{@link #ERROR_BURNER_FAILE},or {@link #ERROR_IPUT_ID_INVALID}
	 * @throws BurnPermissionException 
	 */
	public int writeEthMAC(String ethMac) throws BurnPermissionException{
		return mFactoryBurnUtil.writeEthMAC(ethMac);		
	}
	
	/**
	 * Read the ethernet mac from EPROM;
	 * @return ethernet mac.
	 */
	public String readEthMAC() {
		return mFactoryBurnUtil.readEthMAC();
	}
	
	/**
     * Burn the chip id to dm2016
     * @param chipID The valid chipid to burn.
     * @return true or false
     * @throws BurnPermissionException 
     */
	public boolean writeChipID(String chipID) throws BurnPermissionException {
	    return mFactoryBurnUtil.writeChipID(chipID);
	}
	
	/**
     * Read the chip id from dm2016;
     * @return chip id.
     */
	public String readChipID(int len) {
	    return mFactoryBurnUtil.readChipID(len);
	}
	
	 /**
     * Read the chip id from dm2016;
     * Defual len is 8
     * @return chip id.
     */
    public String readChipID() {
        return mFactoryBurnUtil.readChipID();
    }
	
	/**
	 * Burn the device sn to EPROM.
	 * @param sn the sn to burn on EPROM.
	 * @param len the target length to be burn.
	 * @return {@link #REC_BURNER_SUCCESS},{@link #ERROR_BURNER_FAILE},or {@link #ERROR_IPUT_ID_INVALID}
	 * @throws BurnPermissionException 
	 */
	public int writeDeviceSN(String sn, int len) throws BurnPermissionException{
		return mFactoryBurnUtil.writeDeviceSN(sn, len);
	}
	
	/**
	 * Read the device sn on  EPROM;
	 * @param snLen the sn max len = 24
	 * @return return device sn on EPROM;
	 */
	public String readDeviceSN(int snLen){
		return mFactoryBurnUtil.readDeviceSN(snLen);
	}
	
	/**
     * Burn the device sn to EPROM;
     * @param sn the  sn to burn on EPROM.
     * @return {@link #REC_BURNER_SUCCESS},{@link #ERROR_BURNER_FAILE},or {@link #ERROR_IPUT_ID_INVALID}
     * @throws BurnPermissionException 
     */
    public int writeDeviceSN(String sn) throws BurnPermissionException{
        return mFactoryBurnUtil.writeDeviceSN(sn);
    }
    
    /**
     * Read the device sn on  EPROM;
     * @return return device sn on EPROM, the sn length is 24 .
     */
    public  String readDeviceSN(){
        return mFactoryBurnUtil.readDeviceSN();
    }
    
    /**
     * burn ac for s2;
     * @param acStr the string to bur, length  10
     * @return {@link #REC_BURNER_SUCCESS},{@link #ERROR_BURNER_FAILE},or {@link #ERROR_IPUT_ID_INVALID}
     * @throws BurnPermissionException 
     */
    public int writeS2AC(final String acStr) throws BurnPermissionException{
        return mFactoryBurnUtil.writeS2AC(acStr);
    }
    
    /**
     * burn sn for s2;
     * @param snStr the string to burn,length 10
     * @return {@link #REC_BURNER_SUCCESS},{@link #ERROR_BURNER_FAILE},or {@link #ERROR_IPUT_ID_INVALID}
     * @throws BurnPermissionException 
     */
    public int writeS2SN(final String snStr) throws BurnPermissionException{
        return mFactoryBurnUtil.writeS2SN(snStr);
    }
    
    /**
     * burn cid for s2;
     * @param cid the string to burn ,length 16;
     * @return {@link #REC_BURNER_SUCCESS},{@link #ERROR_BURNER_FAILE},or {@link #ERROR_IPUT_ID_INVALID}
     * @throws BurnPermissionException 
     */
    public int writeS2ChipID(final String cid) throws BurnPermissionException {
        return mFactoryBurnUtil.writeS2ChipID(cid);
    }
    
    /**
     * Read the device S2AC on  EPROM;
     * @return return device S2AC on EPROM;
     */
    public String readS2AC(){
        return mFactoryBurnUtil.readS2AC();
    }

    /**
     * Read the device S2SN on  EPROM;
     * @return return device S2SN  on EPROM;
     */
    public String readS2SN(){
        return mFactoryBurnUtil.readS2SN();
    }
    
    /**
     * Read the device S2ChipID on  EPROM;
     * @return return device S2ChipID  on EPROM;
     */
    public String readS2ChipID() {
        return mFactoryBurnUtil.readS2ChipID();
    }
    
    public boolean checkRecoveryButton() {
        return mFactoryBurnUtil.checkRecoveryButton();
    } 
    
	/**
     * Burn the wifi mac to the wifi model,before burn the wifi model should be open.
     * @param wifiMAC the valid mac to burn to wifi model;
     * @return {@link #REC_BURNER_SUCCESS},{@link #ERROR_BURNER_FAILE},or {@link #ERROR_IPUT_ID_INVALID}
     * @throws BurnPermissionException 
     */
    @Deprecated
    public int writeWiFiMAC(String wifiMAC) throws BurnPermissionException{
        return mFactoryBurnUtil.writeWiFiMAC(wifiMAC);
    }
    
    /**
     * Read the wifi mac from wifi model,before read the wifi, model should be open.
     * @param wifiModelType wifiModel type.
     * @return wifi mac 
     */
    @Deprecated
    public String readWiFiMAC(String wifiModelType) {
        return mFactoryBurnUtil.readWiFiMAC(wifiModelType);
    }
	
	/**
	 * Check the DHCP file is valid
	 * @param keyFilePath the key file path;
	 * @return return true if valid else return false;
	 * @throws BurnPermissionException 
	 */
	@Deprecated
	public boolean checkHDCPFileValid(String keyFilePath) throws BurnPermissionException{
		return mFactoryBurnUtil.checkHDCPFileValid(keyFilePath);
	}
	
	/**
	 * Get DHCP key already use num on the key file;
	 * @param keyFilePath the key file path;
	 * @return return the have used key num;
	 */
	@Deprecated
	public int getHDCPKeyUsedNum(String keyFilePath){
		return mFactoryBurnUtil.getHDCPKeyUsedNum(keyFilePath);
	}
	
	/**
	 * Get DHCP key already unuse num on the key file;
	 * @param keyFilePath the keyfile path;
	 * @return return the unused key num;
	 */
	@Deprecated
	public int getHDCPKeyUnusedNum(String keyFilePath){
		return mFactoryBurnUtil.getHDCPKeyUnusedNum(keyFilePath);
	}
	
	/**
	 * Burn the DHCP key on EPROM.
	 * @param keyFilePath the keyfile path;
	 * @return {@link #REC_BURNER_SUCCESS},{@link #ERROR_BURNER_FAILE},or {@link #ERROR_IPUT_ID_INVALID}
	 * @throws BurnPermissionException 
	 */
	
	@Deprecated
	public int writeHDCPKey(String keyFilePath) throws BurnPermissionException{
		return mFactoryBurnUtil.writeHDCPKey(keyFilePath);
	}
	
	/**
	 * Get the current DHCP burn status
	 * @return return true if HDCP key have burned, else return false;
	 */
	
	@Deprecated
	public boolean isHDCPBurned(){
		return mFactoryBurnUtil.isHDCPBurned();
	}
	
	/**
	 * Write the dongle secure key on EPROM
	 * @param secureKey secure key to be burned
	 * @return return true if burn success ,else return false
	 * @throws BurnPermissionException 
	 */
	@Deprecated
	public boolean writeDongleSecureKey(String secureKey) throws BurnPermissionException{
		return mFactoryBurnUtil.writeDongleSecureKey(secureKey);
	}
	
	/**
	 * Get current dongle secure key on EPROM
	 * @param len the secure key length 
	 * @return return the secure key
	 * @throws BurnPermissionException 
	 */
	@Deprecated
	public String readDongleSecureKey(int len) throws BurnPermissionException{
		return mFactoryBurnUtil.readDongleSecureKey(len);
	}
	
	/**
	 * burn id for linglong customer;
	 * @param MACID the default len is 32
	 * @return {@link #REC_BURNER_SUCCESS},{@link #ERROR_BURNER_FAILE},or {@link #ERROR_IPUT_ID_INVALID}
	 * @throws BurnPermissionException 
	 */
	@Deprecated
	public int writeMACID(String MACID) throws BurnPermissionException{
		return -1;
	}
	
	/**
	 * Read the device MACID on  EPROM;
	 * @return return device MACID  on EPROM;
	 */
	
	@Deprecated
	public String readMACID(){
		return "";
	}
	
	/**
	 * Read the device ID, the device ID is special IMEI for customer;
	 * @return return device ID;
	 */
	@Deprecated
	public String readDeviceID(){
		return mFactoryBurnUtil.readDeviceID();
	}
	
	/**
	 * Burn the device ID, the device ID is special IMEI for customer.
	 * @param deviceID the device ID to burn.
	 * @return {@link #REC_BURNER_SUCCESS},{@link #ERROR_BURNER_FAILE},or {@link #ERROR_IPUT_ID_INVALID}
	 * @throws BurnPermissionException 
	 */
	@Deprecated
	public int writeDeviceID(String deviceID) throws BurnPermissionException {
		return mFactoryBurnUtil.writeDeviceID(deviceID);
	}
	
	/**
	 * m3 hkbn secure key burn,no completetion now
	 * @return 0
	 */
	@Deprecated
	public static int burnerSecureKey(){
		return 0;
	}
	
	/**
	 * m3 hkbn check secure key burn,no completetion now
	 * @return 0
	 */
	@Deprecated
	public static int checkSecureKey(){
		return -1;
	}
	
	/**
	 * Test system ddr.
	 * @param testCount DDR test count
	 * @return {@link #REC_BURNER_SUCCESS},or {@link #ERROR_BURNER_FAILE}
	 */
	public int DDRTest(int testCount){
		return mFactoryBurnUtil.DDRTest(testCount);
	}
	
	/**
	 * Before write any thing on EPROM ,should call this key verify,or throw exception
	 * @param key the verify key
	 */
	public void setPermissionKey(String key){
		FactoryUtil.setPermissionKey(key);
	}
	
	/**
	 * Get the burn permission exception
	 * @author lx
	 */
	public static class BurnPermissionException extends Exception {
		private static final long serialVersionUID = 1L;
		private String mMsg;

	    public BurnPermissionException(String key) {
			mMsg = key +  "is not avaible to get the burn permission";
		}
		
		@Override
		public void printStackTrace() {
			CoreSSLog.e("msg = ", mMsg);
		}
	}
}
