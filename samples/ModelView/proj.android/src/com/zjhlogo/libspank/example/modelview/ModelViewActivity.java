package com.zjhlogo.libspank.example.modelview;
import android.os.Bundle;

import com.zjhlogo.libspank.SpankActivityBase;


public class ModelViewActivity extends SpankActivityBase {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
	}
	
	static {
		System.loadLibrary("model_view");
	}

}
