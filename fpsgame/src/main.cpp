#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#include <vector>
#include <iostream>

#include "loader.h"
#include "mesh.h"
#include "shaderprogram.h"
#include "renderer.h"
#include "transform.h"
#include "gameobject.h"

// Error funcs
void glfwErrorCallback(int error, const char* desc) {
    std::cout << "GLFW Error " << error << ": " << desc << std::endl;
}

void APIENTRY glErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data){
    // credit to liam-middlebrook @github, with minor modifications
    // https://gist.github.com/liam-middlebrook/c52b069e4be2d87a6d2f

    std::string _source;
    std::string _type;
    std::string _severity;

    switch (source) {
    case GL_DEBUG_SOURCE_API:
        _source = "API";
        break;

    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        _source = "WINDOW SYSTEM";
        break;

    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        _source = "SHADER COMPILER";
        break;

    case GL_DEBUG_SOURCE_THIRD_PARTY:
        _source = "THIRD PARTY";
        break;

    case GL_DEBUG_SOURCE_APPLICATION:
        _source = "APPLICATION";
        break;

    case GL_DEBUG_SOURCE_OTHER:
        _source = "UNKNOWN";
        break;

    default:
        _source = "UNKNOWN";
        break;
    }

    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        _type = "ERROR";
        break;

    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        _type = "DEPRECATED BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        _type = "UDEFINED BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_PORTABILITY:
        _type = "PORTABILITY";
        break;

    case GL_DEBUG_TYPE_PERFORMANCE:
        _type = "PERFORMANCE";
        break;

    case GL_DEBUG_TYPE_OTHER:
        _type = "OTHER";
        break;

    case GL_DEBUG_TYPE_MARKER:
        _type = "MARKER";
        break;

    default:
        _type = "UNKNOWN";
        break;
    }

    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        _severity = "HIGH";
        break;

    case GL_DEBUG_SEVERITY_MEDIUM:
        _severity = "MEDIUM";
        break;

    case GL_DEBUG_SEVERITY_LOW:
        _severity = "LOW";
        break;

    case GL_DEBUG_SEVERITY_NOTIFICATION:
        _severity = "NOTIFICATION";
        break;

    default:
        _severity = "UNKNOWN";
        break;
    }

    printf("%d: %s of %s severity, raised from %s: %s\n",
        id, _type.c_str(), _severity.c_str(), _source.c_str(), msg);
}


//Transform* cam;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        //cam->position.x += 0.1;
    }
}



using namespace missan;

int main(void){
    
    GLFWwindow* window;

    // INITIALIZATION
    {
        glfwSetErrorCallback(glfwErrorCallback);

        if (!glfwInit())
            exit(EXIT_FAILURE);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(640, 480, "fpsgame", NULL, NULL);
        if (!window) {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window);

        glfwSwapInterval(1);

        int glewState = glewInit();
        if (glewState != GLEW_OK) {
            std::cout << "GLEW Error: " << glewGetErrorString(glewState) << std::endl;
            exit(EXIT_FAILURE);
        }

        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glErrorCallback, NULL);

        std::cout << glGetString(GL_VERSION) << std::endl;

        glfwSetKeyCallback(window, keyCallback);

    }

    

    // DATA
    std::vector<float> vertices = {
        -.25, -.5, 0.0,
        .5, -.5, 0.0,
        .5, .5, 0.0,
        -.5, .25 ,0.0
    };

    std::vector<unsigned int> indices = {
        3,1,0,
        3,1,2
    };


    // other stuff
    Loader loader;
    ShaderProgram shader("shaders/vertex.shader", "shaders/fragment.shader");

    Renderer renderer;
    renderer.SetShader(shader);

    Mesh mesh = loader.CreateCubeMesh();

    GameObject go;
    go.SetMesh(mesh);

    Texture texture = loader.LoadTexture("textures/cat.png");
    go.SetTexture(texture);

    Transform camera;
    renderer.SetCamera(camera);
    renderer.SetProjection(glm::ortho(-1, 1, -1, 1, -1, 1));

    GameObject go2;
    go2.SetMesh(mesh);
    go2.SetTexture(texture);
    go2.GetTransform().position += glm::vec3(1, 0, 0);

    // testing input
    //cam = &camera;

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();




        renderer.Prepare();
        renderer.Render(go);
        renderer.Render(go2);

        go.GetTransform().rotation += glm::vec3(0.01, 0.01, 0.01);
        go2.GetTransform().rotation += glm::vec3(-0.01, -0.01, 0.01);
        //go2.GetTransform().position.x += -0.1;

        glfwSwapBuffers(window);          
    }
    
    
    loader.FreeAssets();
    glfwTerminate();
    return 0;

}




