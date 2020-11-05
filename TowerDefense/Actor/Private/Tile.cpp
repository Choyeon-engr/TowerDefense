#include "Tile.hpp"
#include "Game.hpp"
#include "SpriteComponent.hpp"

Tile::Tile(Game* game)
: Actor(game), mTileState(EDefault), mParent(nullptr), f(0.f), g(0.f), h(0.f), mIsInOpenSet(false), mIsInClosedSet(false), mIsBlocked(false), mIsSelected(false)
{
    mSprite = new SpriteComponent(this, 4);
    UpdateTexture();
}

void Tile::SetTileState(TileState tileState)
{
    mTileState = tileState;
    UpdateTexture();
}

void Tile::ToggleSelect()
{
    mIsSelected = !mIsSelected;
    UpdateTexture();
}

void Tile::UpdateTexture()
{
    string texture;
    
    switch (mTileState)
    {
        case EDefault:
            if (mIsSelected)
                texture = "/Assets/TileBrownSelected.png";
            else
                texture = "/Assets/TileBrown.png";
            break;
            
        case EPath:
            if (mIsSelected)
                texture = "/Assets/TileGreySelected.png";
            else
                texture = "/Assets/TileGrey.png";
            break;
            
        case EStart:
            texture = "/Assets/Cauldron.png";
            break;
            
        case EBase:
            texture = "/Assets/Cat.png";
            break;
    }
    
    mSprite->SetTexture(GetGame()->GetTexture(texture));
}
