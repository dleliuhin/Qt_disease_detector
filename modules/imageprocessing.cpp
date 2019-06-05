#include "imageprocessing.h"

using namespace std;
using namespace cv;

//=======================================================================================
Mat Glcm::get_one_channel(Mat &src, Container::EnumChannels channel)
{
    Mat res;

    if (src.channels() == 1)
    {
        src.copyTo(res);
    }
    else
    {
        vector<Mat> bgr;

        split(src, bgr);

        switch (channel) {
        case Container::CHANNEL_B:
            bgr[0].copyTo(res);
            break;

        case Container::CHANNEL_G:
            bgr[1].copyTo(res);
            break;

        case Container::CHANNEL_R:
            bgr[2].copyTo(res);
            break;

        case Container::CHANNEL_RG:
            add(bgr[2], - bgr[1], res);
            break;

        case Container::CHANNEL_RB:
            add(bgr[2], - bgr[0], res);
            break;

        case Container::CHANNEL_GB:
            add(bgr[1], - bgr[0], res);
            break;

        default:
            qDebug() << QString("ERROR in get_one_channel(): No Such Channel.");
        }
    }

    return res;
}
//=======================================================================================
Mat Glcm::get_gray_magnitude(Mat &src, Container::GrayLevel level)
{
    Mat res;
    Mat tmp(src);
    tmp.convertTo(tmp, CV_8U);

    if (src.channels() > 1)
    {
        cvtColor(src, tmp, CV_BGR2GRAY);
    }

    equalizeHist(tmp, res);

    for (int j = 0; j < res.rows; j++)
    {
        uchar *cur = src.ptr<uchar>(j);
        uchar *out = res.ptr<uchar>(j);

        for (int i = 0; i < res.cols; i++)
        {
            switch (level) {
            case Container::GRAY_4:
                out[i] = cv::saturate_cast<uchar>(cur[i] / 64);
                break;

            case Container::GRAY_8:
                out[i] = cv::saturate_cast<uchar>(cur[i] / 32);
                break;

            case Container::GRAY_16:
                out[i] = cv::saturate_cast<uchar>(cur[i] / 16);
                break;

            default:
                qDebug() << QString("ERROR in get_gray_magnitude(): No Such Channel.");
                break;
            }
        }
    }

    return res;
}
//=======================================================================================
//void
//=======================================================================================
