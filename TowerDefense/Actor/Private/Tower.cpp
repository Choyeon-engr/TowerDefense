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
    mAI->RegisterState(new TowerPatrol(mAI));
    mAI->RegisterState(new TowerAttack(mAI));
    mAI->SetCurrentState("TowerPatrol");
    
    mAttackCoolTime = mAttackInterval;
}

void Tower::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
    
    mAttackCoolTime -= deltaTime;
    
    mAI->Update(deltaTime);
}
