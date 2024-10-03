//
//  RBMath.cpp
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

#include "RBMath.hpp"

RBVec3D RBVec3DMake(int x, int y, int z) {
    return { float(x), float(y), float(z)};
}

RBVec3D RBVec3DAdd(RBVec3D &v1, RBVec3D &v2) {
    return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

RBVec3D RBVec3DSub(RBVec3D &v1, RBVec3D &v2) {
    return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

RBVec3D RBVec3DMul(RBVec3D &v1, float k) {
    return { v1.x * k, v1.y * k, v1.z * k };
}

RBVec3D RBVec3DDiv(RBVec3D &v1, float k) {
    return { v1.x / k, v1.y / k, v1.z / k };
}

float RBVec3DDotProduct(RBVec3D &v1, RBVec3D &v2) {
    return v1.x*v2.x + v1.y*v2.y + v1.z * v2.z;
}

float RBVec3DLength(RBVec3D &v) {
    return sqrtf(RBVec3DDotProduct(v, v));
}

RBVec3D RBVec3DNormalise(RBVec3D &v) {
    float l = RBVec3DLength(v);
    return { v.x / l, v.y / l, v.z / l };
}

RBVec3D RBVec3DCrossProduct(RBVec3D &v1, RBVec3D &v2) {
    RBVec3D v;
    v.x = v1.y * v2.z - v1.z * v2.y;
    v.y = v1.z * v2.x - v1.x * v2.z;
    v.z = v1.x * v2.y - v1.y * v2.x;
    return v;
}

RBVec3D RBVec3DIntersectPlane(RBVec3D &plane_p, RBVec3D &plane_n, RBVec3D &lineStart, RBVec3D &lineEnd) {
    plane_n = RBVec3DNormalise(plane_n);
    float plane_d = -RBVec3DDotProduct(plane_n, plane_p);
    float ad = RBVec3DDotProduct(lineStart, plane_n);
    float bd = RBVec3DDotProduct(lineEnd, plane_n);
    float t = (-plane_d - ad) / (bd - ad);
    RBVec3D lineStartToEnd = RBVec3DSub(lineEnd, lineStart);
    RBVec3D lineToIntersect = RBVec3DMul(lineStartToEnd, t);
    
    return RBVec3DAdd(lineStart, lineToIntersect);
}

float Vec3DAngle(RBVec3D& vec1, RBVec3D& vec2) {
    float dot = vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
    float lenSq1 = vec1.x*vec1.x + vec1.y*vec1.y + vec1.z*vec1.z;
    float lenSq2 = vec2.x*vec2.x + vec2.y*vec2.y + vec2.z*vec2.z;
    float angle = acos(dot/sqrt(lenSq1 * lenSq2));

    return RAD_TO_DEG(angle);
}

RBVec3D RBMatrixMultiplyVector(RBMat4x4 &m, RBVec3D &i) {
    RBVec3D v;
    v.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + i.w * m.m[3][0];
    v.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + i.w * m.m[3][1];
    v.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + i.w * m.m[3][2];
    v.w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + i.w * m.m[3][3];
    
    return v;
}

RBMat4x4 RBMatrixMakeIdentity() {
    RBMat4x4 matrix = { 0 };
    matrix.m[0][0] = 1.0f;
    matrix.m[1][1] = 1.0f;
    matrix.m[2][2] = 1.0f;
    matrix.m[3][3] = 1.0f;
    
    return matrix;
}

RBMat4x4 RBMatrixMakeRotationX(float fAngleRad) {
    RBMat4x4 matrix = { 0 };
    matrix.m[0][0] = 1.0f;
    matrix.m[1][1] = cosf(fAngleRad);
    matrix.m[1][2] = sinf(fAngleRad);
    matrix.m[2][1] = -sinf(fAngleRad);
    matrix.m[2][2] = cosf(fAngleRad);
    matrix.m[3][3] = 1.0f;
    
    return matrix;
}

RBMat4x4 RBMatrixMakeRotationY(float fAngleRad) {
    RBMat4x4 matrix = { 0 };
    matrix.m[0][0] = cosf(fAngleRad);
    matrix.m[0][2] = sinf(fAngleRad);
    matrix.m[2][0] = -sinf(fAngleRad);
    matrix.m[1][1] = 1.0f;
    matrix.m[2][2] = cosf(fAngleRad);
    matrix.m[3][3] = 1.0f;
    
    return matrix;
}

RBMat4x4 RBMatrixMakeRotationZ(float fAngleRad) {
    RBMat4x4 matrix = { 0 };
    matrix.m[0][0] = cosf(fAngleRad);
    matrix.m[0][1] = sinf(fAngleRad);
    matrix.m[1][0] = -sinf(fAngleRad);
    matrix.m[1][1] = cosf(fAngleRad);
    matrix.m[2][2] = 1.0f;
    matrix.m[3][3] = 1.0f;
    
    return matrix;
}

RBMat4x4 RBMatrixMakeScale(float sx, float sy, float sz) {
    RBMat4x4 matrix = { 0 };
    matrix.m[0][0] = sx;
    matrix.m[0][1] = 0;
    matrix.m[0][2] = 0;
    matrix.m[0][3] = 0;
    
    matrix.m[1][0] = 0;
    matrix.m[1][1] = sy;
    matrix.m[1][2] = 0;
    matrix.m[1][3] = 0;
    
    matrix.m[2][0] = 0;
    matrix.m[2][1] = 0;
    matrix.m[2][2] = sz;
    matrix.m[2][3] = 0;
    
    matrix.m[3][0] = 0;
    matrix.m[3][1] = 0;
    matrix.m[3][2] = 0;
    matrix.m[3][3] = 1;

    return matrix;
}

RBMat4x4 RBMatrixMakeTranslation(float x, float y, float z) {
    RBMat4x4 matrix = { 0 };
    matrix.m[0][0] = 1.0f;
    matrix.m[1][1] = 1.0f;
    matrix.m[2][2] = 1.0f;
    matrix.m[3][3] = 1.0f;
    matrix.m[3][0] = x;
    matrix.m[3][1] = y;
    matrix.m[3][2] = z;
    
    return matrix;
}

RBMat4x4 RBMatrixMultiplyMatrix(RBMat4x4 &m1, RBMat4x4 &m2) {
    RBMat4x4 matrix = {0 };
    for (int c = 0; c < 4; c++)
        for (int r = 0; r < 4; r++)
            matrix.m[r][c] = m1.m[r][0] * m2.m[0][c] + m1.m[r][1] * m2.m[1][c] + m1.m[r][2] * m2.m[2][c] + m1.m[r][3] * m2.m[3][c];

    return matrix;
}

RBMat4x4 RBMatrixMakeProjection2D(float width, float height) {
    RBMat4x4 matrix = {2.0f / width, 0.0f, 0.0f, -1.0f,
                       0.0f, 2.0f / height, 0.0f, -1.0f,
                       0.0f, 0.0f, -1.0f, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f};

    return matrix;
}

RBMat4x4 RBMatrixMakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar) {
    float fFovRad = 1.0f / tanf(fFovDegrees * 0.5f / 180.0f * 3.14159f);

    RBMat4x4 matrix = {0 };
    matrix.m[0][0] = fAspectRatio * fFovRad;
    matrix.m[1][1] = fFovRad;
    matrix.m[2][2] = fFar / (fFar - fNear);
    matrix.m[3][2] = (-fFar * fNear) / (fFar - fNear);
    matrix.m[2][3] = 1.0f;
    matrix.m[3][3] = 0.0f;

    return matrix;
}

RBMat4x4 RBMatrixMakeProjection3D(float fFovDegrees, float fAspectRatio, float fNear, float fFar) {
    RBMat4x4 matrix = { 0 };

    float frustumW, frustumH;

    frustumH = tanf(fFovDegrees / 360.0f * M_PI) * fNear;
    frustumW = frustumH * fAspectRatio;

    matrix = RBMatrixMakeFrustum(-frustumW, frustumW, -frustumH, frustumH, fNear, fFar);

    return matrix;
}

RBMat4x4 RBMatrixMakeFrustum(float left, float right, float bottom, float top, float nearZ, float farZ) {
    float deltaX = right - left;
    float deltaY = top - bottom;
    float deltaZ = farZ - nearZ;
    RBMat4x4 frust = { 0 };

    if ((nearZ <= 0.0f) || (farZ <= 0.0f) ||
        (deltaX <= 0.0f) || (deltaY <= 0.0f) || (deltaZ <= 0.0f)) {
        return RBMatrixMakeIdentity();
    }

    frust.m[0][0] = 2.0f * nearZ / deltaX;
    frust.m[0][1] = frust.m[0][2] = frust.m[0][3] = 0.0f;

    frust.m[1][1] = 2.0f * nearZ / deltaY;
    frust.m[1][0] = frust.m[1][2] = frust.m[1][3] = 0.0f;

    frust.m[2][0] = (right + left) / deltaX;
    frust.m[2][1] = (top + bottom) / deltaY;
    frust.m[2][2] = -(nearZ + farZ) / deltaZ;
    frust.m[2][3] = -1.0f;

    frust.m[3][2] = -2.0f * nearZ * farZ / deltaZ;
    frust.m[3][0] = frust.m[3][1] = frust.m[3][3] = 0.0f;

    return frust;
}

// Multiply matrix specified by result with a perspective matrix and return new matrix in result
// result Specifies the input matrix.  new matrix is returned in result.
// left, right Coordinates for the left and right vertical clipping planes
// bottom, top Coordinates for the bottom and top horizontal clipping planes
// nearZ, farZ Distances to the near and far depth clipping planes.  These values are negative if plane is behind the viewer
RBMat4x4 RBMatrixMakeOrtho(float left, float right, float bottom, float top, float nearZ, float farZ) {
    float deltaX = right - left;
    float deltaY = top - bottom;
    float deltaZ = farZ - nearZ;

    RBMat4x4 matrix = {0 };

    if ((deltaX == 0.0f) || (deltaY == 0.0f) || (deltaZ == 0.0f)) {
        return matrix;
    }
    
    matrix.m[0][0] = 2.0/deltaX;
    matrix.m[0][3] = -1.0;
    matrix.m[1][1] = 2.0/deltaY;
    matrix.m[1][3] = -1.0;
    matrix.m[2][2] = -2.0/(farZ-nearZ);
    matrix.m[3][3] = 1.0;
    
    return matrix;
}

RBMat4x4 RBMatrixPointAt(RBVec3D &pos, RBVec3D &target, RBVec3D &up) {
    // Calculate new forward direction
    RBVec3D newForward = RBVec3DSub(target, pos);
    newForward = RBVec3DNormalise(newForward);

    // Calculate new Up direction
    RBVec3D a = RBVec3DMul(newForward, RBVec3DDotProduct(up, newForward));
    RBVec3D newUp = RBVec3DSub(up, a);
    newUp = RBVec3DNormalise(newUp);

    // New Right direction is easy, its just cross product
    RBVec3D newRight = RBVec3DCrossProduct(newUp, newForward);

    // Construct Dimensioning and Translation Matrix
    RBMat4x4 matrix = {0 };
    matrix.m[0][0] = newRight.x;    matrix.m[0][1] = newRight.y;    matrix.m[0][2] = newRight.z;    matrix.m[0][3] = 0.0f;
    matrix.m[1][0] = newUp.x;        matrix.m[1][1] = newUp.y;        matrix.m[1][2] = newUp.z;        matrix.m[1][3] = 0.0f;
    matrix.m[2][0] = newForward.x;    matrix.m[2][1] = newForward.y;    matrix.m[2][2] = newForward.z;    matrix.m[2][3] = 0.0f;
    matrix.m[3][0] = pos.x;            matrix.m[3][1] = pos.y;            matrix.m[3][2] = pos.z;            matrix.m[3][3] = 1.0f;
    
    return matrix;

}

// Only for Rotation/Translation Matrices
RBMat4x4 MatrixQuickInverse(RBMat4x4 &m) {
    RBMat4x4 matrix = { 0 };
    matrix.m[0][0] = m.m[0][0]; matrix.m[0][1] = m.m[1][0]; matrix.m[0][2] = m.m[2][0]; matrix.m[0][3] = 0.0f;
    matrix.m[1][0] = m.m[0][1]; matrix.m[1][1] = m.m[1][1]; matrix.m[1][2] = m.m[2][1]; matrix.m[1][3] = 0.0f;
    matrix.m[2][0] = m.m[0][2]; matrix.m[2][1] = m.m[1][2]; matrix.m[2][2] = m.m[2][2]; matrix.m[2][3] = 0.0f;
    matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
    matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
    matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
    matrix.m[3][3] = 1.0f;
    
    return matrix;
}
