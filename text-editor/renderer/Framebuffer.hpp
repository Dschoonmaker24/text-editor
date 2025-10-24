#pragma once

struct SDL_Surface;

namespace Renderer {
    struct Framebuffer {
        //size of the framebuffer, read-only
        int2 size;

        //pixel data, laid out row by row
        color8* data;

        Framebuffer(int2 size);
        Framebuffer(const Framebuffer& framebuffer) = delete;
        Framebuffer& operator=(const Framebuffer& framebuffer) = delete;
        ~Framebuffer();

        void resize(int2 newSize);
    };

    void clearFramebuffer(Framebuffer* const framebuffer, color8 clearColor);

    void copyFramebufferToSurface(
        const Framebuffer* const framebuffer,
        SDL_Surface* const surface
    );
}