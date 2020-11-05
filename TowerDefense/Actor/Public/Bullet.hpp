#pragma once

#include "Actor.hpp"

class Bullet : public Actor
{
public:
    Bullet(class Game* game);
    
    void UpdateActor(float deltaTime) override;
    
private:
    class MovementComponent* mMovement;
    class CircleComponent* mCircle;
    
    float mLiveTime;
};