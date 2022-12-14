#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include"glew/glew.h"
#include <iostream>
#include"glfw/glfw3.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"Shader.h"
#include"Renderer/Shader.h"

class Camera
{
public:
	glm::vec3 Position = glm::vec3(8.5f, 15.5f, -20.0f);

	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	//glm::mat4 cameraMatrix = glm::mat4(1.0f);
	glm::mat4 MVP = glm::mat4(1.0f);

	bool firstClick = true;

	int width = 0, height = 0;

	float speed = 0.05f;
	float sensitivity = 30.0f;

	Camera() = default;
	Camera(int _width, int _height , glm::vec3 _position);

	void Setup(int _width, int _height, glm::vec3 _position);
	void UpdateMatrix(float _FOVdeg, float _nearPlane, float _farPlane, Shader& shader);
	void Input(GLFWwindow* window);
};
#endif