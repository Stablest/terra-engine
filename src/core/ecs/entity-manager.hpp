#pragma once
#include <array>
#include <bitset>
#include <queue>

#include "component/components.hpp"

constexpr std::size_t MAX_ENTITIES = 5000;

using Entity = std::uint32_t;
using ComponentSignature = std::bitset<MAX_COMPONENTS>;

class EntityManager {
    std::queue<Entity> availableEntities_;
    std::array<ComponentSignature, MAX_ENTITIES> signatures_;
    std::uint32_t entityCount_ = 0;

    EntityManager();

public:
    static EntityManager &getInstance();

    Entity createEntity();

    unsigned int destroyEntity(Entity entity);

    void setSignature(Entity entity, ComponentSignature signature);

    [[nodiscard]] ComponentSignature getSignature(Entity entity) const;

    std::vector<Entity> getEntitiesWithSignature(const ComponentSignature& signature) const;

    EntityManager(const EntityManager &) = delete;

    EntityManager &operator=(const EntityManager &) = delete;

    EntityManager(EntityManager &&) = delete;

    EntityManager &operator=(EntityManager &&) = delete;
};
