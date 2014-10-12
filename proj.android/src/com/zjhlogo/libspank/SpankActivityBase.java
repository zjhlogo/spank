package com.zjhlogo.libspank;
import android.app.Activity;
import android.content.res.AssetManager;
import android.os.Build;
import android.os.Bundle;
import android.view.View;


public class SpankActivityBase extends Activity {

	OpenGLES3View mView;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		initNativeAssetManager(getApplication().getAssets());
		
		mView = new OpenGLES3View(getApplication());
		setContentView(mView);

        // The UI options currently enabled are represented by a bitfield.
        // getSystemUiVisibility() gives us that bitfield.
        int uiOptions = mView.getSystemUiVisibility();
        int newUiOptions = uiOptions;
        // Navigation bar hiding:  Backwards compatible to ICS.
        if (Build.VERSION.SDK_INT >= 14) {newUiOptions |= View.SYSTEM_UI_FLAG_HIDE_NAVIGATION;}
 
        // Status bar hiding: Backwards compatible to Jellybean
        if (Build.VERSION.SDK_INT >= 16) {newUiOptions |= View.SYSTEM_UI_FLAG_FULLSCREEN;}
 
        // Immersive mode: Backward compatible to KitKat.
        // Note that this flag doesn't do anything by itself, it only augments the behavior
        // of HIDE_NAVIGATION and FLAG_FULLSCREEN.  For the purposes of this sample
        // all three flags are being toggled together.
        // Note that there are two immersive mode UI flags, one of which is referred to as "sticky".
        // Sticky immersive mode differs in that it makes the navigation and status bars
        // semi-transparent, and the UI flag does not get cleared when the user interacts with
        // the screen.
        if (Build.VERSION.SDK_INT >= 18) {newUiOptions |= View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY;}
 
        mView.setSystemUiVisibility(newUiOptions);
	}

	@Override
	protected void onPause() {
		super.onPause();
		mView.onPause();
	}

	@Override
	protected void onResume() {
		super.onResume();
		mView.onResume();
	}

	public static native void initNativeAssetManager(AssetManager assetManager);

}
