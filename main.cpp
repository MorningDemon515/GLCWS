#include <glad/glad.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_opengl.h>
#include <iostream>
#include <array>

#define WIDTH 1280
#define HEIGHT 720

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;
SDL_GLContext glc;

bool run = true;

void Draw()
{
    std::array<SDL_Vertex, 3> origin_vertices = {
    SDL_Vertex { { 150, 100 }, { 1.0f, 0.0f, 0.0f, 1.0f } }, // top
    SDL_Vertex { { 000, 300 }, { 0.0f, 1.0f, 0.0f, 1.0f } }, // left bottom
    SDL_Vertex { { 300, 300 }, { 0.0f, 0.0f, 1.0f, 1.0f } } // right bottom
    };

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_RenderGeometry(renderer, nullptr, origin_vertices.data(), origin_vertices.size(), nullptr, 0);
    
    SDL_RenderPresent(renderer);

}

int main(int argc, char* argv[])
{
    SDL_SetLogPriorities(SDL_LOG_PRIORITY_VERBOSE);
    
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return -1;
    }

    window =SDL_CreateWindow(
        "Simple Game", 
        WIDTH, HEIGHT, 
        SDL_WINDOW_RESIZABLE);

    if (!window) {
        SDL_Log("Could not create a window: %s", SDL_GetError());
        return -1;
    }

    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    renderer = SDL_CreateRenderer(window, "opengl");

    if (!renderer) {
        SDL_Log("Create renderer failed: %s", SDL_GetError());
        return -1;
    }

    glc = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window,glc);

    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    while (run)
    {
        SDL_PollEvent(&event);

        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            run = false;
            break;
        
        default:
            break;
        }

        Draw();
    }
    
    SDL_GL_DestroyContext(glc);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}