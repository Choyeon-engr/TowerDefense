#include "Tower.hpp"
#include "Game.hpp"
#include "MovementComponent.hpp"
#include "SpriteComponent.hpp"
#include "AIComponent.hpp"
#include "AIState.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "CML.hpp"

Tower::Tower(Game* game)
: Actor(game)
{
    mMovement = new MovementComponent(this, 3);
    
    SpriteComponent* sprite = new SpriteComponent(this, 4);
    sprite->SetTexture(GetGame()->GetTexture("/Assets/Ghost.png"));
    
    mAI = new AIComponent(this, 1);
    mAI->RegisterState(new AIPatrol(mAI));
    mAI->RegisterState(new AIAttack(mAI));
    
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
                mAI->ChangeState("Attack");
                
                SetRotation(CML::Arctan(-direction.Y, direction.X));
                
                Bullet* bullet = new Bullet(GetGame());
                bullet->SetPosition(GetPosition());
                bullet->SetRotation(GetRotation());
                
                mAttackCoolTime = mAttackInterval;
            }
            else
                mAI->ChangeState("Patrol");
        }
        else
            mAI->ChangeState("Patrol");
    }
    else
        mAI->ChangeState("Patrol");
}
