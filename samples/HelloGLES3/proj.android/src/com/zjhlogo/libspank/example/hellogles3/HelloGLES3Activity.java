package com.zjhlogo.libspank.example.hellogles3;
import android.os.Bundle;

import com.zjhlogo.libspank.SpankActivityBase;


public class HelloGLES3Activity extends SpankActivityBase {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
	}
	
	static {
		System.loadLibrary("hello_gles3");
	}

}
