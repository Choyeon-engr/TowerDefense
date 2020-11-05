#include "NavigationComponent.hpp"
#include "Tile.hpp"

void NavigationComponent::Update(float deltaTime)
{
    if (mNextNode)
    {
        CML::Vector2D d = mOwner->GetPosition() - mNextNode->GetPosition();
        if (CML::CloseToZero(d.Length(), 2.f))
        {
            mNextNode = mNextNode->GetParent();
            TurnTo(mNextNode->GetPosition());
        }
    }
    
    MovementComponent::Update(deltaTime);
}

void NavigationComponent::SetStartPoint(const Tile* start)
{
    mNextNode = start->GetParent();
    TurnTo(mNextNode->GetPosition());
}

void NavigationComponent::TurnTo(const CML::Vector2D& position)
{
    CML::Vector2D direction = position - mOwner->GetPosition();
    float angle = CML::Arctan(-direction.Y, direction.X);
    mOwner->SetRotation(angle);
}
