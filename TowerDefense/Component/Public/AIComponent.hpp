#pragma once

#include <string>
#include <unordered_map>

#include "Component.hpp"

using namespace std;

class AIComponent : public Component
{
public:
    AIComponent(class Actor* owner, int updateOrder) : Component(owner, updateOrder), mCurrentState(nullptr){}
    ~AIComponent();
    
    void Update(float deltaTime) override;
    
    void RegisterState(class AIState* state);
    void SetCurrentState(const string& stateName);
    void ChangeState(const string& stateName);
    
private:
    class AIState* mCurrentState;
    unordered_map<string, class AIState*> mStates;
};
