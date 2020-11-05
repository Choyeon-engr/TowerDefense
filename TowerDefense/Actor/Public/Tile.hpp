#pragma once

#include <vector>

#include "Actor.hpp"

using namespace std;

class Tile : public Actor
{
public:
    friend class Grid;
    
    enum TileState
    {
        EDefault,
        EPath,
        EStart,
        EBase
    };
    
    Tile(class Game* game);
    
    void SetTileState(TileState tileState);
    TileState GetTileState() const noexcept { return mTileState; }
    
    void ToggleSelect();
    
    const Tile* GetParent() const noexcept { return mParent; }
    
private:
    void UpdateTexture();
    
    class SpriteComponent* mSprite;
    
    TileState mTileState;
    
    vector<Tile*> mNeighborTiles;
    Tile* mParent;
    
    float f;
    float g;
    float h;
    
    bool mIsInOpenSet;
    bool mIsInClosedSet;
    bool mIsBlocked;
    bool mIsSelected;
};
