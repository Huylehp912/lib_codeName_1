package com.sdmc.jni;

import com.sdmc.jni.FactoryBurn.BurnPermissionException;

public class FactoryUtil {
	public static long CMD_EXCUTE_TIME_OUT = 5000;
	
	private static final String KEY_VERIFIER = "sdmccoress1234";
	
	private static final String INVALID_MAC_SECOND_POSITION = "13579BDF";
	private static final String MAC_VALID_ZERO = "000000000000";
	private static final String MAC_VALID_FF = "ffffffffffff";
	public static final String SN_FLAG = "NEW";
	public static final int SN_FLAGED_LENGTH_MAX = 25;    //the max length of sn , which can set flag 
	public static final int SN_FLAG_LENGTH = 5;
	private static final int  MAC_VALID_LEN = 12;
	
	public static final String DEVICE_SN_EPPROM_DEFAULT_VALUED = "ffffffffffffffffffffffffffffffffffffffffffffffff";

    private static final String TAG = "FactoryUtil";
	private static String mVerifyKey;
	
	private static int mS2SNLen = 10;
	private static int nS2ACLen = 10;
	
	public static void setPermissionKey(String key){
		mVerifyKey = key;
	}
	
	/*public static String getVerifyKey(){
		return KEY_VERIFIER;
	}*/

	public static void permissionVerify() throws BurnPermissionException {
		if(!isVerifyKey(mVerifyKey)){
			throw new BurnPermissionException(mVerifyKey);
		}
	}
	
	public static boolean checkMACIDValid(String macid) {
		if(macid.length() == 32){
			return true;
		}		
		return false;
	}
	
	public final static boolean checkValid(final String str, final int length,
			final int... multiOpts) {
		if (str == null) {
			return false;
		} else {
			int len = str.length();
			boolean valid = false;
			valid = len == length;
			for (int l : multiOpts) {
				if (l == len) {
					valid = true;
					break;
				}
			}
			return valid;
		}
	}
	
	public final static String wrapMe(final String oriStr, final int maxLen) {
		if (oriStr == null) {
			return null;
		}
		int num = maxLen - oriStr.length();
		StringBuffer sb = new StringBuffer(oriStr);
		for (int i = 0; i < num; i++) {
			sb.append('0');
		}
		return sb.toString();
	}

	public synchronized static void setSNLen(int len) {
        mS2SNLen = len;
    }
    
	public static int getSNLen() {
        return mS2SNLen;
    }
    
	public synchronized static void setACLen(int len) {
        nS2ACLen = len;
    }
    
	public static int getACLen() {
        return nS2ACLen;
    }
	
	public static boolean isMACValid(String mac) {
		if(mac.equals("")){
			return false;
		}
		String macstr = mac.replaceAll(":", "");
		if(macstr.length()!= MAC_VALID_LEN){
			return false;
		}
		String secondInvalid = INVALID_MAC_SECOND_POSITION; // "13579bdf";
		String secondStr = macstr.substring(1, 2);
		String secondStrLow = secondStr.toLowerCase();
		String secondStrHigh = secondStr.toUpperCase();

		if (secondInvalid.contains(secondStrLow)
				|| secondInvalid.contains(secondStrHigh)) {
			return false;
		}

		if (macstr.equalsIgnoreCase(MAC_VALID_ZERO)
				|| macstr.equalsIgnoreCase(MAC_VALID_FF)) {
			return false;
		}
		
		for(int i = 0; i < macstr.length(); i ++){
			try {
				String signleStr = macstr.substring(i, i + 1);
				int value = -1;
				int singlehex = Integer.valueOf(bin2hex(signleStr.toUpperCase()));
				if(singlehex <= Integer.valueOf(bin2hex("9"))){
					value = singlehex - Integer.valueOf(bin2hex("0"));
				}
				if(singlehex >= Integer.valueOf(bin2hex("A"))){
					value = singlehex - Integer.valueOf(bin2hex("A")) + 10;
				}
				CoreSSLog.d("isMACValid ", "value = " + value);
				if((value < 0) || (value > 0xf)){
					return false;
				}
			} catch (NumberFormatException e) {
				CoreSSLog.d("NumberFormatException ", macstr);
				return false;
			}
		}
		return true;
	}
	
	public static String bin2hex(String bin) {
		bin = bin.toUpperCase();
		char[] digital = "0123456789ABCDEF".toCharArray();
		StringBuffer sb = new StringBuffer("");
		byte[] bs = bin.getBytes();
		int bit;
		for (int i = 0; i < bs.length; i++) {
			bit = (bs[i] & 0x0f0) >> 4;
			sb.append(digital[bit]);
			bit = bs[i] & 0x0f;
			sb.append(digital[bit]);
		}
		return sb.toString();
	}

	public static String hex2bin(String hex) {
		if(hex.equalsIgnoreCase(DEVICE_SN_EPPROM_DEFAULT_VALUED)){
			return "";
		}
		hex = hex.toUpperCase();
		String digital = "0123456789ABCDEF";
		char[] hex2char = hex.toCharArray();
		byte[] bytes = new byte[hex.length() / 2];
		int temp;
		for (int i = 0; i < bytes.length; i++) {
			temp = digital.indexOf(hex2char[2 * i]) * 16;
			temp += digital.indexOf(hex2char[2 * i + 1]);
			bytes[i] = (byte) (temp & 0xff);
		}
		return new String(bytes);
	}
	
	public static boolean isDeviceSNValid(String deviceStr, int defaultLen) {
		return (deviceStr != null && deviceStr.length() == defaultLen);
	}
	
	public static String getValidStrWrite(String deviceStr, int standardSnLen, int defaultLen) {
		String deviceValid = null;
		// add "0" at the end;
		if(standardSnLen > 0){
			int len = standardSnLen;
			if(standardSnLen <= SN_FLAGED_LENGTH_MAX){
				deviceStr = SN_FLAG + getValidStrLengthWrite(standardSnLen) + deviceStr;
				len = defaultLen - standardSnLen - SN_FLAG_LENGTH;
			}
		    if(len >= 0 ){
		    	deviceValid = addZeroForNum(deviceStr, len);
		    }
		}
		CoreSSLog.d("deviceValid", "deviceValid = " + deviceValid + " Length " + deviceValid.length());
		return deviceValid;
	}
	
	public static String getValidStrLengthWrite(int snLen){
	    String length = String.valueOf(snLen);
		if(snLen < 10){
	    	length = "0" + length;
	    }
		return length;
	}
	
	public static String addZeroForNum(String str, int strLength) {
		for (int i = 0 ; i < strLength; i ++  ) {
				StringBuffer sb = new StringBuffer();
				sb.append(str).append("0");//�Ҳ�0
				str = sb.toString();
		}
		return str;
	}
	

	private static boolean isVerifyKey(String key) {
		return KEY_VERIFIER.equals(key);
	}
}
