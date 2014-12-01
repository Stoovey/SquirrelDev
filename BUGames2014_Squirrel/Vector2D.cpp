
#include "Vector2D.h"
#include <math.h>
#include <iostream>

Vector2D::Vector2D() {
	X = 0;
	Y = 0;
}

Vector2D::Vector2D(float x, float y) {
	X = x;
	Y = y;
}

Vector2D::~Vector2D() {}

void Vector2D::add(const Vector2D& other) {
	X += other.X;
	Y += other.Y;
}

void Vector2D::sub(const Vector2D& other) {
	X -= other.X;
	Y -= other.Y;
}

void Vector2D::scl(float value) {
	X *= value;
	Y *= value;
}

void Vector2D::Normalise() {
	float length = Length();
	X /= length;
	Y /= length;
}

float Vector2D::Length() {
	
	return sqrt((X * X) + (Y * Y));
}

void Vector2D::Print() {
	std::cout << "X: " << X << " Y: " << Y << " Length: " << Length();
}