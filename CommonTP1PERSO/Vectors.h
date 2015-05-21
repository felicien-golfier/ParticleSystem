#ifndef Vectors_h
#define Vectors_h


#include <math.h>
#include <string.h>

#include "Types.h"


template <class T>
class AbstractVec2
{
    public:
        AbstractVec2()
        {
            memset( this, 0, sizeof( T )*2 );
        }

        AbstractVec2( T X, T Y ) : x( X ), y( Y )
        {
        }


        bool operator==( const AbstractVec2 & v )
        {
            return (x == v.x && y == v.y);
        }


        AbstractVec2 operator+( T v ) const
        {
            return AbstractVec2( x+v, y+v );
        }

        AbstractVec2 operator-( T v ) const
        {
            return AbstractVec2( x-v, y-v );
        }

        AbstractVec2 operator*( T v ) const
        {
            return AbstractVec2( x*v, y*v );
        }

        AbstractVec2 operator/( T v ) const
        {
            return AbstractVec2( x/v, y/v );
        }


        AbstractVec2 & operator+=( T v )
        {
            x += v;
            y += v;

            return (*this);
        }


    public:
        T x, y;
};


template <class T>
class AbstractVec3
{
    public:
        AbstractVec3()
        {
            memset( this, 0, sizeof( T )*3 );
        }

        AbstractVec3( T X, T Y, T Z ) : x( X ), y( Y ), z( Z )
        {
        }


        bool operator==( const AbstractVec3 & v ) const
        {
            return (x == v.x && y == v.y && z == v.z);
        }

        bool operator!=( const AbstractVec3 & v ) const
        {
            return (x != v.x || y != v.y || z != v.z);
        }

        AbstractVec3 & operator+=( const AbstractVec3 & vVector )
        {
            x += vVector.x;
            y += vVector.y;
            z += vVector.z;

            return (*this);
        }

        AbstractVec3 & operator*=( T factor )
        {
            x *= factor;
            y *= factor;
            z *= factor;

            return (*this);
        }

        AbstractVec3 operator+( const AbstractVec3 & vVector ) const
        {
            return AbstractVec3(vVector.x + x, vVector.y + y, vVector.z + z);
        }

        AbstractVec3 operator-( const AbstractVec3 & vVector ) const
        {
            return AbstractVec3(x - vVector.x, y - vVector.y, z - vVector.z);
        }

        AbstractVec3 operator-() const
        {
            return AbstractVec3(-x, -y, -z);
        }

        AbstractVec3 operator*( T num ) const
        {
            return AbstractVec3(x * num, y * num, z * num);
        }

        AbstractVec3 operator/( T num ) const
        {
            num = 1/num;

            return AbstractVec3(x * num, y * num, z * num);
        }

        AbstractVec3 crossProduct( const AbstractVec3 & vVector ) const
        {
            AbstractVec3 vNormal;

            // Valeur X:  (V1.y * V2.z) - (V1.z * V2.y)
            vNormal.x = ((y * vVector.z) - (z * vVector.y));
            // Valeur Y:  (V1.z * V2.x) - (V1.x * V2.z)
            vNormal.y = ((z * vVector.x) - (x * vVector.z));
            // Valeur Z:  (V1.x * V2.y) - (V1.y * V2.x)
            vNormal.z = ((x * vVector.y) - (y * vVector.x));

            return vNormal;
        }

        const T dotProduct( const AbstractVec3 & vVector ) const
        {
            return x*vVector.x + y*vVector.y + z*vVector.z;
        }

        static T length( const AbstractVec3 & vNormal )
        {
            return (T) sqrt((vNormal.x * vNormal.x) + (vNormal.y * vNormal.y) + (vNormal.z * vNormal.z));
        }


        float getSquaredEuclideanDistance( const AbstractVec3 & v ) const
        {
            return SQ3DDistance( x, y, z, v.x, v.y, v.z );
        }

        float getEuclideanDistance( const AbstractVec3 & v ) const
        {
            return SR3DDistance( x, y, z, v.x, v.y, v.z );
        }


        T length() const
        {
            return (T) sqrt((x * x) + (y * y) + (z * z));
        }

        static AbstractVec3 normalize( const AbstractVec3 & vVector )
        {
            T len = 1.0f / length(vVector);

            if (len != 0.0)
            {
                return vVector * len;
            }
            else
            {
                return vVector;
            }
        }

        void normalize()
        {
            T len = length();

            if( len != 0.0 )
            {
                len = 1/len;
                x = x * len;
                y = y * len;
                z = z * len;
            }
        }


    public:
        T x, y, z;
};


template <class T>
class AbstractVec4
{
    public:
        T x, y, z, w;
};


typedef AbstractVec2<uint32> Vec2ui;
typedef AbstractVec2<int32> Vec2i;
typedef AbstractVec2<float32> Vec2;

typedef AbstractVec3<uint32> Vec3ui;
typedef AbstractVec3<int32> Vec3i;
typedef AbstractVec3<float32> Vec3;

typedef AbstractVec4<uint32> Vec4ui;
typedef AbstractVec4<int32> Vec4i;
typedef AbstractVec4<float32> Vec4;


#endif
