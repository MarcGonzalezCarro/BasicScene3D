#include "GameObject.hpp"

void GameObject::AddChild(GameObject* child)
{
    if (!child) return;

    child->parent = this;
    children.push_back(child);
}

Matrix4x4 GameObject::GetGlobalMatrix() const
{
    if (parent)
        return parent->GetGlobalMatrix().Multiply(transform.GetLocalMatrix());

    return transform.GetLocalMatrix();
}