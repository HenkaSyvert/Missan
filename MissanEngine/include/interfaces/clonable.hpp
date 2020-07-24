#pragma once

namespace missan {

	class IClonable {

	public:
		virtual ~IClonable() {};	// must have definition - empty body - since derived classes will call it
		virtual IClonable* Clone() const = 0;

	};
}