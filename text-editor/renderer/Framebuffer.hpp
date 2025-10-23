#pragma once

struct SDL_Surface;

namespace Renderer {
    struct Framebuffer {
        int2 size;

        //pixel data, laid out row by row
        color8* data;

        Framebuffer(int2 size);
        ~Framebuffer();
    };

    void clearFramebuffer(Framebuffer* const framebuffer, color8 clearColor);

    void copyFramebufferToSurface(
        const Framebuffer* const framebuffer,
        SDL_Surface* const surface
    );
}