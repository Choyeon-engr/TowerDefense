#include <SDL2_image/SDL_image.h>

#include "Game.hpp"
#include "Actor.hpp"
#include "SpriteComponent.hpp"
#include "Grid.hpp"
#include "Enemy.hpp"

bool Game::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO))
        return false;
    
    if (!IMG_Init(IMG_INIT_PNG))
        return false;
    
    mWindow = SDL_CreateWindow("TowerDefense", 0, 0, 1024, 768, 0);
    if (!mWindow)
        return false;
    
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer)
        return false;
    
    LoadData();
    
    mTicksCount = SDL_GetTicks();
    
    return true;
}

void Game::Loop()
{
    while (mIsRunning)
    {
        Input();
        Update();
        Output();
    }
}

void Game::Quit()
{
    UnloadData();
    IMG_Quit();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
    if (mIsUpdatingActors)
        mPendingActors.emplace_back(actor);
    else
        mActors.emplace_back(actor);
}

void Game::RemoveActor(Actor* actor)
{
    auto iter = find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end())
    {
        iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
        return;
    }
    
    iter = find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end())
    {
        iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}

void Game::AddSprite(SpriteComponent* sprite)
{
    int drawOrder = sprite->GetDrawOrder();
    auto iter = mSprites.begin();
    
    for (; iter != mSprites.end(); ++iter)
    if (drawOrder < (*iter)->GetDrawOrder())
        break;
    
    mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
    auto iter = find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}

SDL_Texture* Game::GetTexture(const string& fileName)
{
    SDL_Texture* texture = nullptr;
    const string AbsolutePath = string("/Users/choyeon/Game/TowerDefense/TowerDefense") + fileName;
    auto iter = mTextures.find(AbsolutePath.c_str());
    
    if (iter != mTextures.end())
        texture = iter->second;
    else
    {
        SDL_Surface* surface = IMG_Load(AbsolutePath.c_str());
        if (!surface)
            return nullptr;
        
        texture = SDL_CreateTextureFromSurface(mRenderer, surface);
        SDL_free(surface);
        if (!texture)
            return nullptr;
        
        mTextures.emplace(AbsolutePath, texture);
    }
    
    return texture;
}

Enemy* Game::GetNearestEnemy(const CML::Vector2D& position)
{
    Enemy* best = nullptr;
    
    if (mEnemies.size() > 0)
    {
        best = mEnemies[0];
        float bestDistance = (position - mEnemies[0]->GetPosition()).LengthSquared();
        
        for (size_t i = 1; i < mEnemies.size(); ++i)
        {
            float newDistance = (position - mEnemies[i]->GetPosition()).LengthSquared();
            if (newDistance < bestDistance)
            {
                bestDistance = newDistance;
                best = mEnemies[i];
            }
        }
    }
    
    return best;
}

void Game::Input()
{
    SDL_Event event;
    
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                mIsRunning = false;
                break;
        }
    }
    
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);
    if (keyState[SDL_SCANCODE_ESCAPE])
        mIsRunning = false;
    
    /* Specialization for TowerDefense */
    if (keyState[SDL_SCANCODE_B])
        mGrid->BuildTower();
    
    /* Specialization for TowerDefense */
    int x, y;
    Uint32 buttons = SDL_GetMouseState(&x, &y);
    if (SDL_BUTTON(buttons) & SDL_BUTTON_LEFT)
        mGrid->Click(x, y);
    
    mIsUpdatingActors = true;
    for (auto actor : mActors)
        actor->Input(keyState);
    mIsUpdatingActors = false;
}

void Game::Update()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.f;
    if (deltaTime > 0.05f)
        deltaTime = 0.05f;
    
    mTicksCount = SDL_GetTicks();
    
    mIsUpdatingActors = true;
    for (auto actor : mActors)
        actor->Update(deltaTime);
    mIsUpdatingActors = false;
    
    for (auto pendingActor : mPendingActors)
        mActors.emplace_back(pendingActor);
    mPendingActors.clear();
    
    vector<Actor*> disabledActors;
    for (auto actor : mActors)
        if (actor->GetState() == Actor::EDisable)
            disabledActors.emplace_back(actor);
    
    for (auto disabledActor : disabledActors)
        delete disabledActor;
}

void Game::Output()
{
    SDL_SetRenderDrawColor(mRenderer, 128, 0, 128, 255);
    SDL_RenderClear(mRenderer);
    
    for (auto sprite : mSprites)
        sprite->Draw(mRenderer);
    
    SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
    mGrid = new Grid(this);
}

void Game::UnloadData()
{
    while (!mActors.empty())
        delete mActors.back();
    
    for (auto texture : mTextures)
        SDL_DestroyTexture(texture.second);
    
    mTextures.clear();
}
