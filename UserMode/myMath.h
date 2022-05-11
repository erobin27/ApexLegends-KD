#pragma once
#include <assert.h>

# define PI           3.14159265358979323846 

#define CHECK_VALID( _v ) 0
#define Assert( _exp ) ((void)0)
#define FastSqrt(x)			(sqrt)(x)

#define M_PI 3.14159265358979323846264338327950288419716939937510



// Class Vector2
// This class represents a 2D vector.
class Vector2 {

public:

    // -------------------- Attributes -------------------- //

    // Components of the vector
    float x, y;


    // -------------------- Methods -------------------- //

    // Constructor
    Vector2(float x = 0, float y = 0) : x(x), y(y) {}

    // Constructor
    Vector2(const Vector2& vector) : x(vector.x), y(vector.y) {}

    // + operator
    Vector2 operator+(const Vector2& v) const {
        return Vector2(x + v.x, y + v.y);
    }

    // += operator
    Vector2& operator+=(const Vector2& v) {
        x += v.x; y += v.y;
        return *this;
    }

    // - operator
    Vector2 operator-(const Vector2& v) const {
        return Vector2(x - v.x, y - v.y);
    }

    // -= operator
    Vector2& operator-=(const Vector2& v) {
        x -= v.x; y -= v.y;
        return *this;
    }

    // = operator
    Vector2& operator=(const Vector2& vector) {
        if (&vector != this) {
            x = vector.x;
            y = vector.y;
        }
        return *this;
    }

    // == operator
    bool operator==(const Vector2& v) const {
        return x == v.x && y == v.y;
    }

    // * operator
    Vector2 operator*(float f) const {
        return Vector2(f * x, f * y);
    }

    // *= operator
    Vector2& operator*=(float f) {
        x *= f; y *= f;
        return *this;
    }

    // / operator
    Vector2 operator/(float f) const {
        assert(f != 0);
        float inv = 1.f / f;
        return Vector2(x * inv, y * inv);
    }

    // /= operator
    Vector2& operator/=(float f) {
        assert(f != 0);
        float inv = 1.f / f;
        x *= inv; y *= inv;
        return *this;
    }

    // - operator
    Vector2 operator-() const {
        return Vector2(-x, -y);
    }

    // [] operator
    float& operator[](int i) {
        assert(i >= 0 && i <= 1);
        switch (i) {
        case 0: return x;
        case 1: return y;
        }
        return y;
    }

    // Normalize the vector and return it
    Vector2 normalize() {
        float l = length();
        assert(l > 0);
        x /= l;
        y /= l;
        return *this;
    }

    // Clamp the vector values between 0 and 1
    Vector2 clamp01() {
        if (x > 1.f) x = 1.f;
        else if (x < 0.f) x = 0.f;
        if (y > 1.f) y = 1.f;
        else if (y < 0.f) y = 0.f;
        return *this;
    }

    // Return the squared length of the vector
    float lengthSquared() const { return x * x + y * y; }

    // Return the length of the vector
    float length() const { return sqrt(lengthSquared()); }
};


//Vector3
#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
class Vector3
{
public:
    float x, y, z;
    Vector3(void);
    Vector3(float X, float Y, float Z);
    void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
    bool IsValid() const;
    float operator[](int i) const;
    float& operator[](int i);
    inline void Zero();
    bool operator==(const Vector3& v) const;
    bool operator!=(const Vector3& v) const;
    inline Vector3& operator+=(const Vector3& v);
    inline Vector3& operator-=(const Vector3& v);
    inline Vector3& operator*=(const Vector3& v);
    inline Vector3& operator*=(float s);
    inline Vector3& operator/=(const Vector3& v);
    inline Vector3& operator/=(float s);
    inline Vector3& operator+=(float fl);
    inline Vector3& operator-=(float fl);
    inline float	Length() const;
    inline float LengthSqr(void) const
    {
        CHECK_VALID(*this);
        return (x * x + y * y + z * z);
    }
    bool IsZero(float tolerance = 0.01f) const
    {
        return (x > -tolerance && x < tolerance&&
            y > -tolerance && y < tolerance&&
            z > -tolerance && z < tolerance);
    }
    Vector3	Normalize();
    float	NormalizeInPlace();
    inline float	DistTo(const Vector3& vOther) const;
    inline float	DistToSqr(const Vector3& vOther) const;
    float	Dot(const Vector3& vOther) const;
    float	Length2D(void) const;
    float	Length2DSqr(void) const;
    Vector3& operator=(const Vector3& vOther);
    Vector3	operator-(void) const;
    Vector3	operator+(const Vector3& v) const;
    Vector3	operator-(const Vector3& v) const;
    Vector3	operator*(const Vector3& v) const;
    Vector3	operator/(const Vector3& v) const;
    Vector3	operator*(float fl) const;
    Vector3	operator/(float fl) const;
    // Base address...
    float* Base();
    float const* Base() const;
};
//===============================================
inline void Vector3::Init(float ix, float iy, float iz)
{
    x = ix; y = iy; z = iz;
    CHECK_VALID(*this);
}
//===============================================
inline Vector3::Vector3(float X, float Y, float Z)
{
    x = X; y = Y; z = Z;
    CHECK_VALID(*this);
}
//===============================================
inline Vector3::Vector3(void) { Zero(); }
//===============================================
inline void Vector3::Zero()
{
    x = y = z = 0.0f;
}
//===============================================
inline void Vector3Clear(Vector3& a)
{
    a.x = a.y = a.z = 0.0f;
}
//===============================================
inline Vector3& Vector3::operator=(const Vector3& vOther)
{
    CHECK_VALID(vOther);
    x = vOther.x; y = vOther.y; z = vOther.z;
    return *this;
}
//===============================================
inline float& Vector3::operator[](int i)
{
    Assert((i >= 0) && (i < 3));
    return ((float*)this)[i];
}
//===============================================
inline float Vector3::operator[](int i) const
{
    Assert((i >= 0) && (i < 3));
    return ((float*)this)[i];
}
//===============================================
inline bool Vector3::operator==(const Vector3& src) const
{
    CHECK_VALID(src);
    CHECK_VALID(*this);
    return (src.x == x) && (src.y == y) && (src.z == z);
}
//===============================================
inline bool Vector3::operator!=(const Vector3& src) const
{
    CHECK_VALID(src);
    CHECK_VALID(*this);
    return (src.x != x) || (src.y != y) || (src.z != z);
}
//===============================================
inline void Vector3Copy(const Vector3& src, Vector3& dst)
{
    CHECK_VALID(src);
    dst.x = src.x;
    dst.y = src.y;
    dst.z = src.z;
}
//===============================================
inline  Vector3& Vector3::operator+=(const Vector3& v)
{
    CHECK_VALID(*this);
    CHECK_VALID(v);
    x += v.x; y += v.y; z += v.z;
    return *this;
}
//===============================================
inline  Vector3& Vector3::operator-=(const Vector3& v)
{
    CHECK_VALID(*this);
    CHECK_VALID(v);
    x -= v.x; y -= v.y; z -= v.z;
    return *this;
}
//===============================================
inline  Vector3& Vector3::operator*=(float fl)
{
    x *= fl;
    y *= fl;
    z *= fl;
    CHECK_VALID(*this);
    return *this;
}
//===============================================
inline  Vector3& Vector3::operator*=(const Vector3& v)
{
    CHECK_VALID(v);
    x *= v.x;
    y *= v.y;
    z *= v.z;
    CHECK_VALID(*this);
    return *this;
}
//===============================================
inline Vector3& Vector3::operator+=(float fl)
{
    x += fl;
    y += fl;
    z += fl;
    CHECK_VALID(*this);
    return *this;
}
//===============================================
inline Vector3& Vector3::operator-=(float fl)
{
    x -= fl;
    y -= fl;
    z -= fl;
    CHECK_VALID(*this);
    return *this;
}
//===============================================
inline  Vector3& Vector3::operator/=(float fl)
{
    Assert(fl != 0.0f);
    float oofl = 1.0f / fl;
    x *= oofl;
    y *= oofl;
    z *= oofl;
    CHECK_VALID(*this);
    return *this;
}
//===============================================
inline  Vector3& Vector3::operator/=(const Vector3& v)
{
    CHECK_VALID(v);
    Assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f);
    x /= v.x;
    y /= v.y;
    z /= v.z;
    CHECK_VALID(*this);
    return *this;
}
//===============================================
inline float Vector3::Length(void) const
{
    CHECK_VALID(*this);

    float root = 0.0f;

    float sqsr = x * x + y * y + z * z;

    root = sqrt(sqsr);

    return root;
}
//===============================================
inline float Vector3::Length2D(void) const
{
    CHECK_VALID(*this);

    float root = 0.0f;

    float sqst = x * x + y * y;

    root = sqrt(sqst);

    return root;
}
//===============================================
inline float Vector3::Length2DSqr(void) const
{
    return (x * x + y * y);
}
//===============================================
inline Vector3 CrossProduct(const Vector3& a, const Vector3& b)
{
    return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
//===============================================
float Vector3::DistTo(const Vector3& vOther) const
{
    Vector3 delta;

    delta.x = x - vOther.x;
    delta.y = y - vOther.y;
    delta.z = z - vOther.z;

    return delta.Length();
}
float Vector3::DistToSqr(const Vector3& vOther) const
{
    Vector3 delta;

    delta.x = x - vOther.x;
    delta.y = y - vOther.y;
    delta.z = z - vOther.z;

    return delta.LengthSqr();
}
//===============================================
inline Vector3 Vector3::Normalize()
{
    Vector3 Vector3;
    float length = this->Length();

    if (length != 0)
    {
        Vector3.x = x / length;
        Vector3.y = y / length;
        Vector3.z = z / length;
    }
    else
    {
        Vector3.x = Vector3.y = 0.0f; Vector3.z = 1.0f;
    }

    return Vector3;
}
//===============================================
inline float Vector3::NormalizeInPlace()
{
    Vector3& v = *this;

    float iradius = 1.f / (this->Length() + 1.192092896e-07F); //FLT_EPSILON

    v.x *= iradius;
    v.y *= iradius;
    v.z *= iradius;
}
//===============================================
inline float Vector3Normalize(Vector3& v)
{
    Assert(v.IsValid());
    float l = v.Length();
    if (l != 0.0f)
    {
        v /= l;
    }
    else
    {
        // FIXME:
        // Just copying the existing implemenation; shouldn't res.z == 0?
        v.x = v.y = 0.0f; v.z = 1.0f;
    }
    return l;
}
//===============================================
inline float Vector3Normalize(float* v)
{
    return Vector3Normalize(*(reinterpret_cast<Vector3*>(v)));
}
//===============================================
inline Vector3 Vector3::operator+(const Vector3& v) const
{
    Vector3 res;
    res.x = x + v.x;
    res.y = y + v.y;
    res.z = z + v.z;
    return res;
}

//===============================================
inline Vector3 Vector3::operator-(const Vector3& v) const
{
    Vector3 res;
    res.x = x - v.x;
    res.y = y - v.y;
    res.z = z - v.z;
    return res;
}
//===============================================
inline Vector3 Vector3::operator*(float fl) const
{
    Vector3 res;
    res.x = x * fl;
    res.y = y * fl;
    res.z = z * fl;
    return res;
}
//===============================================
inline Vector3 Vector3::operator*(const Vector3& v) const
{
    Vector3 res;
    res.x = x * v.x;
    res.y = y * v.y;
    res.z = z * v.z;
    return res;
}
//===============================================
inline Vector3 Vector3::operator/(float fl) const
{
    Vector3 res;
    res.x = x / fl;
    res.y = y / fl;
    res.z = z / fl;
    return res;
}
//===============================================
inline Vector3 Vector3::operator/(const Vector3& v) const
{
    Vector3 res;
    res.x = x / v.x;
    res.y = y / v.y;
    res.z = z / v.z;
    return res;
}
inline float Vector3::Dot(const Vector3& vOther) const
{
    const Vector3& a = *this;

    return(a.x * vOther.x + a.y * vOther.y + a.z * vOther.z);
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------

inline float Vector3Length(const Vector3& v)
{
    CHECK_VALID(v);
    return (float)FastSqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

//Vector3 SUBTRAC
inline void Vector3Subtract(const Vector3& a, const Vector3& b, Vector3& c)
{
    CHECK_VALID(a);
    CHECK_VALID(b);
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;
}

//Vector3ADD
inline void Vector3Add(const Vector3& a, const Vector3& b, Vector3& c)
{
    CHECK_VALID(a);
    CHECK_VALID(b);
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
inline float* Vector3::Base()
{
    return (float*)this;
}

inline float const* Vector3::Base() const
{
    return (float const*)this;
}

inline void Vector3MAInline(const float* start, float scale, const float* direction, float* dest)
{
    dest[0] = start[0] + direction[0] * scale;
    dest[1] = start[1] + direction[1] * scale;
    dest[2] = start[2] + direction[2] * scale;
}

inline void Vector3MAInline(const Vector3& start, float scale, const Vector3& direction, Vector3& dest)
{
    dest.x = start.x + direction.x * scale;
    dest.y = start.y + direction.y * scale;
    dest.z = start.z + direction.z * scale;
}

inline void Vector3MA(const Vector3& start, float scale, const Vector3& direction, Vector3& dest)
{
    Vector3MAInline(start, scale, direction, dest);
}

inline void Vector3MA(const float* start, float scale, const float* direction, float* dest)
{
    Vector3MAInline(start, scale, direction, dest);
}

class QAngleByValue;
class QAngle
{
public:
    // Members
    float x, y, z;

    // Construction/destruction
    QAngle(void);
    QAngle(float X, float Y, float Z);
    //      QAngle(RadianEuler const &angles);      // evil auto type promotion!!!

    // Allow pass-by-value
    operator QAngleByValue& () { return *((QAngleByValue*)(this)); }
    operator const QAngleByValue& () const { return *((const QAngleByValue*)(this)); }

    // Initialization
    void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
    void Random(float minVal, float maxVal);

    // Got any nasty NAN's?
    bool IsValid() const;
    void Invalidate();

    // array access...
    float operator[](int i) const;
    float& operator[](int i);

    // Base address...
    float* Base();
    float const* Base() const;

    // equality
    bool operator==(const QAngle& v) const;
    bool operator!=(const QAngle& v) const;

    bool IsZero(float tolerance = 0.01f) const
    {
        return (x > -tolerance && x < tolerance&&
            y > -tolerance && y < tolerance&&
            z > -tolerance && z < tolerance);
    }

    // arithmetic operations
    QAngle& operator+=(const QAngle& v);
    QAngle& operator-=(const QAngle& v);
    QAngle& operator*=(float s);
    QAngle& operator/=(float s);

    // Get the vector's magnitude.
    float   Length() const;
    float   LengthSqr() const;

    // negate the QAngle components
    //void  Negate();

    // No assignment operators either...
    QAngle& operator=(const QAngle& src);

#ifndef VECTOR_NO_SLOW_OPERATIONS
    // copy constructors

    // arithmetic operations
    QAngle  operator-(void) const;

    QAngle  operator+(const QAngle& v) const;
    QAngle  operator-(const QAngle& v) const;
    QAngle  operator*(float fl) const;
    QAngle  operator/(float fl) const;
#else

private:
    // No copy constructors allowed if we're in optimal mode
    QAngle(const QAngle& vOther);

#endif
};

//-----------------------------------------------------------------------------
// constructors
//-----------------------------------------------------------------------------
inline QAngle::QAngle(void)
{
#ifdef _DEBUG
#ifdef VECTOR_PARANOIA
    // Initialize to NAN to catch errors
    x = y = z = VEC_T_NAN;
#endif
#endif
}

inline QAngle::QAngle(float X, float Y, float Z)
{
    x = X; y = Y; z = Z;
    CHECK_VALID(*this);
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------
inline void QAngle::Init(float ix, float iy, float iz)
{
    x = ix; y = iy; z = iz;
    CHECK_VALID(*this);
}

inline void QAngle::Random(float minVal, float maxVal)
{
    x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
    y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
    z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
    CHECK_VALID(*this);
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------
inline QAngle& QAngle::operator=(const QAngle& vOther)
{
    CHECK_VALID(vOther);
    x = vOther.x; y = vOther.y; z = vOther.z;
    return *this;
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------
inline bool QAngle::operator==(const QAngle& src) const
{
    CHECK_VALID(src);
    CHECK_VALID(*this);
    return (src.x == x) && (src.y == y) && (src.z == z);
}

inline bool QAngle::operator!=(const QAngle& src) const
{
    CHECK_VALID(src);
    CHECK_VALID(*this);
    return (src.x != x) || (src.y != y) || (src.z != z);
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------
inline QAngle& QAngle::operator+=(const QAngle& v)
{
    CHECK_VALID(*this);
    CHECK_VALID(v);
    x += v.x; y += v.y; z += v.z;
    return *this;
}

inline QAngle& QAngle::operator-=(const QAngle& v)
{
    CHECK_VALID(*this);
    CHECK_VALID(v);
    x -= v.x; y -= v.y; z -= v.z;
    return *this;
}

inline QAngle& QAngle::operator*=(float fl)
{
    x *= fl;
    y *= fl;
    z *= fl;
    CHECK_VALID(*this);
    return *this;
}

inline QAngle& QAngle::operator/=(float fl)
{
    Assert(fl != 0.0f);
    float oofl = 1.0f / fl;
    x *= oofl;
    y *= oofl;
    z *= oofl;
    CHECK_VALID(*this);
    return *this;
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
inline float* QAngle::Base()
{
    return (float*)this;
}

inline float const* QAngle::Base() const
{
    return (float const*)this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------
inline float& QAngle::operator[](int i)
{
    Assert((i >= 0) && (i < 3));
    return ((float*)this)[i];
}

inline float QAngle::operator[](int i) const
{
    Assert((i >= 0) && (i < 3));
    return ((float*)this)[i];
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
inline float QAngle::Length() const
{
    CHECK_VALID(*this);
    return (float)FastSqrt(LengthSqr());
}


inline float QAngle::LengthSqr() const
{
    CHECK_VALID(*this);
    return x * x + y * y + z * z;
}


//-----------------------------------------------------------------------------
// arithmetic operations (SLOW!!)
//-----------------------------------------------------------------------------
#ifndef VECTOR_NO_SLOW_OPERATIONS

inline QAngle QAngle::operator-(void) const
{
    return QAngle(-x, -y, -z);
}

inline QAngle QAngle::operator+(const QAngle& v) const
{
    QAngle res;
    res.x = x + v.x;
    res.y = y + v.y;
    res.z = z + v.z;
    return res;
}

inline QAngle QAngle::operator-(const QAngle& v) const
{
    QAngle res;
    res.x = x - v.x;
    res.y = y - v.y;
    res.z = z - v.z;
    return res;
}

inline QAngle QAngle::operator*(float fl) const
{
    QAngle res;
    res.x = x * fl;
    res.y = y * fl;
    res.z = z * fl;
    return res;
}

inline QAngle QAngle::operator/(float fl) const
{
    QAngle res;
    res.x = x / fl;
    res.y = y / fl;
    res.z = z / fl;
    return res;
}

inline QAngle operator*(float fl, const QAngle& v)
{
    return v * fl;
}

#endif // VECTOR_NO_SLOW_OPERATIONS


//QANGLE SUBTRAC
inline void QAngleSubtract(const QAngle& a, const QAngle& b, QAngle& c)
{
    CHECK_VALID(a);
    CHECK_VALID(b);
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;
}

//QANGLEADD
inline void QAngleAdd(const QAngle& a, const QAngle& b, QAngle& c)
{
    CHECK_VALID(a);
    CHECK_VALID(b);
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;
}

inline void NormalizeAngles(QAngle& angle)
{
    while (angle.x > 89.0f)
        angle.x -= 180.f;

    while (angle.x < -89.0f)
        angle.x += 180.f;

    while (angle.y > 180.f)
        angle.y -= 360.f;

    while (angle.y < -180.f)
        angle.y += 360.f;
}
inline void NormalizeAngles(Vector3& angle)
{
    while (angle.x > 89.0f)
        angle.x = 89.0;

    while (angle.x < -89.0f)
        angle.x = -89.0f;

    while (angle.y > 180.f)
        angle.y -= 360.f;

    while (angle.y < -180.f)
        angle.y += 360.f;
}
inline void ClampAngles(Vector3& angle)
{
    if (angle.y > 180.0f)
        angle.y = 180.0f;
    else if (angle.y < -180.0f)
        angle.y = -180.0f;

    if (angle.x > 89.0f)
        angle.x = 89.0f;
    else if (angle.x < -89.0f)
        angle.x = -89.0f;

    angle.z = 0;
}
inline float GetFov(const QAngle& viewAngle, const QAngle& aimAngle)
{
    QAngle delta = aimAngle - viewAngle;
    NormalizeAngles(delta);

    return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
}
inline QAngle CalcAngle(const Vector3& src, const Vector3& dst)
{
    QAngle srca = { src.x, src.y, src.z };
    QAngle dsta = { dst.x, dst.y, dst.z };

    QAngle angle;
    QAngle delta = srca - dsta;

    double hyp = sqrtf((delta.x * delta.x) + (delta.y * delta.y));
    angle.x = (float)(atan(delta.z / hyp) * 57.295779513082f);
    angle.y = (float)(atan(delta.y / delta.x) * 57.295779513082f);
    if (delta.x >= 0.0) angle.y += 180.0f;


    return angle;
}
