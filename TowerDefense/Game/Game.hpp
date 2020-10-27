#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <unordered_map>

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
    
private:
    void Input();
    void Update();
    void Output();
    
    void LoadData();
    void UnloadData();
    
    bool mIsRunning;
    bool mIsUpdatingActors;
    
    Uint32 mTicksCount;
    
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    
    vector<class Actor*> mActors;
    vector<class Actor*> mPendingActors;
    
    vector<class SpriteComponent*> mSprites;
    unordered_map<string, SDL_Texture*> mTextures;
};
