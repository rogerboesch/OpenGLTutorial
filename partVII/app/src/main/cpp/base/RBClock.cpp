//
//  RBClock.hpp
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

#include "RBClock.hpp"
#include "RBLog.hpp"

#include <chrono>

RBClock::RBClock() {
    Reset();
}

void RBClock::Reset() {
    m_firstTime = true;
    Delta();
}

float RBClock::Delta() {
    if (m_firstTime) {
        m_timestamp = std::chrono::high_resolution_clock::now();
        m_firstTime = false;

        return 0.0f;
    }

    std::chrono::duration<float> fs = std::chrono::high_resolution_clock::now() - m_timestamp;
    m_timestamp = std::chrono::high_resolution_clock::now();

    return fs.count();
}

float RBClock::Duration() {
    std::chrono::duration<float> fs = std::chrono::high_resolution_clock::now() - m_timestamp;

    return fs.count();
}

long RBClock::Current() {
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    return (long)now.time_since_epoch().count();
}
