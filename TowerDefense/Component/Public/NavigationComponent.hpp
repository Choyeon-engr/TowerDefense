#pragma once

#include "MovementComponent.hpp"
#include "CML.hpp"

class NavigationComponent : public MovementComponent
{
public:
    NavigationComponent(class Actor* owner, int updateOrder) : MovementComponent(owner, updateOrder), mNextNode(nullptr) {}
    
    void Update(float deltaTime) override;
    
    void SetStartPoint(const class Tile* start);
    void TurnTo(const CML::Vector2D& position);
    
private:
    const class Tile* mNextNode;
};
