#include "missan.hpp"

using namespace Missan;

class Test : public Component {

public:


	void Update() {

		//std::cout << Vector3::Normalize({ 2,2,2 }) << "\n";

	}

	Test* Clone() const { return new Test(*this); }

};


int main() {



	
	Engine::Initialize();
	GameObject g;
	g.AddComponent<Test>();
	Engine::Instantiate(g);


	Engine::Run();
	Engine::Terminate();
	


	return 0;
}