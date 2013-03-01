#ifndef QUATERNION_H
#define	QUATERNION_H

#include "Vector3.h"
#include <cmath>

template <class T>
class Quat 
{
private:
    T x, y, z, w;
    
public:
    /*****************************************************/
    /*                  Constructors                     */
    /*****************************************************/
    inline Quat()
    {
     
    }
    
    inline Quat(Vector3<T> axis, T theta)
    {
        if(axis.squaredMag() > 1)
            axis.normalize();
        x = axis[0]*sin(theta/2)
        y = axis[1]*sin(theta/2);
        z = axis[2]*sin(theta/2);
        w = cos(theta/2);
    }
    
    inline Quat(T x, T y, T z, T w):
    x(x), y(y), z(z), w(w)
    {
        
    }
    
    /*****************************************************/
    /*                 Member Functions                  */
    /*****************************************************/
    inline Quat mult(Quat q)
    {
        return Quat(w*q.x + x*q.w + y*q.z - z*q.y, 
                    w*q.y + x*q.z + y*q.w - z*q.x, 
                    w*q.z + x*q.y + y*q.x - z*q.w, 
                    w*q.w + x*q.x + y*q.y - z*q.z);
    }
    
    inline void rotateXYZ(Vector3<T>& v)
    {
        v[0] = v[0]*(1 - 2*y*y - 2*z*z) + 
                     v[1]*(2*x*y - 2*w*z) + 
                            v[2]*(2*x*z + 2*w*y);
        v[1] = v[0]*(2*x*y + 2*w*z) + 
                     v[1]*(1 - 2*x*x - 2*z*z) + 
                            v[2]*(2*y*z + 2*w*x);
        v[2] = v[0]*(2*x*z - 2*w*y) + 
                     v[1]*(2*y*z - 2*w*x) + 
                            v[2]*(1 - 2*x*x - 2*y*y);
    }
    
    inline Vector3<T> getRotateXYZ(const Vector3<T>& v)
    {
        return Vector3<T>(v[0]*(1 - 2*y*y - 2*z*z) + 
                                v[1]*(2*x*y - 2*w*z) + 
                                      v[2]*(2*x*z + 2*w*y),
                          v[0]*(2*x*y + 2*w*z) + 
                                v[1]*(1 - 2*x*x - 2*z*z) + 
                                      v[2]*(2*y*z + 2*w*x),
                          v[0]*(2*x*z - 2*w*y) + 
                                v[1]*(2*y*z - 2*w*x) + 
                                      v[2]*(1 - 2*x*x - 2*y*y));
    }
    
    inline T mag()
    {
        return sqrt(x*x + y*y + z*z + w*w);
    }
    
    inline T squaredMag()
    {
        return (x*x + y*y + z*z + w*w);
    }
    
    inline void normalize()
    {
        T m = squaredMag();
        
        if(m > 1)
        {
            m = sqrt(m);
            x /= m;
            y /= m;
            z /= m;
            w /= m;
        }
    }
};

#endif	/* QUATERNION_H */

