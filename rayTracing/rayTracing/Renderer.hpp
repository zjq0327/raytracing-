#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include"Scene.hpp"


class Renderer
{
public:
	void Render(const Scene& scene);

private:


    void printImage(const Scene& scene, const vector<Vector3f>& framebuffer)
    {
        FILE* fp = fopen("binary.ppm", "wb");
        (void)fprintf(fp, "P6\n%d %d\n255\n", scene.width, scene.height);
        for (auto i = 0; i < scene.height * scene.width; ++i) {
            static unsigned char color[3];
            color[0] = (char)(255 * clamp(0, 1, framebuffer[i].x));
            color[1] = (char)(255 * clamp(0, 1, framebuffer[i].y));
            color[2] = (char)(255 * clamp(0, 1, framebuffer[i].z));
            fwrite(color, 1, 3, fp);
        }
        fclose(fp);
    }
};