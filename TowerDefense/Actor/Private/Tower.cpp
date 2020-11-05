#include "Tower.hpp"
#include "Game.hpp"
#include "MovementComponent.hpp"
#include "SpriteComponent.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "CML.hpp"

Tower::Tower(Game* game)
: Actor(game)
{
    mMovement = new MovementComponent(this, 3);
    
    SpriteComponent* sprite = new SpriteComponent(this, 4);
    sprite->SetTexture(GetGame()->GetTexture("/Assets/Ghost.png"));
    
    mAttackCoolTime = mAttackInterval;
}

void Tower::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
    
    mAttackCoolTime -= deltaTime;
    if (mAttackCoolTime <= 0.f)
    {
        Enemy* enemy = GetGame()->GetNearestEnemy(GetPosition());
        if (enemy)
        {
            CML::Vector2D direction = enemy->GetPosition() - GetPosition();
            float distance = direction.Length();
            if (distance <= mAttackRange)
            {
                SetRotation(CML::Arctan(-direction.Y, direction.X));
                
                Bullet* bullet = new Bullet(GetGame());
                bullet->SetPosition(GetPosition());
                bullet->SetRotation(GetRotation());
            }
        }
        
        mAttackCoolTime = mAttackInterval;
    }
}
