#pragma once

#include <cstdint>

class Component
{
public:
    Component(class Actor* owner, int updateOrder);
    virtual ~Component();
    
    virtual void Update(float deltaTime) {}
    
    virtual void Input(const uint8_t* keyState) {}
    
    class Actor* GetOwner() const noexcept { return mOwner; }
    int GetUpdateOrder() const noexcept { return mUpdateOrder; }
    
protected:
    class Actor* mOwner;
    
    int mUpdateOrder;
};
