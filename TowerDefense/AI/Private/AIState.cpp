#include "AIState.hpp"
#include "Game.hpp"
#include "AIComponent.hpp"
#include "Actor.hpp"
#include "Tower.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "CML.hpp"

void TowerPatrol::Update(float deltaTime)
{
    Tower* tower = reinterpret_cast<Tower*>(mOwner->GetOwner());
    if (tower->GetAttackCoolTime() <= 0.f)
    {
        Enemy* enemy = tower->GetGame()->GetNearestEnemy(tower->GetPosition());
        if (enemy)
        {
            CML::Vector2D direction = enemy->GetPosition() - tower->GetPosition();
            float distance = direction.Length();
            if (distance <= tower->GetAttackRange())
            {
                tower->SetRotation(CML::Arctan(-direction.Y, direction.X));
                mOwner->ChangeState("TowerAttack");
            }
        }
    }
}

void TowerAttack::Update(float deltaTime)
{
    Tower* tower = reinterpret_cast<Tower*>(mOwner->GetOwner());
    
    Bullet* bullet = new Bullet(tower->GetGame());
    bullet->SetPosition(tower->GetPosition());
    bullet->SetRotation(tower->GetRotation());
    
    tower->ResetAttackCoolTime();
    
    mOwner->ChangeState("TowerPatrol");
}
