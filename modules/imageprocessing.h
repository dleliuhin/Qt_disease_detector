#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <iostream>
#include <vector>
#include <math.h>

#include <QDebug>

#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv2/imgproc.hpp"

#include "container.h"

class ImageProcessing
{
public:
    static void calc_glcm();
};

class Glcm
{
public:
    // Extract a channel from RGB Image
    static cv::Mat get_one_channel(cv::Mat &src,
                                   Container::EnumChannels channel =
                                   Container::CHANNEL_R);

    // Magnitude all pixels of Gray Image, and Magnitude Level can be chosen in 4/8/16;
    static cv::Mat get_gray_magnitude(cv::Mat &src,
                                      Container::GrayLevel level = Container::GRAY_8);

//    static void calc_image_textures(cv::Mat &src,
//                                    Container::GrayLevel level = Container::GRAY_8,
//                                    Container::GrayDirection direct);

    //    // Calculate the GLCM of one Mat Window according to one Statistical Direction.
    //    void CalcuOneGLCM(Mat src, Mat &dst, int src_i, int src_j, int size,
    //                      GrayLevel level = GRAY_8, GrayDirection direct = DIR_0);

    //    // Normalize the Martix, make all pixels of Mat divided by the sum of
    //    // all pixels of Mat, then get Probability Matrix.
    //    void NormalizeMat(Mat src, Mat& dst);

    //    // Calculate Texture Eigenvalues of One Window Mat, which is including
    //    // Contrast, Correlation, Energy, Homogenity.
    //    void CalcuOneTextureEValue(Mat src, TextureEValues& EValue, bool ToCheckMat = false);

    //    // Calculate Texture Eigenvalues of One Window Mat, which is including
    //    // Contrast, Correlation, Energy, Homogenity.
    //    void CalcuTextureEValue(Mat src, TextureEValues& EValue,
    //                            int size = 5, GrayLevel level = GRAY_8);
};

#endif // IMAGEPROCESSING_H
