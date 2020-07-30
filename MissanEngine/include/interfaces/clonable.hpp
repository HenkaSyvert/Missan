#pragma once

namespace Missan {

	// for polymorphic dynamic memory management
	class IClonable {

	public:
		// must have definition - empty body - since derived classes will call it
		virtual ~IClonable() {};	

		// derived class must implement this
		virtual IClonable* Clone() const = 0;

	};
}