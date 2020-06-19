#include "gl3d.h"

#include "Rubik.h"

using namespace gl3d;

bool keys[1024];

Vec2d mousePrevPos;
Vec2d mousePos;

Vec2f cameraAngle;
const Vec2f maxCameraAngle = { 35.0f, 35.0f };

static void key_callback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mode)
{
	if (key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, true);
	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	mousePos.x = xpos;
	mousePos.y = ypos;
}

int main()
{
	Window::create(Vec2i(1400, 1000), "Rubik's cube");

	// window settings

	glfwSetKeyCallback(Window::getInstance(), key_callback);
	glfwSetCursorPosCallback(Window::getInstance(), cursor_position_callback);
	mousePos.x = mousePrevPos.x = Window::size().x / 2.0f;
	mousePos.y = mousePrevPos.y = Window::size().y / 2.0f;
	glfwSetCursorPos(Window::getInstance(), mousePos.x, mousePos.y);

	// shader

	Shader shader("vshader.shdr", "fshader.shdr");

	// matrix

	glm::mat4 viewPos = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -15.0f));
	glm::mat4 viewX(1.0f);
	glm::mat4 viewY(1.0f);

	glm::mat4 projection = glm::perspective(45.0f, (float)Window::size().x / Window::size().y, 0.1f, 100.0f);

	Rubik rubik;
	rubik.setRotationSpeed(1.0f);

	while (!Window::shouldClose())
	{
		Window::clear(Color(32, 32, 32, 255));

		// move camera

		Vec2f angle = { (float)(mousePos.x - mousePrevPos.x) / 7.5f,
			(float)(mousePos.y - mousePrevPos.y) / 7.5f };

		if (cameraAngle.y + angle.y < maxCameraAngle.y &&
			cameraAngle.y + angle.y > -maxCameraAngle.y)
		{
			cameraAngle.y += angle.y;
			viewY = glm::rotate(viewY, glm::radians(angle.y), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (cameraAngle.x + angle.x < maxCameraAngle.x &&
			cameraAngle.x + angle.x > -maxCameraAngle.x)
		{
			cameraAngle.x += angle.x;
			viewX = glm::rotate(viewX, glm::radians(angle.x), glm::vec3(0.0f, 1.0f, 0.0f));
		}

		mousePrevPos = mousePos;

		// rotations

		if (!rubik.isRotating() && rubik.isQueueEmpty())
		{
			if (keys[GLFW_KEY_R])
				rubik.addRotationsToQueue("R U R' U' R' F R R U' R' U' R U R' F'");
			if (keys[GLFW_KEY_T])
				rubik.addRotationsToQueue("R U R' F' R U R' U' R' F R R U' R' U' R U R' F'");

			// scramble
			if (keys[GLFW_KEY_SPACE])
			{
				for (int i = 0; i < 15; ++i)
					rubik.addRotationToQueue(Rubik::Rotation(Rubik::Rotation::Side,
						(Axis)(rand() % 3), rand() % 3, rand() % 2, false));
			}

			// L
			if (keys[GLFW_KEY_KP_4] && keys[GLFW_KEY_KP_7])
				rubik.setRotation(Rubik::Rotation::Side, Axis::X, 0, false);
			else if (keys[GLFW_KEY_KP_4] && keys[GLFW_KEY_KP_1])
				rubik.setRotation(Rubik::Rotation::Side, Axis::X, 0, true);
			// M
			if (keys[GLFW_KEY_KP_5] && keys[GLFW_KEY_KP_8])
				rubik.setRotation(Rubik::Rotation::Side, Axis::X, 1, false);
			else if (keys[GLFW_KEY_KP_5] && keys[GLFW_KEY_KP_2])
				rubik.setRotation(Rubik::Rotation::Side, Axis::X, 1, true);
			// R
			else if (keys[GLFW_KEY_KP_6] && keys[GLFW_KEY_KP_3])
				rubik.setRotation(Rubik::Rotation::Side, Axis::X, 2, true);
			else if (keys[GLFW_KEY_KP_6] && keys[GLFW_KEY_KP_9])
				rubik.setRotation(Rubik::Rotation::Side, Axis::X, 2, false);
			// U
			else if (keys[GLFW_KEY_KP_8] && keys[GLFW_KEY_KP_9])
				rubik.setRotation(Rubik::Rotation::Side, Axis::Y, 2, true);
			else if (keys[GLFW_KEY_KP_8] && keys[GLFW_KEY_KP_7])
				rubik.setRotation(Rubik::Rotation::Side, Axis::Y, 2, false);
			// D
			else if (keys[GLFW_KEY_KP_2] && keys[GLFW_KEY_KP_1])
				rubik.setRotation(Rubik::Rotation::Side, Axis::Y, 0, false);
			else if (keys[GLFW_KEY_KP_2] && keys[GLFW_KEY_KP_3])
				rubik.setRotation(Rubik::Rotation::Side, Axis::Y, 0, true);
			// E
			else if (keys[GLFW_KEY_KP_5] && keys[GLFW_KEY_KP_4])
				rubik.setRotation(Rubik::Rotation::Side, Axis::Y, 1, false);
			else if (keys[GLFW_KEY_KP_5] && keys[GLFW_KEY_KP_6])
				rubik.setRotation(Rubik::Rotation::Side, Axis::Y, 1, true);
			// F
			else if (keys[GLFW_KEY_KP_5] && keys[GLFW_KEY_KP_1])
				rubik.setRotation(Rubik::Rotation::Side, Axis::Z, 2, true);
			else if (keys[GLFW_KEY_KP_5] && keys[GLFW_KEY_KP_3])
				rubik.setRotation(Rubik::Rotation::Side, Axis::Z, 2, false);
			// B
			else if (keys[GLFW_KEY_KP_8] && keys[GLFW_KEY_KP_6])
				rubik.setRotation(Rubik::Rotation::Side, Axis::Z, 0, false);
			else if (keys[GLFW_KEY_KP_8] && keys[GLFW_KEY_KP_4])
				rubik.setRotation(Rubik::Rotation::Side, Axis::Z, 0, true);

			else if (keys[GLFW_KEY_W])
				rubik.setRotation(Rubik::Rotation::Cube, Axis::X, 0, false);
			else if (keys[GLFW_KEY_S])
				rubik.setRotation(Rubik::Rotation::Cube, Axis::X, 0, true);
			else if (keys[GLFW_KEY_A])
				rubik.setRotation(Rubik::Rotation::Cube, Axis::Y, 0, false);
			else if (keys[GLFW_KEY_D])
				rubik.setRotation(Rubik::Rotation::Cube, Axis::Y, 0, true);
			else if (keys[GLFW_KEY_E])
				rubik.setRotation(Rubik::Rotation::Cube, Axis::Z, 0, false);
			else if (keys[GLFW_KEY_Q])
				rubik.setRotation(Rubik::Rotation::Cube, Axis::Z, 0, true);
		}

		rubik.rotate();

		// draw

		rubik.draw(viewPos * viewX * viewY, projection, shader);

		Window::show();
	}
	Window::destroy();
}