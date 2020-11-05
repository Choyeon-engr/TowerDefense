#pragma once

#include "Actor.hpp"

class Tower : public Actor
{
public:
    Tower(class Game* game);
    
    void UpdateActor(float deltaTime) override;
    
private:
    class MovementComponent* mMovement;
    
    float mAttackCoolTime;
    const float mAttackInterval = 2.5f;
    const float mAttackRange = 250.f;
};
