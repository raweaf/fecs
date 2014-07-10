#pragma once

#include <vector>
#include <deque>
#include <unordered_set>
#include <typeinfo>
#include <iterator>

#include "Entity.hpp"

using namespace std;

vector<void*> componentVectors;

vector<Entity> entities;

deque<size_t> unusedEntities;

unordered_set<size_t> registeredComponentTypes;




template<class T>
ComponentTypeId<T> registerComponentType(T& componentPrototype) {

    
    size_t hash = typeid(componentPrototype).hash_code();
    
    if (registeredComponentTypes.find(hash) == registeredComponentTypes.end() ) {
        registeredComponentTypes.insert(hash);
    } else {
        //crash
    }
    
    return ComponentTypeId<T>();
}

template<typename T>
void ensureSizeOfVector(vector<T>& vector, size_t size) {
    if (vector.size() < size) {
        vector.resize(size);
    }
}

template<typename T>
size_t indexOfItemInVector(vector<T>& vector, const T& item) {
    for (size_t i = 0; i < vector.size(); i++) {
        if (item == vector[i]) {
            return i;
        }
    }

    return -1;
}

Entity& createEntity () {
    if (unusedEntities.empty() ) {
        entities.emplace_back(entities.size(), true);

        return entities.back();
    } else {
        Entity& entity = entities[unusedEntities.back()];

        entity.active = true;
        unusedEntities.pop_back();

        return entity;
    }
}

template<typename T>
void deleteEntity () {

    componentVectors.push_back(new vector<int>() );

    vector<T> vec = (vector<T>*)componentVectors[0];
}
