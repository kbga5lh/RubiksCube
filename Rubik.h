#pragma once

#include "gl3d.h"

#include <queue>
#include <list>
#include <string>
#include <map>

using namespace gl3d;

struct Cube
{
	Color front, back, left, right, top, bottom;

	glm::mat4 position = glm::mat4(1.0f);
	glm::mat4 rotation = glm::mat4(1.0f);

	void rotate(Axis n_axis, bool reverse)
	{
		if (n_axis == Axis::X)
		{
			Color buff = right;
			if (reverse)
			{
				right = bottom;
				bottom = left;
				left = top;
				top = buff;
			}
			else
			{
				right = top;
				top = left;
				left = bottom;
				bottom = buff;
			}
		}
		else if (n_axis == Axis::Y)
		{
			Color buff = front;
			if (reverse)
			{
				front = bottom;
				bottom = back;
				back = top;
				top = buff;
			}
			else
			{
				front = top;
				top = back;
				back = bottom;
				bottom = buff;
			}
		}
		else if (n_axis == Axis::Z)
		{
			Color buff = front;
			if (reverse)
			{
				front = right;
				right = back;
				back = left;
				left = buff;
			}
			else
			{
				front = left;
				left = back;
				back = right;
				right = buff;
			}
		}
	}
};



class Rubik
{
public:
	struct Rotation
	{
		enum RotationType
		{
			None,
			Side,
			Cube,
		};

		RotationType rotationType = None;
		Axis rotationAxis = Axis::X;
		bool isRotationClockwise = true;
		bool isRotationDouble = false;
		int sideNum = 0;
		int xl = 0, xh = 0, yl = 0, yh = 0, zl = 0, zh = 0;

		Rotation(RotationType n_rt, Axis n_ax, int n_sideNum, bool n_isClockwise, bool n_isDouble)
			: rotationType(n_rt), rotationAxis(n_ax), sideNum(n_sideNum), isRotationClockwise(n_isClockwise),
			isRotationDouble(n_isDouble) {}
		Rotation()
		{}
	};

private:
	Cube cubes[3][3][3];
	std::queue<Rotation> rotationsQueue;

	// opengl data

	static GLfloat vertices[];

	static GLuint indicesBack[];
	static GLuint indicesFront[];
	static GLuint indicesLeft[];
	static GLuint indicesRight[];
	static GLuint indicesTop[];
	static GLuint indicesBottom[];
	
	static GLuint VAO, VBO,
		IBOleft, IBOright, IBOback, IBOfront, IBOtop, IBObottom;

	bool isGraphicsInit = false;
	void initGraphics();

	// other

	float rotationSpeed = 1.0f;
	float rotationAngle = 0.0f;

	Rotation rotation;

	void resetTransformations();

public:
	Rubik();

	void setRotation(Rotation::RotationType n_type, Axis n_axis, int n_side, bool n_isClockwise = true, bool n_isDouble = false);
	void rotate();

	void addRotationToQueue(Rotation n_rotation);
	void addRotationsToQueue(const std::string &rotations);
	void executeFromQueue();

	void setRotationSpeed(float n_speed)
	{ if (!isRotating()) rotationSpeed = n_speed; }

	float getRotationSpeed()
	{ return rotationSpeed; }

	bool isRotating()
	{ return rotation.rotationType != Rotation::None; }

	bool isQueueEmpty()
	{ return rotationsQueue.empty(); }

	void draw(const glm::mat4& n_view, const glm::mat4& n_projection, Shader &n_shader);

	// algorithms

};