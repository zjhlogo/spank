package com.zjhlogo.libspank;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLSurfaceView;


public class OpenGLES3View extends GLSurfaceView {

	public OpenGLES3View(Context context) {
		super(context);
		setEGLConfigChooser(8, 8, 8, 0, 16, 0);
		setEGLContextClientVersion(2);
		setRenderer(new Renderer());
	}

	private static class Renderer implements GLSurfaceView.Renderer {

		@Override
		public void onDrawFrame(GL10 gl) {
			// step
			GameEntry.step();
		}

		@Override
		public void onSurfaceChanged(GL10 gl, int width, int height) {
			// resize
			GameEntry.resize(width, height);
		}

		@Override
		public void onSurfaceCreated(GL10 gl, EGLConfig config) {
			// initialize
			GameEntry.initialize();
		}
		
	}
}
