#ifndef VECTOR3_H
#define	VECTOR3_H

#include <iostream>

template <class T, class U>
class Vector3
{
private:
    T x, y, z;
    U r, g, b, a;
    int totalVecs;
    
public:
    /*****************************************************/
    /*                  Constructors                     */
    /*****************************************************/
    inline Vector3()
    {
        x=y=z=0;
        r=g=b=a=0;
    }
    
    inline Vector3(T x, T y, T z, U r, U g, U b, U a):
    x(x), y(y), z(z), r(r), g(g), b(b), a(a)
    {
        totalVecs++;
    }
    
    inline Vector3(T* xyz)
    {
        x = xyz[0];
        y = xyz[1];
        z = xyz[2];
        r=g=b=a=0;
        totalVecs++;
    }

    inline Vector3(T* xyz, U* rgba)
    {
        x = xyz[0];
        y = xyz[1];
        z = xyz[2];
        r = rgba[0];
        g = rgba[1];
        b = rgba[2];
        a = rgba[3];
        totalVecs++;
    }
    
    inline Vector3(const Vector3& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        r = v.r;
        g = v.g;
        b = v.b;
        a = v.a;
    }
    
    /*****************************************************/
    /*              Member Overloaded Ops                */
    /*****************************************************/
    inline Vector3& operator=(const Vector3& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        r = v.r;
        g = v.g;
        b = v.b;
        a = v.a;
    }
    
    inline Vector3& operator+=(const Vector3& v) 
    {
        return Vector3(x += v.x, y += v.y, z += v.z);
    }

    inline Vector3& operator+=(T s) 
    {
        return Vector3(x += s, y += s, z += s);
    }

    inline Vector3& operator-=(const Vector3& v) 
    {
        return Vector3(x -= v.x, y -= v.y, z -= v.z);
    }

    inline Vector3& operator-=(T s) 
    {
        return Vector3(x -= s, y -= s, z -= s);
    }

    inline Vector3& operator*=(T s) 
    {
        return Vector3(x *= s, y *= s, z *= s);
    }

    inline Vector3& operator/=(T s) 
    {
        return Vector3(x /= s, y /= s, z /= s);
    }

    inline Vector3& operator++() 
    {
        return Vector3(x += 1, y += 1, z += 1);
    }

    inline Vector3& operator--() 
    {
        return Vector3(x -= 1, y -= 1, z -= 1);
    }

    inline T operator[](int index)
    {
        T val = 0;
        switch(index)
        {
            case 0:
                return x;
                break;
            case 1:
                return y;
                break;
            case 2:
                return z;
                break;
            default:
                std::cout << "Error: index value out of range";
                break;
        }
        return val;
    }

    inline bool operator==(const Vector3& v) const 
    {
        return (x == v.x && y == v.y && z == v.z);
    }
    
    inline bool operator!=(const Vector3& v) const 
    {
        return (x != v.x || y != v.y || z != v.z);
    }

    inline std::ostream& operator<<(std::ostream& output, const Vector3& vec) 
    {
        output << "(" <<  vec.x << ", " << vec.y <<", " << vec.z <<")";
        return output;
    }
    
    /*****************************************************/
    /*                 Member Functions                  */
    /*****************************************************/
    inline T mag()
    {
        return sqrt(x*x + y*y + z*z);
    }
    
    inline T squaredMag()
    {
        return (x*x + y*y + z*z);
    }
    
    inline void normalize()
    {
        T m = mag();
        *this /= m;
    }
    
    inline T dist(const Vector3& v)
    {
        T dx = x-v.x;
        T dy = y-v.y;
        T dz = z-v.z;

        return sqrt(dx*dx + dy*dy + dz*dz);
    }
    
    inline T squaredDist(const Vector3& v)
    {
        T dx = x-v.x;
        T dy = y-v.y;
        T dz = z-v.z;

        return (dx*dx + dy*dy + dz*dz);
    }

    inline T angle(const Vector3& v)
    {
        T d = dot(v);
        T am = mag();
        Vector3 b = v;
        T bm = b.mag();
        T ang = acos(d/(am*bm));

        return ang;
    }

    inline T dot(const Vector3& v)
    {
        return (x*v.x + y*v.y + z*v.z);
    }

    inline Vector3 cross(const Vector3& v)
    {
        return Vector3(y*v.z - z*v.y,
                       z*v.x - x*v.z,
                       x*v.y - y*v.x);
    }

    inline Vector3& rotate(T theta, const Vector3& axis) 
    {
        T s = sin(theta);
        T c = cos(theta);
        T k = 1.0 - c;

        T tempX = x * (c + k * axis.x * axis.x) + 
                  y * (k * axis.x * axis.y - s * axis.z) + 
                  z * (k * axis.x * axis.z + s * axis.y);
        T tempY = x * (k * axis.x * axis.y + s * axis.z) + 
                  y * (c + k * axis.y * axis.y) + 
                  z * (k * axis.y * axis.z - s * axis.x);
        T tempZ = x * (k * axis.x * axis.z - s * axis.y) + 
                  y * (k * axis.y * axis.z + s * axis.x) + 
                  z * (c + k * axis.z * axis.z);

        x = tempX;
        y = tempY;
        z = tempZ;

        return (*this);
    }
    
    /*****************************************************/
    /*            Non-Member Ops & Functions             */
    /*****************************************************/
    friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
    {
        return Vector3(lhs) += rhs;
    }
    
    friend Vector3 operator+(const T s, const Vector3& v)
    {
        return Vector3(v.x + s, v.y + s, v.z + s);
    }
    
    friend Vector3 operator+(const Vector3& v, const T s)
    {
        return Vector3(v.x + s, v.y + s, v.z + s);
    }
    
    friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
    {
        return Vector3(lhs) -= rhs;
    }
    
    friend Vector3 operator-(const T s, const Vector3& v)
    {
        return Vector3(s - v.x, s - v.y, s - v.z);
    }
    
    friend Vector3 operator-(const Vector3& v, const T s)
    {
        return Vector3(v.x - s, v.y - s, v.z - s);
    }
    
    friend Vector3 operator-(const Vector3& v)
    {
        return Vector3(-v.x, -v.y, -v.z);
    }
    
    friend Vector3 operator*(const T s, const Vector3& v)
    {
        return Vector3(v.x * s, v.y * s, v.z * s);
    }
    
    friend Vector3 operator*(const Vector3& v, const T s)
    {
        return Vector3(v.x * s, v.y * s, v.z * s);
    }
    
    friend Vector3 operator/(const Vector3& v, const T s)
    {
        return Vector3(v.x / s, v.y / s, v.z / s);
    }
    
    friend Vector3 cross(const Vector3& lhs, const Vector3& rhs)
    {
        return Vector3(lhs.y*rhs.z - lhs.z*rhs.y,
                       lhs.z*rhs.x - lhs.x*rhs.z,
                       lhs.x*rhs.y - lhs.y*rhs.x);
    }
    
    friend T mag(const Vector3& v)
    {
        return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    }
    
    friend T dot(const Vector3& lhs, const Vector3& rhs)
    {
        return (lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z);
    }
    
    friend Vector3 rotate(T theta, const Vector3& axis, const Vector3& v)
    {
        Vector3 rv;
        T s = sin(theta);
        T c = cos(theta);
        T k = 1.0 - c;
        
        rv.x = v.x * (c + k * axis.x * axis.x) + 
               v.y * (k * axis.x * axis.y - s * axis.z) + 
               v.z * (k * axis.x * axis.z + s * axis.y);
        rv.y = v.x * (k * axis.x * axis.y + s * axis.z) + 
               v.y * (c + k * axis.y * axis.y) + 
               v.z * (k * axis.y * axis.z - s * axis.x);
        rv.z = v.x * (k * axis.x * axis.z - s * axis.y) + 
               v.y * (k * axis.y * axis.z + s * axis.x) + 
               v.z * (c + k * axis.z * axis.z);
        
        return rv;
        
    }
    
    friend T angle(const Vector3& lhs, const Vector3& rhs)
    {
        T d = dot(lhs, rhs);
        T lm = mag(lhs);
        T rm = mag(rhs);
        T ang = acos(d/(lm*rm));
        
        return ang;
    }
};

#endif	/* VECTOR3_H */

