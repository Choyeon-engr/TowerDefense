#include "Enemy.hpp"
#include "Game.hpp"
#include "SpriteComponent.hpp"
#include "NavigationComponent.hpp"
#include "CircleComponent.hpp"
#include "Grid.hpp"
#include "Tile.hpp"
#include "CML.hpp"

Enemy::Enemy(Game* game)
:Actor(game)
{
    game->GetEnemies().emplace_back(this);
    
    SetPosition(GetGame()->GetGrid()->GetStartTile()->GetPosition());
    
    SpriteComponent* sprite = new SpriteComponent(this, 4);
    sprite->SetTexture(game->GetTexture("/Assets/Pumpkin.png"));
    
    mNavigation = new NavigationComponent(this, 2);
    mNavigation->AddForce(CML::Vector2D(GetForwardVector().X * 2000.f, GetForwardVector().Y * 2000.f));
    mNavigation->SetMass(1.f);
    mNavigation->SetStartPoint(GetGame()->GetGrid()->GetStartTile());
    
    mCircle = new CircleComponent(this, 5);
    mCircle->SetRadius(25.f);
}

Enemy::~Enemy()
{
    auto iter = find(GetGame()->GetEnemies().begin(), GetGame()->GetEnemies().end(), this);
    GetGame()->GetEnemies().erase(iter);
}

void Enemy::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
    
    mNavigation->AddForce(CML::Vector2D(GetForwardVector().X * 2000.f, GetForwardVector().Y * 2000.f));
    
    CML::Vector2D d = GetPosition() - GetGame()->GetGrid()->GetGoalTile()->GetPosition();
    if (CML::CloseToZero(d.Length(), 10.f))
        SetState(EDisable);
}
