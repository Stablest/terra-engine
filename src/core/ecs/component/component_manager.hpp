#pragma once
#include <memory>
#include <ranges>
#include <unordered_map>
#include "component-storage.hpp"
#include "components.hpp"

struct Transform;
struct Text;
struct Sprite;

class ComponentManager {
    std::unordered_map<Component, std::shared_ptr<IComponentStorage> > components_;

    template<typename T>
    std::shared_ptr<ComponentStorage<T> > getComponentArray() {
        const ComponentType typeId = getComponentType<T>();
        return std::static_pointer_cast<ComponentStorage<T> >(components_.at(typeId));
    }

    ComponentManager() = default;

    ~ComponentManager() = default;

public:
    static ComponentManager &getInstance() {
        static ComponentManager instance;
        return instance;
    }

    ComponentManager(const ComponentManager &) = delete;

    ComponentManager &operator=(const ComponentManager &) = delete;

    ComponentManager(ComponentManager &&) = delete;

    ComponentManager &operator=(ComponentManager &&) = delete;

    template<typename T>
    ComponentType registerComponent() {
        const ComponentType typeId = getComponentType<T>();
        if (components_.contains(typeId)) {
            return 0;
        }
        components_[typeId] = std::make_shared<ComponentStorage<T> >();
        return typeId;
    }

    template<typename T>
    void bindComponent(const Entity entity, const T component) {
        const ComponentType typeId = getComponentType<T>();
        std::static_pointer_cast<ComponentStorage<T> >(components_.at(typeId))->add(entity, component);
        auto signature = EntityManager::getInstance().getSignature(entity);
        signature.set(typeId, true);
        EntityManager::getInstance().setSignature(entity, signature);
    }

    template<typename T>
    void unbindComponent(const Entity entity) {
        const ComponentType typeId = getComponentType<T>();
        std::static_pointer_cast<ComponentStorage<T> >(components_.at(typeId))->remove(entity);
        auto signature = EntityManager::getInstance().getSignature(entity);
        signature.set(typeId, false);
        EntityManager::getInstance().setSignature(entity, signature);
    }

    void unbindComponents(const Entity entity) const {
        for (const auto &val: components_ | std::views::values) {
            val->remove(entity);
        }
        auto signature = EntityManager::getInstance().getSignature(entity);
        signature.reset();
        EntityManager::getInstance().setSignature(entity, signature);
    }

    template<typename T>
    T &getComponent(const Entity entity) {
        return getComponentArray<T>()->get(entity);
    }
};
