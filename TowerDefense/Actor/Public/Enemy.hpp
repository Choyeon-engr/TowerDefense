#pragma once

#include "Actor.hpp"

class Enemy : public Actor
{
public:
    Enemy(class Game* game);
    ~Enemy();
    
    void UpdateActor(float deltaTime) override;
    
    class CircleComponent* GetCircle() const noexcept { return mCircle; }
    
private:
    class NavigationComponent* mNavigation;
    class CircleComponent* mCircle;
};
