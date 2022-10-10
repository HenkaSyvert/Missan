#include "ecs/object.hpp"

#include <queue>

using namespace Missan;
using namespace std;


// generate new unique ID or reuse an old one
Object::IdType Object::GetUniqueId() {
	static IdType newId = 0;
	static queue<IdType> freeIds;

	if (freeIds.empty()) return newId++;

	IdType id = freeIds.front();
	freeIds.pop();

	return id;
}