#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include <vector>

class Container
{
public:
    Container();

public:
    struct Textures
    {
        std::vector<float> Contrast;
        std::vector<float> Correlation;
        std::vector<float> Energy;
        std::vector<float> Homogeneity;
    };

    struct Channels
    {
        std::vector<Textures> R;
        std::vector<Textures> G;
        std::vector<Textures> B;
        std::vector<Textures> RG;
        std::vector<Textures> RB;
        std::vector<Textures> GB;
    };

    struct Groups
    {
        std::vector<Channels> h;

        std::vector<Channels> nh1;
        std::vector<Channels> nh2;
        std::vector<Channels> nh3;
        std::vector<Channels> nh4;
        std::vector<Channels> nh5;
        std::vector<Channels> nh6;
        std::vector<Channels> nh7;
        std::vector<Channels> nh8;
        std::vector<Channels> nh9;
        std::vector<Channels> nh10;
    };
};

#endif // CONTAINER_H
