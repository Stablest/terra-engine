#pragma once

#include "../entity-manager.hpp"
#include "misc/dense_array/dense_array.hpp"

class IComponentStorage {
    public:
    virtual ~IComponentStorage() = default;
    virtual void remove(Entity entity) = 0;
};

template <typename T>
class ComponentStorage final : public IComponentStorage {
    DenseArray<T> components_;
    DenseArray<Entity> entities_;
    std::vector<int> sparse_;

    public:

    [[nodiscard]] bool contains(const Entity entity) const {
        if (entity >= sparse_.size()) {
            return false;
        }
        return sparse_[entity] >= 0;
    }

    void add(const Entity entity, const T component) {
        if (entity >= sparse_.size()) {
            sparse_.resize((sparse_.size() + 1) * 2, -1);
        }
        if (sparse_[entity] >= 0) {
            return;
        }
        entities_.add(entity);
        components_.add(component);
        sparse_[entity] = entities_.size() - 1;
    }

     void remove(const Entity entity) override {
        if (!contains(entity)) {
            return;
        }
        const auto lastEntity = entities_.get(entities_.size() - 1);
        entities_.swap(entities_.size() - 1, sparse_[entity]);
        components_.swap(components_.size() - 1, sparse_[entity]);
        sparse_[lastEntity] = sparse_[entity];
        sparse_[entity] = -1;
        entities_.pop();
        components_.pop();
    }

    T& get(const Entity entity) {
        return components_.get(sparse_[entity]);
    }
};
