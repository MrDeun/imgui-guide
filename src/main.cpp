#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <print>
#include <imgui.h>
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

int main(int argc, char **argv) {
  std::println("Welcome to imgui guide");
  bool ok = SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer("hello world", 1024, 768, SDL_WINDOW_BORDERLESS,
                              &window, &renderer);
  if (!window) {
    std::println("Failure of window creation - {}", SDL_GetError());
    return -1;
  }
  bool game_alive = true;

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;

  while (game_alive) {
    SDL_Event event{};
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        game_alive = false;
      }
    }
    const double now = ((double)SDL_GetTicks()) /
                       1000.0; /* convert from milliseconds to seconds. */
    /* choose the color for the frame we will draw. The sine wave trick makes it
     * fade between colors smoothly. */
    const float red = (float)(0.5 + 0.5 * SDL_sin(now));
    const float green = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const float blue = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
    SDL_SetRenderDrawColorFloat(
        renderer, red, green, blue,
        SDL_ALPHA_OPAQUE_FLOAT); /* new color, full alpha. */
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  return 0;
}
