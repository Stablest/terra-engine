#include "entity-manager.hpp"

EntityManager::EntityManager() {
    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
        availableEntities_.push(entity);
    }
}

EntityManager &EntityManager::getInstance() {
    static EntityManager instance;
    return instance;
}

Entity EntityManager::createEntity() {
    if (entityCount_ >= MAX_ENTITIES) {
        return 0;
    }
    const Entity entity = availableEntities_.front();
    availableEntities_.pop();
    entityCount_++;
    return entity;
}

unsigned int EntityManager::destroyEntity(const Entity entity) {
    signatures_[entity].reset();
    availableEntities_.push(entity);
    entityCount_--;
    return entity;
}

void EntityManager::setSignature(const Entity entity, const ComponentSignature signature) {
    signatures_[entity] = signature;
}

ComponentSignature EntityManager::getSignature(const Entity entity) const{
    return signatures_[entity];
}

std::vector<Entity> EntityManager::getEntitiesWithSignature(const ComponentSignature &signature) const {
    std::vector<Entity> entities;
    entities.reserve(entityCount_);
    for (Entity entity = 0; entity < entityCount_; ++entity) {
        if (signatures_[entity].none()) continue;
        if ((signatures_[entity] & signature) == signature) {
            entities.push_back(entity);
        }
    }
    return entities;
}



