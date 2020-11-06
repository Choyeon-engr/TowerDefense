#include "AIComponent.hpp"
#include "AIState.hpp"

AIComponent::~AIComponent()
{
    for (auto iter = mStates.begin(); iter != mStates.end(); ++iter)
        delete iter->second;
}

void AIComponent::Update(float deltaTime)
{
    if (mCurrentState)
        mCurrentState->Update(deltaTime);
}

void AIComponent::RegisterState(AIState* state)
{
    mStates.emplace(state->GetName(), state);
}

void AIComponent::SetCurrentState(const string& stateName)
{
    auto iter = mStates.find(stateName);
    if (iter != mStates.end())
        mCurrentState = iter->second;
}

void AIComponent::ChangeState(const string& stateName)
{
    if (mCurrentState)
        mCurrentState->OnExit();
    
    auto iter = mStates.find(stateName);
    if (iter != mStates.end())
    {
        mCurrentState = iter->second;
        mCurrentState->OnEnter();
    }
    else
        mCurrentState = nullptr;
}
