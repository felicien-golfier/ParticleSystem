#ifndef CAMERA_H
#define CAMERA_H
#include "Vect3.h"
#include "Quaternion.h"
#include "GlFramework.h"

class Camera
{
public:
    Camera();

protected:
    Vect3 m_Position;
    Quaternion m_Orientation;
    GLMatrix m_ViewMatrix;
    GLMatrix m_Projection;

    void setPosition(Vect3 tmp);
    void setOrientation (Quaternion tmp);
    void setViewMatrix (GLMatrix tmp);
    void setProjection (GLMatrix tmp);

protected:
    void translate(float x, float y, float z);
    void translateX(float shift);
    void translateY(float shift);
    void translateZ(float shift);
    void rotate(float ax, float ay, float az, float angle);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    const GLMatrix& getViewMatrix();
    void setAspectRatio(float ar);
    void setPlanes(float np, float fp);
    void setFOV(float angle);
    const GLMatrix& getProjectionMatrix();

};

#endif // CAMERA_H
