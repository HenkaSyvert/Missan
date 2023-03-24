#pragma once

#include "ecs.hpp"
#include "graphics/color.hpp"

namespace Missan {

	///
	/// Represents a light source in the Scene. 
	/// Not all fields are used by the different types. 
	/// Note that not all shaders take Lights into account. 
	class Light : public Component<Light> {

	public:

		///
		/// The ambient Color emitted from this Light. Ambient light represents the 
		/// scattered light in real world. Usually, it is almost never -completely- dark, 
		/// so ambient applies a Color, from all directions, to represent this. 
		/// Usually ambient is kept rather weak. 
		Color ambient = Color::Lerp(Color::yellow, Color::white, 0.8) * 0.4f;

		///
		/// The diffuse Color emitted from this Light. Diffuse light simulates the 
		/// directional impact of the Light, and it colors the faces of an object
		/// in lighter shades if they face the light source, and darker if they face away. 
		Color diffuse = Color::Lerp(Color::yellow, Color::white, 0.8) * 0.8f;

		///
		/// The specular Color emitted from this Light. Specular simulates the bright spot of the
		/// Light that can appear on shiny surfaces, giving a glassy or metallic look. How shiny
		/// it looks also depends on the shininess of the material. 
		Color specular = Color::Lerp(Color::yellow, Color::white, 0.9);

		void DisplayInInspector() {
			using namespace ImGui;
			if (CollapsingHeader("Light")) {
				ColorEdit4("ambient", (float*)&ambient);
				ColorEdit4("diffuse", (float*)&diffuse);
				ColorEdit4("specular", (float*)&specular);
			}
		}
	};

}