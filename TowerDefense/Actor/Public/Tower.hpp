#pragma once

#include "Actor.hpp"

class Tower : public Actor
{
public:
    Tower(class Game* game);
    
    void UpdateActor(float deltaTime) override;
    
    float GetAttackCoolTime() const noexcept { return mAttackCoolTime; }
    void ResetAttackCoolTime() { mAttackCoolTime = mAttackInterval; }
    
    float GetAttackRange() const noexcept { return mAttackRange; }
    
private:
    class MovementComponent* mMovement;
    class AIComponent* mAI;
    
    float mAttackCoolTime;
    const float mAttackInterval = 2.5f;
    const float mAttackRange = 250.f;
};
