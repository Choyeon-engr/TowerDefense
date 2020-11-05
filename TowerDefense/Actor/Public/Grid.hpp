#pragma once

#include <vector>

#include "Actor.hpp"

using namespace std;

class Grid : public Actor
{
public:
    Grid(class Game* game);
    
    void UpdateActor(float deltaTime) override;
    
    void Click(int x, int y);
    
    bool FindPath(class Tile* start, class Tile* goal);
    
    void BuildTower();
    
    class Tile* GetStartTile();
    class Tile* GetGoalTile();
    
private:
    void SelectTile(size_t row, size_t column);
    
    void UpdatePathTiles(class Tile* start);
    
    class Tile* mSelectedTile;
    
    vector<vector<class Tile*>> mTiles;
    
    float mEnemySpawnCoolTime;
    
    const size_t mRowSize = 7;
    const size_t mColumnSize = 16;
    
    const float mStartY = 192.f;
    const float mTileSize = 64.f;
    const float mEnemySpawnInterval = 1.5f;
};
