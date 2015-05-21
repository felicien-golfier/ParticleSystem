#include "Quaternion.h"


Quaternion::Quaternion()
{

}

void Quaternion::set(float xTmp, float yTmp, float zTmp, float wTmp)
{
    x = xTmp;
    y = yTmp;
    z = zTmp;
    w = wTmp;
}

Quaternion Quaternion::operator*(const Quaternion& q1){

    Quaternion q2,result;
    q2.set(this->x,this->y,this->z,this->w);
    float xTmp,yTmp,zTmp,wTmp;
    xTmp =  q1.x * q2.w + q1.y * q2.z - q1.z * q2.y + q1.w * q2.x;
    yTmp = -q1.x * q2.z + q1.y * q2.w + q1.z * q2.x + q1.w * q2.y;
    zTmp =  q1.x * q2.y - q1.y * q2.x + q1.z * q2.w + q1.w * q2.z;
    wTmp = -q1.x * q2.x - q1.y * q2.y - q1.z * q2.z + q1.w * q2.w;

    result.set(xTmp,yTmp,zTmp,wTmp);

    return result;
}

Vect3 Quaternion::operator*(Vect3 v){


    return v;
}

Quaternion Quaternion::operator*(float f){
    Quaternion result;

    return result;}
Quaternion Quaternion::operator+(const Quaternion& q){

    Quaternion result;
    result.set(q.x,q.y,q.z,q.w);

    result.x += this->x;
    result.y += this->y;
    result.z += this->z;
    result.w += this->w;

    return result;
}

Quaternion& Quaternion::operator*=(const Quaternion& q){
    Quaternion result;
    return result;

}

float Quaternion::dot(Quaternion q){
    float result;

    return result;
}

void Quaternion::setFromAxis(float ax, float ay, float az, float angle)
{
//    setX(x);
//    setY(y);
//    setZ(z);
//    setW(w);
}

Quaternion Quaternion::conjugate(){
    Quaternion q;
    q.set(- this->x,- this->y,- this->z,this->w);
    return q;
}

Quaternion Quaternion::slerp(const Quaternion & q1, const Quaternion & q2, float t){
    Quaternion q;
    return q;
}

void Quaternion::normalize(){

}

void Quaternion::setRotationMatrix(float mat){

}
