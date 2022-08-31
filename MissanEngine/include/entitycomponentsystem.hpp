#pragma once

#include <vector>


namespace Missan {
	class GameObject;
	class Component;
}

extern std::vector<Missan::Component*> components;


// event funcs per component
void EcsComponentsStart();
void EcsComponentsUpdate();
void EcsComponentsLateUpdate();
void EcsGameObjectInstantiate();
void EcsGameObjectDestroy();


std::vector<Missan::GameObject*>& EcsGetGameObjects();
template <class T> T* EcsAddComponent() {
	components.push_back(new T());
	return (T*)components.back();
}

void EcsDeleteComponent(Missan::Component* component);


