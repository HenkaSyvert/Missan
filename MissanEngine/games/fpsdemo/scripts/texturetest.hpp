#pragma once

#include "missan.hpp"

using namespace Missan;


class TextureTest : public Component {


	Renderer* r;
	void Start() {
		
		r = gameObject->GetComponent<Renderer>();
	}
	int wrap = 0;
	int filter = 0;
	void Update() {
		Texture& t = *r->material->texture;
		if (Input::GetMouseButtonDown(MouseButton::Left)) {
			
			switch (wrap) {
			case 0:
				t.wrapMode(Texture::WrapMode::clampToBorder);
				break;
			case 1:
				t.wrapMode(Texture::WrapMode::clampToEdge);
				break;
			case 2:
				t.wrapMode(Texture::WrapMode::repeat);
				break;
			case 3:
				t.wrapMode(Texture::WrapMode::mirroredRepeat);
				break;
			}
			wrap++;
			wrap %= 4;
		}

		if (Input::GetMouseButtonDown(MouseButton::Right)) {
			switch (filter) {
			case 0:
				t.filterMode(Texture::FilterMode::linear);
					break;
			case 1:
				t.filterMode(Texture::FilterMode::nearest);
					break;
			}
			filter++;
			filter %= 2;
		}


	}



	TextureTest* Clone() const { return new TextureTest(*this); }
};