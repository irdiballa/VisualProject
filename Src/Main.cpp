
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Snowflake.h"
#include "Cube.h"
#include "Polynomial.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


using namespace std;

bool is_snowing = true;

bool is_cube_mode = true;

glm::vec3 lastPressed(0.0f, 0.0f, 0.0f);

Cube cube;
Polynomial poly;


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        is_snowing = !is_snowing;

    if (key == GLFW_KEY_C && action == GLFW_PRESS)
        is_cube_mode = !is_cube_mode;

    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        if (is_cube_mode) {
            cube.reset();
        }
        else {
            poly.reset();
        }
    }
     
}

static void mouse_click_callback(GLFWwindow* window, int button, int action, int mods)
{
    

    double x, y;
    glfwGetCursorPos(window, &x, &y);
    if ((button == GLFW_MOUSE_BUTTON_1 || button == GLFW_MOUSE_BUTTON_2) && action == GLFW_PRESS)
        lastPressed = glm::vec3(x, y, 0);


}

static void mouse_move_callback(GLFWwindow* window, double x, double y)
{

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {

        double x, y;
        glfwGetCursorPos(window, &x, &y);

        if (is_cube_mode)
            cube.translate(glm::vec3(x - lastPressed.x, lastPressed.y - y, 0));
        else
            poly.translate(glm::vec3(x - lastPressed.x, lastPressed.y - y, 0));

        lastPressed = glm::vec3(x, y, 0);
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        if (is_cube_mode) {
            cube.rotate(glm::vec3(0.0f, 1.0f, 0.0f), ((float)x - lastPressed.x) * 0.01f);
            cube.rotate(glm::vec3(1.0f, 0.0f, 0.0f),(lastPressed.y - (float)y) * 0.01f);   
        }
        else {
            poly.rotate(glm::vec3(0.0f, 1.0f, 0.0f), ((float)x - lastPressed.x) * 0.01f);
            poly.rotate(glm::vec3(1.0f, 0.0f, 0.0f), (lastPressed.y - (float)y) * 0.01f);
        }

        lastPressed = glm::vec3(x, y, 0);
    }

}

static void scroll_callback(GLFWwindow* window, double x, double y)
{

    if (is_cube_mode)
        cube.scale(y > 0 ? true : false);
    else
        poly.scale(y > 0 ? true : false);
}




int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    srand(time(0));
    int width = 960;
    int height = 540;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Visual Project", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_click_callback);
    glfwSetCursorPosCallback(window, mouse_move_callback);
    glfwSetScrollCallback(window, scroll_callback);


    GLenum err = glewInit();
    if (GLEW_OK != err)
    {/* Problem: glewInit failed, something is seriously wrong. */
        std::cout << "ERROR!" << endl;
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    float positionsSnowflake[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f
    };
    unsigned int indicesSnowflake[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    VertexArray vaSnowflake;
    VertexBuffer vbSnowflake(positionsSnowflake, 4 * 4 * sizeof(float));
    
    VertexBufferLayout layoutSnowflake;
    layoutSnowflake.Push<float>(2);
    layoutSnowflake.Push<float>(2);

    vaSnowflake.addBuffer(vbSnowflake, layoutSnowflake);
    IndexBuffer ibSnowflake(indicesSnowflake, 6);

    Shader shaderSnowflake("resources/shaders/snowflake.shader");
    shaderSnowflake.bind();

    Texture textureSnowflake("resources/textures/snowflake.png");
    textureSnowflake.bind(0);
    shaderSnowflake.setUnifrom1i("u_Texture", 0);

    vaSnowflake.unbind();
    shaderSnowflake.unbind();
    vbSnowflake.unbindBuffer();
    ibSnowflake.unbindBuffer();

    std::vector<Snowflake> snowflakes;
    for (int i = 0; i < 100; i++) {
        snowflakes.push_back(Snowflake(height / 2, width / 2));
    }


    VertexArray vaCube;
    VertexBuffer vbCube(cube.getPositions(), cube.getNumberOfVertices() * sizeof(float));

    VertexBufferLayout layoutCube;
    layoutCube.Push<float>(3);

    vaCube.addBuffer(vbCube, layoutCube);
    IndexBuffer ibCube(cube.getIndices(), cube.getNumberOfIndices());
    

    Shader shaderCube("resources/shaders/cube.shader");
    shaderCube.bind();
    glm::mat4 mvpCube = glm::mat4(1.0f);
    shaderCube.setUnifrom4f("u_Color", 1.0f,0.0f,0.0f,1.0f);
    shaderCube.setUnifromMat4f("u_mvp", mvpCube);

    vaCube.unbind();
    shaderCube.unbind();
    vbCube.unbindBuffer();
    ibCube.unbindBuffer();



    VertexArray vaPoly;
    VertexBuffer vbPoly(poly.getPositions(), poly.getNumberOfVertices() * sizeof(float));

    VertexBufferLayout layoutPoly;
    layoutPoly.Push<float>(3);

    vaPoly.addBuffer(vbPoly, layoutPoly);
    IndexBuffer ibPoly(poly.getIndices(), poly.getNumberOfIndices());


    Shader shaderPoly("resources/shaders/Polynomial.shader");
    shaderPoly.bind();
    glm::mat4 mvpPoly = glm::mat4(1.0f);
    shaderPoly.setUnifrom4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
    shaderPoly.setUnifromMat4f("u_mvp", mvpPoly);

    vaPoly.unbind();
    shaderPoly.unbind();
    vbPoly.unbindBuffer();
    ibPoly.unbindBuffer();





    Renderer renderer;
    glm::mat4 proj = glm::ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, -1000.0f, 1000.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 100.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.clear();
        

        if (is_snowing) {
            shaderSnowflake.bind();
            for (auto& snow : snowflakes) {
                glm::mat4 mvp = proj * snow.getModel();
                shaderSnowflake.setUnifromMat4f("u_mvp", mvp);
                renderer.draw(vaSnowflake, ibSnowflake, shaderSnowflake);
            }
        }

        if (is_cube_mode) {
            shaderCube.bind();
            mvpCube = proj* view * cube.getModelMatrix();
            shaderCube.setUnifrom4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
            shaderCube.setUnifromMat4f("u_mvp", mvpCube);
            renderer.draw(vaCube, ibCube, shaderCube);
        }
        else {
            shaderPoly.bind();
            mvpPoly = proj * poly.getModelMatrix();
            shaderPoly.setUnifrom4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
            shaderPoly.setUnifromMat4f("u_mvp", mvpPoly);
            renderer.draw(vaPoly, ibPoly, shaderPoly);
        }






        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
