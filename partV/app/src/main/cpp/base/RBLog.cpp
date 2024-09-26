//
//  RBLog.cpp
//
//  The OpenGL Tutorial
//  This code was written as part of a tutorial at https://medium.com/@rogerboesch/
//
//  Created by Roger Boesch on 07/30/2018.
//
//  DISCLAIMER:
//  The intention of this tutorial is not to always write the best possible code but
//  to show different ways to create a game or app that even can be published.
//  I will also refactor a lot during the tutorial and improve things step by step
//  or even show completely different approaches.
//
//  Feel free to use the code in the way you want :)
//

#include "RBLog.hpp"

#include <android/log.h>

void rb_message(const char* msg, int severity) {
	__android_log_print(severity == 1 ? ANDROID_LOG_ERROR : ANDROID_LOG_DEBUG, (const char*)"rblog", "%s", msg);
}

void rb_message_str1(const char* msg, const char* str1, int severity) {
	__android_log_print(severity == 1 ? ANDROID_LOG_ERROR : ANDROID_LOG_DEBUG,  (const char*)"rblog", "%s: %s", msg, str1);
}

void rb_message_num1(const char* msg, int num1, int severity) {
	__android_log_print(severity == 1 ? ANDROID_LOG_ERROR : ANDROID_LOG_DEBUG, (const char*)"rblog", "%s: %d", msg, num1);
}

void rb_message_2d(const char* msg, float x, float y, int severity) {
	__android_log_print(severity == 1 ? ANDROID_LOG_ERROR : ANDROID_LOG_DEBUG, (const char*)"rblog", "%s: %f, %f", msg, x, y);
}

void rb_message_trace(const char* clazz, const char* function, int severity) {
    __android_log_print(severity == 1 ? ANDROID_LOG_ERROR : ANDROID_LOG_DEBUG, (const char*)"rblog", "%s::%s()", clazz, function);
}
