#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "CML.hpp"

using namespace std;

class Game
{
public:
    Game() : mIsRunning(true), mIsUpdatingActors(false), mTicksCount(0), mWindow(nullptr), mRenderer(nullptr) {}
    
    bool Init();
    void Loop();
    void Quit();
    
    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);
    
    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);
    
    SDL_Texture* GetTexture(const string& fileName);
    
    /* Specialization for TowerDefense */
    void GameOver() { mIsRunning = false; }
    
    class Grid* GetGrid() const noexcept { return mGrid; }
    
    vector<class Enemy*>& GetEnemies() { return mEnemies; }
    class Enemy* GetNearestEnemy(const CML::Vector2D& position);
    
private:
    void Input();
    void Update();
    void Output();
    
    void LoadData();
    void UnloadData();
    
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    
    Uint32 mTicksCount;
    
    bool mIsRunning;
    bool mIsUpdatingActors;
    
    vector<class Actor*> mActors;
    vector<class Actor*> mPendingActors;
    
    vector<class SpriteComponent*> mSprites;
    unordered_map<string, SDL_Texture*> mTextures;
    
    /* Specialization for TowerDefense */
    class Grid* mGrid;
    
    vector<class Enemy*> mEnemies;
    float mEnemySpawnCoolTime;
};
