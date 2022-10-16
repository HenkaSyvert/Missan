#include "ecs/component.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "memory/memory.hpp"

#define DEBUG_COMPONENT 1

using namespace Missan;
using namespace std;


size_t Component::componentOffset = 0;

void Component::UpdateAll() {
	for (int j = Component::componentOffset; j < Memory::arrays.size(); j++) {
		auto compArr = Memory::arrays[j];
		RawArrayBase arr = compArr->AsRawArrayBase();
		for (int i = 0; i < arr.count; i++)
			((Component*)arr[i])->Update();
	}
}

void Component::LateUpdateAll() {
	for (int j = Component::componentOffset; j < Memory::arrays.size(); j++) {
		auto compArr = Memory::arrays[j];
		RawArrayBase arr = compArr->AsRawArrayBase();
		for (int i = 0; i < arr.count; i++)
			((Component*)arr[i])->LateUpdate();
	}
}

void Component::OnGuiAll() {
	for (int j = Component::componentOffset; j < Memory::arrays.size(); j++) {
		auto compArr = Memory::arrays[j];
		RawArrayBase arr = compArr->AsRawArrayBase();
		for (int i = 0; i < arr.count; i++)
			((Component*)arr[i])->OnGui();
	}
}