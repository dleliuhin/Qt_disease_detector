#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include <vector>
#include <math.h>

#include <QDebug>

#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv2/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>

//=======================================================================================

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

//===================================================================================

struct Dataset
{
    std::vector<cv::Mat> h;

    std::vector<cv::Mat> nh1;
    std::vector<cv::Mat> nh2;
    std::vector<cv::Mat> nh3;
    std::vector<cv::Mat> nh4;
    std::vector<cv::Mat> nh5;
    std::vector<cv::Mat> nh6;
    std::vector<cv::Mat> nh7;
    std::vector<cv::Mat> nh8;
    std::vector<cv::Mat> nh9;
    std::vector<cv::Mat> nh10;
};

//=======================================================================================

// Gray Level (Choose in 4/8/16)
enum GrayLevel
{
    GRAY_4,
    GRAY_8,
    GRAY_16
};

// Gray Value Statistical Direction
// (Choose in 0°, 45°, 90°, 135°)
enum GrayDirection
{
    DIR_0,
    DIR_45,
    DIR_90,
    DIR_135
};

// Point out R, G, B Channel of a Image
enum EnumChannels
{
    // inter channels
    CHANNEL_R,
    CHANNEL_G,
    CHANNEL_B,

    // intra channels
    CHANNEL_RG,
    CHANNEL_RB,
    CHANNEL_GB
};

struct TextureValues
{
    float contrast;
    float correlation;
    float energy;
    float homogeneity;
};

//=======================================================================================

#endif // CONTAINER_H
