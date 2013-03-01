#ifndef VECTOR3_H
#define	VECTOR3_H

#include <cstdlib>
#include <iostream>

// templated 3D vector class with default types float and int
template <class T = float, class U = int>
class Vector3
{
private:
    T x, y, z; // x, y, z coordinates with default type float
    U r, g, b, a; // r, g, b, a color and alpha values with default type int
    int totalVecs; // total number of created vectors
    
public:
    /*****************************************************/
    /*                  Constructors                     */
    /*****************************************************/
    // default constructor (creates a zero vector)
    inline Vector3()
    {
        x=y=z=0.0;
        r=g=b=a=0;
        totalVecs++;
    }
    
    // constructor for passing in xyz coordinates
    inline Vector3(T x, T y, T z):
    x(x), y(y), z(z)
    {
        totalVecs++;
    }
    
    // constructor for passing in xyz coordinates and rgb color values
    inline Vector3(T x, T y, T z, U r, U g, U b):
    x(x), y(y), z(z), r(r), g(g), b(b)
    {
        totalVecs++;
    }
    
    // constructor for passing in xyz coordinates, rgb color values, and an alpha value
    inline Vector3(T x, T y, T z, U r, U g, U b, U a):
    x(x), y(y), z(z), r(r), g(g), b(b), a(a)
    {
        totalVecs++;
    }
    
    // constructor for passing in an array of coordinate values
    inline Vector3(T* xyz)
    {
        x = xyz[0];
        y = xyz[1];
        z = xyz[2];
        r=g=b=a=0;
        totalVecs++;
    }

    // constructor for passing in an array of coordinate and color values
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
    
    // copy constructor
    inline Vector3(const Vector3& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        r = v.r;
        g = v.g;
        b = v.b;
        a = v.a;
        totalVecs++;
    }
    
    /*****************************************************/
    /*              Member Overloaded Ops                */
    /*****************************************************/
    // overloaded assignment operator
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
    
    // overloaded operator+= for adding two vectors
    inline Vector3& operator+=(const Vector3& v) 
    {
        return Vector3(x += v.x, y += v.y, z += v.z);
    }

    // overloaded operator+= for adding a scalar to a vector
    inline Vector3& operator+=(T s) 
    {
        return Vector3(x += s, y += s, z += s);
    }

    // overloaded operator-= for subtracting two vectors
    inline Vector3& operator-=(const Vector3& v) 
    {
        return Vector3(x -= v.x, y -= v.y, z -= v.z);
    }

    // overloaded operator-= for subtracting a vector by a scalar
    inline Vector3& operator-=(T s) 
    {
        return Vector3(x -= s, y -= s, z -= s);
    }

    // overloaded operator*= for multiplying a vector by a scalar
    inline Vector3& operator*=(T s) 
    {
        return Vector3(x *= s, y *= s, z *= s);
    }

    // overloaded operator+= for dividing a vector by a scalar
    inline Vector3& operator/=(T s) 
    {
        return Vector3(x /= s, y /= s, z /= s);
    }

    // overloaded operator++ to increment the xyz coordinates by 1
    inline Vector3& operator++() 
    {
        return Vector3(x += 1, y += 1, z += 1);
    }

    // overloaded operator-- to decrease the xyz coordinates by 1
    inline Vector3& operator--() 
    {
        return Vector3(x -= 1, y -= 1, z -= 1);
    }

    // overloaded operator[] to get/return the x, y, or z coordinate based on index
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

    // overloaded operator== to test whether two vectors are equivalent
    inline bool operator==(const Vector3& v) const 
    {
        return (x == v.x && y == v.y && z == v.z);
    }
    
    // overloaded operator!= to test whether two vectors are not equal
    inline bool operator!=(const Vector3& v) const 
    {
        return (x != v.x || y != v.y || z != v.z);
    }
    
    /*****************************************************/
    /*                 Member Functions                  */
    /*****************************************************/
    // returns the magnitude of a vector
    inline T mag()
    {
        return sqrt(x*x + y*y + z*z);
    }
    
    // returns the squared magnitude of a vector (less computationally expensive
    inline T squaredMag()
    {
        return (x*x + y*y + z*z);
    }
    
    // normalizes the vector (a vector in the same direction with magnitude 1)
    inline void normalize()
    {
        T m = mag();
        *this /= m;
    }
    
    // returns the distance between two vectors
    inline T dist(const Vector3& v)
    {
        T dx = x-v.x;
        T dy = y-v.y;
        T dz = z-v.z;

        return sqrt(dx*dx + dy*dy + dz*dz);
    }
    
    // returns the squared distance between two vectors (less computationally expensive)
    inline T squaredDist(const Vector3& v)
    {
        T dx = x-v.x;
        T dy = y-v.y;
        T dz = z-v.z;

        return (dx*dx + dy*dy + dz*dz);
    }

    // returns the angle between two vectors using the dot product
    inline T angle(const Vector3& v)
    {
        T d = dot(v);
        T am = mag();
        Vector3 b = v;
        T bm = b.mag();
        T ang = acos(d/(am*bm));

        return ang;
    }

    // returns the dot product (scalar value) of two vectors
    inline T dot(const Vector3& v)
    {
        return (x*v.x + y*v.y + z*v.z);
    }

    // returns the cross product (perpendicular vector) of two vectors
    inline Vector3 cross(const Vector3& v)
    {
        return Vector3(y*v.z - z*v.y,
                       z*v.x - x*v.z,
                       x*v.y - y*v.x);
    }

    // rotates a vector around an axis by a certain number of degrees
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
    /*                 Getters & Setters                 */
    /*****************************************************/
    inline T getX() const
    {
        return x;
    }
    
    inline void setX(T x)
    {
        this->x = x;
    }
    
    inline T getY() const
    {
        return y;
    }
    
    inline void setY(T y)
    {
        this->y = y;
    }
    
    inline T getZ() const
    {
        return z;
    }
    
    inline void setZ(T z)
    {
        this->z = z;
    }
    
    inline U getR() const
    {
        return r;
    }
    
    inline void setR(U r)
    {
        this->r = r;
    }
    
    inline U getG() const
    {
        return g;
    }
    
    inline void setG(U g)
    {
        this->g = g;
    }
    
    inline U getB() const
    {
        return b;
    }
    
    inline void setB(U b)
    {
        this->b = b;
    }
    
    inline U getA() const
    {
        return a;
    }
    
    inline void setA(U a)
    {
        this->a = a;
    }
    
    inline T* getXYZ() const
    {
        T tempXYZ[3] = {x, y, z};
        T* xyz = tempXYZ;
        return xyz;
    }
    
    inline void setXYZ(T* xyz)
    {
        x = xyz[0];
        y = xyz[1];
        z = xyz[2];
    }
    
    inline U* getRGB() const
    {
        U tempRGB[3] = {r, g, b};
        U* rgb = tempRGB;
        return rgb;
    }
    
    inline void setRGB(U* rgb)
    {
        r = rgb[0];
        g = rgb[1];
        b = rgb[2];
    }
    
    /*****************************************************/
    /*            Non-Member Ops & Functions             */
    /*****************************************************/
    // overloaded outstream operator to print the x, y, and z coordinates
    inline friend std::ostream& operator<<(std::ostream& out, const Vector3& v) 
    {
        out << "(" <<  v.x << ", " << v.y <<", " << v.z <<")";
        return out;
    }
    
    // overloaded operator+ to add two vectors
    inline friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
    {
        return Vector3(lhs) += rhs;
    }
    
    // overloaded operator+ to add a scalar (left side) with a vector (right side)
    inline friend Vector3 operator+(const T s, const Vector3& v)
    {
        return Vector3(v.x + s, v.y + s, v.z + s);
    }
    
    // overloaded operator+ to add a vector (left side) with a scalar (right side)
    inline friend Vector3 operator+(const Vector3& v, const T s)
    {
        return Vector3(v.x + s, v.y + s, v.z + s);
    }
    
    // overloaded operator- to subtract two vectors
    inline friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
    {
        return Vector3(lhs) -= rhs;
    }
    
    // overloaded operator- to flip the direction of a vector and add a scalar
    inline friend Vector3 operator-(const T s, const Vector3& v)
    {
        return Vector3(s - v.x, s - v.y, s - v.z);
    }
    
    // overloaded operator- to subtract a scalar from a vector
    inline friend Vector3 operator-(const Vector3& v, const T s)
    {
        return Vector3(v.x - s, v.y - s, v.z - s);
    }
    
    // overloaded operator- to return a vector in the opposite direction
    inline friend Vector3 operator-(const Vector3& v)
    {
        return Vector3(-v.x, -v.y, -v.z);
    }
    
    // overloaded operator* to multiply a vector (right side) by a scalar (left side)
    inline friend Vector3 operator*(const T s, const Vector3& v)
    {
        return Vector3(v.x * s, v.y * s, v.z * s);
    }
    
    // overloaded operator* to multiply a vector (left side) by a scalar (right side)
    inline friend Vector3 operator*(const Vector3& v, const T s)
    {
        return Vector3(v.x * s, v.y * s, v.z * s);
    }
    
    // overloaded operator/ to divide a vector (left side) by a scalar (right side)
    inline friend Vector3 operator/(const Vector3& v, const T s)
    {
        return Vector3(v.x / s, v.y / s, v.z / s);
    }
    
    // returns the cross product (perpendicular vector) of two vectors
    inline friend Vector3 cross(const Vector3& lhs, const Vector3& rhs)
    {
        return Vector3(lhs.y*rhs.z - lhs.z*rhs.y,
                       lhs.z*rhs.x - lhs.x*rhs.z,
                       lhs.x*rhs.y - lhs.y*rhs.x);
    }
    
    // returns the magnitude of a vector
    inline friend T mag(const Vector3& v)
    {
        return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    }
    
    // returns the dot product (scalar value) of two vectors
    inline friend T dot(const Vector3& lhs, const Vector3& rhs)
    {
        return (lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z);
    }
    
    // rotates a vector around an axis by a certain number of degrees
    inline friend Vector3 rotate(T theta, const Vector3& axis, const Vector3& v)
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
    
    // returns the angle between two vectors using the dot product
    inline friend T angle(const Vector3& lhs, const Vector3& rhs)
    {
        T d = dot(lhs, rhs);
        T lm = mag(lhs);
        T rm = mag(rhs);
        T ang = acos(d/(lm*rm));
        
        return ang;
    }
};

#endif	/* VECTOR3_H */

