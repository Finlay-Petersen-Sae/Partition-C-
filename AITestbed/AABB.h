#pragma once

#include "Vector.h"

template <typename CoordinateType>
struct AABB
{
public:
	/**
	 * Constructs a new AABB from the provided coordinates.
	 *
	 * @param _min The minimum.
	 * @param _max The maximum.
	 */
	AABB(const Vector2<CoordinateType>& _min = Vector2<CoordinateType>::Zero, const Vector2<CoordinateType>& _max = Vector2<CoordinateType>::Zero);

	/**
	 * Constructs a new AABB from an existing AABB.
	 *
	 * @param other The existing AABB to copy the data from.
	 */
	AABB(const AABB<CoordinateType>& other);

	/**
	 * Copies one AABB to this AABB.
	 *
	 * @param other The existing AABB to copy the data from.
	 *
	 * @return The updated AABB.
	 */
	AABB<CoordinateType>& operator = (const AABB<CoordinateType>& other);


	/**
	 * Tests if two AABB objects are the same
	 *
	 * @param other The other AABB to compare with.
	 *
	 * @return true if the AABBs are considered equivalent.
	 */
	bool operator == (const AABB<CoordinateType>& other) const;

	/**
	 * Tests if two AABB objects are not the same.
	 *
	 * @param other The other AABB to compare with.
	 *
	 * @return true if the AABBs are not considered equivalent.
	 */
	bool operator != (const AABB<CoordinateType>& other) const;

	/**
	 * Combines this AABB with another AABB and returns the result. The current AABB is unchanged.
	 *
	 * @param other The other AABB to combine with this one.
	 *
	 * @return An AABB that encompasses both bounding boxes.
	 */
	AABB<CoordinateType> operator + (const AABB<CoordinateType>& other) const;

	/**
	 * Combines this AABB with another AABB and returns the result. The current AABB is changed.
	 *
	 * @param other The other AABB to combine with this one.
	 *
	 * @return An AABB that encompasses both bounding boxes.
	 */
	AABB<CoordinateType> operator += (const AABB<CoordinateType>& other);

	/**
	 * Query if this object contains the given point.
	 *
	 * @param point The location that you want to check against the bounding box.
	 *
	 * @return true if the location is inside the AABB, false if not.
	 */
	bool Contains(const Vector2<CoordinateType>& point) const;

	/**
	 * Query if this object intersects another AABB.
	 *
	 * @param other The other AABB to test for intersection.
	 *
	 * @return true if the AABBs intersect, false if they do not intersect.
	 */
	bool Intersects(const AABB<CoordinateType>& other) const;

	/**
	 * Gets the centre of the AABB.
	 *
	 * @return The centre of the AABB;
	 */
	Vector2<CoordinateType> Centre() const;

	/**
	 * Gets the width.
	 *
	 * @return The width of the bounding box.
	 */
	CoordinateType Width() const;

	/**
	 * Gets the height.
	 *
	 * @return The height of the bounding box.
	 */
	CoordinateType Height() const;

public:
	static const AABB<CoordinateType> Zero;

public:
	Vector2<CoordinateType> boxMin;
	Vector2<CoordinateType> boxMax;
};

/** Defines an alias representing the aab bi. */
typedef AABB<int> AABBi;

/** Defines an alias representing the aab bf. */
typedef AABB<float> AABBf;

template <typename CoordinateType>
const AABB<CoordinateType> AABB<CoordinateType>::Zero;

// Constructors
template <typename CoordinateType>
AABB<CoordinateType>::AABB(const Vector2<CoordinateType>& _min, const Vector2<CoordinateType>& _max) :
boxMin(_min),
boxMax(_max)
{

}

template <typename CoordinateType>
AABB<CoordinateType>::AABB(const AABB<CoordinateType>& other) :
boxMin(other.boxMin),
boxMax(other.boxMax)
{

}

// Assignment
template <typename CoordinateType>
AABB<CoordinateType>& AABB<CoordinateType>::operator = (const AABB<CoordinateType>& other)
{
	boxMin = other.boxMin;
	boxMax = other.boxMax;

	return *this;
}


// Comparison
template <typename CoordinateType>
bool AABB<CoordinateType>::operator == (const AABB<CoordinateType>& other) const
{
	return (boxMin == other.boxMin) && (boxMax == other.boxMax);
}

template <typename CoordinateType>
bool AABB<CoordinateType>::operator != (const AABB<CoordinateType>& other) const
{
	return !(*this == other);
}

// Expands the bounding box to encompass the point
template <typename CoordinateType>
AABB<CoordinateType> AABB<CoordinateType>::operator + (const AABB<CoordinateType>& other) const
{
	return AABB<CoordinateType>(*this) += other;
}

template <typename CoordinateType>
AABB<CoordinateType> AABB<CoordinateType>::operator += (const AABB<CoordinateType>& other)
{
	boxMin.X = min(boxMin.X, other.X);
	boxMin.Y = min(boxMin.Y, other.Y);
	boxMax.X = max(boxMax.X, other.X);
	boxMax.Y = max(boxMax.Y, other.Y);

	return *this;
}

// Contains/Intersects testing
template <typename CoordinateType>
bool AABB<CoordinateType>::Contains(const Vector2<CoordinateType>& point) const
{
	return (point.X >= boxMin.X) && (point.X <= boxMax.X) &&
		   (point.Y >= boxMin.Y) && (point.Y <= boxMax.Y);
}

template <typename CoordinateType>
bool AABB<CoordinateType>::Intersects(const AABB<CoordinateType>& other) const
{
	if ((boxMin.X > other.boxMax.X) || (other.boxMin.X > boxMax.X))
		return false;

	if ((boxMin.Y > other.boxMax.Y) || (other.boxMin.Y > boxMax.Y))
		return false;

	return true;
}

// Information Retrieval
template <typename CoordinateType>
Vector2<CoordinateType> AABB<CoordinateType>::Centre() const
{
	return Vector2<CoordinateType>((boxMax + boxMin) / 2);
}

template <typename CoordinateType>
CoordinateType AABB<CoordinateType>::Width() const
{
	return static_cast<CoordinateType>(abs(boxMax.X - boxMin.X));
}

template <typename CoordinateType>
CoordinateType AABB<CoordinateType>::Height() const
{
	return static_cast<CoordinateType>(abs(boxMax.Y - boxMin.Y));
}
