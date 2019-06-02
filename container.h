#ifndef CONTAINER_H
#define CONTAINER_H


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
};

#endif // CONTAINER_H
