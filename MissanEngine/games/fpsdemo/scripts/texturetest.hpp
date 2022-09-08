#pragma once

#include "missan.hpp"

using namespace Missan;


class TextureTest : public Component {


	Transform* t;
	Renderer* r;

	void Start() {

		t = gameObject->GetComponent<Transform>();
		r = gameObject->GetComponent<Renderer>();
	}
	int wrap = 0;
	int filter = 0;
	void Update() {

		if (Input::GetMouseButtonDown(MouseButton::Left)) {
			switch (wrap) {
			case 0:
				r->texture->wrapMode(Texture::WrapMode::clampToBorder);
				break;
			case 1:
				r->texture->wrapMode(Texture::WrapMode::clampToEdge);
				break;
			case 2:
				r->texture->wrapMode(Texture::WrapMode::repeat);
				break;
			case 3:
				r->texture->wrapMode(Texture::WrapMode::mirroredRepeat);
				break;
			}
			wrap++;
			wrap %= 4;
		}

		if (Input::GetMouseButtonDown(MouseButton::Right)) {
			switch (filter) {
			case 0:
				r->texture->filterMode(Texture::FilterMode::linear);
					break;
			case 1:
				r->texture->filterMode(Texture::FilterMode::nearest);
					break;
			}
			filter++;
			filter %= 2;
		}


	}



	TextureTest* Clone() const { return new TextureTest(*this); }
};