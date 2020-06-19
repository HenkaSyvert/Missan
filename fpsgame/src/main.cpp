#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#include <iostream>
#include <vector>
#include <fstream>


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




class Mesh {
public:
    const GLuint vaoID, vertexCount;

    Mesh(GLuint id, GLuint count) : vaoID(id), vertexCount(count){}
};

class Loader {
public:

    Mesh LoadMesh(std::vector<float>& vertices, std::vector<unsigned int>& indices) {
        GLuint vaoID = CreateVAO();
        GLuint iboID = CreateIndexBuffer(indices);
        GLuint vboID = CreateVertexBuffer(vertices);
        return Mesh(vaoID, indices.size());
    }

    void FreeAssets() {
        glDeleteVertexArrays(vaos.size(), vaos.data());
        glDeleteBuffers(vbos.size(), vbos.data());
    }

    static std::string LoadShaderSrc(const std::string& filePath) {

        std::fstream input(filePath);
        if (!input.is_open()) {
            std::cout << "error: could not open \"" << filePath << "\"\n";
            exit(EXIT_FAILURE);
        }

        std::string str;
        while (input.peek() != EOF)
            str += input.get();

        return str;

    }

private:
    std::vector<GLuint> vaos, vbos; // for memory management

    // functions
    GLuint CreateVAO() {
        GLuint vaoID;
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);
        vaos.push_back(vaoID);
        return vaoID;
    }

    GLuint CreateVertexBuffer(std::vector<float>& vertices) {
        GLuint vboID;
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        vbos.push_back(vboID);
        return vboID;
    }

    GLuint CreateIndexBuffer(std::vector<unsigned int>& indices) {
        GLuint iboID;
        glGenBuffers(1, &iboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
        vbos.push_back(iboID);
        return iboID;
    }

   

};

class Transform {
public:
    glm::vec3 position = glm::vec3(0,0,0), 
        rotation = glm::vec3(0,0,0), 
        scale = glm::vec3(1,1,1);

    glm::mat4 GetMatrix() {
        glm::mat4 matrix = glm::mat4(1.0f);
        matrix = glm::translate(matrix, position);
        matrix = glm::rotate(matrix, rotation.x, glm::vec3(1, 0, 0));
        matrix = glm::rotate(matrix, rotation.y, glm::vec3(0, 1, 0));
        matrix = glm::rotate(matrix, rotation.z, glm::vec3(0, 0, 1));
        matrix = glm::scale(matrix, scale);
        return matrix;
    }

};

class Entity {
public:
    Transform transform;

    Mesh& mesh;

    Entity(Mesh& m) : mesh(m) {}
};

class ShaderProgram {
    // TODO:
    // proper cleanup on delete
    // 
    // ShaderProgram handles communication with GPU via uniform variables

private:
    unsigned int programID, vertexShader, fragmentShader;
    unsigned int u_projLocation, u_modelLocation, u_viewLocation;

    // COMPILATION
    void PrintGLErrorMsg(unsigned int id) {

        int maxLength;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<char> infoLog(maxLength);
        glGetShaderInfoLog(id, maxLength, &maxLength, &infoLog[0]);

        std::cout << std::string(infoLog.data()) << std::endl;
    }

    unsigned int CompileShader(unsigned int shaderType, const std::string& shaderSource) {

        unsigned int shader = glCreateShader(shaderType);
        const char* source = shaderSource.c_str();
        glShaderSource(shader, 1, &source, nullptr);

        glCompileShader(shader);
        int isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, (int*)&isCompiled);
        if (isCompiled == GL_FALSE) {

            PrintGLErrorMsg(shader);
            glDeleteShader(shader);
            exit(EXIT_FAILURE);
        }

        return shader;
    }

    void BindAttributes() {
        glBindAttribLocation(programID, 0, "position");
        glBindAttribLocation(programID, 1, "textureCoords");
    }

    void GetUniformLocations() {
        u_projLocation = glGetUniformLocation(programID, "u_proj");
        u_modelLocation = glGetUniformLocation(programID, "u_model");
        u_viewLocation = glGetUniformLocation(programID, "u_view");
    }

public:
    ShaderProgram(std::string vertexFile, std::string fragmentFile) {

        std::string vssrc = Loader::LoadShaderSrc(vertexFile);
        std::string fssrc = Loader::LoadShaderSrc(fragmentFile);

        vertexShader = CompileShader(GL_VERTEX_SHADER, vssrc);
        fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fssrc);

        programID = glCreateProgram();
        glAttachShader(programID, vertexShader);
        glAttachShader(programID, fragmentShader);

        // bind variables
        //BindAttributes();


        glLinkProgram(programID);
        int isLinked = 0;
        glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE) {

            PrintGLErrorMsg(programID);
            glDeleteProgram(programID);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            return;
        }
        glDetachShader(programID, vertexShader);
        glDetachShader(programID, fragmentShader);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

    }

    ~ShaderProgram() {
        glDeleteProgram(programID);
        glDetachShader(programID, vertexShader);
        glDetachShader(programID, fragmentShader);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void Use() {
        glUseProgram(programID);
    }

    void Stop() {
        glUseProgram(0);
    }

    

    /*
    // UNIFORM VARIABLES MANIPULATION
    void LoadProjMat(glm::mat4& m) {
        glUniformMatrix4fv(u_projLocation, 1, GL_FALSE, &m[0][0]);
    }
    
    void LoadViewMat(glm::mat4& m) {
        glUniformMatrix4fv(u_viewLocation, 1, GL_FALSE, &m[0][0]);
    }
   
    void LoadModelMat(glm::mat4& m) {
        glUniformMatrix4fv(u_modelLocation, 1, GL_FALSE, &m[0][0]);
    }
    */
};

class Renderer {

public:
    glm::mat4 proj = glm::ortho(-1.0, 1.0, -1.0, 1.0, 0.0, 0.0);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));


    void Prepare() {    
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1, 0, 0, 1);
    }

    void Render(Mesh& mesh, ShaderProgram shader) {
        //Mesh* mesh = &entity.mesh;

        glBindVertexArray(mesh.vaoID);
        glEnableVertexAttribArray(0);

        
        

        //shader.LoadModelMat(model);


        glDrawElements(GL_TRIANGLES, mesh.vertexCount, GL_UNSIGNED_INT, 0);
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
    }

};



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

    }

    

    // DATA
    std::vector<float> vertices = {
        -.5, -.5, 0.0,
        .5, -.5, 0.0,
        .5, .5, 0.0,
        -.5, .5 ,0.0
    };

    std::vector<unsigned int> indices = {
        3,1,0,
        3,1,2
    };


    // other stuff
    Loader loader;
    Renderer renderer;
    ShaderProgram shader("shaders/vertex.shader", "shaders/fragment.shader");

    Mesh mesh = loader.LoadMesh(vertices, indices);
    //Entity entity(mesh);


    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();


        shader.Use();
        renderer.Prepare();
        renderer.Render(mesh, shader);
        shader.Stop();

        glfwSwapBuffers(window);          
    }
    
    
    loader.FreeAssets();
    glfwTerminate();
    return 0;

}