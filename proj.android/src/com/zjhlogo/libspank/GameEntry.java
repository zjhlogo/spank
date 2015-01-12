package com.zjhlogo.libspank;

public class GameEntry {
	public static int TOUCH_UNKNOWN = 0;
	public static int TOUCH_BEGIN = 1;
	public static int TOUCH_END = 2;
	public static int TOUCH_MOVE = 3;
	public static int TOUCH_CANCEL = 4;
	
	public static native boolean initialize(int width, int height);
	public static native void terminate();
	public static native void resize(int width, int height);
	public static native void step();
	
	public static native void touchEvent(int actionType, float x, float y);
	public static native void zoom(float zoom);
	
}
