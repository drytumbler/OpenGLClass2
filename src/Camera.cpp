// Camera.cpp

#include "Camera.h"
#include <GLFW/glfw3.h>

#define clamp(X, MIN, MAX) ( (X < MIN) ? MIN : ( (X > MAX) ? MAX : X) )

Camera::Camera(int width, int height, glm::vec3 center)
   {
     Camera::width = width;
     Camera::height = height;
     position = center;
   }

void Camera::Update(float FOV, float near, float far){
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);

  view = glm::lookAt(position, position + direction, up);
  projection = glm::perspective(FOV, 1.0f * width / height, near, far);

  cameraMatrix = projection * view;

}


void Camera::Export(Shader& shader, const char* uniform) {
  glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));  
}

void Camera::ExportPos(Shader& shader, const char* uniform) {
  glUniform3fv(glGetUniformLocation(shader.ID, uniform), 1, glm::value_ptr(position));  
}

void Camera::ExportDir(Shader& shader, const char* uniform) {
  glUniform3fv(glGetUniformLocation(shader.ID, uniform), 1, glm::value_ptr(direction));  
}

void Camera::ExportRight(Shader& shader, const char* uniform) {
  glUniform3fv(glGetUniformLocation(shader.ID, uniform), 1, glm::value_ptr(right));  
}

void Camera::Inputs(GLFWwindow* window)
{
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += keyVector.z * speed * direction;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position += keyVector.x * speed * -glm::normalize(glm::cross(direction, up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position += keyVector.z * speed * -direction;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += keyVector.x * speed * glm::normalize(glm::cross(direction, up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		position += keyVector.y * speed * up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		position += keyVector.y * speed * -up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}

	position = glm::vec3(position.x, clamp(position.y, 0.3, 10.0), position.z);
	
	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2.), (height / 2.));
			firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - (height / 2.)) / height * mouseVector.y;
		float rotY = sensitivity * (float)(mouseX - (width / 2.)) / width * mouseVector.x;

		// Calculates upcoming vertical change in the direction
		glm::vec3 newdirection = glm::rotate(direction, glm::radians(-rotX), glm::normalize(glm::cross(direction, up)));

		// Decides whether or not the next vertical direction is legal or not
		if (abs(glm::angle(newdirection, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			direction = newdirection;
		}

		// Rotates the direction left and right
		direction = glm::rotate(direction, glm::radians(-rotY), up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (width / 2.), (height / 2.));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}

	right = glm::normalize(glm::cross(glm::vec3(0.0, 1.0, 0.0), direction));
}

void Camera::setKeyVector(glm::vec3 vec) {
  keyVector = vec;
}
void Camera::setMouseVector(glm::vec3 vec) {
  mouseVector = vec;        
}
