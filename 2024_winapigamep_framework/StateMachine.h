#pragma once

#include "State.h"

template <typename T>
class StateMachine {
public:
    StateMachine() {};
    ~StateMachine() {
        for (auto& pair : stateMap) {
            delete pair.second;
        }
        stateMap.clear();
    }

    void Initialize(T startState, void* ownerObject) {
        owner = ownerObject;
        CurrentState = stateMap[startState];
        CurrentState->Enter();
    }  

    void ChangeState(T newState) {
        if (CurrentState == stateMap[newState])
            return;

        if (CurrentState) {
            CurrentState->Exit();
        }
        CurrentState = stateMap[newState];
        if (CurrentState) {
            CurrentState->Enter();
        }
    }

    void Update() {
        if (CurrentState) {
            CurrentState->UpdateState();
        }
    }

    void AddState(T stateEnum, State<T>* state) {
        stateMap[stateEnum] = state;
    }
public:
    State<T>* CurrentState;
private:
    std::unordered_map<T, State<T>*> stateMap;
    void* owner;
};