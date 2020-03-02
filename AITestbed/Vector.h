#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

template <typename CoordinateType>
struct Vector2
{
public:
	/**
	 * Constructs a new Vector2 from the individual coordinates.
	 *
	 * @param _X The x coordinate.
	 * @param _Y The y coordinate.
	 */
	Vector2(CoordinateType _X = 0, CoordinateType _Y = 0);

	/**
	 * Constructs a new Vector2 from an existing Vector2.
	 *
	 * @param other The Vector2 to copy the data from.
	 */
	Vector2(const Vector2<CoordinateType>& other);

	/**
	 * Copy the data from another Vector2 to this one.
	 *
	 * @param other The Vector2 to copy the data from.
	 *
	 * @return A shallow copy of this object.
	 */
	Vector2<CoordinateType>& operator = (const Vector2<CoordinateType>& other);

	/**
	 * Tests if two Vector2 objects are the same.
	 *
	 * @param other The other Vector2 to test against.
	 *
	 * @return true if the two Vector2 objects are the same.
	 */
	bool operator == (const Vector2<CoordinateType>& other) const;

	/**
	 * Tests if two Vector2 objects are NOT the same.
	 *
	 * @param other The other Vector2 to test against.
	 *
	 * @return true if the two Vector2 objects are not the same.
	 */
	bool operator != (const Vector2<CoordinateType>& other) const;

	/**
	 * Adds another Vector2 to this one and returns the result. The current Vector2 is unchanged.
	 *
	 * @param other The other Vector2 to add to this Vector2.
	 *
	 * @return The result of the operation.
	 */
	Vector2<CoordinateType> operator + (const Vector2<CoordinateType>& other) const;

	/**
	 * Adds another Vector2 to this one and returns the result. The current Vector2 is updated.
	 *
	 * @param other The other Vector2 to add to this Vector2.
	 *
	 * @return The result of the operation.
	 */
	Vector2<CoordinateType> operator += (const Vector2<CoordinateType>& other);

	/**
	 * Subtracts another Vector2 from this one and returns the result. The current Vector2 is unchanged.
	 *
	 * @param other The other Vector2 to subtract from this Vector2.
	 *
	 * @return The result of the operation.
	 */
	Vector2<CoordinateType> operator - (const Vector2<CoordinateType>& other) const;

	/**
	 * Subtracts another Vector2 from this one and returns the result. The current Vector2 is updated.
	 *
	 * @param other The other Vector2 to subtract from this Vector2.
	 *
	 * @return The result of the operation.
	 */
	Vector2<CoordinateType> operator -= (const Vector2<CoordinateType>& other);

	/**
	 * Scales the current Vector2 by a value. The current vector 2 is not changed.
	 *
	 * @param scale The scale.
	 *
	 * @return The result of the operation.
	 */
	Vector2<CoordinateType> operator * (float scale) const;

	/**
	 * Scales the current Vector2 by a value. The current vector 2 is changed.
	 *
	 * @param scale The scale.
	 *
	 * @return The result of the operation.
	 */
	Vector2<CoordinateType> operator *= (float scale);

	/**
	 * Divides the current Vector2 by a value. The current vector 2 is not changed.
	 *
	 * @param scale The scale.
	 *
	 * @return The result of the operation.
	 */
	Vector2<CoordinateType> operator / (float scale) const;

	/**
	 * Divides the current Vector2 by a value. The current vector 2 is changed.
	 *
	 * @param scale The scale.
	 *
	 * @return The result of the operation.
	 */
	Vector2<CoordinateType> operator /= (float scale);

	/**
	 * Calculates the dot product of this vector and another vector.
	 *
	 * @param other The other vector to dot with this vector.
	 *
	 * @return The result of the operation.
	 */
	CoordinateType operator | (const Vector2<CoordinateType>& other) const;

	/**
	 * Calculates the cross product of this vector and another vector.
	 *
	 * @param other The other to cross with this vector. The other vector is on the right hand side of the cross product.
	 *
	 * @return The result of the operation.
	 */
	CoordinateType operator ^ (const Vector2<CoordinateType>& other) const;

	/**
	 * Calculates the magnitude of the vector.
	 *
	 * @return A float.
	 */
	float Magnitude() const;

	/**
	 * Calculates the square of the magnitude of the vector.
	 *
	 * @return A CoordinateType.
	 */
	CoordinateType MagnitudeSquared() const;

	/**
	 * Returns a normalised version of the vector.
	 *
	 * @return The normalised version of the vector.
	 */
	Vector2<CoordinateType> Normalised() const;

	/**
	 * Normalises the current vector and returns the magnitude.
	 *
	 * @return The magnitude of the vector before it was normalised.
	 */
	float Normalise();

	/**
	 * Constructs a Vector2 given an angle in degrees.
	 *
	 * @param angle The angle in degrees.
	 *
	 * @return A Vector2 that points in the direction of the angle.
	 */
	static Vector2<CoordinateType> FromAngle(float angle);

public:
	static const Vector2<CoordinateType> Zero;

public:
	CoordinateType X;
	CoordinateType Y;
};

/** Defines an alias representing the vector 2i. */
typedef Vector2<int> Vector2i;

/** Defines an alias representing the vector 2f. */
typedef Vector2<float> Vector2f;

template <typename CoordinateType>
const Vector2<CoordinateType> Vector2<CoordinateType>::Zero;

// Constructors
template <typename CoordinateType>
Vector2<CoordinateType>::Vector2(CoordinateType _X, CoordinateType _Y) :
X(_X),
Y(_Y)
{

}

template <typename CoordinateType>
Vector2<CoordinateType>::Vector2(const Vector2<CoordinateType>& other) :
X(other.X),
Y(other.Y)
{

}

// Assignment
template <typename CoordinateType>
Vector2<CoordinateType>& Vector2<CoordinateType>::operator = (const Vector2<CoordinateType>& other)
{
	X = other.X;
	Y = other.Y;

	return *this;
}

// Comparison
template <typename CoordinateType>
bool Vector2<CoordinateType>::operator == (const Vector2<CoordinateType>& other) const
{
	return (X == other.X) && (Y == other.Y);
}

template <typename CoordinateType>
bool Vector2<CoordinateType>::operator != (const Vector2<CoordinateType>& other) const
{
	return !(*this == other);
}

// Addition and Subtraction
template <typename CoordinateType>
Vector2<CoordinateType> Vector2<CoordinateType>::operator + (const Vector2<CoordinateType>& other) const
{
	return Vector2<CoordinateType>(X + other.X, Y + other.Y);
}

template <typename CoordinateType>
Vector2<CoordinateType> Vector2<CoordinateType>::operator += (const Vector2<CoordinateType>& other)
{
	X += other.X;
	Y += other.Y;

	return *this;
}

template <typename CoordinateType>
Vector2<CoordinateType> Vector2<CoordinateType>::operator - (const Vector2<CoordinateType>& other) const
{
	return Vector2<CoordinateType>(X - other.X, Y - other.Y);
}

template <typename CoordinateType>
Vector2<CoordinateType> Vector2<CoordinateType>::operator -= (const Vector2<CoordinateType>& other)
{
	X -= other.X;
	Y -= other.Y;

	return *this;
}

// Scaling
template <typename CoordinateType>
Vector2<CoordinateType> Vector2<CoordinateType>::operator * (float scale) const
{
	return Vector2<CoordinateType>(static_cast<CoordinateType>(X * scale), 
								   static_cast<CoordinateType>(Y * scale));
}

template <typename CoordinateType>
Vector2<CoordinateType> Vector2<CoordinateType>::operator *= (float scale)
{
	X *= scale;
	Y *= scale;

	return *this;
}

template <typename CoordinateType>
Vector2<CoordinateType> Vector2<CoordinateType>::operator / (float scale) const
{
	return Vector2<CoordinateType>(X / scale, Y / scale);
}

template <typename CoordinateType>
Vector2<CoordinateType> Vector2<CoordinateType>::operator /= (float scale)
{
	X /= scale;
	Y /= scale;

	return *this;
}

// Dot Product
template <typename CoordinateType>
CoordinateType Vector2<CoordinateType>::operator | (const Vector2<CoordinateType>& other) const
{
	return (X * other.X) + (Y * other.Y);
}

// Cross Product
template <typename CoordinateType>
CoordinateType Vector2<CoordinateType>::operator ^ (const Vector2<CoordinateType>& other) const
{
	return (X * other.Y) - (Y * other.X);
}

// Magnitude
template <typename CoordinateType>
float Vector2<CoordinateType>::Magnitude() const
{
	return static_cast<CoordinateType>(sqrt(X * X + Y * Y));
}

template <typename CoordinateType>
CoordinateType Vector2<CoordinateType>::MagnitudeSquared() const
{
	return X * X + Y * Y;
}

// Normalisation
template <typename CoordinateType>
Vector2<CoordinateType> Vector2<CoordinateType>::Normalised() const
{
	const float magnitude = Magnitude();

	return Vector2<CoordinateType>(static_cast<CoordinateType>(X / magnitude), 
								   static_cast<CoordinateType>(Y / magnitude));
}

template <typename CoordinateType>
float Vector2<CoordinateType>::Normalise()
{
	const float magnitude = Magnitude();

	X = static_cast<CoordinateType>(X / magnitude);
	Y = static_cast<CoordinateType>(Y / magnitude);

	return magnitude;
}

// From Angle
template <typename CoordinateType>
Vector2<CoordinateType> Vector2<CoordinateType>::FromAngle(float angle)
{
	return Vector2<CoordinateType>(static_cast<CoordinateType>(cos(angle * M_PI / 180.0f)),
								   static_cast<CoordinateType>(sin(angle * M_PI / 180.0f)));
}
