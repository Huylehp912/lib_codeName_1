package com.sdmc.jni;

public class BytesUtil {
	
	public static void int2bytes(int n, byte[] bytes, int start){
		for(int i = 0; i < 4; i ++){
			bytes[i + start] = (byte)(n >> (24 - i * 8)); 
		}
	}
	
	public static void float2bytes(float x, byte[] bytes, int start) {  
		int l = Float.floatToIntBits(x);  
		for (int i = 0; i < 4; i++) {  
			bytes[start + i] = Integer.valueOf(l).byteValue();
			l = l >> 8;  
		}  
	}  
	
	public static void short2bytes(short s, byte[] bytes, int start){
		for(int i = 0; i < 2; i ++){
			bytes[i + start] = (byte)(s >> (8 - i * 8)); 
		}
	}
	
	public static int byte2int(byte b){
		return (int) (b & 0xff);
	}
	
	public static int bytes2int(byte[] b, int start){
		return (int)(((b[start] & 0xff) << 24) | ((b[start + 1] & 0xff) << 16)
				| ((b[start + 2] & 0xff) << 8) | ((b[start + 3] & 0xff) << 0));
	}
	
	public static void copyBytes(byte[] from, byte[] to, int start, int offset, int length) {
		for (int i = 0; i < length; i ++) {
			to[start + i] = from[i + offset];
		}
	}
	
	public static String byte2HexString(byte b) {
		int v = b & 0xFF;
		String s = String.format("%02x", v);
		return s;
	}
	
    public static String bytes2HexString(byte[] bt) {
        StringBuilder stringBuilder = new StringBuilder("");
        if (bt == null || bt.length <= 0) {
            return null;
        }
        for (int i = 0; i < bt.length; i++) {
            int v = bt[i] & 0xFF;
            String hv = Integer.toHexString(v);
            if (hv.length() < 2) {
                stringBuilder.append(0);
            }
            stringBuilder.append(hv);
        }
        return stringBuilder.toString();
    }
    
    /** 
     * Convert hex string to byte[] 
     * @param hexString the hex string 
     * @return byte[] 
     */  
    public static byte[] hexStringToBytes(String hexString) {  
        if (hexString == null || hexString.equals("")) {  
            return null;  
        }  
        hexString = hexString.toUpperCase();  
        int length = hexString.length() / 2;  
        char[] hexChars = hexString.toCharArray();  
        byte[] d = new byte[length];  
        for (int i = 0; i < length; i++) {  
            int pos = i * 2;  
            d[i] = (byte) (charToByte(hexChars[pos]) << 4 | charToByte(hexChars[pos + 1]));  
        }  
        return d;  
    }  
    
    /** 
     * Convert char to byte 
     * @param c char 
     * @return byte 
     */  
     private static byte charToByte(char c) {  
        return (byte) "0123456789ABCDEF".indexOf(c);  
    }  
}
