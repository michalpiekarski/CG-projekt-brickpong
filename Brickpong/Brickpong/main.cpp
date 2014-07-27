    // Include Sysytem Headers
#include <iostream>

    //Check if on Windows - both x86 and x64
#ifdef _WIN32
    // Include GLEW
#include "GL/glew.h"
#endif

    // Include GLFW
    // Check if on OSX
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include "GLFW/glfw3.h"

GLFWwindow* window;

    // Include GLM
#include "glm/gtc/matrix_transform.hpp"

    // Include Custom Headers
#include "shader.hpp"

void CreateVBO(GLfloat g_vertex_buffer_data[], int g_vertex_buffer_data_length, GLfloat g_color_buffer_data[], int g_color_buffer_data_length, GLuint vertexbuffers[], GLuint colorbuffers[], int i) {
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer_data_length*sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, g_color_buffer_data_length*sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    vertexbuffers[i] = vertexbuffer;
    colorbuffers[i] = colorbuffer;
}

void Draw(GLuint vertexbuffer, GLuint colorbuffer) {
        // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
                          0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );

        // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
                          1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                          3,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized?
                          0,                                // stride
                          (void*)0                          // array buffer offset
                          );

        // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

float CursorX = 0.0f;
float CurserOffset = 150.0f;
float CursorDamping = 10.0f;
void cursorPositionChanged(GLFWwindow *window, double x, double y)
{
    int windowWidth;
    glfwGetWindowSize(window, &windowWidth, NULL);
    CursorX = glm::clamp(float(-(x - windowWidth / 2.0f)), -CurserOffset, CurserOffset)/CursorDamping;
    printf("Cursor x position: %f\n", CursorX);
}

glm::vec3 BallPosition = glm::vec3(1.0f, -6.0f, 0);
glm::vec3 BallVelocity = glm::vec3(0.05f, 0.1f, 0);

glm::vec3 PauseBallVelocity = glm::vec3(0, 0, 0);
bool bricks[100];

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_RELEASE && key == GLFW_KEY_SPACE)
    {
        glm::vec3 tmp = BallVelocity;
        tmp = BallVelocity;
        BallVelocity = PauseBallVelocity;
        PauseBallVelocity = tmp;
    }
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        if (key == GLFW_KEY_A || key == GLFW_KEY_LEFT)
        {
            CursorX += 1.0f;
        }
        else if (key == GLFW_KEY_D || key == GLFW_KEY_RIGHT)
        {
            CursorX -= 1.0f;
        }
        if (key == GLFW_KEY_R)
        {
            BallPosition = glm::vec3(1.0f, -6.0f, 0);
            BallVelocity = glm::vec3(0.05f, 0.1f, 0);
            for (int i = 0; i < 100; i++)
            {
                bricks[i] = false;
            }
        }
    }
}

void CheckBallBoundsCol()
{
        // Horizontal
    if (BallPosition.x <= -14.0f || BallPosition.x >= 14.0f)
    {
        BallVelocity.x = -BallVelocity.x;
        printf("Wall collision at: %f x %f\n", BallPosition.x, BallPosition.y);
    }
        // Top
    else if (BallPosition.y >= 8.0f)
    {
        BallVelocity.y = -BallVelocity.y;
        printf("Wall collision at: %f x %f\n", BallPosition.x, BallPosition.y);
    }
        // Bottom
    else if (BallPosition.y <= -8.0f)
    {
        printf("Wall collision at: %f x %f\n", BallPosition.x, BallPosition.y);
        printf("GAME OVER - ball fell down");
        BallPosition = glm::vec3(1.0f, -6.0f, 0);
        BallVelocity = glm::vec3(0.05f, 0.1f, 0);
        for (int i = 0; i < 100; i++)
        {
            bricks[i] = false;
        }
    }
}

void CheckBallPadCol()
{
    if (BallPosition.y <= -6.2f && (BallPosition.x >= CursorX-2.0f && BallPosition.x <= CursorX+2.0f))
    {
        if (BallPosition.x > CursorX - 0.5f && BallPosition.x < CursorX + 0.5f)
        {
            BallVelocity.x = BallVelocity.x / 1.5f;
            BallVelocity.y = glm::clamp(BallVelocity.y * 1.25f, -0.5f, 0.5f);
        }
        else
        {
            BallVelocity.x = glm::clamp(BallVelocity.x * 1.25f, -0.5f, 0.5f);
        }
        if ((BallVelocity.x < 0 && BallPosition.x > CursorX+1.0f) || (BallVelocity.x > 0 && BallPosition.x < CursorX-1.0f))
        {
            BallVelocity.x = -BallVelocity.x;
        }
        BallVelocity.y = -BallVelocity.y;
        printf("Pad collision at: %f x %f\n", BallPosition.x, BallPosition.y);
    }
}

bool CheckBallBrickCol(float brickX, float brickY)
{
    // top
    if (BallPosition.y - 0.25f > brickY + 0.25f)
    {
        return false;
    }
    // left
    if (BallPosition.x - 0.25f > brickX + 0.5f)
    {
        return false;
    }
    // bottom
    if (BallPosition.y + 0.25f < brickY - 0.25f)
    {
        return false;
    }
    // right
    if (BallPosition.x + 0.25f < brickX - 0.5f)
    {
        return false;
    }
    return true;
}

int main( void ) {
        // Initialise GLFW
	if( !glfwInit() ) {
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//        // Print supported OpenGL version
//    printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
        // Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 576, "Tutorial 04 - Colored Cube", NULL, NULL);
	if(!window){
		fprintf( stderr, "Failed to open GLFW window!\nIf you have an Intel GPU and on Windows, they are not OpenGL 3.3 compatible.\n" );
        glfwTerminate();
        exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

        //Check if on Windows - botx x86 and x64
#ifdef _WIN32
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
#endif

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetCursorPosCallback(window, cursorPositionChanged);
    glfwSetKeyCallback(window, KeyCallback);

        // Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

        // Enable depth test
	glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

        // Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );

        // Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

        // Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);

        // View (Camera) matrix :
	glm::mat4 View       = glm::lookAt(
                                       glm::vec3(0,0,-20), // Camera is at (0,0,-20), in World Space
                                       glm::vec3(0,0,0), // and looks at the origin
                                       glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                                       );

        // Projection matrix :
    glm::mat4 Projection = glm::perspective(
                                            45.0f, // 45° Field of View
                                            16.0f / 9.0f, // 16:9 ratio
                                            0.1f, 100.0f // display range : 0.1 unit <-> 100 units
                                            );

//        // Our ModelViewProjection : multiplication of our 3 matrices
//	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around
//
        // Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
        // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	static GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
	};

        // One color for each vertex. They were generated randomly.
	static GLfloat g_color_buffer_data[] = {
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f
	};

    GLuint vertexbuffers[1] = {};
    GLuint colorbuffers[1] = {};
    CreateVBO(g_vertex_buffer_data, 108, g_color_buffer_data, 108, vertexbuffers, colorbuffers, 0);

    glm::mat4 tmpModel, tmpMVP;
    for (int i = 0; i < 100; i++)
    {
        bricks[i] = false;
    }
	do{
            // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Use our shader
		glUseProgram(programID);

            // Bricks
        int brick_i = 0;
        for (float i = -12.0f; i <= 12.2f; i += 2.2f) {
            for (float j = 0.0f; j <= 8.0f; j += 1.1f)
            {
                if (!bricks[brick_i])
                {
                    if (!CheckBallBrickCol(i, j))
                    {
                        // Send our transformation to the currently bound shader,
                        // in the "MVP" uniform
                        tmpModel = glm::scale(glm::translate(Model, glm::vec3(i, j, 0)), glm::vec3(1.0f, 0.5f, 0.5f));
                        tmpMVP = Projection * View * tmpModel;
                        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &tmpMVP[0][0]);

                        Draw(vertexbuffers[0], colorbuffers[0]);
                    }
                    else
                    {
                        printf("Brick nr. %d collision", brick_i);
                        bricks[brick_i] = true;
                        BallVelocity.y = -BallVelocity.y;
                    }
                }
                ++brick_i;
            }
        }

            // Pad
            // Send our transformation to the currently bound shader,
            // in the "MVP" uniform
        tmpModel = glm::scale(glm::translate(Model, glm::vec3(CursorX,-7.0f,0)), glm::vec3(2.0f,0.25f,2.0f));
        tmpMVP = Projection * View * tmpModel;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &tmpMVP[0][0]);

        Draw(vertexbuffers[0], colorbuffers[0]);

            // Ball
            // Send our transformation to the currently bound shader,
            // in the "MVP" uniform
        tmpModel = glm::scale(glm::translate(Model, BallPosition), glm::vec3(0.25f,0.25f,0.25f));
        BallPosition += BallVelocity;
        CheckBallBoundsCol();
        CheckBallPadCol();
        tmpMVP = Projection * View * tmpModel;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &tmpMVP[0][0]);

        Draw(vertexbuffers[0], colorbuffers[0]);

            // Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
        // Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffers[0]);
	glDeleteBuffers(1, &colorbuffers[0]);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);
    
        // Close OpenGL window and terminate GLFW
	glfwTerminate();
    
	return 0;
}

