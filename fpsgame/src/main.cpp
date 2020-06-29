#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#include <vector>
#include <iostream>
#include <cmath>

#include "loader.h"
#include "mesh.h"
#include "shaderprogram.h"
#include "renderer.h"
#include "transform.h"
#include "gameobject.h"
#include "input.h"
#include "camera.h"
#include "window.h"



using namespace missan;

int main(void){

    Window window(960, 720, "Missan 3D");
    Input input(window.GetHandle());

    Loader loader;
    ShaderProgram shader("shaders/vertex.shader", "shaders/fragment.shader");

    Renderer renderer;
    renderer.SetShader(shader);

    Mesh mesh = loader.CreateCubeMesh();

    GameObject go;
    go.SetMesh(mesh);

    Texture texture = loader.LoadTexture("textures/cat.png");
    go.SetTexture(texture);
    go.GetTransform().position.z += -5;

    Camera camera(window.GetAspectRatio());
    renderer.SetCamera(camera);


    GameObject go2;
    go2.SetMesh(mesh);
    go2.SetTexture(texture);
    go2.GetTransform().position += glm::vec3(1, 0, -5);
    
    double deltaTime = 0.0f;
    double time = glfwGetTime();

    while (!glfwWindowShouldClose(window.GetHandle())) {
        deltaTime = glfwGetTime() - time;
        time = glfwGetTime();
        glfwPollEvents();

        camera.HandleInput(input, deltaTime);

        renderer.Prepare();
        renderer.Render(go);
        //renderer.Render(go2);




        glfwSwapBuffers(window.GetHandle());          
    }
    
    
    loader.FreeAssets();
    glfwTerminate();
    return 0;

}




