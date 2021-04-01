## About
Missan Engine is a game engine written by me ([LinkedIn: Henrik Syvertsson](https://www.linkedin.com/in/henrik-syvertsson-806983197/)) 
as part of a project at Karlstad University. 
Missan provides an API and environment in which
users can create interactive simulations. 

It is written (as much as possible) from scratch, in C++ with OpenGL/GLFW as a base. 
Currently the project is about 1700 significant lines of code (sloc). 
This project is a work in progress, but some notable features it currently supports are:
- **Scripting Engine** which allows user-defined scripts to be injected at various stages of the game loop. 
- **Physics Engine**, implemented from scratch. Collision avoidance currently only partly implemented. 
- **Graphical User Interface**, via 3rd party library ImGui. 
- Importing textures. 
- Fundamental Built-in Components like Transform, Renderer, Camera, Collider, RigidBody. 

## Video Presentation
[![Missan Engine Presentation](https://img.youtube.com/vi/aGF7JEpwYEE/0.jpg)](https://www.youtube.com/watch?v=aGF7JEpwYEE)

## Scripting
[Link to Missan Scripting API Documentation](https://henkasyvert.github.io/Missan/class_missan_1_1_component.html)
This example shows how to write a simple first person camera script using Missan API:
```c++
// User defined scripts must inherit from Component, which provides event functions that can be overrided. 
// a simple script for moving camera with mouse on y axis, and x axis (constrained to 89.9 degrees)
class FPSCamera : public Component {

public:   
    float rotationSpeedDeg = 30.0f;	  // How fast the camera rotates, or mouse sensitivity. 
    float pitchConstraint = 89.9f; 	  // limits maximum pitch (in degrees), i.e. rotation on the x-axis. Recommended not higher than 89.9
    Transform* transform = nullptr;	  // pointer to transform component attached to this game object. 
    
    // called once when game starts. Initialization of references should happen here. 
    void Start() {        
        // fetching this pointer once here is cheaper than doing it in every frame in Update(). 
        transform = GetGameObject().GetComponent<Transform>();	
    }
  
    // this is called every frame. Bulk of game logic should go here. 
    void Update() {
        // change rotation based on mouse input
        float dyRot = -Input::mouseDelta.x * rotationSpeedDeg * Time::unscaledDeltaTime;
        float dxRot = -Input::mouseDelta.y * rotationSpeedDeg * Time::unscaledDeltaTime;
        
        // apply delta rotations
        transform->rotationDeg.y += dyRot;
        transform->rotationDeg.x = glm::clamp(transform->rotationDeg.x + dxRot, -pitchConstraint, pitchConstraint);      
    }
}
```
## The Report
The report (in Swedish), as part of the project course:
[Link to report](https://drive.google.com/file/d/1UEbyQDgeKQjmjQmAAX_eAy41uurMqaDQ/view?usp=sharing)
