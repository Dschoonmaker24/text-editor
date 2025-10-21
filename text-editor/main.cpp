#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <freetype/freetype.h>

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO);

	FT_Library ftLibrary;
	FT_Error error = FT_Init_FreeType(&ftLibrary);
	if (error != 0) {
		exit(1);
	}

	FT_Done_FreeType(ftLibrary);

	std::cout << "hello world\n";

	SDL_Quit();

	return 0;
}