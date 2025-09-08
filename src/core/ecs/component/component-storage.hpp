#pragma once
#include <unordered_map>

#include "../entity-manager.hpp"

class IComponentStorage {
    public:
    virtual ~IComponentStorage() = default;
    virtual void entityDestroyed() {};
};

template <typename T>
class ComponentStorage final : public IComponentStorage {
    std::unordered_map<Entity, T> components_;
    public:

    void add(Entity entity, T component) {
        components_[entity] = component;
    }

    void remove(Entity entity) {
        components_.erase(entity);
    }

    T& get(Entity entity) {
        return components_[entity];
    }

    void entityDestroyed(Entity entity) {
        components_.erase(entity);
    }
};
