## About
Missan Engine is a game engine written by
([LinkedIn: Henrik Syvertsson](https://www.linkedin.com/in/henrik-syvertsson-806983197/)) 
as part of a project at Karlstad University. 
Missan provides a scripting API with which users can create interactive simulations. 

It is written in C++ with OpenGL (via GLEW) as renderer and GLFW as platform. 
It also uses glm as for maths, 
ImGui for GUI, 
doxygen for documentation, 
and stb for file handling. 

The scripting API is inspired by Unity3D's API, 
so it should look very familiar to those who know it. 
Some features that Missan supports are:
- **Scripting Engine** which allows user-defined scripts to be injected at various stages of the game loop,
e.g. every **Update** or **OnCollisionEnter**. 
- Fundamental Built-in **Components** like Transform, Renderer, Camera, Collider, RigidBody. 
- **Physics Engine** which handles applying forces, and detecting and resolving collisions. 
- **Graphical User Interface** via ImGui
- Importing **Assets**, like textures. 


## Video Presentation
[![Missan Engine Presentation](https://img.youtube.com/vi/S2b47aMwBjc/0.jpg)](https://www.youtube.com/watch?v=S2b47aMwBjc)

## Scripting
[Link to Missan Scripting API Documentation](https://henkasyvert.github.io/Missan/class_missan_1_1_component.html)
This example shows how to write a simple first person camera script using Missan API:
```c++
// Simple script for rotating camera with mouse
// User defined scripts must inherit from Component, which provides event functions that can be overrided,
// in this case Start() and Update(). 
class FPSCamera : public Component {

public:   
    float rotationSpeedDeg = 30.0f;	  // How fast the camera rotates, or mouse sensitivity. 
    float pitchConstraint = 89.9f; 	  // limits maximum pitch (in degrees), i.e. rotation on the x-axis. 
    Transform* transform = nullptr;	  // pointer to transform component attached to this game object. 
    
    // Start is called once when game starts. Initialization should happen here. 
    void Start() {        
        // fetching this pointer once here is cheaper than doing it in every frame in Update(). 
        transform = GetGameObject().GetComponent<Transform>(); 
    }
  
    // Update is called every frame. Bulk of game logic should happen here. 
    void Update() {
        // calculate delta rotation by mouse input. Use delta time for smooth, frame-rate independent movement. 
        float dyRot = -Input::mouseDelta.x * rotationSpeedDeg * Time::unscaledDeltaTime;
        float dxRot = -Input::mouseDelta.y * rotationSpeedDeg * Time::unscaledDeltaTime;
        
        // apply delta rotations and clamp x-axis
        transform->rotationDeg.y += dyRot;
        transform->rotationDeg.x = glm::clamp(transform->rotationDeg.x + dxRot, -pitchConstraint, pitchConstraint);      
    }
}

...

// How to instantiate a GameObject with the script:
GameObject player;
player.AddComponent<FPSCamera>();
GameObject::Instantiate(&player);


```
## The Report
The report (in Swedish), as part of the project course:
[Link to report](https://drive.google.com/file/d/1UEbyQDgeKQjmjQmAAX_eAy41uurMqaDQ/view?usp=sharing)
