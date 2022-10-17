#pragma once


namespace Missan {

	// Unique ID per instance
	typedef size_t InstanceId;



	// Unique ID per type
	// also, typeid(T).hash_code() does NOT (apparently) return
	// a unique ID per type per the specificiation, only that
	// same class gets same hash, but 2 classes may share hash. 
	// hence the need for my own TypeId. 
	typedef size_t TypeId;


}