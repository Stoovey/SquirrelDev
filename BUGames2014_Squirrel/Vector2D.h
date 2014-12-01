
#ifndef __VECTOR2D_H__
#define __VECTOR2D_H__

class Vector2D {

public:
	Vector2D();
	Vector2D(float x, float y);
	~Vector2D();

	float X;
	float Y;

	void add(const Vector2D& other);
	void sub(const Vector2D& other);
	void scl(float value);
	void Normalise();
	float Length();

	void Print();
};

#endif