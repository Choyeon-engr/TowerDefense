#include "Bullet.hpp"
#include "Game.hpp"
#include "MovementComponent.hpp"
#include "SpriteComponent.hpp"
#include "CircleComponent.hpp"
#include "Enemy.hpp"

Bullet::Bullet(Game* game)
:Actor(game)
{
    mMovement = new MovementComponent(this, 3);
    mMovement->AddForce(CML::Vector2D(GetForwardVector().X * 20000.f, GetForwardVector().Y * 20000.f));
    mMovement->SetMass(1.f);
    
    SpriteComponent* sprite = new SpriteComponent(this, 4);
    sprite->SetTexture(GetGame()->GetTexture("/Assets/Candy.png"));
    
    mCircle = new CircleComponent(this, 5);
    mCircle->SetRadius(5.f);
    
    mLiveTime = 1.f;
}

void Bullet::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
    
    mMovement->AddForce(CML::Vector2D(GetForwardVector().X * 20000.f, GetForwardVector().Y * 20000.f));
    
    for (Enemy* enemy : GetGame()->GetEnemies())
    {
        if (Intersect(*mCircle, *(enemy->GetCircle())))
        {
            enemy->SetState(EDisable);
            SetState(EDisable);
            break;
        }
    }
    
    mLiveTime -= deltaTime;
    if (mLiveTime <= 0.f)
        SetState(EDisable);
}
