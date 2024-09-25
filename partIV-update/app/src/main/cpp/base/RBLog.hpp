//
//  RBLog.hpp
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

#pragma  once

void rb_message(const char* msg, int severity);
void rb_message_str1(const char* msg, int severity);
void rb_message_num1(const char* msg, int severity);
void rb_message_trace(const char* clazz, const char* function);

#define RBTRACELOG(clazz, function) rb_message_trace(clazz, function);

#define RBLOG(msg) rb_message(msg, 0);
#define RBLOG_STR1(msg, str1) rb_message_str1(msg, str1, 0);
#define RBLOG_NUM1(msg, num1) rb_message_num1(msg, num1, 0);

#define RBERROR(msg) rb_message(msg, 1);
#define RBERROR_STR1(msg, str1) rb_message_str1(msg, str1, 1);
#define RBERROR_NUM1(msg, num1) rb_message_num1(msg, num1, 1);
