#pragma once

#include "imgui.h"
#include "Vector.h"
#include "AABB.h"
#include <iostream>

enum TileType
{
    ettFree,
    ettObstructed,
    ettUndesirable,
    ettDesirable
};

class Tile
{
    public:
        TileType Type;
        ImColor Colour;
        Vector2f Location;
        float FieldStrength;
        float FieldRange;

        Vector2f LocalFieldValue;

        Tile(TileType _type, const ImColor& _colour, const Vector2f& _location, float _fieldStrength, float _fieldRange) :
            Type(_type), Colour(_colour), Location(_location), FieldStrength(_fieldStrength), FieldRange(_fieldRange)
        {

        }

        Vector2f CalculateFieldTo(Tile* otherTile)
        {
            // does this tile not apply a field?
            if (FieldStrength == 0)
                return Vector2f::Zero;

            // calculate the vector to the other tile
            Vector2f vecToTile = otherTile->Location - Location;

            // is the other tile too far away?
            float distToTile = vecToTile.Normalise();
            if (distToTile >= FieldRange)
                return Vector2f::Zero;

            // calculate and return the field strength
            return vecToTile * FieldStrength * (1.0f - (distToTile / FieldRange));
        }
};
