#pragma once

class AIState
{
public:
    AIState(class AIComponent* owner) : mOwner(owner) {}
    virtual ~AIState() = default;
    
    virtual void Update(float deltaTime) = 0;
    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;
    
    virtual const char* GetName() const = 0;
    
protected:
    class AIComponent* mOwner;
};

class TowerPatrol : public AIState
{
public:
    TowerPatrol(class AIComponent* owner) : AIState(owner) {}
    
    void Update(float deltaTime) override;
    void OnEnter() override {}
    void OnExit() override {}
    
    const char* GetName() const override { return "TowerPatrol"; }
};

class TowerAttack : public AIState
{
public:
    TowerAttack(class AIComponent* owner) : AIState(owner) {}
    
    void Update(float deltaTime) override;
    void OnEnter() override {}
    void OnExit() override {}
    
    const char* GetName() const override { return "TowerAttack"; }
};
