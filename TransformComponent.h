#pragma once
#include "Components.h"
#include "Vector2d.h"

class TransformComponent : public Component
{
public:

	Vector2d position;
	Vector2d velocity;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 3;

	TransformComponent() {
		setPos(0.0f, 0.0f);
	}

	TransformComponent(float x, float y) {
		setPos(x, y);
	}

	void init() override {
		velocity.x = 0;
		velocity.y = 0;
	}

	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

	void setPos(float x, float y) {
		position.x = x;
		position.y = y;
	}


};
