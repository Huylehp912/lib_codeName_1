package com.sdmc.jni;

import com.sdmc.jni.FactoryBurn.BurnPermissionException;
/**
 * @author lx
 *	for a20 and amlogic from idburner jni;
 */
public class FactoryBurnUtilImp extends FactoryBurnUtil{
    private static final String TAG = "FactoryBurnUtilImp";
    private static final String RECOVERY_DEVICE_NODE_ADDRESS = "/sys/class/saradc/ch0";
    private static final int MAX_CHIP_ID_LENGTH = 16;
	
    private static int defaultSNLength = 30;
    
	//sn with flag "NEW"(3bytes) ,after with sn length(2bytes), end with sn(sn length bytes) 
	private static int SN_LENGTH_INDEX_START = 3;     
	private static int SN_LENGTH_INDEX_END = 5;
	
	@Override
	public int writeEthMAC(String ethMac) throws BurnPermissionException {
		FactoryUtil.permissionVerify();
		byte[] ethMacBytes = BytesUtil.hexStringToBytes(ethMac);
		for(int i = 0; i < ethMacBytes.length; i++) {
            CoreSSLog.d(TAG, "ethMacBytes[" + i + "]= " + ethMacBytes[i]);
        }
		if (FactoryUtil.isMACValid(ethMac)) {
			return (IDburner.writeMacAddr(ethMacBytes) == FactoryBurn.REC_BURNER_SUCCESS) ? FactoryBurn.REC_BURNER_SUCCESS
					: FactoryBurn.ERROR_BURNER_FAILE;
		} else {
			return FactoryBurn.ERROR_IPUT_ID_INVALID;
		}
	}

	@Override
	public String readEthMAC() {
	    byte[] macBytes = new byte[6];
	    int result = IDburner.readMacAddr(macBytes);
	    CoreSSLog.d(TAG, "mac:" + macBytes[0]+ ":"+ macBytes[1]
                + ":"+ macBytes[2]+ ":"+ macBytes[3]+ ":"+ macBytes[4] + ":"+ macBytes[5]);
	    if(result == 0) {
	        StringBuilder stringBuilder = new StringBuilder("");
	        for (int i = 0; i < macBytes.length; i++) {
	            int v = macBytes[i] & 0xFF;
	            String hv = Integer.toHexString(v);
	            if (hv.length() < 2) {
	                stringBuilder.append(0);
	            }
	            stringBuilder.append(hv);
	            if(i == macBytes.length - 1) {
	            } else {
	                stringBuilder.append(":");
	            }
	        }
	        return stringBuilder.toString();   
	    } else {
	        return "";
	    }
	    
	}



	@Override
	public int writeDeviceSN(String sn, int standardSnLen) throws BurnPermissionException {
		FactoryUtil.permissionVerify();
		String deviceStr = FactoryUtil.getValidStrWrite(sn ,standardSnLen, defaultSNLength);
		if ((FactoryUtil.isDeviceSNValid(deviceStr, defaultSNLength))) {
			deviceStr = FactoryUtil.bin2hex(deviceStr);
			return (IDburner.writeUserDeviceID(BytesUtil.hexStringToBytes(deviceStr)) == FactoryBurn.REC_BURNER_SUCCESS)? 
					FactoryBurn.REC_BURNER_SUCCESS : FactoryBurn.ERROR_BURNER_FAILE;
		} else{ 
			return FactoryBurn.ERROR_IPUT_ID_INVALID;
		}
	}

	@Override
	public String readDeviceSN(int snLen) {
	    byte SNBytes[] = new byte[24];
	    int result = IDburner.readUserDeviceID(SNBytes);
		String burnerId = BytesUtil.bytes2HexString(SNBytes);
		burnerId = FactoryUtil.hex2bin(burnerId);

		if (burnerId.startsWith(FactoryUtil.SN_FLAG)) {
			int length = Integer.valueOf(burnerId.substring(SN_LENGTH_INDEX_START, 
					                                        SN_LENGTH_INDEX_END));
			burnerId = burnerId.substring(SN_LENGTH_INDEX_END, length + SN_LENGTH_INDEX_END);
		}else if (snLen > 0 && (snLen <= burnerId.length())) {
			burnerId = burnerId.substring(0, snLen);
		}
		return burnerId;
	}

	@Override
	public int writeDeviceSN(String sn) throws BurnPermissionException {
		return writeDeviceSN(sn, sn.length());
	}

	@Override
	public String readDeviceSN() {
		return readDeviceSN(defaultSNLength);
	}

	@Override
	public boolean checkHDCPFileValid(String keyFilePath) throws BurnPermissionException {
		FactoryUtil.permissionVerify();
		return false;
	}

	@Override
	public int getHDCPKeyUsedNum(String keyFilePath) {
		return -1;
	}

	@Override
	public int getHDCPKeyUnusedNum(String keyFilePath) {
		return -1;
	}

	@Override
	public int writeHDCPKey(String keyFilePath) throws BurnPermissionException {
		FactoryUtil.permissionVerify();
		return -1;
	}

	@Override
	public boolean isHDCPBurned() {
		return false;
	}

	@Override
	public boolean writeDongleSecureKey(String secureKey)throws BurnPermissionException {
		return false;
	}

	@Override
	public String readDongleSecureKey(int len) throws BurnPermissionException {
		return "";
	}

	@Override
	public int writeS2AC(String acStr) throws BurnPermissionException {
		FactoryUtil.permissionVerify();
        boolean valid = FactoryUtil.checkValid(acStr, 20, 10);
        if (valid) {
        	FactoryUtil. setACLen(acStr.length());
            int result = IDburner.writeS2Activecode(BytesUtil.hexStringToBytes(FactoryUtil.wrapMe(acStr, 20)));
            CoreSSLog.d(TAG,"writeS2AC result : " + result);
            if (result != 0) {
                return FactoryBurn.ERROR_BURNER_FAILE;
            } else {
                return FactoryBurn.REC_BURNER_SUCCESS;
            }
        } else {
            return FactoryBurn.ERROR_IPUT_ID_INVALID;
        }
	}

	@Override
	public int writeS2SN(String snStr) throws BurnPermissionException {
	    return writeDeviceSN(snStr, snStr.length());
    
	}

	@Override
	public int writeS2ChipID(String cid) throws BurnPermissionException {
		FactoryUtil.permissionVerify();
        boolean valid = FactoryUtil.checkValid(cid, 16, 10);
        if (valid) {
            String chipidString = FactoryUtil.wrapMe(cid, 16);
            CoreSSLog.d(TAG, "chipidString: " + chipidString);
            byte[] chipidByte = BytesUtil.hexStringToBytes(chipidString);
            
            CoreSSLog.d(TAG, "chipidByte: " + chipidByte.length);
            for(int i = 0; i < chipidByte.length; i++) {
                CoreSSLog.d(TAG, "chipidByte[" + i +"] :" + chipidByte[i]) ;
            }
            
            int result = IDburner.writeChipID(chipidByte);
            CoreSSLog.d(TAG, "result : " + result);
            if (result != 0) {
                return FactoryBurn.ERROR_BURNER_FAILE;
            } else {
                return FactoryBurn.REC_BURNER_SUCCESS;
            }
        } else {
            return FactoryBurn.ERROR_IPUT_ID_INVALID;
        }
	}
	
	@Override
	public String readS2AC() {
	    byte[] acBytes = new byte[16]; 
	    int result = IDburner.readS2Activecode(acBytes);
	    if(result == 0) {
	        return BytesUtil.bytes2HexString(acBytes).substring(0, FactoryUtil.getACLen());
	    }
	    return "";
	}
	
	@Override
	public String readS2SN() {
        return readDeviceSN(defaultSNLength);
	}

	@Override
	public String readS2ChipID() {
	    String chipID = "";
	    byte[] chipIdBytes = new byte[MAX_CHIP_ID_LENGTH/2];
	    int result = IDburner.readChipID(chipIdBytes,MAX_CHIP_ID_LENGTH/2);
	    if(result == 0) {
	        chipID = BytesUtil.bytes2HexString(chipIdBytes);
	    }
	    return chipID;
	}

	@Override
	public int DDRTest(int testCount) {
		return IDburner.ddrTest(testCount);
	}
	
	@Override
	public String readDeviceID() {
		return "";
	}

	@Override
	public int writeDeviceID(String deviceID) {
		return -1;
	}
	
    @Override
    public int writeMACID(String MACID) throws BurnPermissionException {
        return -1;
    }
	
    @Override
    public String readMACID() {
        return "";
    }
	
    @Override
    public int writeWiFiMAC(String wifiMAC) throws BurnPermissionException {
        return -1;
    }
	
    @Override
    public String readWiFiMAC(String wifiModelType) {
        return "";
    }

    @Override
    public boolean writeChipID(String chipID) throws BurnPermissionException {
        FactoryUtil.permissionVerify();
        CoreSSLog.d(TAG, "chip id length: " + chipID.length());
        if(chipID.length() > MAX_CHIP_ID_LENGTH ) {
            CoreSSLog.d(TAG, "chip id length invaild");
            return false;
        }
        boolean valid = FactoryUtil.checkValid(chipID, chipID.length());
        if (valid) {
            String chipidString = FactoryUtil.wrapMe(chipID, 16);
            CoreSSLog.d(TAG, "wrapMe chipidString: " + chipidString);
            byte[] chipidByte = BytesUtil.hexStringToBytes(chipidString);
            
            CoreSSLog.d(TAG, "chipidByte: " + chipidByte.length);
            for(int i = 0; i < chipidByte.length; i++) {
                CoreSSLog.d(TAG, "chipidByte[" + i +"] :" + chipidByte[i]) ;
            }
            
            int result = IDburner.writeChipID(chipidByte);
            CoreSSLog.d(TAG, "write ChipID result : " + result);
            if (result != 0) {
                return false;
            } else {
                return true;
            }
        } else {
            return false;
        }
    }

    @Override
    public String readChipID(int len) {
        String chipID = "";
        byte[] chipIdBytes = new byte[len/2];
        int result = IDburner.readChipID(chipIdBytes, len/2);
        
        for(int i= 0 ; i < len/2; i++) {
            CoreSSLog.d(TAG, "chipIdBytes[" + i + "] : " + chipIdBytes[i]);
        }
        
        if(result == 0) {
            chipID = BytesUtil.bytes2HexString(chipIdBytes);
        }
        return chipID;
    }

    @Override
    public boolean checkRecoveryButton() {
        String checkResult = FileAccessUtil.readStringFromFile(RECOVERY_DEVICE_NODE_ADDRESS);
        CoreSSLog.d(TAG, "checkResult: " + checkResult);
        return Integer.parseInt(checkResult, 10) >= 0 && Integer.parseInt(checkResult, 10) <= 512;
    }

    @Override
    public String readChipID() {
        return readChipID(MAX_CHIP_ID_LENGTH);
    }
}
