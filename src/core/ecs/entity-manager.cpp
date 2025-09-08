#include "entity-manager.hpp"

EntityManager::EntityManager() {
    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
        _availableEntities.push(entity);
    }
}

EntityManager &EntityManager::getInstance() {
    static EntityManager instance;
    return instance;
}

Entity EntityManager::createEntity() {
    if (_entityCount >= MAX_ENTITIES) {
        return 0;
    }
    const Entity entity = _availableEntities.front();
    _availableEntities.pop();
    _entityCount++;
    return entity;
}

unsigned int EntityManager::destroyEntity(const Entity entity) {
    _signatures[entity].reset();
    _availableEntities.push(entity);
    _entityCount--;
    return entity;
}

void EntityManager::setSignature(const Entity entity, const ComponentSignature signature) {
    _signatures[entity] = signature;
}

ComponentSignature EntityManager::getSignature(const Entity entity) const{
    return _signatures[entity];
}

std::vector<Entity> EntityManager::getEntitiesWithSignature(const ComponentSignature &signature) const {
    std::vector<Entity> entities;
    entities.reserve(_entityCount);
    for (Entity entity = 0; entity < _entityCount; ++entity) {
        if (_signatures[entity].none()) continue;
        if ((_signatures[entity] & signature) == signature) {
            entities.push_back(entity);
        }
    }
    return entities;
}



