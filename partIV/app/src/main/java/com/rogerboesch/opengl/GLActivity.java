//
//  GLActivity.java
//
//  Created by Roger Boesch on 26.07.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

package com.rogerboesch.opengl;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.graphics.Color;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.widget.RelativeLayout;

import com.android.gl2jni.GL2JNIView;

public class GLActivity extends Activity {

    GL2JNIView mView;
    GLTouchView mLeftView;
    GLTouchView mRightView;

    private static final int TRANSPARENT = Color.argb(0,1,1,1);

        @Override protected void onCreate(Bundle icicle) {
            super.onCreate(icicle);

            setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);

            DisplayMetrics dm = new DisplayMetrics();
            this.getWindow().getWindowManager().getDefaultDisplay().getMetrics(dm);
            int width = dm.widthPixels;
            int height = dm.heightPixels;

            RelativeLayout layout = new RelativeLayout(this);
            layout.setLayoutParams(new RelativeLayout.LayoutParams(width, height));
            setContentView(layout);

            mView = new GL2JNIView(getApplication());
            mView.setLayoutParams(new RelativeLayout.LayoutParams(width, height));
            layout.addView(mView);

            mLeftView = new GLTouchView(this);
            mLeftView.tag = 1;
            mLeftView.setLayoutParams(new RelativeLayout.LayoutParams(width/2, height));
            mLeftView.setBackgroundColor(GLActivity.TRANSPARENT);
            layout.addView(mLeftView);

            RelativeLayout.LayoutParams rightLayoutParams = new RelativeLayout.LayoutParams(width/2, height);
            rightLayoutParams.leftMargin = width/2;
            mRightView = new GLTouchView(this);
            mRightView.tag = 2;
            mRightView.setLayoutParams(rightLayoutParams);
            mRightView.setBackgroundColor(GLActivity.TRANSPARENT);
            layout.addView(mRightView);
    }

    @Override protected void onPause() {
        super.onPause();
        mView.onPause();
    }

    @Override protected void onResume() {
        super.onResume();
        mView.onResume();
    }
}
