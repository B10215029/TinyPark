#ifndef VEC_H
#define VEC_H

#include <cmath>

class vec3
{
public:
	static const vec3 ZERO;
	static const vec3 UNIT_X;
	static const vec3 UNIT_Y;
	static const vec3 UNIT_Z;
	static const vec3 NEGATIVE_UNIT_X;
	static const vec3 NEGATIVE_UNIT_Y;
	static const vec3 NEGATIVE_UNIT_Z;
	static const vec3 UNIT_SCALE;

	float x, y, z;

public:
	inline vec3()
	{
		operator=(ZERO);
	}

	inline vec3( const float fX, const float fY, const float fZ )
		: x( fX ), y( fY ), z( fZ )
	{
	}

	inline explicit vec3( const float afCoordinate[3] )
		: x( afCoordinate[0] ),
		  y( afCoordinate[1] ),
		  z( afCoordinate[2] )
	{
	}

	inline explicit vec3( const int afCoordinate[3] )
	{
		x = (float)afCoordinate[0];
		y = (float)afCoordinate[1];
		z = (float)afCoordinate[2];
	}

	inline explicit vec3( float* const r )
		: x( r[0] ), y( r[1] ), z( r[2] )
	{
	}

	inline explicit vec3( const float scaler )
		: x( scaler )
		, y( scaler )
		, z( scaler )
	{
	}


//	// Exchange the contents of this vector with another.
//	inline void swap(vec3& other)
//	{
//		std::swap(x, other.x);
//		std::swap(y, other.y);
//		std::swap(z, other.z);
//	}

	inline float operator [] ( const int i ) const
	{
		//assert( i < 3 );

		return *(&x+i);
	}

	inline float& operator [] ( const int i )
	{
		//assert( i < 3 );

		return *(&x+i);
	}
	/// Pointer accessor for direct copying
	inline float* ptr()
	{
		return &x;
	}
	/// Pointer accessor for direct copying
	inline const float* ptr() const
	{
		return &x;
	}

	// Assigns the value of the other vector.
	// 	param
	//		rkVector The other vector
	inline vec3& operator = ( const vec3& rkVector )
	{
		x = rkVector.x;
		y = rkVector.y;
		z = rkVector.z;

		return *this;
	}

	inline vec3& operator = ( const float fScaler )
	{
		x = fScaler;
		y = fScaler;
		z = fScaler;

		return *this;
	}

	inline bool operator == ( const vec3& rkVector ) const
	{
		return ( x == rkVector.x && y == rkVector.y && z == rkVector.z );
	}

	inline bool operator != ( const vec3& rkVector ) const
	{
		return ( x != rkVector.x || y != rkVector.y || z != rkVector.z );
	}

	// arithmetic operations
	inline vec3 operator + ( const vec3& rkVector ) const
	{
		return vec3(
			x + rkVector.x,
			y + rkVector.y,
			z + rkVector.z);
	}

	inline vec3 operator - ( const vec3& rkVector ) const
	{
		return vec3(
			x - rkVector.x,
			y - rkVector.y,
			z - rkVector.z);
	}

	inline vec3 operator * ( const float fScalar ) const
	{
		return vec3(
			x * fScalar,
			y * fScalar,
			z * fScalar);
	}

	inline vec3 operator * ( const vec3& rhs) const
	{
		return vec3(
			x * rhs.x,
			y * rhs.y,
			z * rhs.z);
	}

	inline vec3 operator / ( const float fScalar ) const
	{
		//assert( fScalar != 0.0 );
		float fInv = 1.0f / fScalar;
		return vec3(
			x * fInv,
			y * fInv,
			z * fInv);
	}

	inline vec3 operator / ( const vec3& rhs) const
	{
		return vec3(
			x / rhs.x,
			y / rhs.y,
			z / rhs.z);
	}

	inline const vec3& operator + () const
	{
		return *this;
	}

	inline vec3 operator - () const
	{
		return vec3(-x, -y, -z);
	}

	// arithmetic updates
	inline vec3& operator += ( const vec3& rkVector )
	{
		x += rkVector.x;
		y += rkVector.y;
		z += rkVector.z;

		return *this;
	}

	inline vec3& operator += ( const float fScalar )
	{
		x += fScalar;
		y += fScalar;
		z += fScalar;
		return *this;
	}

	inline vec3& operator -= ( const vec3& rkVector )
	{
		x -= rkVector.x;
		y -= rkVector.y;
		z -= rkVector.z;

		return *this;
	}

	inline vec3& operator -= ( const float fScalar )
	{
		x -= fScalar;
		y -= fScalar;
		z -= fScalar;
		return *this;
	}

	inline vec3& operator *= ( const float fScalar )
	{
		x *= fScalar;
		y *= fScalar;
		z *= fScalar;
		return *this;
	}

	inline vec3& operator *= ( const vec3& rkVector )
	{
		x *= rkVector.x;
		y *= rkVector.y;
		z *= rkVector.z;

		return *this;
	}

	inline vec3& operator /= ( const float fScalar )
	{
		//assert( fScalar != 0.0 );

		float fInv = 1.0f / fScalar;

		x *= fInv;
		y *= fInv;
		z *= fInv;

		return *this;
	}

	inline vec3& operator /= ( const vec3& rkVector )
	{
		x /= rkVector.x;
		y /= rkVector.y;
		z /= rkVector.z;

		return *this;
	}


	// Returns the length (magnitude) of the vector.
	//	warning
	//		This operation requires a square root and is expensive in
	//		terms of CPU operations. If you don't need to know the exact
	//		length (e.g. for just comparing lengths) use squaredLength()
	//		instead.
	inline float length () const
	{
		return sqrt( x * x + y * y + z * z );
	}

	// Returns the square of the length(magnitude) of the vector.
	// 	remarks
	// 		This  method is for efficiency - calculating the actual
	// 		length of a vector requires a square root, which is expensive
	// 		in terms of the operations required. This method returns the
	// 		square of the length of the vector, i.e. the same as the
	// 		length but before the square root is taken. Use this if you
	// 		want to find the longest / shortest vector without incurring
	// 		the square root.
	inline float squaredLength () const
	{
		return x * x + y * y + z * z;
	}

	// Returns the distance to another vector.
	// 	warning
	// 		This operation requires a square root and is expensive in
	// 		terms of CPU operations. If you don't need to know the exact
	// 		distance (e.g. for just comparing distances) use squaredDistance()
	// 		instead.
	inline float distance(const vec3& rhs) const
	{
		return (*this - rhs).length();
	}

	// Returns the square of the distance to another vector.
	// 	remarks
	// 		This method is for efficiency - calculating the actual
	// 		distance to another vector requires a square root, which is
	// 		expensive in terms of the operations required. This method
	// 		returns the square of the distance to another vector, i.e.
	// 		the same as the distance but before the square root is taken.
	// 		Use this if you want to find the longest / shortest distance
	// 		without incurring the square root.
	inline float squaredDistance(const vec3& rhs) const
	{
		return (*this - rhs).squaredLength();
	}

	// Calculates the dot (scalar) product of this vector with another.
	// 	remarks
	// 		The dot product can be used to calculate the angle between 2
	// 		vectors. If both are unit vectors, the dot product is the
	// 		cosine of the angle; otherwise the dot product must be
	// 		divided by the product of the lengths of both vectors to get
	// 		the cosine of the angle. This result can further be used to
	// 		calculate the distance of a point from a plane.
	// 	param
	// 		vec Vector with which to calculate the dot product (together
	// 		with this one).
	// 	return
	// 		A float representing the dot product value.
	inline float dotProduct(const vec3& vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}

	// Calculates the absolute dot (scalar) product of this vector with another.
	// 	remarks
	// 		This function work similar dotProduct, except it use absolute value
	// 		of each component of the vector to computing.
	// 	param
	// 		vec Vector with which to calculate the absolute dot product (together
	// 		with this one).
	// 	return
	// 		A float representing the absolute dot product value.
	inline float absDotProduct(const vec3& vec) const
	{
		return fabs(x * vec.x + y * vec.y + z * vec.z);
	}

	// Normalises the vector.
	// 	remarks
	// 		This method normalises the vector such that it's
	// 		length / magnitude is 1. The result is called a unit vector.
	// 	note
	// 		This function will not crash for zero-sized vectors, but there
	// 		will be no changes made to their components.
	// 	return The previous length of the vector.
	inline float normalise()
	{
		float fLength = sqrt( x * x + y * y + z * z );
		// Will also work for zero-sized vectors, but will change nothing
		// We're not using epsilons because we don't need to.
		if ( fLength > float(0.0f) )
		{
			float fInvLength = 1.0f / fLength;
			x *= fInvLength;
			y *= fInvLength;
			z *= fInvLength;
		}

		return fLength;
	}

	// Calculates the cross-product of 2 vectors, i.e. the vector that
	// lies perpendicular to them both.
	// 	remarks
	// 		The cross-product is normally used to calculate the normal
	// 		vector of a plane, by calculating the cross-product of 2
	// 		non-equivalent vectors which lie on the plane (e.g. 2 edges
	// 		of a triangle).
	// 	param
	// 		vec Vector which, together with this one, will be used to
	// 		calculate the cross-product.
	// 	return
	// 		A vector which is the result of the cross-product. This
	// 		vector will <b>NOT</b> be normalised, to maximise efficiency
	// 		- call vec3::normalise on the result if you wish this to
	// 		be done. As for which side the resultant vector will be on, the
	// 		returned vector will be on the side from which the arc from 'this'
	// 		to rkVector is anticlockwise, e.g. UNIT_Y.crossProduct(UNIT_Z)
	// 		= UNIT_X, whilst UNIT_Z.crossProduct(UNIT_Y) = -UNIT_X.
	// 		This is because OGRE uses a right-handed coordinate system.
	// 	par
	// 		For a clearer explanation, look a the left and the bottom edges
	// 		of your monitor's screen. Assume that the first vector is the
	// 		left edge and the second vector is the bottom edge, both of
	// 		them starting from the lower-left corner of the screen. The
	// 		resulting vector is going to be perpendicular to both of them
	// 		and will go <i>inside</i> the screen, towards the cathode tube
	// 		(assuming you're using a CRT monitor, of course).
	inline vec3 crossProduct( const vec3& rkVector ) const
	{
		return vec3(
			y * rkVector.z - z * rkVector.y,
			z * rkVector.x - x * rkVector.z,
			x * rkVector.y - y * rkVector.x);
	}

	// Returns a vector at a point half way between this and the passed in vector.
	inline vec3 midPoint( const vec3& vec ) const
	{
		return vec3(
			( x + vec.x ) * 0.5f,
			( y + vec.y ) * 0.5f,
			( z + vec.z ) * 0.5f );
	}

	// Returns true if the vector's scalar components are all greater
	//	that the ones of the vector it is compared against.
	inline bool operator < ( const vec3& rhs ) const
	{
		if( x < rhs.x && y < rhs.y && z < rhs.z )
			return true;
		return false;
	}

	// Returns true if the vector's scalar components are all smaller
	//	that the ones of the vector it is compared against.
	inline bool operator > ( const vec3& rhs ) const
	{
		if( x > rhs.x && y > rhs.y && z > rhs.z )
			return true;
		return false;
	}

	// Sets this vector's components to the minimum of its own and the
	// ones of the passed in vector.
	// 	remarks
	// 		'Minimum' in this case means the combination of the lowest
	// 		value of x, y and z from both vectors. Lowest is taken just
	// 		numerically, not magnitude, so -1 < 0.
	inline void makeFloor( const vec3& cmp )
	{
		if( cmp.x < x ) x = cmp.x;
		if( cmp.y < y ) y = cmp.y;
		if( cmp.z < z ) z = cmp.z;
	}

	// Sets this vector's components to the maximum of its own and the
	// ones of the passed in vector.
	// 	remarks
	// 		'Maximum' in this case means the combination of the highest
	// 		value of x, y and z from both vectors. Highest is taken just
	// 		numerically, not magnitude, so 1 > -3.
	inline void makeCeil( const vec3& cmp )
	{
		if( cmp.x > x ) x = cmp.x;
		if( cmp.y > y ) y = cmp.y;
		if( cmp.z > z ) z = cmp.z;
	}

	// Generates a vector perpendicular to this vector (eg an 'up' vector).
	// 	remarks
	// 		This method will return a vector which is perpendicular to this
	// 		vector. There are an infinite number of possibilities but this
	// 		method will guarantee to generate one of them. If you need more
	// 		control you should use the Quaternion class.
	inline vec3 perpendicular(void) const
	{
		static const float fSquareZero = (float)(1e-06 * 1e-06);

		vec3 perp = this->crossProduct( vec3::UNIT_X );

		// Check length
		if( perp.squaredLength() < fSquareZero )
		{
			// This vector is the Y axis multiplied by a scalar, so we have
			// to use another axis.
			perp = this->crossProduct( vec3::UNIT_Y );
		}
		perp.normalise();

		return perp;
	}
//	/** Generates a new random vector which deviates from this vector by a
//		given angle in a random direction.
//		@remarks
//			This method assumes that the random number generator has already
//			been seeded appropriately.
//		@param
//			angle The angle at which to deviate
//		@param
//			up Any vector perpendicular to this one (which could generated
//			by cross-product of this vector and any other non-colinear
//			vector). If you choose not to provide this the function will
//			derive one on it's own, however if you provide one yourself the
//			function will be faster (this allows you to reuse up vectors if
//			you call this method more than once)
//		@return
//			A random vector which deviates from this vector by angle. This
//			vector will not be normalised, normalise it if you wish
//			afterwards.
//	*/
//	inline vec3 randomDeviant(
//		const Radian& angle,
//		const vec3& up = vec3::ZERO ) const
//	{
//		vec3 newUp;

//		if (up == vec3::ZERO)
//		{
//			// Generate an up vector
//			newUp = this->perpendicular();
//		}
//		else
//		{
//			newUp = up;
//		}

//		// Rotate up vector by random amount around this
//		Quaternion q;
//		q.FromAngleAxis( Radian(Math::UnitRandom() * Math::TWO_PI), *this );
//		newUp = q * newUp;

//		// Finally rotate this by given angle around randomised up
//		q.FromAngleAxis( angle, newUp );
//		return q * (*this);
//	}

	// Gets the angle between 2 vectors.
	//	remarks
	//		Vectors do not have to be unit-length but must represent directions.
	inline float angleBetween(const vec3& dest) const
	{
		float lenProduct = length() * dest.length();

		// Divide by zero check
		if(lenProduct < 1e-6f)
			lenProduct = 1e-6f;

		float f = dotProduct(dest) / lenProduct;

		return acos(f);

	}
//	/** Gets the shortest arc quaternion to rotate this vector to the destination
//		vector.
//	@remarks
//		If you call this with a dest vector that is close to the inverse
//		of this vector, we will rotate 180 degrees around the 'fallbackAxis'
//		(if specified, or a generated axis if not) since in this case
//		ANY axis of rotation is valid.
//	*/
//	Quaternion getRotationTo(const vec3& dest,
//		const vec3& fallbackAxis = vec3::ZERO) const
//	{
//		// Based on Stan Melax's article in Game Programming Gems
//		Quaternion q;
//		// Copy, since cannot modify local
//		vec3 v0 = *this;
//		vec3 v1 = dest;
//		v0.normalise();
//		v1.normalise();

//		float d = v0.dotProduct(v1);
//		// If dot == 1, vectors are the same
//		if (d >= 1.0f)
//		{
//			return Quaternion::IDENTITY;
//		}
//		if (d < (1e-6f - 1.0f))
//		{
//			if (fallbackAxis != vec3::ZERO)
//			{
//				// rotate 180 degrees about the fallback axis
//				q.FromAngleAxis(Radian(Math::PI), fallbackAxis);
//			}
//			else
//			{
//				// Generate an axis
//				vec3 axis = vec3::UNIT_X.crossProduct(*this);
//				if (axis.isZeroLength()) // pick another if colinear
//					axis = vec3::UNIT_Y.crossProduct(*this);
//				axis.normalise();
//				q.FromAngleAxis(Radian(Math::PI), axis);
//			}
//		}
//		else
//		{
//			float s = Math::Sqrt( (1+d)*2 );
//			float invs = 1 / s;

//			vec3 c = v0.crossProduct(v1);

//			q.x = c.x * invs;
//			q.y = c.y * invs;
//			q.z = c.z * invs;
//			q.w = s * 0.5f;
//			q.normalise();
//		}
//		return q;
//	}

	// Returns true if this vector is zero length.
	inline bool isZeroLength(void) const
	{
		float sqlen = (x * x) + (y * y) + (z * z);
		return (sqlen < (1e-06 * 1e-06));

	}

	// As normalise, except that this vector is unaffected and the
	// normalised vector is returned as a copy.
	inline vec3 normalisedCopy(void) const
	{
		vec3 ret = *this;
		ret.normalise();
		return ret;
	}

	// Calculates a reflection vector to the plane with the given normal .
	//	remarks
	//		NB assumes 'this' is pointing AWAY FROM the plane, invert if it is not.
	inline vec3 reflect(const vec3& normal) const
	{
		return vec3( *this - ( normal * 2 * this->dotProduct(normal) ) );
	}

	// Returns whether this vector is within a positional tolerance
	// of another vector.
	// 	param rhs
	// 		The vector to compare with
	// 	param
	// 		tolerance The amount that each element of the vector may vary by
	// 		and still be considered equal
	inline bool positionEquals(const vec3& rhs, float tolerance = 1e-03) const
	{
		return fabs(x - rhs.x) <= tolerance &&
			fabs(y - rhs.y) <= tolerance &&
			fabs(z - rhs.z) <= tolerance;
	}

	// Returns whether this vector is within a positional tolerance
	// of another vector, also take scale of the vectors into account.
	// 	param rhs
	// 		The vector to compare with
	// 	param tolerance
	// 		The amount (related to the scale of vectors) that distance
	// 		of the vector may vary by and still be considered close
	inline bool positionCloses(const vec3& rhs, float tolerance = 1e-03f) const
	{
		return squaredDistance(rhs) <=
			(squaredLength() + rhs.squaredLength()) * tolerance;
	}

	// Returns whether this vector is within a directional tolerance
	// of another vector.
	// 	param rhs
	// 		The vector to compare with
	// 	param tolerance
	// 		The maximum angle by which the vectors may vary and
	// 		still be considered equal
	// 	note
	// 		Both vectors should be normalised.
	inline bool directionEquals(const vec3& rhs,
		const float& tolerance) const
	{
		float dot = dotProduct(rhs);
		float angle = acos(dot);

		return fabs(angle) <= tolerance;

	}

//	/// Check whether this vector contains valid values
//	inline bool isNaN() const
//	{
//		return Math::isNaN(x) || Math::isNaN(y) || Math::isNaN(z);
//	}

	/// Extract the primary (dominant) axis from this direction vector
	inline vec3 primaryAxis() const
	{
		float absx = fabs(x);
		float absy = fabs(y);
		float absz = fabs(z);
		if (absx > absy)
			if (absx > absz)
				return x > 0 ? vec3::UNIT_X : vec3::NEGATIVE_UNIT_X;
			else
				return z > 0 ? vec3::UNIT_Z : vec3::NEGATIVE_UNIT_Z;
		else // absx <= absy
			if (absy > absz)
				return y > 0 ? vec3::UNIT_Y : vec3::NEGATIVE_UNIT_Y;
			else
				return z > 0 ? vec3::UNIT_Z : vec3::NEGATIVE_UNIT_Z;
	}

//	/** Function for writing to a stream.
//	*/
//	inline _OgreExport friend std::ostream& operator <<
//		( std::ostream& o, const vec3& v )
//	{
//		o << "vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
//		return o;
//	}
};

class vec4
{
public:
	static const vec4 ZERO;

	float x, y, z, w;

public:
	inline vec4()
	{
		operator=(ZERO);
	}

	inline vec4( const float fX, const float fY, const float fZ, const float fW )
		: x( fX ), y( fY ), z( fZ ), w( fW )
	{
	}

	inline explicit vec4( const float afCoordinate[4] )
		: x( afCoordinate[0] ),
		  y( afCoordinate[1] ),
		  z( afCoordinate[2] ),
		  w( afCoordinate[3] )
	{
	}

	inline explicit vec4( const int afCoordinate[4] )
	{
		x = (float)afCoordinate[0];
		y = (float)afCoordinate[1];
		z = (float)afCoordinate[2];
		w = (float)afCoordinate[3];
	}

	inline explicit vec4( float* const r )
		: x( r[0] ), y( r[1] ), z( r[2] ), w( r[3] )
	{
	}

	inline explicit vec4( const float scaler )
		: x( scaler )
		, y( scaler )
		, z( scaler )
		, w( scaler )
	{
	}

	inline explicit vec4(const vec3& rhs)
		: x(rhs.x), y(rhs.y), z(rhs.z), w(1.0f)
	{
	}

	~vec4(){}

//	// Exchange the contents of this vector with another.
//	inline void swap(vec4& other)
//	{
//		std::swap(x, other.x);
//		std::swap(y, other.y);
//		std::swap(z, other.z);
//		std::swap(w, other.w);
//	}

	inline float operator [] ( const int i ) const
	{
		//assert( i < 4 );
		return *(&x+i);
	}

	inline float& operator [] ( const int i )
	{
		//assert( i < 4 );
		return *(&x+i);
	}

	/// Pointer accessor for direct copying
	inline float* ptr()
	{
		return &x;
	}
	/// Pointer accessor for direct copying
	inline const float* ptr() const
	{
		return &x;
	}

	// Assigns the value of the other vector.
	// rkVector The other vector
	inline vec4& operator = ( const vec4& rkVector )
	{
		x = rkVector.x;
		y = rkVector.y;
		z = rkVector.z;
		w = rkVector.w;
		return *this;
	}

	inline vec4& operator = ( const float fScalar)
	{
		x = fScalar;
		y = fScalar;
		z = fScalar;
		w = fScalar;
		return *this;
	}

	inline bool operator == ( const vec4& rkVector ) const
	{
		return ( x == rkVector.x &&
			y == rkVector.y &&
			z == rkVector.z &&
			w == rkVector.w );
	}

	inline bool operator != ( const vec4& rkVector ) const
	{
		return ( x != rkVector.x ||
			y != rkVector.y ||
			z != rkVector.z ||
			w != rkVector.w );
	}

	inline vec4& operator = (const vec3& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = 1.0f;
		return *this;
	}

	// arithmetic operations
	inline vec4 operator + ( const vec4& rkVector ) const
	{
		return vec4(
			x + rkVector.x,
			y + rkVector.y,
			z + rkVector.z,
			w + rkVector.w);
	}

	inline vec4 operator - ( const vec4& rkVector ) const
	{
		return vec4(
			x - rkVector.x,
			y - rkVector.y,
			z - rkVector.z,
			w - rkVector.w);
	}

	inline vec4 operator * ( const float fScalar ) const
	{
		return vec4(
			x * fScalar,
			y * fScalar,
			z * fScalar,
			w * fScalar);
	}

	inline vec4 operator * ( const vec4& rhs) const
	{
		return vec4(
			rhs.x * x,
			rhs.y * y,
			rhs.z * z,
			rhs.w * w);
	}

	inline vec4 operator / ( const float fScalar ) const
	{
		//assert( fScalar != 0.0 );

		float fInv = 1.0f / fScalar;

		return vec4(
			x * fInv,
			y * fInv,
			z * fInv,
			w * fInv);
	}

	inline vec4 operator / ( const vec4& rhs) const
	{
		return vec4(
			x / rhs.x,
			y / rhs.y,
			z / rhs.z,
			w / rhs.w);
	}

	inline const vec4& operator + () const
	{
		return *this;
	}

	inline vec4 operator - () const
	{
		return vec4(-x, -y, -z, -w);
	}

	// arithmetic updates
	inline vec4& operator += ( const vec4& rkVector )
	{
		x += rkVector.x;
		y += rkVector.y;
		z += rkVector.z;
		w += rkVector.w;

		return *this;
	}

	inline vec4& operator -= ( const vec4& rkVector )
	{
		x -= rkVector.x;
		y -= rkVector.y;
		z -= rkVector.z;
		w -= rkVector.w;

		return *this;
	}

	inline vec4& operator *= ( const float fScalar )
	{
		x *= fScalar;
		y *= fScalar;
		z *= fScalar;
		w *= fScalar;
		return *this;
	}

	inline vec4& operator += ( const float fScalar )
	{
		x += fScalar;
		y += fScalar;
		z += fScalar;
		w += fScalar;
		return *this;
	}

	inline vec4& operator -= ( const float fScalar )
	{
		x -= fScalar;
		y -= fScalar;
		z -= fScalar;
		w -= fScalar;
		return *this;
	}

	inline vec4& operator *= ( const vec4& rkVector )
	{
		x *= rkVector.x;
		y *= rkVector.y;
		z *= rkVector.z;
		w *= rkVector.w;

		return *this;
	}

	inline vec4& operator /= ( const float fScalar )
	{
		//assert( fScalar != 0.0 );

		float fInv = 1.0f / fScalar;

		x *= fInv;
		y *= fInv;
		z *= fInv;
		w *= fInv;

		return *this;
	}

	inline vec4& operator /= ( const vec4& rkVector )
	{
		x /= rkVector.x;
		y /= rkVector.y;
		z /= rkVector.z;
		w /= rkVector.w;

		return *this;
	}

	// Calculates the dot (scalar) product of this vector with another.
	//	 @param
	//		 vec Vector with which to calculate the dot product (together
	//		 with this one).
	//	 @return
	//		 A float representing the dot product value.
	inline float dotProduct(const vec4& vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
	}
//	/// Check whether this vector contains valid values
//	inline bool isNaN() const
//	{
//		return Math::isNaN(x) || Math::isNaN(y) || Math::isNaN(z) || Math::isNaN(w);
//	}
//	/** Function for writing to a stream.
//	*/
//	inline _OgreExport friend std::ostream& operator <<
//		( std::ostream& o, const vec4& v )
//	{
//		o << "vec4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
//		return o;
//	}
};

// overloaded operators to help vec3
inline vec3 operator * ( const float fScalar, const vec3& rkVector )
{
	return vec3(
		fScalar * rkVector.x,
		fScalar * rkVector.y,
		fScalar * rkVector.z);
}

inline vec3 operator / ( const float fScalar, const vec3& rkVector )
{
	return vec3(
		fScalar / rkVector.x,
		fScalar / rkVector.y,
		fScalar / rkVector.z);
}

inline vec3 operator + (const vec3& lhs, const float rhs)
{
	return vec3(
		lhs.x + rhs,
		lhs.y + rhs,
		lhs.z + rhs);
}

inline vec3 operator + (const float lhs, const vec3& rhs)
{
	return vec3(
		lhs + rhs.x,
		lhs + rhs.y,
		lhs + rhs.z);
}

inline vec3 operator - (const vec3& lhs, const float rhs)
{
	return vec3(
		lhs.x - rhs,
		lhs.y - rhs,
		lhs.z - rhs);
}

inline vec3 operator - (const float lhs, const vec3& rhs)
{
	return vec3(
		lhs - rhs.x,
		lhs - rhs.y,
		lhs - rhs.z);
}

inline vec4 operator * ( const float fScalar, const vec4& rkVector )
{
	return vec4(
		fScalar * rkVector.x,
		fScalar * rkVector.y,
		fScalar * rkVector.z,
		fScalar * rkVector.w);
}

inline vec4 operator / ( const float fScalar, const vec4& rkVector )
{
	return vec4(
		fScalar / rkVector.x,
		fScalar / rkVector.y,
		fScalar / rkVector.z,
		fScalar / rkVector.w);
}

inline vec4 operator + (const vec4& lhs, const float rhs)
{
	return vec4(
		lhs.x + rhs,
		lhs.y + rhs,
		lhs.z + rhs,
		lhs.w + rhs);
}

inline vec4 operator + (const float lhs, const vec4& rhs)
{
	return vec4(
		lhs + rhs.x,
		lhs + rhs.y,
		lhs + rhs.z,
		lhs + rhs.w);
}

inline vec4 operator - (const vec4& lhs, float rhs)
{
	return vec4(
		lhs.x - rhs,
		lhs.y - rhs,
		lhs.z - rhs,
		lhs.w - rhs);
}

inline vec4 operator - (const float lhs, const vec4& rhs)
{
	return vec4(
		lhs - rhs.x,
		lhs - rhs.y,
		lhs - rhs.z,
		lhs - rhs.w);
}

#endif // VEC_H
