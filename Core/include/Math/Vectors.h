#ifndef _VECTORS_H_
#define _VECTORS_H_

#include <cstdlib>
#include <Utility/Limits.h>
#include <string.h>
#include <math.h>

// Magic! I wonder if this is actually faster.
inline float InvSqrt( float x )
{
	float xhalf = 0.5f * x;
	int i = *reinterpret_cast< int * >( &x ); // store floating-point bits in integer
	i = 0x5f3759d5 - ( i >> 1 ); // initial guess for Newton's method
	x = *reinterpret_cast< float * >( &i ); // convert new bits into float
	x = x * ( 1.5f - xhalf * x * x ); // One round of Newton's method
	return x;
}

/**
 * 2-vector.
 */
class Vector2
{

public:

	float X;
	float Y;

	Vector2() : X( 0 ), Y( 0 ) { }
	Vector2( const Vector2 &other ) : X( other.X ), Y( other.Y ) { }
	Vector2( float x, float y ) : X( x ), Y( y ) { }
	explicit Vector2( float x ) : X( x ), Y( x ) { }

	float x() const { return X; }
	float y() const { return Y; }

	float LengthSquared() const { return X * X + Y * Y; }
	
	float Length() const { return sqrtf( LengthSquared() ); }
	
	void Normalize()
	{
		float length = Length();
		X /= length;
		Y /= length;
	}

	void FastNormalize()
	{
		float invsqrt = InvSqrt( LengthSquared() );
		X *= invsqrt;
		Y *= invsqrt;
	}

	Vector2 Normalized() const
	{
		float length = Length();
		return Vector2( X / length, Y / length );
	}

	Vector2 FastNormalized() const
	{
		float invsqrt = InvSqrt( LengthSquared() );
		return Vector2( X * invsqrt, Y * invsqrt );
	}

	static Vector2 CatmullRom(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4, float t)
	{
		Vector2 v;

		float t2 = t * t;
		float t3 = t * t2;

		v.X = 0.5f * ((((2.f * v2.X) + ((-v1.X + v3.X) * t)) + (((((2.f * v1.X) - (5.f * v2.X)) + (4.f * v3.X)) - v4.X) * t2)) + ((((-v1.X + (3.f * v2.X)) - (3.f * v3.X)) + v4.X) * t3));
		v.Y = 0.5f * ((((2.f * v2.Y) + ((-v1.Y + v3.Y) * t)) + (((((2.f * v1.Y) - (5.f * v2.Y)) + (4.f * v3.Y)) - v4.Y) * t2)) + ((((-v1.Y + (3.f * v2.Y)) - (3.f * v3.Y)) + v4.Y) * t3));
		
		return v;
	}

	static float Distance( const Vector2 &a, const Vector2 &b )
	{
		return ( b - a ).Length();
	}

	static float Dot( const Vector2 &a, const Vector2 &b )
	{
		return a.X * b.X + a.Y * b.Y;
	}

	static Vector2 Min( const Vector2 &a, const Vector2 &b )
	{
		return Vector2( __min( a.X, b.X ), __min( a.Y, b.Y ) );
	}

	static Vector2 Max( const Vector2 &a, const Vector2 &b )
	{
		return Vector2( __max( a.X, b.X ), __max( a.Y, b.Y ) );
	}

    /// <summary>
    /// Whether the vector is less than or equal to another vector in both components
    /// </summary>
    bool LE(Vector2 a)
    {
        if (X <= a.X && Y <= a.Y) return true;
        return false;
    }
    /// <summary>
    /// Whether the vector is greater than or equal to another vector in both components
    /// </summary>
    bool GE(Vector2 a)
    {
        if (X >= a.X && Y >= a.Y) return true;
        return false;
    }

	Vector2 &operator += ( const Vector2 &a )
	{
		X += a.x();
		Y += a.y();
		return *this;
	}

	Vector2 &operator -= ( const Vector2 &a )
	{
		X -= a.X;
		Y -= a.Y;
		return *this;
	}

	Vector2 &operator *= ( float k )
	{
		X *= k;
		Y *= k;
		return *this;
	}

	Vector2 &operator *= ( const Vector2 &a )
	{
		X *= a.X;
		Y *= a.Y;
		return *this;
	}

	Vector2 &operator /= ( float k )
	{
		X /= k;
		Y /= k;
		return *this;
	}

	Vector2 operator / ( const Vector2 &a )
	{
		return Vector2( X / a.X, Y / a.Y );
	}

	Vector2 operator + ( const Vector2 &a ) const
	{
		return Vector2( X + a.X, Y + a.Y );
	}

	Vector2 operator * ( float k ) const
	{
		return Vector2( X * k, Y * k );
	}

	Vector2 operator * ( const Vector2 &a )
	{
		return Vector2( X * a.X, Y * a.Y );
	}

	Vector2 operator - ( const Vector2 &a ) const
	{
		return Vector2( X - a.X, Y - a.Y );
	}

	Vector2 operator / ( float k ) const
	{
		return Vector2( X / k, Y / k );
	}

	Vector2 operator / ( const Vector2 &a ) const
	{
		return Vector2( X / a.X, Y / a.Y );
	}

	bool operator == ( const Vector2 &a ) const
	{
		return X == a.X && Y == a.Y;
	}

	bool operator != ( const Vector2 &a ) const
	{
		return !( *this == a );
	}

	static Vector2 Lerp( const Vector2 &a, const Vector2 &b, float t )
	{
		return a * ( 1 - t ) + b * t;
	}

};

inline Vector2 operator * ( float k, const Vector2 &a )
{
	return a * k;
}

class Vector3
{

public:

	float X;
	float Y;
	float Z;

	Vector3() : X(0), Y(0), Z(0) { }
	Vector3( const Vector3 &other ) : X( other.X ), Y( other.Y ), Z( other.Z ) { }
	Vector3( float x, float y, float z ) : X(x), Y(y), Z(z) { }
	explicit Vector3( float x ) : X(x), Y(x), Z(x) { }

	static Vector3 Lerp( const Vector3 &v1, const Vector3 &v2, float t )
	{
		return v1 * ( 1 - t ) + v2 * t;
	}

	static Vector3 CatmullRom(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4, float t)
	{
		Vector3 v;

		float t2 = t * t;
		float t3 = t * t2;

		v.X = 0.5f * ((((2.f * v2.X) + ((-v1.X + v3.X) * t)) + (((((2.f * v1.X) - (5.f * v2.X)) + (4.f * v3.X)) - v4.X) * t2)) + ((((-v1.X + (3.f * v2.X)) - (3.f * v3.X)) + v4.X) * t3));
		v.Y = 0.5f * ((((2.f * v2.Y) + ((-v1.Y + v3.Y) * t)) + (((((2.f * v1.Y) - (5.f * v2.Y)) + (4.f * v3.Y)) - v4.Y) * t2)) + ((((-v1.Y + (3.f * v2.Y)) - (3.f * v3.Y)) + v4.Y) * t3));
		v.Z = 0.5f * ((((2.f * v2.Z) + ((-v1.Z + v3.Z) * t)) + (((((2.f * v1.Z) - (5.f * v2.Z)) + (4.f * v3.Z)) - v4.Z) * t2)) + ((((-v1.Z + (3.f * v2.Z)) - (3.f * v3.Z)) + v4.Z) * t3));
		
		return v;
	}

	Vector3 operator + ( const Vector3 &a ) const
	{
		return Vector3( X + a.X, Y + a.Y, Z + a.Z );
	}

	Vector3 operator * ( float k ) const
	{
		return Vector3( X * k, Y * k, Z * k );
	}

};

inline Vector3 operator * ( float k, const Vector3 &a )
{
	return a * k;
}

class Vector4
{

public:

	float X;
	float Y;
	float Z;
	float W;

	Vector4() : X( 0 ), Y( 0 ), Z( 0 ), W( 0 ) { }
	Vector4( const Vector4 &other) : X( other.X ), Y( other.Y ),
		Z( other.Z ), W( other.W ) { }
	explicit Vector4( float x ) : X( x ), Y( x ), Z( x ), W( x ) { }
	Vector4( float x, float y, float z, float w ) :
		X( x ), Y( y ), Z( z ), W( w ) { }

	float x() const { return X; }
	float y() const { return Y; }
	float z() const { return Z; }
	float w() const { return W; }

	float r() const { return X; }
	float g() const { return Y; }
	float b() const { return Z; }
	float a() const { return W; }

	static Vector4 Lerp( const Vector4 &a, const Vector4 &b, float t )
	{
		return a * ( 1 - t ) + b * t;
	}

	Vector4 operator + ( const Vector4 &a ) const
	{
		return Vector4( X + a.X, Y + a.Y, Z + a.Z, W + a.W );
	}

	Vector4 operator - ( const Vector4 &a ) const
	{
		return Vector4( X - a.X, Y - a.Y, Z - a.Z, W - a.W );
	}

	Vector4 operator * ( const Vector4 &a ) const
	{
		return Vector4( X * a.X, Y * a.Y, Z * a.Z, W * a.W );
	}

	Vector4 operator * ( float k ) const
	{
		return Vector4( X * k, Y * k, Z * k, W * k );
	}

	Vector4 &operator *= ( const Vector4 &a )
	{
		X *= a.X;
		Y *= a.Y;
		Z *= a.Z;
		W *= a.W;
		return *this;
	}

	Vector4 &operator *= ( float k )
	{
		X *= k;
		Y *= k;
		Z *= k;
		W *= k;
		return *this;
	}

	Vector4 &operator += ( const Vector4 &a )
	{
		X += a.X;
		Y += a.Y;
		Z += a.Z;
		W += a.W;
		return *this;
	}

	bool operator == ( const Vector4 &a ) const
	{
		return X == a.X && Y == a.Y && Z == a.Z && W == a.W;
	}

	bool operator != ( const Vector4 &a ) const
	{
		return !( *this == a );
	}

};

inline Vector4 operator * ( float k, const Vector4 &a )
{
	return a * k;
}


class Matrix
{

public:

	union
	{
		struct
		{
			float M11, M12, M13, M14;
			float M21, M22, M23, M24;
			float M31, M32, M33, M34;
			float M41, M42, M43, M44;
		};

		float M[16];
	};

	Matrix()
	{
		memset( &M11, 0, sizeof( Matrix ) );
	}

	// FIXME: Might need to transpose this.
	Matrix( float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44 ) :
		M11( m11 ), M12( m12 ), M13( m13 ), M14( m14 ),
		M21( m21 ), M22( m22 ), M23( m23 ), M24( m24 ),
		M31( m31 ), M32( m32 ), M33( m33 ), M34( m34 ),
		M41( m41 ), M42( m42 ), M43( m43 ), M44( m44 )
	{
	}

	static Matrix Identity()
	{
		Matrix m;
		memset( &m, 0, sizeof( Matrix ) );
		m.M11 = m.M22 = m.M33 = m.M44 = 1.f;
		return m;
	}

	static Matrix CreateScale( float x, float y, float z )
	{
		Matrix m = Identity();
		m.M11 = x;
		m.M22 = y;
		m.M33 = z;
		return m;
	}

	const Matrix operator * ( float s ) const
	{
		return Matrix( M11 * s, M12 * s, M13 * s, M14 * s,
					   M21 * s, M22 * s, M23 * s, M24 * s,
					   M31 * s, M32 * s, M33 * s, M34 * s,
					   M41 * s, M42 * s, M43 * s, M44 * s );
	}

	const Matrix operator + ( const Matrix &m ) const
	{
		return Matrix( M11 + m.M11, M12 + m.M12, M13 + m.M13, M14 + m.M14,
					   M21 + m.M21, M22 + m.M22, M23 + m.M23, M24 + m.M24,
					   M31 + m.M31, M32 + m.M32, M33 + m.M33, M34 + m.M34,
					   M41 + m.M41, M42 + m.M42, M43 + m.M43, M44 + m.M44 );
	}

	const Matrix operator * ( const Matrix &m ) const
	{
		Matrix product = Matrix(
			M11 * m.M11 + M12 * m.M21 + M13 * m.M31 + M14 * m.M41,
			M11 * m.M12 + M12 * m.M22 + M13 * m.M32 + M14 * m.M42,
			M11 * m.M13 + M12 * m.M23 + M13 * m.M33 + M14 * m.M43,
			M11 * m.M14 + M12 * m.M24 + M13 * m.M34 + M14 * m.M44,

			M21 * m.M11 + M22 * m.M21 + M23 * m.M31 + M24 * m.M41,
			M21 * m.M12 + M22 * m.M22 + M23 * m.M32 + M24 * m.M42,
			M21 * m.M13 + M22 * m.M23 + M23 * m.M33 + M24 * m.M43,
			M21 * m.M14 + M22 * m.M24 + M23 * m.M34 + M24 * m.M44,

			M31 * m.M11 + M32 * m.M21 + M33 * m.M31 + M34 * m.M41,
			M31 * m.M12 + M32 * m.M22 + M33 * m.M32 + M34 * m.M42,
			M31 * m.M13 + M32 * m.M23 + M33 * m.M33 + M34 * m.M43,
			M31 * m.M14 + M32 * m.M24 + M33 * m.M34 + M34 * m.M44,

			M41 * m.M11 + M42 * m.M21 + M43 * m.M31 + M44 * m.M41,
			M41 * m.M12 + M42 * m.M22 + M43 * m.M32 + M44 * m.M42,
			M41 * m.M13 + M42 * m.M23 + M43 * m.M33 + M44 * m.M43,
			M41 * m.M14 + M42 * m.M24 + M43 * m.M34 + M44 * m.M44 );

		return product;
	}
};

static const Matrix operator * ( float s, const Matrix &m )
{
	return m * s;
}

#endif
