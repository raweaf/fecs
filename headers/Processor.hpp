#pragma once

#include <vector>
#include "EntityType.hpp"
#include "global.hpp"
#include "Entity.hpp"

using namespace std;

template <class T>
class Processor {

public:
    Processor () = delete;
    Processor (EntityType<T>& entityType) : entityTypeId {entityType.id} {}

    void use() {
        EntityStorage<T>* storage = static_cast<EntityStorage<T>*> (entityStorages[entityTypeId]);
        vector<T>& entities = storage->entities;

        initializeBeforeProcessing();

        for (int i = 0; i < entities.size(); i++) {
            T& entity = entities[i];

            if (entity.active) {
                process(entity);
            }
        }

        cleanUpAfterProcessing();
    }

private:
    const size_t entityTypeId;

    virtual void initializeBeforeProcessing () {}
    virtual void cleanUpAfterProcessing () {}
    virtual void process (T& entity) {}


};
