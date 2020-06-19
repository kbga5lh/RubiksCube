#include "Rubik.h"

GLfloat Rubik::vertices[] =
{
	// 1 2
	// 0 3
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	// 5 6
	// 4 7
	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
};

GLuint Rubik::indicesBack[] =
{
	0, 1, 2,
	0, 3, 2,
};

GLuint Rubik::indicesFront[] =
{
	4, 5, 6,
	4, 7, 6,
};

GLuint Rubik::indicesLeft[] =
{
	0, 1, 5,
	0, 4, 5,
};

GLuint Rubik::indicesRight[] =
{
	3, 2, 6,
	3, 7, 6,
};

GLuint Rubik::indicesTop[] =
{
	1, 2, 6,
	1, 5, 6,
};

GLuint Rubik::indicesBottom[] =
{
	0, 3, 7,
	0, 4, 7,
};

GLuint Rubik::VAO, Rubik::VBO,
	Rubik::IBOleft, Rubik::IBOright,
	Rubik::IBOback, Rubik::IBOfront,
	Rubik::IBOtop, Rubik::IBObottom;

void Rubik::initGraphics()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glGenBuffers(1, &IBOleft);
	glGenBuffers(1, &IBOright);
	glGenBuffers(1, &IBOback);
	glGenBuffers(1, &IBOfront);
	glGenBuffers(1, &IBOtop);
	glGenBuffers(1, &IBObottom);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOleft);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesLeft), indicesLeft, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOright);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesRight), indicesRight, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOback);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesBack), indicesBack, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOfront);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesFront), indicesFront, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOtop);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesTop), indicesTop, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBObottom);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesBottom), indicesBottom, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	isGraphicsInit = true;
}

Rubik::Rubik()
{
	if (!isGraphicsInit)
		initGraphics();

	resetTransformations();

	// front
	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			cubes[x][y][2].front = Color(0, 255, 0);
	// back
	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			cubes[x][y][0].back = Color(0, 0, 255);
	// left
	for (int z = 0; z < 3; ++z)
		for (int y = 0; y < 3; ++y)
			cubes[0][y][z].left = Color(255, 128, 0);
	// right
	for (int z = 0; z < 3; ++z)
		for (int y = 0; y < 3; ++y)
			cubes[2][y][z].right = Color(255, 0, 0);
	// top
	for (int x = 0; x < 3; ++x)
		for (int z = 0; z < 3; ++z)
			cubes[x][2][z].top = Color(255, 255, 255);
	// bottom
	for (int x = 0; x < 3; ++x)
		for (int z = 0; z < 3; ++z)
			cubes[x][0][z].bottom = Color(255, 255, 0);
}

void drawSide(Shader& n_shader, Color n_color, GLuint n_IBOside)
{
	glUniform4fv(glGetUniformLocation(n_shader.GetProgram(), "color"), 1,
		glm::value_ptr(glm::vec4(
			Color::toGLcolor(n_color.red),
			Color::toGLcolor(n_color.green),
			Color::toGLcolor(n_color.blue), 1.0f
		)
	));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, n_IBOside);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Rubik::resetTransformations()
{
	for (int x = -1; x < 2; ++x)
		for (int y = -1; y < 2; ++y)
			for (int z = -1; z < 2; ++z)
			{
				Cube& cube = cubes[x + 1][y + 1][z + 1];
				cube.rotation = glm::mat4(1.0f);
				cube.position = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f * x, 2.0f * y, 2.0f * z));
			}
}

void Rubik::draw(const glm::mat4& n_view, const glm::mat4& n_projection, Shader& n_shader)
{
	for (int x = -1; x < 2; ++x)
		for (int y = -1; y < 2; ++y)
			for (int z = -1; z < 2; ++z)
			{
				Cube& cube = cubes[x + 1][y + 1][z + 1];

				n_shader.Use();
				glBindVertexArray(VAO);
				
				glUniformMatrix4fv(glGetUniformLocation(n_shader.GetProgram(), "model"), 1, GL_FALSE,
					glm::value_ptr(cube.rotation * cube.position));

				glUniformMatrix4fv(glGetUniformLocation(n_shader.GetProgram(), "view"), 1, GL_FALSE,
					glm::value_ptr(n_view));

				glUniformMatrix4fv(glGetUniformLocation(n_shader.GetProgram(), "projection"), 1, GL_FALSE,
					glm::value_ptr(n_projection));

				drawSide(n_shader, cube.left, IBOleft);
				drawSide(n_shader, cube.right, IBOright);
				drawSide(n_shader, cube.front, IBOfront);
				drawSide(n_shader, cube.back, IBOback);
				drawSide(n_shader, cube.top, IBOtop);
				drawSide(n_shader, cube.bottom, IBObottom);

				glBindVertexArray(0);
			}
}



void Rubik::setRotation(Rotation::RotationType n_type, Axis n_axis, int n_side, bool n_isClockwise, bool n_isDouble)
{
	if (isRotating())
		return;
	rotation.rotationType = n_type;
	rotation.rotationAxis = n_axis;
	rotation.isRotationDouble = n_isDouble;
	rotation.isRotationClockwise = n_isClockwise;
	rotation.sideNum = n_side;

	rotation.xl = rotation.yl = rotation.zl = 0;
	rotation.xh = rotation.yh = rotation.zh = 3;
	if (n_type == Rotation::Side)
	{
		if (n_axis == Axis::X)
		{
			rotation.xl = n_side;
			rotation.xh = n_side + 1;
		}
		else if (n_axis == Axis::Y)
		{
			rotation.yl = n_side;
			rotation.yh = n_side + 1;
		}
		else if (n_axis == Axis::Z)
		{
			rotation.zl = n_side;
			rotation.zh = n_side + 1;
		}

		Cube sideBuff[3][3];

		for (int x = rotation.xl; x < rotation.xh; ++x)
			for (int y = rotation.yl; y < rotation.yh; ++y)
				for (int z = rotation.zl; z < rotation.zh; ++z)
				{
					if (rotation.rotationAxis == Axis::X) sideBuff[y][z] = cubes[rotation.sideNum][y][z];
					else if (rotation.rotationAxis == Axis::Y) sideBuff[x][z] = cubes[x][rotation.sideNum][z];
					else if (rotation.rotationAxis == Axis::Z) sideBuff[x][y] = cubes[x][y][rotation.sideNum];
				}
		for (int x = rotation.xl; x < rotation.xh; ++x)
			for (int y = rotation.yl; y < rotation.yh; ++y)
				for (int z = rotation.zl; z < rotation.zh; ++z)
				{
					if (rotation.rotationAxis == Axis::X)
						cubes[rotation.sideNum][y][z] =
						sideBuff[!rotation.isRotationClockwise ? 2 - z : z][rotation.isRotationClockwise ? 2 - y : y];
					else if (rotation.rotationAxis == Axis::Y)
						cubes[x][rotation.sideNum][z] =
						sideBuff[rotation.isRotationClockwise ? 2 - z : z][!rotation.isRotationClockwise ? 2 - x : x];
					else if (rotation.rotationAxis == Axis::Z)
						cubes[x][y][rotation.sideNum] =
						sideBuff[!rotation.isRotationClockwise ? 2 - y : y][rotation.isRotationClockwise ? 2 - x : x];
				}
	}
	else
	{
		Cube buff[3][3][3];

		for (int y = 0; y < 3; ++y)
			for (int x = 0; x < 3; ++x)
				for (int z = 0; z < 3; ++z)
					buff[x][y][z] = cubes[x][y][z];

		for (int y = 0; y < 3; ++y)
			for (int x = 0; x < 3; ++x)
				for (int z = 0; z < 3; ++z)
				{
					if (rotation.rotationAxis == Axis::X)
					{
						cubes[x][y][z] = buff[x][!rotation.isRotationClockwise ? 2 - z : z]
							[rotation.isRotationClockwise ? 2 - y : y];
					}
					else if (rotation.rotationAxis == Axis::Y)
					{
						cubes[x][y][z] = buff[rotation.isRotationClockwise ? 2 - z : z][y]
							[!rotation.isRotationClockwise ? 2 - x : x];
					}
					else if (rotation.rotationAxis == Axis::Z)
					{
						cubes[x][y][z] = buff[!rotation.isRotationClockwise ? 2 - y : y]
							[rotation.isRotationClockwise ? 2 - x : x][z];
					}
				}
	}

}

void Rubik::rotate()
{
	if (!isRotating())
	{
		executeFromQueue();
		return;
	}
	else if (rotationAngle < 90.0f)
	{
		if (rotationAngle + rotationSpeed > 90.0f)
			rotationAngle += 90.5f - rotationAngle;
		else
			rotationAngle += rotationSpeed;

		auto rotateVisualCubes = [&](bool xb, bool yb, bool zb)
		{
			for (int x = rotation.xl; x < rotation.xh; ++x)
				for (int y = rotation.yl; y < rotation.yh; ++y)
					for (int z = rotation.zl; z < rotation.zh; ++z)
					{
						Cube& cube = cubes[x][y][z];
						cube.position = glm::translate(cube.position,
							glm::vec3(-2.0f * (x - 1) * (int)xb, -2.0f * (y - 1) * (int)yb, -2.0f * (z - 1) * (int)zb));
						cube.rotation = glm::rotate(cube.rotation,
							glm::radians(rotation.isRotationClockwise ? rotationSpeed : -rotationSpeed),
							glm::vec3((float)xb, (float)yb, (float)zb));
						cube.position = glm::translate(cube.position,
							glm::vec3(2.0f * (x - 1) * (int)xb, 2.0f * (y - 1) * (int)yb, 2.0f * (z - 1) * (int)zb));
					}
		};
		rotateVisualCubes(rotation.rotationAxis == Axis::X,
			rotation.rotationAxis == Axis::Y,
			rotation.rotationAxis == Axis::Z);
	}
	else
	{
		rotationAngle = 0.0f;
		resetTransformations();

		Axis ax = Axis::X;
		switch (rotation.rotationAxis)
		{
		case Axis::X: ax = Axis::Y; break;
		case Axis::Y: ax = Axis::Z; break;
		case Axis::Z: ax = Axis::X; break;
		}

		for (int x = rotation.xl; x < rotation.xh; ++x)
			for (int y = rotation.yl; y < rotation.yh; ++y)
				for (int z = rotation.zl; z < rotation.zh; ++z)
					cubes[x][y][z].rotate(ax, rotation.rotationAxis == Axis::Z ?
						rotation.isRotationClockwise : !rotation.isRotationClockwise);
		
		rotation.rotationType = Rotation::None;
	}
}

void Rubik::executeFromQueue()
{
	if (!rotationsQueue.empty())
	{
		Rotation r = rotationsQueue.front();
		setRotation(r.rotationType, r.rotationAxis, r.sideNum, r.isRotationClockwise, r.isRotationDouble);
		rotationsQueue.pop();
	}
}

void Rubik::addRotationToQueue(Rotation n_rotation)
{
	rotationsQueue.push(n_rotation);
}

void Rubik::addRotationsToQueue(const std::string& rotations)
{
	static const std::map<char, Rotation> alphabet
	{
		{ 'R',		Rotation(Rotation::Side, Axis::X, 2, false, false)},

		{ 'L',		Rotation(Rotation::Side, Axis::X, 0, true, false)},

		{ 'U',		Rotation(Rotation::Side, Axis::Y, 2, false, false)},

		{ 'D',		Rotation(Rotation::Side, Axis::Y, 0, true, false)},

		{ 'F',		Rotation(Rotation::Side, Axis::Z, 2, false, false)},

		{ 'B',		Rotation(Rotation::Side, Axis::Z, 0, true, false)},

	};

	Rotation buff;
	bool pushed = true;

	for (int i = 0; i < rotations.length(); ++i)
	{
		char curr = rotations[i];

		// postfix

		if (!pushed)
		{
			if (curr == '\'')
			{
				buff.isRotationClockwise = !buff.isRotationClockwise;
				continue;
			}
		}

		// move

		auto found = alphabet.find(curr);
		if (found != alphabet.end())
		{
			if (!pushed)
			{
				addRotationToQueue(buff);
				pushed = true;
			}
			buff = (*found).second;
			pushed = false;
		}
	}
	if (!pushed)
		addRotationToQueue(buff);
}