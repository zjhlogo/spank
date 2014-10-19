package com.zjhlogo.libspank;

public class GameEntry {
	public static native boolean initialize(int width, int height);
	public static native void terminate();
	public static native void resize(int width, int height);
	public static native void step();
}
