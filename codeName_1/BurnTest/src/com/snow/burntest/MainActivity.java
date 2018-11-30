package com.snow.burntest;
import com.sdmc.jni.FactoryBurn;
import com.sdmc.jni.FactoryBurn.BurnPermissionException;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

@SuppressLint("SdCardPath")
public class MainActivity extends Activity {
	private static final String TAG = "MainActivity";
	private static final String KEY_VERIFIER = "sdmccoress1234";

	private Button mWriteMac;
	private Button mWriteSn;
	
	private EditText mInput;
	private FactoryBurn mFactoryBurn;
	//private Burn mBurunTest;
    private TextView mSnText;
    private TextView mMacText;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		init();
	}
    
	private void init(){
		mInput = (EditText) findViewById(R.id.input);
		mWriteMac = (Button) findViewById(R.id.burn_mac);
		mWriteSn = (Button) findViewById(R.id.burn_sn);
		
		mSnText = (TextView) findViewById(R.id.sn);
		mMacText = (TextView) findViewById(R.id.mac);
		
		mFactoryBurn = new FactoryBurn();
		mFactoryBurn.setPermissionKey(KEY_VERIFIER);
		
		
		mWriteMac.setOnClickListener(mListener);
		mWriteSn.setOnClickListener(mListener);
		
		Log.i(TAG, "ori mac:" + mFactoryBurn.readEthMAC());
		Log.i(TAG, "ori sn:" + mFactoryBurn.readDeviceSN());
	}
	
	private OnClickListener mListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			int result = -1;
			Log.i(TAG, "input" + mInput.getText().toString());
			if( v.getId() == R.id.burn_mac){
				
				try {
					result = mFactoryBurn.writeEthMAC(mInput.getText().toString());
				} catch (BurnPermissionException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
				Log.i(TAG, "result1 = " + result);
			}else if( v.getId() == R.id.burn_sn) {
				try {
					result = mFactoryBurn.writeDeviceSN(mInput.getText().toString());
				} catch (BurnPermissionException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				Log.i(TAG, "result2 = " + result);
			}
			if(result == 0) {
				Toast.makeText(MainActivity.this, R.string.success, Toast.LENGTH_LONG).show();
			}else{
				Toast.makeText(MainActivity.this, R.string.error, Toast.LENGTH_LONG).show();
			}
			
			mSnText.setText("sn : " + mFactoryBurn.readDeviceSN());
			mMacText.setText("mac : " + mFactoryBurn.readEthMAC());
			mInput.setText("");
		}
	};
}
