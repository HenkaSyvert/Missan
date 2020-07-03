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
#include "gui.h"
#include "scene.h"



using namespace missan;

int main(void){

    // SETUP
    Window window(960, 720, "Missan 3D");
    Input input(window);
    Loader loader;
    ShaderProgram shader("vertex.shader", "fragment.shader");
    Camera camera(window);
    Renderer renderer(shader, camera);
    GUI gui(window, camera);
    Scene scene;


    // LOAD ASSETS
    Mesh planeMesh = loader.CreatePlaneMesh(10, 2);
    Mesh cubeMesh = loader.CreateCubeMesh();

    Texture catTex = loader.LoadTexture("cat.png");
    Texture brickTex = loader.LoadTexture("brickwall.png");
    Texture stoneTex = loader.LoadTexture("stonefloor.png");

    Model brickWall(planeMesh, brickTex);
    Model stoneFloor(planeMesh, stoneTex);

    
    // CREATE GAME OBJECTS
    GameObject
        wall1(brickWall, { 0,0,5 }),
        wall2(brickWall, { 5,0,0 }, { 0,90,0 }),
        wall3(brickWall, { -5,0,0 }, { 0,90,0 }),
        floor(stoneFloor, { 0,-1,0 }, { 90,0,0 });
    floor.GetTransform().scale.y = 5;
    
    scene.Instantiate(wall1);
    scene.Instantiate(wall2);
    scene.Instantiate(wall3);
    scene.Instantiate(floor);


    


    while (!glfwWindowShouldClose(window.GetHandle())) {
        input.Update();
        
        
        camera.HandleInput(input);

        renderer.Prepare();
        renderer.Render(scene);
        
        gui.Run();  // do after renderer, or will get overdrawn

        glfwSwapBuffers(window.GetHandle());          
    }
    
    gui.Exit();
    
    loader.FreeAssets();
    glfwTerminate();
    return 0;

}




