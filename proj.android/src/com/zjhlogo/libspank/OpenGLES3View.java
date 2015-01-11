package com.zjhlogo.libspank;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;


public class OpenGLES3View extends GLSurfaceView {

	public static int TOUCH_MODE_UNKNOWN = 0;
	public static int TOUCH_MODE_SINGLE = 1;
	public static int TOUCH_MODE_MULTI = 2;
	
	Renderer mRenderer = null;
	double mDistBefore = 0.0;
	double mDistAfter = 0.0;
	
	int mPrevTouchMode = TOUCH_MODE_UNKNOWN;
	int mCurrTouchMode = TOUCH_MODE_UNKNOWN;
	boolean mSkipSingleTouch = false;
	
	private class Renderer implements GLSurfaceView.Renderer {

		boolean mRequestInitialize = false;
		boolean mInitialized = false;
		
		@Override
		public void onDrawFrame(GL10 gl) {
			if (mRequestInitialize) return;
			// step
			GameEntry.step();
		}

		@Override
		public void onSurfaceChanged(GL10 gl, int width, int height) {
			if (mRequestInitialize) {
				mRequestInitialize = false;
				
				GameEntry.initialize(width, height);
				mInitialized = true;
			}
			
			// resize
			GameEntry.resize(width, height);
		}

		@Override
		public void onSurfaceCreated(GL10 gl, EGLConfig config) {
			// initialize
			mRequestInitialize = true;
		}
		
		public boolean isInitialized() { return mInitialized;}
		
	}
	
	public OpenGLES3View(Context context) {
		super(context);
		setEGLConfigChooser(8, 8, 8, 0, 16, 0);
		setEGLContextClientVersion(2);
		mRenderer = new Renderer();
		setRenderer(mRenderer);
	}

	private int getNativeActionType(int actionType)
	{
		int formatActionType = actionType & 0xFF;
		switch (formatActionType)
		{
		case MotionEvent.ACTION_POINTER_DOWN:
		case MotionEvent.ACTION_DOWN: return GameEntry.TOUCH_BEGIN;
		case MotionEvent.ACTION_POINTER_UP:
		case MotionEvent.ACTION_UP: return GameEntry.TOUCH_END;
		case MotionEvent.ACTION_MOVE: return GameEntry.TOUCH_MOVE;
		case MotionEvent.ACTION_CANCEL: return GameEntry.TOUCH_CANCEL;
		}
		
		return GameEntry.TOUCH_UNKNOWN;
	}
	
	private void processSingleTouchEvent(MotionEvent event)
	{
		final int nativeActionType = getNativeActionType(event.getAction());
		if (nativeActionType == GameEntry.TOUCH_UNKNOWN) return;
		if (mSkipSingleTouch && nativeActionType != GameEntry.TOUCH_END) return;
		
		final float x = event.getX(0);
		final float y = event.getY(0);
		
		mSkipSingleTouch = false;
		this.queueEvent(new Runnable(){public void run() { GameEntry.touchEvent(nativeActionType, x, y);}});
	}
	
	private void processZoomEvent(MotionEvent event)
	{
		final int nativeActionType = getNativeActionType(event.getAction());
		if (nativeActionType == GameEntry.TOUCH_UNKNOWN) return;
		
		double distX = event.getX(1) - event.getX(0);
		double distY = event.getY(1) - event.getY(0);
		double dist = Math.sqrt(distX*distX + distY*distY);

		if (nativeActionType == GameEntry.TOUCH_BEGIN)
		{
			mDistBefore = dist;
			
			// send single touch end event when in zoom mode
			mSkipSingleTouch = true;
			
			final float x = event.getX(0);
			final float y = event.getY(0);

			this.queueEvent(new Runnable(){public void run() { GameEntry.touchEvent(GameEntry.TOUCH_END, x, y);}});

			return;
		}
		else if (nativeActionType == GameEntry.TOUCH_MOVE)
		{
			mDistAfter = dist;
			double distOffset = mDistAfter - mDistBefore;
			if (distOffset == 0.0) return;
			
			float zoom = (float)((-distOffset+mDistBefore) / mDistBefore);
			if (zoom < 0.1f) zoom = 0.1f;
			if (zoom > 10.0f) zoom = 10.0f;
			final float finalZoom = zoom;
			
			mDistBefore = mDistAfter;
			
			this.queueEvent(new Runnable(){public void run() { GameEntry.zoom(finalZoom);}});
		}
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {
		if (mRenderer == null || !mRenderer.isInitialized()) return true;
		
		mPrevTouchMode = mCurrTouchMode;
		int numPointers = event.getPointerCount();
		if (numPointers == 1)
		{
			mCurrTouchMode = TOUCH_MODE_SINGLE;
			processSingleTouchEvent(event);
		}
		else if (numPointers == 2)
		{
			mCurrTouchMode = TOUCH_MODE_MULTI;
			processZoomEvent(event);
		}
		
		return true;
	}

}
