#pragma once

#include "memory/memory.hpp"

namespace Missan {

	class Component;

	namespace ECS {

		InstanceId AddComponent(TypeId componentTypeId, InstanceId gameObjectId, void* originalComponent = nullptr);

		void* GetComponent(TypeId componentTypeId, InstanceId gameObjectId);

		void RemoveComponent(TypeId componentTypeId, InstanceId gameObjectId);



		void Destroy(InstanceId gameObjectId);

		void DestroyImmediate(InstanceId gameObjectId);

		void DestroyQueued();



		InstanceId Instantiate(InstanceId originalGameObjectId = NULL);

		RawArray<Component*> GetAttachedComponents(InstanceId gameObjectId);

		




		// TODO: remove these, by making monobehaviour or something
		void UpdateAll();
		void LateUpdateAll();
		void OnGuiAll();



	}

}
