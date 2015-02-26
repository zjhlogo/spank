package com.zjhlogo.libspank.example.spine;
import android.os.Bundle;

import com.zjhlogo.libspank.SpankActivityBase;


public class SpineActivity extends SpankActivityBase {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
	}
	
	static {
		System.loadLibrary("app_spine");
	}

}
