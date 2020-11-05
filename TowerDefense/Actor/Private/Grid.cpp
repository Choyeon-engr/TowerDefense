#include <algorithm>

#include "Grid.hpp"
#include "Game.hpp"
#include "Tile.hpp"
#include "Tower.hpp"
#include "Enemy.hpp"
#include "CML.hpp"

Grid::Grid(Game* game)
: Actor(game), mSelectedTile(nullptr)
{
    mTiles.resize(mRowSize);
    for (size_t i = 0; i < mTiles.size(); ++i)
        mTiles[i].resize(mColumnSize);
    
    for (size_t i = 0; i < mRowSize; ++i)
    {
        for (size_t j = 0; j < mColumnSize; ++j)
        {
            mTiles[i][j] = new Tile(GetGame());
            mTiles[i][j]->SetPosition(CML::Vector2D(mTileSize / 2.f + j * mTileSize, mStartY + i * mTileSize));
        }
    }
    
    GetStartTile()->SetTileState(Tile::EStart);
    GetGoalTile()->SetTileState(Tile::EBase);
    
    for (size_t i = 0; i < mRowSize; ++i)
    {
        for (size_t j = 0; j < mColumnSize; ++j)
        {
            if (i > 0)
                mTiles[i][j]->mNeighborTiles.emplace_back(mTiles[i - 1][j]);
            if (i < mRowSize - 1)
                mTiles[i][j]->mNeighborTiles.emplace_back(mTiles[i + 1][j]);
            if (j > 0)
                mTiles[i][j]->mNeighborTiles.emplace_back(mTiles[i][j - 1]);
            if (j < mColumnSize - 1)
                mTiles[i][j]->mNeighborTiles.emplace_back(mTiles[i][j + 1]);
        }
    }
    
    FindPath(GetGoalTile(), GetStartTile());
    UpdatePathTiles(GetStartTile());
    
    mEnemySpawnCoolTime = mEnemySpawnInterval;
}

void Grid::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
    
    mEnemySpawnCoolTime -= deltaTime;
    if (mEnemySpawnCoolTime <= 0.f)
    {
        new Enemy(GetGame());
        mEnemySpawnCoolTime = mEnemySpawnInterval;
    }
}

void Grid::Click(int x, int y)
{
    y -= static_cast<int>(mStartY - mTileSize / 2);
    if (y >= 0)
    {
        x /= static_cast<int>(mTileSize);
        y /= static_cast<int>(mTileSize);
        if (x >= 0 && x < static_cast<int>(mColumnSize) && y >= 0 && y < static_cast<int>(mRowSize))
            SelectTile(y, x);
    }
}

bool Grid::FindPath(Tile* start, Tile* goal)
{
    for (size_t i = 0; i < mRowSize; ++i)
    {
        for (size_t j = 0; j < mColumnSize; ++j)
        {
            mTiles[i][j]->g = 0.f;
            mTiles[i][j]->mIsInOpenSet = false;
            mTiles[i][j]->mIsInClosedSet = false;
        }
    }
    
    vector<Tile*> openSet;
    
    Tile* current = start;
    current->mIsInClosedSet = true;
    
    do
    {
        for (Tile* neighborTile : current->mNeighborTiles)
        {
            if (neighborTile->mIsBlocked)
                continue;
            
            if (!neighborTile->mIsInClosedSet)
            {
                if (!neighborTile->mIsInOpenSet)
                {
                    neighborTile->mParent = current;
                    neighborTile->h = (neighborTile->GetPosition() - goal->GetPosition()).Length();
                    neighborTile->g = current->g + mTileSize;
                    neighborTile->f = neighborTile->h + neighborTile->g;
                    openSet.emplace_back(neighborTile);
                    neighborTile->mIsInOpenSet = true;
                }
                else
                {
                    float g = current->g + mTileSize;
                    if (g < neighborTile->g)
                    {
                        neighborTile->mParent = current;
                        neighborTile->g = g;
                        neighborTile->f = neighborTile->h + neighborTile->g;
                    }
                }
            }
        }
        
        if (openSet.empty())
            break;
        
        auto iter = min_element(openSet.begin(), openSet.end(), [](Tile* a, Tile* b){ return a->f < b->f; });
        current = *iter;
        openSet.erase(iter);
        current->mIsInOpenSet = false;
        current->mIsInClosedSet = true;
    } while (current != goal);
    
    return current == goal;
}

void Grid::BuildTower()
{
    if (mSelectedTile && !mSelectedTile->mIsBlocked)
    {
        mSelectedTile->mIsBlocked = true;
        
        if (FindPath(GetGoalTile(), GetStartTile()))
        {
            Tower* tower = new Tower(GetGame());
            tower->SetPosition(mSelectedTile->GetPosition());
        }
        else
        {
            mSelectedTile->mIsBlocked = false;
            FindPath(GetGoalTile(), GetStartTile());
        }
        
        UpdatePathTiles(GetStartTile());
    }
}

Tile* Grid::GetStartTile()
{
    return mTiles[3][0];
}

Tile* Grid::GetGoalTile()
{
    return mTiles[3][15];
}

void Grid::SelectTile(size_t row, size_t column)
{
    Tile::TileState tileState = mTiles[row][column]->GetTileState();
    if (tileState != Tile::EStart && tileState != Tile::EBase)
    {
        if (mSelectedTile)
            mSelectedTile->ToggleSelect();
        
        mSelectedTile = mTiles[row][column];
        mSelectedTile->ToggleSelect();
    }
}

void Grid::UpdatePathTiles(class Tile* start)
{
    for (size_t i = 0; i < mRowSize; ++i)
    {
        for (size_t j = 0; j < mColumnSize; ++j)
        {
            if (!(i == 3 && j == 0) && !(i == 3 && j == 15))
                mTiles[i][j]->SetTileState(Tile::EDefault);
        }
    }
    
    Tile* tile = start->mParent;
    while (tile != GetGoalTile())
    {
        tile->SetTileState(Tile::EPath);
        tile = tile->mParent;
    }
}
