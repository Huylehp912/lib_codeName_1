package com.sdmc.jni;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class FileAccessUtil {
	
	public static boolean writeStringToFile(final String fileName, final String msg) {
		if (msg == null) {
			return false;
		}
		File file = new File(fileName);
		if (!file.exists()) {
			try {
				file.createNewFile();
			} catch (IOException e) {
				e.printStackTrace();
				return false;
			}
		}
		
		FileWriter fw = null;
		BufferedWriter writer = null;
		try {
			fw = new FileWriter(file);
			writer = new BufferedWriter(fw);
			writer.write(msg);
			writer.flush();
		} catch (Exception e) {
		} finally {
			try {
				writer.close();
			} catch (Exception e) {
			}
			try {
				fw.close();
			} catch (Exception e) {
			}
		}
		return true;
	}
	
	public static String readStringFromFile(String fileName){
		File file = new File(fileName);
		if (!file.exists()) {
			try {
				file.createNewFile();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		FileReader freader;
		try {
			freader = new FileReader(file);
			BufferedReader reader = new BufferedReader(freader);
			String line = reader.readLine();
			reader.close();
			return line;
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return null;
	}
}
