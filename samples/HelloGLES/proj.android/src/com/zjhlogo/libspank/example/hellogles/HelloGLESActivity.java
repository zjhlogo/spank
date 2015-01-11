package com.zjhlogo.libspank.example.hellogles;
import android.os.Bundle;

import com.zjhlogo.libspank.SpankActivityBase;


public class HelloGLESActivity extends SpankActivityBase {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
	}
	
	static {
		System.loadLibrary("hello_gles");
	}

}
