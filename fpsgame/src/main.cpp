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
    ShaderProgram shader("vertex.shader", "fragment.shader");
    Camera camera(window.GetAspectRatio());
    Renderer renderer;
    renderer.SetShader(shader);  
    renderer.SetCamera(camera);
    camera.GetTransform().position.z += 5;


    Mesh mesh = loader.CreateCubeMesh();
    Texture texture = loader.LoadTexture("cat.png");
    Texture brickTex = loader.LoadTexture("brickwall.png");

    
    GameObject wall(mesh, brickTex);
    //wall.GetTransform().rotationDeg.z = 45;
    //wall.GetTransform().rotationDeg.y = 45;

    

    while (!glfwWindowShouldClose(window.GetHandle())) {
        input.Update();
        glfwPollEvents();

        camera.HandleInput(input);

        renderer.Prepare();
        renderer.Render(wall);

        float mag = 1;
        float a = sinf(input.GetTime()) * mag;
        float b = a;

        glm::vec3 v = wall.GetTransform().GetUpVector();

        //wall.GetTransform().position = v * a;



        glfwSwapBuffers(window.GetHandle());          
    }
    
    
    loader.FreeAssets();
    glfwTerminate();
    return 0;

}




