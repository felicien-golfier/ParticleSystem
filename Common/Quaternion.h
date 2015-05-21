#ifndef QUATERNION_H
#define QUATERNION_H
#include "Vect3.h"

class Quaternion
{

    public:
        Quaternion();
    protected:

        void set(float xTmp, float yTmp, float zTmp, float wTmp);


        Quaternion operator*(const Quaternion & q);
        Vect3 operator*(Vect3 v);
        Quaternion operator*(float f);
        Quaternion operator+(const Quaternion & q);
        Quaternion & operator*=(const Quaternion & q);
        float dot(Quaternion q);
        void setFromAxis(float ax, float ay, float az, float angle);
        Quaternion conjugate();
        Quaternion slerp(const Quaternion & q1, const Quaternion & q2, float t);
        void normalize();
        void setRotationMatrix(float mat);

    protected:
        float x,y,z,w;

};
#endif // QUATERNION_H
