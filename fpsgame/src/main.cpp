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
#include "model.h"



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


    Mesh planeMesh = loader.CreatePlaneMesh(10, 2);
    Mesh cubeMesh = loader.CreateCubeMesh();

    Texture catTex = loader.LoadTexture("cat.png");
    Texture brickTex = loader.LoadTexture("brickwall.png");
    Texture stoneTex = loader.LoadTexture("stonefloor.png");

    Model brickWall(planeMesh, brickTex);
    Model stoneFloor(planeMesh, stoneTex);

    std::vector<GameObject> gameObjects;

    GameObject
        wall1(brickWall, { 0,0,5 }),
        wall2(brickWall, { 5,0,0 }, { 0,90,0 }),
        wall3(brickWall, { -5,0,0 }, { 0,90,0 }),
        floor(stoneFloor, { 0,-1,0 }, { 90,0,0 });
    floor.GetTransform().scale.y = 5;

    gameObjects.push_back(wall1);
    gameObjects.push_back(wall2);
    gameObjects.push_back(wall3);
    gameObjects.push_back(floor);

    while (!glfwWindowShouldClose(window.GetHandle())) {
        input.Update();
        glfwPollEvents();

        camera.HandleInput(input);

        renderer.Prepare();
        renderer.Render(gameObjects);


        glfwSwapBuffers(window.GetHandle());          
    }
    
    
    loader.FreeAssets();
    glfwTerminate();
    return 0;

}




