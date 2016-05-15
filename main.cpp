#include <iostream>
#include <vector>

#include <cmath>
#include <cassert>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SOIL/SOIL.h>

#include "./debug.h"
#include "./shader.h"
#include "./camera.h"

#include <imgui.h>
#include "./imgui_impl_gl2/imgui_impl_glfw_gl2.h"

class TriUVNormMesh 
{
  GLuint VAO;

  void Init(float *data) 
  {
    GLuint VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    // vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
  }
};



GLfloat box_mesh[] = {
  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
   0.5f, -0.5f, -0.5f,  1.0,  0.0f,  0.0f,  0.0f, -1.0f,
   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,

  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
   0.5f, -0.5f,  0.5f,  1.0,  0.0f,  0.0f,  0.0f,  1.0f,
   0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
   0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
  -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,

  -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
  -0.5f,  0.5f, -0.5f,  1.0,  0.0f, -1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
  -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,

   0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
   0.5f,  0.5f, -0.5f,  1.0,  0.0f,  1.0f,  0.0f,  0.0f,
   0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
   0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
   0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
   0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,

  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
   0.5f, -0.5f, -0.5f,  1.0,  0.0f,  0.0f, -1.0f,  0.0f,
   0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
   0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,

  -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
   0.5f,  0.5f, -0.5f,  1.0,  0.0f,  0.0f,  1.0f,  0.0f,
   0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
   0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
  -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
  -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
};

glm::vec3 cameraPos = glm::vec3(0,0,5);
glm::vec3 cameraFront = glm::vec3(0,0,-1);
glm::vec3 cameraUp = glm::vec3(0,1,0);

bool keys[1024];

GLfloat lastX = 400;
GLfloat lastY = 300;
GLfloat yaw = 0;
GLfloat pitch = 0;
bool firstMouse = true;

Camera camera;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }

  if(action == GLFW_PRESS)
    {
      keys[key] = true;
    }
  if(action == GLFW_RELEASE)
    {
      keys[key] = false;
    }

  ImGui_ImplGlfwGL2_KeyCallback(window, key, scancode, action, mode);
}

void do_movement()
{
  GLfloat cameraSpeed = 0.05f;
  if(keys[GLFW_KEY_W])
    {
      camera.ProcessKeyboard(FORWARD, 0.016);
    }
  if(keys[GLFW_KEY_S])
    {
      camera.ProcessKeyboard(BACKWARD, 0.016);
    }
  if(keys[GLFW_KEY_A])
    {
      camera.ProcessKeyboard(LEFT, 0.016);
    }
  if(keys[GLFW_KEY_D])
    {
      camera.ProcessKeyboard(RIGHT, 0.016);
    }
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
  if(firstMouse)
    {
      lastX = xpos;
      lastY = ypos;
      firstMouse = false;
    }

  GLfloat xoffset = xpos - lastX;
  GLfloat yoffset = ypos - lastY;
  lastX = xpos;
  lastY = ypos;

  camera.ProcessMouseMovement(xoffset, yoffset);
}

void build_gui() {
  ImGui::Begin("ImGui window");
  ImGui::Text("Camera:");
  ImGui::Separator();
  ImGui::Text("Position:");
  ImGui::Text("% 2.2f % 2.2f % 2.2f", camera.Position.x, camera.Position.y, camera.Position.z);
  ImGui::Text("Front:");
  ImGui::Text("% 2.2f % 2.2f % 2.2f", camera.Front.x, camera.Front.y, camera.Front.z);
  ImGui::Text("Up:");
  ImGui::Text("% 2.2f % 2.2f % 2.2f", camera.Up.x, camera.Up.y, camera.Up.z);
  ImGui::End();
}

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  int screenWidth = 800;
  int screenHeight = 600;

  GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", nullptr, nullptr);

  if(window == nullptr)
    {
      std::cout << "Failed to create GLFW window\n";
      glfwTerminate();
      return -1;
    }

  glfwMakeContextCurrent(window);

  ImGui_ImplGlfwGL2_Init(window, false);

  glfwSetMouseButtonCallback(window, ImGui_ImplGlfwGL2_MouseButtonCallback);
  glfwSetScrollCallback(window, ImGui_ImplGlfwGL2_ScrollCallback);
  // glfwSetKeyCallback(window, ImGui_ImplGlfwGL2_KeyCallback);
  glfwSetCharCallback(window, ImGui_ImplGlfwGL2_CharCallback);

  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if(glewInit() != GLEW_OK)
    {
      std::cout << "Failed to initialize GLEW\n";
      return -1;
    }

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);

  glViewport(0, 0, width, height);

  GLuint texture;
  {
    int width, height;
    unsigned char *image = SOIL_load_image("./textures/container.jpg", &width, &height, 0, SOIL_LOAD_RGB);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    free(image);
  }

  Shader shader;
  shader.Load("./shaders/first.vs", "./shaders/first.fs");

  GLuint VBO;
  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  // vertex buffer
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(box_mesh), box_mesh, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);
  glBindVertexArray(0);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glEnable(GL_DEPTH_TEST);

  check_gl_error();

  std::vector<glm::vec3> cubePositions =
    {
      glm::vec3(-2,-2, 0),
      glm::vec3(-1,-1, 0),

      glm::vec3( 0, 0, 0),

      glm::vec3( 1, 1, 0),
      glm::vec3( 2, 2, 0),

      glm::vec3( 1,-1, 0),
      glm::vec3( 2,-2, 0),
      glm::vec3(-1, 1, 0),
      glm::vec3(-2, 2, 0),
    };

  // glShadeModel(GL_FLAT);

  camera.Init(glm::vec3(0, 0, -5));

  while(!glfwWindowShouldClose(window))
    {
      glfwPollEvents();
      ImGui_ImplGlfwGL2_NewFrame();
      do_movement();

      glm::mat4 view;
      view = camera.GetViewMatrix();

      // view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
      glm::mat4 projection;
      projection = glm::perspective(45.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);
      glm::mat4 VP = projection * view;

      glClearColor(0.2, 0.3, 0.3, 1.0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      shader.Use();

      glBindTexture(GL_TEXTURE_2D, texture);

      glBindVertexArray(VAO);

      for(auto&& cubePosition : cubePositions)
	{
	  glm::mat4 model;

	  model = glm::translate(model, cubePosition);
	  GLfloat angle = glfwGetTime() * glm::radians(50.0f);

	  model = glm::rotate(model, angle, glm::vec3(1, 1, 0));

	  glm::mat4 MVP = VP * model;

	  GLint pos = glGetUniformLocation(shader.m_program, "MVP");
	  assert(pos != -1);
	  glUniformMatrix4fv(pos, 1, GL_FALSE, glm::value_ptr(MVP));

	  pos = glGetUniformLocation(shader.m_program, "Normal");
	  assert(pos != -1);
	  glUniformMatrix4fv(pos, 1, GL_FALSE, glm::value_ptr(model));

	  pos = glGetUniformLocation(shader.m_program, "lightDirection");
	  assert(pos != -1);
	  glm::vec3 lightDir = glm::vec3(0, 0, 1);
	  glUniform3fv(pos, 1, glm::value_ptr(lightDir));

	  glDrawArrays(GL_TRIANGLES, 0, 36);
	}

      build_gui();

      int display_x, display_y;
      glfwGetFramebufferSize(window, &display_x, &display_y);
      glViewport(0, 0, display_x, display_y);
      ImGui::Render();

      glfwSwapBuffers(window);
      check_gl_error();
    }

  glDeleteBuffers(1, &VBO);
  ImGui_ImplGlfwGL2_Shutdown();
  glfwTerminate();
  return 0;
}
