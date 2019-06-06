#ifndef GLCMBUILDER_H
#define GLCMBUILDER_H

#include "container.h"

class GlcmBuilder
{
public:
    // Extract a channel from RGB Image
    static cv::Mat get_one_channel(cv::Mat &src, EnumChannels channel = CHANNEL_R);

    // Magnitude all pixels of Gray Image, and Magnitude Level can be chosen in 4/8/16;
    static cv::Mat get_gray_magnitude(cv::Mat &src, GrayLevel level = GRAY_8);

    static void calc_image_textures(cv::Mat &src,
                                    GrayLevel level = GRAY_8,
                                    bool to_adjust = false);

    static void calc_texture_evalue(cv::Mat &src, TextureValues &evalue,
                                    GrayLevel level = GRAY_8);

private:

    static void calc_glcm(cv::Mat &src, cv::Mat &dst, const int &src_i, const int &src_j,
                   GrayLevel level = GRAY_8, GrayDirection direct = DIR_0);

    static void normalize_mat(cv::Mat &src, cv::Mat &dst);

    static void calc_evalue(cv::Mat &src, TextureValues &evalue, bool to_check);

    //    // Calculate Texture Eigenvalues of One Window Mat, which is including
    //    // Contrast, Correlation, Energy, Homogenity.
    //    void CalcuTextureEValue(Mat src, TextureEValues& EValue,
    //                            int size = 5, GrayLevel level = GRAY_8);
};

#endif // GLCMBUILDER_H
