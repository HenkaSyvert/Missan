#pragma once

#include <string>

namespace Missan {

	namespace ECS {

		void* AddComponentById(size_t gameObjectId, size_t componentTypeId, size_t componentSize, std::string componentName, void* component);
		
		const void* GetComponentArrayById(size_t componentTypeId);
		
		void RemoveComponentById(size_t gameObjectId, size_t componentTypeId);
		
		void* GetComponentById(size_t gameObjectId, size_t componentTypeId);

		void CopyComponents(size_t sourceId, size_t destinationId);

		void DestroyGameObject(size_t gameObjectId);


		extern size_t freeComponentTypeId;
		template<class T>
		size_t GetComponentTypeId() {
			static size_t typeId = freeComponentTypeId++;
			return typeId;
		}

		template<class T>
		const T* GetComponentArray() {
			return (const T*)GetComponentArrayById(GetComponentTypeId<T>());
		}

		template<class T>
		T* AddComponent(size_t gameObjectId) {
			T component;
			return (T*)AddComponentById(gameObjectId, GetComponentTypeId<T>(), sizeof(T), typeid(T).name(), &component);
		}

		template<class T>
		void RemoveComponent(size_t gameObjectId) {
			RemoveComponentById(gameObjectId, GetComponentTypeId<T>());
		}

		template<class T>
		T* GetComponent(size_t gameObjectId) {
			return (T*)GetComponentById(gameObjectId, GetComponentTypeId<T>());
		}



	}
}