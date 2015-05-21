#include "Camera.h"

Camera::Camera()
{
}

void Camera::setPosition(Vect3 tmp){
    m_Position = tmp;
}

void Camera::setOrientation (Quaternion tmp){
    m_Orientation= tmp;
}

void Camera::setViewMatrix (GLMatrix tmp){
    m_ViewMatrix = tmp;
}

void Camera::setProjection (GLMatrix tmp){
    m_Projection = tmp;
}

void Camera::translate(float x, float y, float z){}

void Camera::translateX(float shift){

}

void Camera::translateY(float shift){

}
void Camera::translateZ(float shift){

}
void Camera::rotate(float ax, float ay, float az, float angle){

}
void Camera::rotateX(float angle){

}
void Camera::rotateY(float angle){

}
void Camera::rotateZ(float angle){

}
const GLMatrix& Camera::getViewMatrix(){

}
void Camera::setAspectRatio(float ar){

}
void Camera::setPlanes(float np, float fp){

}
void Camera::setFOV(float angle){

}
const GLMatrix& getProjectionMatrix(){

}

