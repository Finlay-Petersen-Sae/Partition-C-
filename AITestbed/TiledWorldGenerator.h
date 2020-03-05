#pragma once

#include <vector>
#include <string>
#include "imgui.h"
#include "Tile.h"

class AvailableTile
{
    public:
        int Frequency;
        float Threshold;
        std::string Name;
        ImColor Colour;
        TileType Type;
        float FieldStrength;
        float FieldRange;
        //AABBf boundingBox;
        AvailableTile(int _frequency, const std::string& _name, const ImColor& _colour, TileType _type, float _fieldStrength, float _fieldRange) :
            Frequency(_frequency), Name(_name), Colour(_colour), Type(_type), FieldStrength(_fieldStrength), FieldRange(_fieldRange)
        {

        }
};
/*
Node (variables)
 - Bounding Box (AABB)
 - Layer/level/depth
 - Parent pointer
 - Children
 - Contents

Node (functions)
 - Add a relevant object
 - Find potentially relevant tiles
 */
class Node 
{
    public:
        AABBf boundingBox;
        int layer;
        std::vector<Node*> children;
        std::vector<Tile*> contents;
        Node* parent;

        void AddTile(Tile* targetTile)
        {
            if (children.size() >= 1)
            {
                // if children list is higher then 0
                for (int i = 0; i <= children.size() - 1; i++)
                {
                    {
                        if (children[i]->boundingBox.Intersects(targetTile->boundingBox))
                        {
                            children[i]->AddTile(targetTile);

                            //add the tiles to the children instead of this
                        }
                    }
                }
            }
            else
            {
                // else add the tile to this
                 contents.push_back(targetTile);
                if (contents.size() >= 10 && boundingBox.Height() >= 2 && boundingBox.Width() >= 2) {
                    // make 4 children nodes
                    auto tLNode = new Node();
                    auto tRNode = new Node();
                    auto bLNode = new Node();
                    auto bRNode = new Node();

                    //set their bounding boxs to half of the parents
                   /* tLNode.boundingBox.size = boundingBox. / 2;
                    tRNode.boundingBox.size = boundingBox.size / 2;
                    bLNode.boundingBox.size = boundingBox.size / 2;
                    bRNode.boundingBox.size = boundingBox.size / 2;

                    auto node1Centre =  Vector2f(boundingBox.Centre.x + -boundingBox..x / 2, boundingBox.center.y + boundingBox.extents.y / 2);
                    auto node2Centre =  Vector2f(boundingBox.Centre.x + boundingBox.extents.x / 2, boundingBox.center.y + boundingBox.extents.y / 2);
                    auto node3Centre =  Vector2f(boundingBox.Centre.x + -boundingBox.extents.x / 2, boundingBox.center.y + -boundingBox.extents.y / 2);
                    auto node4Centre =  Vector2f(boundingBox.Centre.x + boundingBox.extents.x / 2, boundingBox.center.y + -boundingBox.extents.y / 2);*/

                    tLNode->boundingBox.boxMax = Vector2f(boundingBox.Centre().X, boundingBox.boxMax.Y);
                    tLNode->boundingBox.boxMin = Vector2f(boundingBox.boxMin.X,boundingBox.Centre().Y);
                    
                    tRNode->boundingBox.boxMax = boundingBox.boxMax;
                    tRNode->boundingBox.boxMin = boundingBox.Centre();

                    bLNode->boundingBox.boxMax = boundingBox.Centre();
                    bLNode->boundingBox.boxMin = boundingBox.boxMin;

                    bRNode->boundingBox.boxMax = Vector2f(boundingBox.boxMax.X, boundingBox.Centre().Y);
                    bRNode->boundingBox.boxMin = Vector2f(boundingBox.Centre().X, boundingBox.boxMin.Y);



                    //set the nodes information respectively



                    tLNode->parent = this;
                    tRNode->parent = this;
                    bLNode->parent = this;
                    bRNode->parent = this;


                    //add the nodes to the list
                    children.push_back(tLNode);
                    children.push_back(tRNode);
                    children.push_back(bLNode);
                    children.push_back(bRNode);

                    for (int i = 0; i <= children.size() - 1; i++)
                    {
                        {
                            for (int x = 0; x <= contents.size() - 1; x++)
                            {
                                auto OB = contents[x];
                                if (children[i]->boundingBox.Intersects(OB->boundingBox))
                                {
                                    children[i]->AddTile(OB);

                                }
                            }
                        }
                    }
                    contents.clear();
                    //check if tile is in the children bounds and add them if they are


                    //add the nodes layers
                    tLNode->layer++;
                    tRNode->layer++;
                    bLNode->layer++;
                    bRNode->layer++;
                }
            }
        };

        std::vector<Tile*> FindObject(Tile* rTile)
        {
            //new list of tiles to make the relevant tiles
            std::vector<Tile*> relevantTiles =  std::vector<Tile*>();

            if (children.size() >= 1)
            {
                for (int i = 0; i <= children.size() - 1; i++)
                {
                    {
                        if (children[i]->boundingBox.Contains(rTile->Location))  
                        {
                            //if children and in the right location add it to the childs list
                            relevantTiles = children[i]->FindObject(rTile);
                            break;
                        }
                    }
                }
                return relevantTiles;
            }
            return contents;
            //return the relevanttiles list
        }

            
};

class TiledWorldGenerator
{
    public:
        int Length;
        int Width;
        std::vector<AvailableTile*> TilePalette;

        TiledWorldGenerator() :
            Length(120), Width(120)
        {
            TilePalette.push_back(new AvailableTile(85, "Free", ImColor(121, 255, 116), ettFree, 0, 0));
            TilePalette.push_back(new AvailableTile(10, "Obstructed", ImColor(81, 0, 0), ettObstructed, 4, 5));
            TilePalette.push_back(new AvailableTile(4, "Undesirable", ImColor(255, 127, 39), ettUndesirable, 3, 10));
            TilePalette.push_back(new AvailableTile(1, "Desirable", ImColor(0, 81, 0), ettDesirable, -10, 60));
        }

        ~TiledWorldGenerator()
        {
            // cleanup the tile palette
            for (AvailableTile* tilePtr : TilePalette)
            {
                delete tilePtr;
            }
            TilePalette.clear();

            ClearWorld();
        }

        void Generate();

        void CalculateField();

        void DrawWorld();

    protected:
	    void NormaliseProbabilities();
	    void ClearWorld();
	    void GenerateWorld();

    protected:
        std::vector<Tile*> world;
        float largestFieldStrength;

    public:
        bool ShowField = false;
};
