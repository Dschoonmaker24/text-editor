#pragma once

struct SDL_Surface;

namespace Renderer {
    struct Framebuffer {
        //size of a square framebuffer tile
        constexpr static int TileSize = 32;
        //tile size squared
        constexpr static int TileSize2 = TileSize * TileSize;

        struct Tile {
            //color data, laid out row by row
            color8 data[TileSize2];
        };

        const int2 size;
        //number of tiles in each direction
        const int2 directionalTileCount;

        //array of tiles, laid out row by row
        Tile* const tiles;

        Framebuffer(int2 size);
        ~Framebuffer();
    };

    void clearFramebuffer(Framebuffer* const framebuffer, color8 clearColor);

    void copyFramebufferToSurface(
        const Framebuffer* const framebuffer,
        SDL_Surface* const surface
    );
}