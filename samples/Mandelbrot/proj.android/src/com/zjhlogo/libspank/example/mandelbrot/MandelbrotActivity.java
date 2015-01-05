package com.zjhlogo.libspank.example.mandelbrot;
import android.os.Bundle;

import com.zjhlogo.libspank.SpankActivityBase;


public class MandelbrotActivity extends SpankActivityBase {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
	}
	
	static {
		System.loadLibrary("mandelbrot");
	}

}
