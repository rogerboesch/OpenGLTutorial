//
//  RBMath.hpp
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

#pragma once

#include <math.h>

#define P_PI 3.14159265358979323846264338327950288
#define DEG_TO_RAD(angleInDegrees) ((angleInDegrees) * P_PI / 180.0)
#define RAD_TO_DEG(angleInRadians) ((angleInRadians) * 180.0 / P_PI)

struct RBVec2D {
    union {
        float value[2];
        struct { float x, y; };
        struct { float width, height; };
    };
};

struct RBVec3D {
    union {
        float value[4];
        struct { float x, y, z, w; };
        struct { float r, g, b, a; };
    };
};

struct RBMat4x4 {
    float m[4][4] = { 0 };
};

RBVec3D RBVec3DMake(int x, int y, int z);
RBVec3D RBVec3DAdd(RBVec3D &v1, RBVec3D &v2);
RBVec3D RBVec3DSub(RBVec3D &v1, RBVec3D &v2);
RBVec3D RBVec3DMul(RBVec3D &v1, float k);
RBVec3D RBVec3DDiv(RBVec3D &v1, float k);
float RBVec3DDotProduct(RBVec3D &v1, RBVec3D &v2);
float RBVec3DLength(RBVec3D &v);
RBVec3D RBVec3DNormalise(RBVec3D &v);
RBVec3D RBVec3DCrossProduct(RBVec3D &v1, RBVec3D &v2);
RBVec3D RBVec3DIntersectPlane(RBVec3D &plane_p, RBVec3D &plane_n, RBVec3D &lineStart, RBVec3D &lineEnd);
float RBVec3DAngle(RBVec3D& vec1, RBVec3D& vec2);

RBVec3D RBMatrixMultiplyVector(RBMat4x4 &m, RBVec3D &i);
RBMat4x4 RBMatrixMakeIdentity();
RBMat4x4 RBMatrixMakeRotationX(float fAngleRad);
RBMat4x4 RBMatrixMakeRotationY(float fAngleRad);
RBMat4x4 RBMatrixMakeRotationZ(float fAngleRad);
RBMat4x4 RBMatrixMakeScale(float sx, float sy, float sz);
RBMat4x4 RBMatrixMakeTranslation(float x, float y, float z);
RBMat4x4 RBMatrixMultiplyMatrix(RBMat4x4 &m1, RBMat4x4 &m2);
RBMat4x4 RBMatrixQuickInverse(RBMat4x4 &m);

RBMat4x4 RBMatrixPointAt(RBVec3D &pos, RBVec3D &target, RBVec3D &up);
RBMat4x4 RBMatrixMakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar);
RBMat4x4 RBMatrixMakeOrtho(float left, float right, float bottom, float top, float nearZ, float farZ);
