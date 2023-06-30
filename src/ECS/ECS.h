#pragma once

#include <iostream>
#include <vector>
#include <bitset>
#include <array>
#include "../../util/log.h"

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComoponentTypeID() {
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComoponentTypeID() noexcept {
	static ComponentID typeID = getNewComoponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component {
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}
};

class Entity {
private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;
public:
	Entity(Manager& _manager): manager(_manager) {}
	void update() {
		for (auto& c: components) c->update();
	}
	void draw() {
		for (auto& c : components) c->draw();
	}
	bool isActive() const { return active; }
	void destory() { active = false; }

	bool hasGroup(Group _group) const {
		return groupBitSet[_group];
	}

	void addGroup(Group group);
	void delGroup(Group group) {
		groupBitSet[group] = false;
	}

	template <typename T> bool hasComponent() const {
		return componentBitSet[getComoponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr {c};
		components.emplace_back(std::move(uPtr));

		componentArray[getComoponentTypeID<T>()] = c;
		componentBitSet[getComoponentTypeID<T>()] = true;

		okay("New component got added. Total count %d", (int) components.size());

		c->init();
		return *c;
	}

	template<typename T> T& getComponent() const {
		auto ptr(componentArray[getComoponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager {
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;
public:
	void update() {
		for (auto& e : entities) e->update();
	}

	void draw() {
		for (auto& e : entities) e->draw();
	}

	void refresh() {

		for (auto i(0u); i < maxGroups; i++) {
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(
					std::begin(v),
					std::end(v),
					[i](const Entity* mEntity) {
						return !mEntity->isActive() || !(mEntity->hasGroup(i));
					}
				),
				std::end(v)
			);
		}

		entities.erase(
			std::remove_if(
				std::begin(entities), 
				std::end(entities),
				[](const std::unique_ptr<Entity>& mEntity) {
					return !mEntity->isActive();
				}
			), 
			std::end(entities)
		);
	}

	void addToGroup(Entity* _entity, Group _group) {
		groupedEntities[_group].emplace_back(_entity);
	}

	std::vector<Entity*>& getGroup(Group _group) {
		return groupedEntities[_group];
	}

	Entity& addEntity() {
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{e};
		entities.emplace_back(std::move(uPtr));
		okay("New entity added. Total count %d", (int) entities.size());
		return *e;
	}
};