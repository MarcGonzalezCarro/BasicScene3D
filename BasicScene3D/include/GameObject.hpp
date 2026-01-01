#pragma once

#include <vector>
#include <string>
#include "Transform.hpp"

struct GameObject
{
    explicit GameObject(const std::string& name)
        : name(name)
    {}

    std::string name;
    Transform transform;

    GameObject* parent = nullptr;
    std::vector<GameObject*> children;

    void AddChild(GameObject* child);

    Matrix4x4 GetGlobalMatrix() const;
    
};