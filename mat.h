#ifndef MAT_H
#define MAT_H

#include "vec.h"

class mat4
{
public:
	static const mat4 ZERO;
//	static const mat4 ZEROAFFINE;
	static const mat4 IDENTITY;
//	static const mat4 CLIPSPACE2DTOIMAGESPACE;
	static const mat4 CLIPSPACE3DTOIMAGESPACE;

protected:
	// The matrix entries, indexed by [row][col].
	union {
		float m[4][4];
		float _m[16];
	};

public:
	inline mat4()
	{
		operator=(ZERO);
	}

	inline mat4(float a)
	{
		operator=(IDENTITY);
		operator*(a);
	}

	inline mat4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33 )
	{
		m[0][0] = m00;
		m[0][1] = m01;
		m[0][2] = m02;
		m[0][3] = m03;
		m[1][0] = m10;
		m[1][1] = m11;
		m[1][2] = m12;
		m[1][3] = m13;
		m[2][0] = m20;
		m[2][1] = m21;
		m[2][2] = m22;
		m[2][3] = m23;
		m[3][0] = m30;
		m[3][1] = m31;
		m[3][2] = m32;
		m[3][3] = m33;
	}

//	// Creates a standard 4x4 transformation matrix with a zero translation part from a rotation/scaling 3x3 matrix.
//	inline mat4(const Matrix3& m3x3)
//	{
//	  operator=(IDENTITY);
//	  operator=(m3x3);
//	}

//	// Creates a standard 4x4 transformation matrix with a zero translation part from a rotation/scaling Quaternion.
//	inline mat4(const Quaternion& rot)
//	{
//	  Matrix3 m3x3;
//	  rot.ToRotationMatrix(m3x3);
//	  operator=(IDENTITY);
//	  operator=(m3x3);
//	}

//	~mat4(){}

//	// Exchange the contents of this matrix with another.
//	inline void swap(mat4& other)
//	{
//		std::swap(m[0][0], other.m[0][0]);
//		std::swap(m[0][1], other.m[0][1]);
//		std::swap(m[0][2], other.m[0][2]);
//		std::swap(m[0][3], other.m[0][3]);
//		std::swap(m[1][0], other.m[1][0]);
//		std::swap(m[1][1], other.m[1][1]);
//		std::swap(m[1][2], other.m[1][2]);
//		std::swap(m[1][3], other.m[1][3]);
//		std::swap(m[2][0], other.m[2][0]);
//		std::swap(m[2][1], other.m[2][1]);
//		std::swap(m[2][2], other.m[2][2]);
//		std::swap(m[2][3], other.m[2][3]);
//		std::swap(m[3][0], other.m[3][0]);
//		std::swap(m[3][1], other.m[3][1]);
//		std::swap(m[3][2], other.m[3][2]);
//		std::swap(m[3][3], other.m[3][3]);
//	}

	inline float* ptr ()
	{
		return _m;
	}

	inline float* operator [] ( int iRow )
	{
		return m[iRow];
	}

	inline const float *operator [] ( int iRow ) const
	{
		return m[iRow];
	}

	inline mat4 concatenate(const mat4 &m2) const
	{
		mat4 r;
		r.m[0][0] = m[0][0] * m2.m[0][0] + m[0][1] * m2.m[1][0] + m[0][2] * m2.m[2][0] + m[0][3] * m2.m[3][0];
		r.m[0][1] = m[0][0] * m2.m[0][1] + m[0][1] * m2.m[1][1] + m[0][2] * m2.m[2][1] + m[0][3] * m2.m[3][1];
		r.m[0][2] = m[0][0] * m2.m[0][2] + m[0][1] * m2.m[1][2] + m[0][2] * m2.m[2][2] + m[0][3] * m2.m[3][2];
		r.m[0][3] = m[0][0] * m2.m[0][3] + m[0][1] * m2.m[1][3] + m[0][2] * m2.m[2][3] + m[0][3] * m2.m[3][3];

		r.m[1][0] = m[1][0] * m2.m[0][0] + m[1][1] * m2.m[1][0] + m[1][2] * m2.m[2][0] + m[1][3] * m2.m[3][0];
		r.m[1][1] = m[1][0] * m2.m[0][1] + m[1][1] * m2.m[1][1] + m[1][2] * m2.m[2][1] + m[1][3] * m2.m[3][1];
		r.m[1][2] = m[1][0] * m2.m[0][2] + m[1][1] * m2.m[1][2] + m[1][2] * m2.m[2][2] + m[1][3] * m2.m[3][2];
		r.m[1][3] = m[1][0] * m2.m[0][3] + m[1][1] * m2.m[1][3] + m[1][2] * m2.m[2][3] + m[1][3] * m2.m[3][3];

		r.m[2][0] = m[2][0] * m2.m[0][0] + m[2][1] * m2.m[1][0] + m[2][2] * m2.m[2][0] + m[2][3] * m2.m[3][0];
		r.m[2][1] = m[2][0] * m2.m[0][1] + m[2][1] * m2.m[1][1] + m[2][2] * m2.m[2][1] + m[2][3] * m2.m[3][1];
		r.m[2][2] = m[2][0] * m2.m[0][2] + m[2][1] * m2.m[1][2] + m[2][2] * m2.m[2][2] + m[2][3] * m2.m[3][2];
		r.m[2][3] = m[2][0] * m2.m[0][3] + m[2][1] * m2.m[1][3] + m[2][2] * m2.m[2][3] + m[2][3] * m2.m[3][3];

		r.m[3][0] = m[3][0] * m2.m[0][0] + m[3][1] * m2.m[1][0] + m[3][2] * m2.m[2][0] + m[3][3] * m2.m[3][0];
		r.m[3][1] = m[3][0] * m2.m[0][1] + m[3][1] * m2.m[1][1] + m[3][2] * m2.m[2][1] + m[3][3] * m2.m[3][1];
		r.m[3][2] = m[3][0] * m2.m[0][2] + m[3][1] * m2.m[1][2] + m[3][2] * m2.m[2][2] + m[3][3] * m2.m[3][2];
		r.m[3][3] = m[3][0] * m2.m[0][3] + m[3][1] * m2.m[1][3] + m[3][2] * m2.m[2][3] + m[3][3] * m2.m[3][3];

		return r;
	}

	// Matrix concatenation using '*'.
	inline mat4 operator * ( const mat4 &m2 ) const
	{
		return concatenate( m2 );
	}

	// Vector transformation using '*'.
	// 	remarks
	// 		Transforms the given 3-D vector by the matrix, projecting the
	// 		result back into <i>w</i> = 1.
	// 	note
	// 		This means that the initial <i>w</i> is considered to be 1.0,
	// 		and then all the tree elements of the resulting 3-D vector are
	// 		divided by the resulting <i>w</i>.
	inline vec3 operator * ( const vec3 &v ) const
	{
		vec3 r;

		float fInvW = 1.0f / ( m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] );

		r.x = ( m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] ) * fInvW;
		r.y = ( m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] ) * fInvW;
		r.z = ( m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] ) * fInvW;

		return r;
	}
	inline vec4 operator * (const vec4& v) const
	{
		return vec4(
			m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
			m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
			m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
			m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w
			);
	}
//	inline Plane operator * (const Plane& p) const
//	{
//		Plane ret;
//		mat4 invTrans = inverse().transpose();
//		vec4 v4( p.normal.x, p.normal.y, p.normal.z, p.d );
//		v4 = invTrans * v4;
//		ret.normal.x = v4.x;
//		ret.normal.y = v4.y;
//		ret.normal.z = v4.z;
//		ret.d = v4.w / ret.normal.normalise();

//		return ret;
//	}

	inline mat4 operator*(float scalar) const
	{
		return mat4(
			scalar*m[0][0], scalar*m[0][1], scalar*m[0][2], scalar*m[0][3],
			scalar*m[1][0], scalar*m[1][1], scalar*m[1][2], scalar*m[1][3],
			scalar*m[2][0], scalar*m[2][1], scalar*m[2][2], scalar*m[2][3],
			scalar*m[3][0], scalar*m[3][1], scalar*m[3][2], scalar*m[3][3]);
	}

	// Matrix addition.
	inline mat4 operator + ( const mat4 &m2 ) const
	{
		mat4 r;

		r.m[0][0] = m[0][0] + m2.m[0][0];
		r.m[0][1] = m[0][1] + m2.m[0][1];
		r.m[0][2] = m[0][2] + m2.m[0][2];
		r.m[0][3] = m[0][3] + m2.m[0][3];

		r.m[1][0] = m[1][0] + m2.m[1][0];
		r.m[1][1] = m[1][1] + m2.m[1][1];
		r.m[1][2] = m[1][2] + m2.m[1][2];
		r.m[1][3] = m[1][3] + m2.m[1][3];

		r.m[2][0] = m[2][0] + m2.m[2][0];
		r.m[2][1] = m[2][1] + m2.m[2][1];
		r.m[2][2] = m[2][2] + m2.m[2][2];
		r.m[2][3] = m[2][3] + m2.m[2][3];

		r.m[3][0] = m[3][0] + m2.m[3][0];
		r.m[3][1] = m[3][1] + m2.m[3][1];
		r.m[3][2] = m[3][2] + m2.m[3][2];
		r.m[3][3] = m[3][3] + m2.m[3][3];

		return r;
	}

	// Matrix subtraction.
	inline mat4 operator - ( const mat4 &m2 ) const
	{
		mat4 r;
		r.m[0][0] = m[0][0] - m2.m[0][0];
		r.m[0][1] = m[0][1] - m2.m[0][1];
		r.m[0][2] = m[0][2] - m2.m[0][2];
		r.m[0][3] = m[0][3] - m2.m[0][3];

		r.m[1][0] = m[1][0] - m2.m[1][0];
		r.m[1][1] = m[1][1] - m2.m[1][1];
		r.m[1][2] = m[1][2] - m2.m[1][2];
		r.m[1][3] = m[1][3] - m2.m[1][3];

		r.m[2][0] = m[2][0] - m2.m[2][0];
		r.m[2][1] = m[2][1] - m2.m[2][1];
		r.m[2][2] = m[2][2] - m2.m[2][2];
		r.m[2][3] = m[2][3] - m2.m[2][3];

		r.m[3][0] = m[3][0] - m2.m[3][0];
		r.m[3][1] = m[3][1] - m2.m[3][1];
		r.m[3][2] = m[3][2] - m2.m[3][2];
		r.m[3][3] = m[3][3] - m2.m[3][3];

		return r;
	}

	// Tests 2 matrices for equality.
	inline bool operator == ( const mat4& m2 ) const
	{
		if(
			m[0][0] != m2.m[0][0] || m[0][1] != m2.m[0][1] || m[0][2] != m2.m[0][2] || m[0][3] != m2.m[0][3] ||
			m[1][0] != m2.m[1][0] || m[1][1] != m2.m[1][1] || m[1][2] != m2.m[1][2] || m[1][3] != m2.m[1][3] ||
			m[2][0] != m2.m[2][0] || m[2][1] != m2.m[2][1] || m[2][2] != m2.m[2][2] || m[2][3] != m2.m[2][3] ||
			m[3][0] != m2.m[3][0] || m[3][1] != m2.m[3][1] || m[3][2] != m2.m[3][2] || m[3][3] != m2.m[3][3] )
			return false;
		return true;
	}

	// Tests 2 matrices for inequality.
	inline bool operator != ( const mat4& m2 ) const
	{
		if(
			m[0][0] != m2.m[0][0] || m[0][1] != m2.m[0][1] || m[0][2] != m2.m[0][2] || m[0][3] != m2.m[0][3] ||
			m[1][0] != m2.m[1][0] || m[1][1] != m2.m[1][1] || m[1][2] != m2.m[1][2] || m[1][3] != m2.m[1][3] ||
			m[2][0] != m2.m[2][0] || m[2][1] != m2.m[2][1] || m[2][2] != m2.m[2][2] || m[2][3] != m2.m[2][3] ||
			m[3][0] != m2.m[3][0] || m[3][1] != m2.m[3][1] || m[3][2] != m2.m[3][2] || m[3][3] != m2.m[3][3] )
			return true;
		return false;
	}

//	// Assignment from 3x3 matrix.
//	inline void operator = ( const Matrix3& mat3 )
//	{
//		m[0][0] = mat3.m[0][0]; m[0][1] = mat3.m[0][1]; m[0][2] = mat3.m[0][2];
//		m[1][0] = mat3.m[1][0]; m[1][1] = mat3.m[1][1]; m[1][2] = mat3.m[1][2];
//		m[2][0] = mat3.m[2][0]; m[2][1] = mat3.m[2][1]; m[2][2] = mat3.m[2][2];
//	}

	inline mat4 transpose(void) const
	{
		return mat4(m[0][0], m[1][0], m[2][0], m[3][0],
					   m[0][1], m[1][1], m[2][1], m[3][1],
					   m[0][2], m[1][2], m[2][2], m[3][2],
					   m[0][3], m[1][3], m[2][3], m[3][3]);
	}

	mat4 adjoint() const;
	float determinant() const;
	mat4 inverse() const;

	// -----------------------------------------------------------------------
	// Translation Transformation
	// -----------------------------------------------------------------------

	// Sets the translation transformation part of the matrix.
	inline void setTrans( const vec3& v )
	{
		m[0][3] = v.x;
		m[1][3] = v.y;
		m[2][3] = v.z;
	}

	// Extracts the translation transformation part of the matrix.
	inline vec3 getTrans() const
	{
	  return vec3(m[0][3], m[1][3], m[2][3]);
	}


	// Builds a translation matrix
	inline void makeTrans( const vec3& v )
	{
		m[0][0] = 1.0; m[0][1] = 0.0; m[0][2] = 0.0; m[0][3] = v.x;
		m[1][0] = 0.0; m[1][1] = 1.0; m[1][2] = 0.0; m[1][3] = v.y;
		m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] = 1.0; m[2][3] = v.z;
		m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = 0.0; m[3][3] = 1.0;
	}

	inline void makeTrans( float tx, float ty, float tz )
	{
		m[0][0] = 1.0; m[0][1] = 0.0; m[0][2] = 0.0; m[0][3] = tx;
		m[1][0] = 0.0; m[1][1] = 1.0; m[1][2] = 0.0; m[1][3] = ty;
		m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] = 1.0; m[2][3] = tz;
		m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = 0.0; m[3][3] = 1.0;
	}

	// Gets a translation matrix.
	inline static mat4 getTrans( const vec3& v )
	{
		mat4 r;

		r.m[0][0] = 1.0; r.m[0][1] = 0.0; r.m[0][2] = 0.0; r.m[0][3] = v.x;
		r.m[1][0] = 0.0; r.m[1][1] = 1.0; r.m[1][2] = 0.0; r.m[1][3] = v.y;
		r.m[2][0] = 0.0; r.m[2][1] = 0.0; r.m[2][2] = 1.0; r.m[2][3] = v.z;
		r.m[3][0] = 0.0; r.m[3][1] = 0.0; r.m[3][2] = 0.0; r.m[3][3] = 1.0;

		return r;
	}

	// Gets a translation matrix - variation for not using a vector.
	inline static mat4 getTrans( float t_x, float t_y, float t_z )
	{
		mat4 r;

		r.m[0][0] = 1.0; r.m[0][1] = 0.0; r.m[0][2] = 0.0; r.m[0][3] = t_x;
		r.m[1][0] = 0.0; r.m[1][1] = 1.0; r.m[1][2] = 0.0; r.m[1][3] = t_y;
		r.m[2][0] = 0.0; r.m[2][1] = 0.0; r.m[2][2] = 1.0; r.m[2][3] = t_z;
		r.m[3][0] = 0.0; r.m[3][1] = 0.0; r.m[3][2] = 0.0; r.m[3][3] = 1.0;

		return r;
	}

	// -----------------------------------------------------------------------
	// Scale Transformation
	// -----------------------------------------------------------------------

	// Sets the scale part of the matrix.
	inline void setScale( const vec3& v )
	{
		m[0][0] = v.x;
		m[1][1] = v.y;
		m[2][2] = v.z;
	}

	// Gets a scale matrix.
	inline static mat4 getScale( const vec3& v )
	{
		mat4 r;
		r.m[0][0] = v.x; r.m[0][1] = 0.0; r.m[0][2] = 0.0; r.m[0][3] = 0.0;
		r.m[1][0] = 0.0; r.m[1][1] = v.y; r.m[1][2] = 0.0; r.m[1][3] = 0.0;
		r.m[2][0] = 0.0; r.m[2][1] = 0.0; r.m[2][2] = v.z; r.m[2][3] = 0.0;
		r.m[3][0] = 0.0; r.m[3][1] = 0.0; r.m[3][2] = 0.0; r.m[3][3] = 1.0;

		return r;
	}

	// Gets a scale matrix - variation for not using a vector.
	inline static mat4 getScale( float s_x, float s_y, float s_z )
	{
		mat4 r;
		r.m[0][0] = s_x; r.m[0][1] = 0.0; r.m[0][2] = 0.0; r.m[0][3] = 0.0;
		r.m[1][0] = 0.0; r.m[1][1] = s_y; r.m[1][2] = 0.0; r.m[1][3] = 0.0;
		r.m[2][0] = 0.0; r.m[2][1] = 0.0; r.m[2][2] = s_z; r.m[2][3] = 0.0;
		r.m[3][0] = 0.0; r.m[3][1] = 0.0; r.m[3][2] = 0.0; r.m[3][3] = 1.0;

		return r;
	}

//	// Extracts the rotation / scaling part of the Matrix as a 3x3 matrix.
//	inline void extract3x3Matrix(Matrix3& m3x3) const
//	{
//		m3x3.m[0][0] = m[0][0];
//		m3x3.m[0][1] = m[0][1];
//		m3x3.m[0][2] = m[0][2];
//		m3x3.m[1][0] = m[1][0];
//		m3x3.m[1][1] = m[1][1];
//		m3x3.m[1][2] = m[1][2];
//		m3x3.m[2][0] = m[2][0];
//		m3x3.m[2][1] = m[2][1];
//		m3x3.m[2][2] = m[2][2];

//	}

//	/** Determines if this matrix involves a scaling. */
//	inline bool hasScale() const
//	{
//		// check magnitude of column vectors (==local axes)
//		float t = m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0];
//		if (!Math::floatEqual(t, 1.0, (float)1e-04))
//			return true;
//		t = m[0][1] * m[0][1] + m[1][1] * m[1][1] + m[2][1] * m[2][1];
//		if (!Math::floatEqual(t, 1.0, (float)1e-04))
//			return true;
//		t = m[0][2] * m[0][2] + m[1][2] * m[1][2] + m[2][2] * m[2][2];
//		if (!Math::floatEqual(t, 1.0, (float)1e-04))
//			return true;

//		return false;
//	}

//	/** Determines if this matrix involves a negative scaling. */
//	inline bool hasNegativeScale() const
//	{
//		return determinant() < 0;
//	}

//	/** Extracts the rotation / scaling part as a quaternion from the Matrix. */
//	inline Quaternion extractQuaternion() const
//	{
//		Matrix3 m3x3;
//		extract3x3Matrix(m3x3);
//		return Quaternion(m3x3);
//	}

//	/** Function for writing to a stream. */
//	inline _OgreExport friend std::ostream& operator <<
//		( std::ostream& o, const mat4& mat )
//	{
//		o << "mat4(";
//		for (int i = 0; i < 4; ++i)
//		{
//			o << " row" << (unsigned)i << "{";
//			for(int j = 0; j < 4; ++j)
//			{
//				o << mat[i][j] << " ";
//			}
//			o << "}";
//		}
//		o << ")";
//		return o;
//	}

//	/** Building a mat4 from orientation / scale / position.
//	@remarks
//		Transform is performed in the order scale, rotate, translation, i.e. translation is independent
//		of orientation axes, scale does not affect size of translation, rotation and scaling are always
//		centered on the origin.
//	*/
//	void makeTransform(const Vector3& position, const Vector3& scale, const Quaternion& orientation);

//	/** Building an inverse mat4 from orientation / scale / position.
//	@remarks
//		As makeTransform except it build the inverse given the same data as makeTransform, so
//		performing -translation, -rotate, 1/scale in that order.
//	*/
//	void makeInverseTransform(const Vector3& position, const Vector3& scale, const Quaternion& orientation);

//	/** Decompose a mat4 to orientation / scale / position.
//	*/
//	void decomposition(Vector3& position, Vector3& scale, Quaternion& orientation) const;

//	/** Check whether or not the matrix is affine matrix.
//		@remarks
//			An affine matrix is a 4x4 matrix with row 3 equal to (0, 0, 0, 1),
//			e.g. no projective coefficients.
//	*/
//	inline bool isAffine(void) const
//	{
//		return m[3][0] == 0 && m[3][1] == 0 && m[3][2] == 0 && m[3][3] == 1;
//	}

//	/** Returns the inverse of the affine matrix.
//		@note
//			The matrix must be an affine matrix. @see mat4::isAffine.
//	*/
//	mat4 inverseAffine(void) const;

//	/** Concatenate two affine matrices.
//		@note
//			The matrices must be affine matrix. @see mat4::isAffine.
//	*/
//	inline mat4 concatenateAffine(const mat4 &m2) const
//	{
//		assert(isAffine() && m2.isAffine());

//		return mat4(
//			m[0][0] * m2.m[0][0] + m[0][1] * m2.m[1][0] + m[0][2] * m2.m[2][0],
//			m[0][0] * m2.m[0][1] + m[0][1] * m2.m[1][1] + m[0][2] * m2.m[2][1],
//			m[0][0] * m2.m[0][2] + m[0][1] * m2.m[1][2] + m[0][2] * m2.m[2][2],
//			m[0][0] * m2.m[0][3] + m[0][1] * m2.m[1][3] + m[0][2] * m2.m[2][3] + m[0][3],

//			m[1][0] * m2.m[0][0] + m[1][1] * m2.m[1][0] + m[1][2] * m2.m[2][0],
//			m[1][0] * m2.m[0][1] + m[1][1] * m2.m[1][1] + m[1][2] * m2.m[2][1],
//			m[1][0] * m2.m[0][2] + m[1][1] * m2.m[1][2] + m[1][2] * m2.m[2][2],
//			m[1][0] * m2.m[0][3] + m[1][1] * m2.m[1][3] + m[1][2] * m2.m[2][3] + m[1][3],

//			m[2][0] * m2.m[0][0] + m[2][1] * m2.m[1][0] + m[2][2] * m2.m[2][0],
//			m[2][0] * m2.m[0][1] + m[2][1] * m2.m[1][1] + m[2][2] * m2.m[2][1],
//			m[2][0] * m2.m[0][2] + m[2][1] * m2.m[1][2] + m[2][2] * m2.m[2][2],
//			m[2][0] * m2.m[0][3] + m[2][1] * m2.m[1][3] + m[2][2] * m2.m[2][3] + m[2][3],

//			0, 0, 0, 1);
//	}

//	/** 3-D Vector transformation specially for an affine matrix.
//		@remarks
//			Transforms the given 3-D vector by the matrix, projecting the
//			result back into <i>w</i> = 1.
//		@note
//			The matrix must be an affine matrix. @see mat4::isAffine.
//	*/
//	inline Vector3 transformAffine(const Vector3& v) const
//	{
//		assert(isAffine());

//		return Vector3(
//				m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3],
//				m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3],
//				m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3]);
//	}

//	/** 4-D Vector transformation specially for an affine matrix.
//		@note
//			The matrix must be an affine matrix. @see mat4::isAffine.
//	*/
//	inline Vector4 transformAffine(const Vector4& v) const
//	{
//		assert(isAffine());

//		return Vector4(
//			m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
//			m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
//			m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
//			v.w);
//	}

};

// Removed from Vector4 and made a non-member here because otherwise
// mat.h and vec.h have to try to include and inline each
// other, which frankly doesn't work ;)
inline vec4 operator * (const vec4& v, const mat4& mat)
{
	return vec4(
		v.x*mat[0][0] + v.y*mat[1][0] + v.z*mat[2][0] + v.w*mat[3][0],
		v.x*mat[0][1] + v.y*mat[1][1] + v.z*mat[2][1] + v.w*mat[3][1],
		v.x*mat[0][2] + v.y*mat[1][2] + v.z*mat[2][2] + v.w*mat[3][2],
		v.x*mat[0][3] + v.y*mat[1][3] + v.z*mat[2][3] + v.w*mat[3][3]
		);
}

#endif // MAT_H
