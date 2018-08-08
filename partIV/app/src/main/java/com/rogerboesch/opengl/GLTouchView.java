//
//  TouchView.java
//
//  Created by Roger Boesch on 26.07.18.
//  Copyright © 2018 Roger Boesch. All rights reserved.
//

package com.rogerboesch.opengl;

import android.content.Context;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;

import com.android.gl2jni.GL2JNILib;

public class GLTouchView extends View {
    public int tag;
    private float mX;
    private float mY;

    public GLTouchView(Context context) {
        super(context);
    }
    public GLTouchView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    protected void onSizeChanged(int w, int h, int width, int height) {
        super.onSizeChanged(w, h, width, height);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        mX = event.getX();
        mY = event.getY();

        switch (event.getAction()){
            case MotionEvent.ACTION_DOWN:
                GL2JNILib.touch(tag, 1, (int)mX, (int)mY);
                break;
            case MotionEvent.ACTION_MOVE:
                break;
            case MotionEvent.ACTION_UP:
                GL2JNILib.touch(tag, 0, (int)mX, (int)mY);
                break;
            default:
                return false;
        }

        return true;
    }
}
