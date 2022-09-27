#pragma once
#include "missan.hpp"

using namespace Missan;

class CameraTest : public Component {


public:

	Camera* c;

	void Start() {
		c = Camera::main;
	}

	void Update() {

		if (Input::GetKey(Keycode::O)) c->aspectRatio -= .1;
		if (Input::GetKey(Keycode::P)) c->aspectRatio += .1;
		if (Input::GetKey(Keycode::K)) c->farClipPlane -= .1;
		if (Input::GetKey(Keycode::L)) c->farClipPlane += .1;
		if (Input::GetKey(Keycode::N)) c->nearClipPlane -= .1;
		if (Input::GetKey(Keycode::M)) c->nearClipPlane += .1;
		if (Input::GetKey(Keycode::H)) c->fieldOfView -= .1;
		if (Input::GetKey(Keycode::J)) c->fieldOfView += .1;
		if (Input::GetKey(Keycode::U)) c->orthographicSize -= .1;
		if (Input::GetKey(Keycode::I)) c->orthographicSize += .1;
		if (Input::GetKeyDown(Keycode::Enter)) {
			if (c->projection == Camera::Projection::perspective)
				c->projection = Camera::Projection::orthographic;
			else
				c->projection = Camera::Projection::perspective;
		}

	}

	CameraTest* Clone() const {
		return new CameraTest(*this);
	}
};