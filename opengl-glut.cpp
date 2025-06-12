// OpenGL teapot example using SDL3 and GLUT
// This code demonstrates how to create a simple OpenGL application using SDL3 and GLUT.
// It initializes an OpenGL context, creates a window, and renders a rotating teapot.
// The teapot is rendered using the GLUT library, which provides a simple way to create 3D shapes.
// The code also includes basic event handling to allow the user to close the window.
// To compile this code, you need to have SDL3 and GLUT installed on your system.

// [ simplified ( no cmake ) ] You can use the following command to compile the code:

// in Windows using MSYS2 MinGW64 , GCC and CLang also
// g++ opengl-glut.cpp -o app $(pkgconf --cflags --libs freeglut sdl3 ) -lopengl32 -lglu32 && ./app

// Linux Debian / Ubuntu , GCC and CLang also
// g++ opengl-glut.cpp -o app $(pkgconf --cflags --libs glut sdl3 ) -lGL -lGLU && ./app

// [ how to , detailed ] To compile this source code file, are needed ( or nice to have ) the following softwares installed:

// OpenGL: A cross-platform graphics API for rendering 2D and 3D graphics.
// GLU: The OpenGL Utility Library, which provides utility functions for OpenGL.

// SDL3: A cross-platform multimedia library that provides low-level access to audio, keyboard, mouse, joystick, and graphics hardware.

// GLUT: The OpenGL Utility Toolkit, which provides a simple API for creating windows and handling user input.
// FreeGLUT: An open-source alternative to the original GLUT library, which is no longer maintained.

// CMake: A cross-platform build system that can generate makefiles for various platforms.
// g++: The GNU C++ compiler, which is used to compile the code.
// pkg-config: A helper tool used when compiling applications and libraries.

// [LinuxOS] APT in Debian / Ubuntu ( and derivatives ) . Maybe Windows too with WSL . Other distros will be similar.
// sudo apt update
// sudo apt install libsdl3-dev # SDL3 development files ( package or git source installation also via CMake automation)
// sudo apt install freeglut3-dev # !important GLUT for OpenGL

// [WindowsOS] Mingw-w64 in MSYS in Windows

// pacman -Ss glut
// pacman -S mingw-w64-x86_64-freeglut

// pacman -Ss sdl3
// pacman -S mingw-w64-x86_64-sdl3

// ----------------------------------------------------------------------------
// This code is a simple OpenGL application that uses SDL3 and GLUT to create a window
// and render a rotating teapot. It initializes an OpenGL context, sets up lighting,
// and handles user input to allow the user to close the window.
// ----------------------------------------------------------------------------

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include <GL/glu.h> // For glu functions

// sudo apt install freeglut3-dev # !important GLUT for OpenGL
#include <GL/glut.h> // For glut functions

#include "obj.h"

// OpenGL rendering context
SDL_GLContext gl_context;

// Camera parameters
float camera_angle = 0.0f;

void initGL()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Set up lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_pos[] = {5.0f, 5.0f, 5.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    GLfloat white_light[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Camera position
    gluLookAt(0, 0, 5,  // eye position
              0, 0, 0,  // look at position
              0, 1, 0); // up vector

    // Save the current matrix
    glPushMatrix();

    // Rotate the entire scene
    glRotatef(camera_angle, 0, 1, 0);

    // draw_box(1.0f); // Draw a cube at the origin
    draw_model(model1); // Draw the loaded model (e.g., a head)

    if (false)
    {
        // Draw the teapot (using GLUT's teapot)
        glPushMatrix();
        glTranslatef(-1.5f, 0.0f, 0.0f);
        glColor3f(0.7f, 0.5f, 0.2f);
        glutSolidTeapot(0.8);
        glPopMatrix();

        // Draw a torus
        glPushMatrix();
        glTranslatef(1.5f, 0.0f, 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glColor3f(0.3f, 0.6f, 0.8f);
        glutSolidTorus(0.2, 0.6, 20, 20);
        glPopMatrix();

        // Draw a sphere above the scene
        glPushMatrix();
        glTranslatef(0.0f, 1.5f, 0.0f);
        glColor3f(0.8f, 0.3f, 0.3f);
        glutSolidSphere(0.4, 20, 20);
        glPopMatrix();

        // Draw a dodecahedron below the scene
        glPushMatrix();
        glTranslatef(0.0f, -1.5f, 0.0f);
        glColor3f(0.5f, 0.8f, 0.2f);
        glutSolidDodecahedron();
        glPopMatrix();
    }

    // Restore the matrix
    glPopMatrix();

    camera_angle += 0.5f;
    if (camera_angle > 360)
        camera_angle -= 360;
}

typedef struct
{
    SDL_Window *window;
    bool fullscreen;
} AppState;
AppState as;

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == false)
    {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Request OpenGL 2.1 context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    window = SDL_CreateWindow("SDL3 OpenGL GLUT Objects", 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    as.window = window;
    as.fullscreen = true;
    SDL_SetWindowFullscreen(as.window, as.fullscreen);

    gl_context = SDL_GL_CreateContext(window);
    if (!gl_context)
    {
        SDL_Log("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize OpenGL
    initGL();
    glutInit(&argc, argv);

    // Set viewport
    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, (double)width / height, 0.1, 100.0);

    init_models(); // Load models if needed, e.g., a cube or other shapes

    // Main loop

    // Main loop flag
    int quit = 0;

    // Event handler
    SDL_Event e;

    // While application is running
    while (!quit)
    {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            // User requests quit
            if (e.type == SDL_EVENT_QUIT)
            {
                quit = 1;
            }

            // User presses a key
            else if (e.type == SDL_EVENT_KEY_DOWN)
            {
                switch (e.key.scancode)
                {
                case SDL_SCANCODE_ESCAPE:
                case SDL_SCANCODE_Q:
                    // Quit the application
                    quit = 1;
                    break;
                case SDL_SCANCODE_F:
                {
                    // Toggle fullscreen.
                    as.fullscreen = !as.fullscreen;
                    SDL_SetWindowFullscreen(as.window, as.fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
                    // Update viewport and projection matrix after changing fullscreen state
                    int w, h;
                    SDL_GetWindowSizeInPixels(as.window, &w, &h); // Use InPixels for accuracy
                    glViewport(0, 0, w, h);
                    glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();                                              // Reset projection matrix
                    gluPerspective(45.0, (double)w / (h > 0 ? h : 1), 0.1, 100.0); // Recalculate perspective
                    glMatrixMode(GL_MODELVIEW);                                    // Switch back to modelview
                    SDL_Log("Toggled fullscreen. New viewport: %dx%d", w, h);
                    break;
                }
                default:
                    break;
                }
            }
            // It's also good practice to handle window resize events
            else if (e.type == SDL_EVENT_WINDOW_RESIZED || e.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED)
            {
                int w, h;
                SDL_GetWindowSizeInPixels(as.window, &w, &h);
                glViewport(0, 0, w, h);
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluPerspective(45.0, (double)w / (h > 0 ? h : 1), 0.1, 100.0);
                glMatrixMode(GL_MODELVIEW);
                SDL_Log("Window resized/pixel size changed. New viewport: %dx%d", w, h);
            }
        } // End SDL_PollEvent loop

        render();
        SDL_GL_SwapWindow(window);
        SDL_Delay(16); // ~60 FPS
    }

    SDL_GL_DestroyContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}