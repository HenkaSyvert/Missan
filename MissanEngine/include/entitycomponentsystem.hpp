#pragma once

#include <vector>


namespace Missan {
	class GameObject;
	class Component;
}



// event funcs per component
void EcsComponentsStart();
void EcsComponentsUpdate();
void EcsComponentsLateUpdate();
void EcsGameObjectInstantiate();
void EcsGameObjectDestroy();


std::vector<Missan::GameObject*>& EcsGetGameObjects();
