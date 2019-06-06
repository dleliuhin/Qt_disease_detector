#include "glcmbuilder.h"

using namespace std;
using namespace cv;

static constexpr auto size = 5;

//=======================================================================================
Mat GlcmBuilder::get_one_channel(Mat &src, EnumChannels channel)
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
        case CHANNEL_B:
            bgr[0].copyTo(res);
            break;

        case CHANNEL_G:
            bgr[1].copyTo(res);
            break;

        case CHANNEL_R:
            bgr[2].copyTo(res);
            break;

        case CHANNEL_RG:
            add(bgr[2], - bgr[1], res);
            break;

        case CHANNEL_RB:
            add(bgr[2], - bgr[0], res);
            break;

        case CHANNEL_GB:
            add(bgr[1], - bgr[0], res);
            break;

        default:
            qDebug() << QString("ERROR in get_one_channel(): No Such Channel.");
        }
    }

    return res;
}
//=======================================================================================
Mat GlcmBuilder::get_gray_magnitude(Mat &src, GrayLevel level)
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
            case GRAY_4:
                out[i] = cv::saturate_cast<uchar>(cur[i] / 64);
                break;

            case GRAY_8:
                out[i] = cv::saturate_cast<uchar>(cur[i] / 32);
                break;

            case GRAY_16:
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
void GlcmBuilder::calc_image_textures(Mat &src, GrayLevel level, bool to_adjust)
{
    Mat glcm_win;
    Mat glcm_norm;

    TextureValues t_values;

    Mat imContrast(src.size(), CV_32FC1);
    Mat imCorrelation(src.size(), CV_32FC1);
    Mat imEnergy(src.size(), CV_32FC1);
    Mat imHomogeneity(src.size(), CV_32FC1);

    for(int i = 0; i < src.rows; i++)
    {
        float* cont_data = imContrast.ptr<float>(i);
        float* corr_data = imCorrelation.ptr<float>(i);
        float* ener_data = imEnergy.ptr<float>(i);
        float* homo_data = imHomogeneity.ptr<float>(i);

        for(int j = 0; j < src.cols; j++)
        {
            calc_glcm(src, glcm_win, i, j, level, DIR_0);
            normalize_mat(glcm_win, glcm_norm);
            calc_evalue(glcm_norm, t_values, false);

            cont_data[j] = t_values.contrast;
            corr_data[j] = t_values.correlation;
            ener_data[j] = t_values.energy;
            homo_data[j] = t_values.homogeneity;
        }
    }

    if (to_adjust)
    {
        normalize(imContrast, imContrast, 0, 255, NORM_MINMAX);
        normalize(imCorrelation, imCorrelation, 0, 255, NORM_MINMAX);
        normalize(imEnergy, imEnergy, 0, 255, NORM_MINMAX);
        normalize(imHomogeneity, imHomogeneity, 0, 255, NORM_MINMAX);
    }
}
//=======================================================================================
void GlcmBuilder::calc_texture_evalue(Mat &src, TextureValues &evalue, GrayLevel level)
{
    Mat gray;
    Mat glcm_win;
    Mat glcm_norm;

    TextureValues tmp_values = {0, 0, 0, 0};

    if(src.channels() != 1)
        cvtColor(src, gray, CV_BGR2GRAY);
    else
        src.copyTo(gray);

    for(int i = 0; i < gray.rows; i++)
    {
        for(int j = 0; j < gray.cols; j++)
        {
            calc_glcm(gray, glcm_win, i, j, level, DIR_0);
            normalize_mat(glcm_win, glcm_norm);
            calc_evalue(glcm_norm, tmp_values, false);

            evalue.contrast    += tmp_values.contrast;
            evalue.correlation += tmp_values.correlation;
            evalue.energy      += tmp_values.energy;
            evalue.homogeneity += tmp_values.homogeneity;
        }
    }
}
//=======================================================================================
void GlcmBuilder::calc_glcm(Mat &src, Mat &dst, const int &src_i, const int &src_j,
                            GrayLevel level, GrayDirection direct)
{
    Mat glcm;

    Mat roi;

    if(src.cols <= 0 || src.rows <= 0)
    {
        qDebug() << QString("ERROR in calc_glcm(): "
                            "source Mat's size is smaller than 0.");
        return;
    }

    auto n_size = size / 2 * 2 + 1;

    if(src_i + (n_size / 2) + 1 > src.rows
            || src_j + (n_size / 2) + 1 > src.cols
            || src_i < (n_size / 2)
            || src_j < (n_size / 2))
    {
        n_size = 3;

        if (src_i <= n_size / 2)
        {
            if (src_j <= n_size / 2)
                roi = Mat(src, Range(0, 3), Range(0, 3));

            else if (src_j + (n_size / 2) + 1 > src.cols)
                roi = Mat(src, Range(0, 3), Range(src.cols - 3, src.cols));

            else
                roi = Mat(src, Range(0, 3), Range(src_j - n_size / 2,
                                                  src_j + n_size / 2 + 1));
        }

        else if (src_i >= src.rows - n_size / 2)
        {
            if (src_j <= n_size / 2)
                roi = Mat(src, Range(src.rows - 3, src.rows), Range(0, 3));

            else if (src_j + (n_size / 2) + 1 > src.cols)
                roi = Mat(src, Range(src.rows - 3, src.rows),
                          Range(src.cols - 3, src.cols));

            else
                roi = Mat(src, Range(src.rows - 3, src.rows),
                          Range(src_j - n_size / 2, src_j + n_size / 2 + 1));
        }

        else if (src_j <= n_size / 2)
        {
            if (src_i <= n_size / 2)
                roi = Mat(src, Range(0, 3), Range(0, 3));

            else if(src_i + (n_size / 2) + 1 > src.rows)
                roi = Mat(src, Range(src.rows - 3, src.rows), Range(0, 3));

            else
                roi = Mat(src, Range(src_i - n_size / 2, src_i + n_size / 2 + 1),
                          Range(0, 3));
        }

        else if (src_j >= src.cols - n_size / 2)
        {
            if(src_i <= n_size / 2)
                roi = Mat(src, Range(0, 3), Range(src.cols - 3, src.cols));

            else if(src_i + (n_size / 2) + 1 > src.rows)
                roi = Mat(src, Range(src.rows - 3, src.rows),
                          Range(src.cols - 3, src.cols));

            else
                roi = Mat(src, Range(src_i - n_size / 2, src_i + n_size / 2 + 1),
                          Range(src.cols - 3, src.cols));
        }

        else
        {
            roi = Mat(src, Range(src_i - n_size / 2, src_i + n_size / 2 + 1),
                      Range(src_j - n_size / 2, src_j + n_size / 2 + 1));
        }
    }
    else
    {
        roi = Mat(src, Range(src_i - n_size / 2, src_i + n_size / 2 + 1),
                  Range(src_j - n_size / 2, src_j + n_size / 2 + 1));
    }

    switch (level)
    {
    case GRAY_4:
    {
        glcm = Mat_<uchar>(4, 4);

        for(int i = 0; i < glcm.rows; i++)
            for(int j = 0; j < glcm.cols; j++)
                glcm.at<uchar>(j, i) = 0;
        break;
    }
    case GRAY_8:
    {
        glcm = Mat_<uchar>(8, 8);

        for(int i = 0; i < glcm.rows; i++)
            for(int j = 0; j < glcm.cols; j++)
                glcm.at<uchar>(j, i) = 0;
        break;
    }
    case GRAY_16:
    {
        glcm = Mat_<uchar>(16, 16);

        for(int i = 0; i < glcm.rows; i++)
            for(int j = 0; j < glcm.cols; j++)
                glcm.at<uchar>(j, i) = 0;
        break;
    }
    default:
        qDebug() << QString("ERROR in calc_glcm(): No Such Gray Level.");
        break;
    }

    switch (direct)
    {
    case DIR_0:
        for(int i = 0; i < roi.rows; i++)
            for(int j = 0; j < roi.cols - 1; j++)
                glcm.at<uchar>(roi.at<uchar>(j, i), roi.at<uchar>(j + 1, i))++;
        break;

    case DIR_45:
        for(int i = 0; i < roi.rows - 1; i++)
            for(int j = 0; j < roi.cols - 1; j++)
                glcm.at<uchar>(roi.at<uchar>(j, i), roi.at<uchar>(j + 1, i + 1))++;
        break;

    case DIR_90:
        for(int i = 0; i < roi.rows - 1; i++)
            for(int j = 0; j < roi.cols; j++)
                glcm.at<uchar>(roi.at<uchar>(j, i), roi.at<uchar>(j, i + 1))++;
        break;

    case DIR_135:
        for(int i = 1; i < roi.rows; i++)
            for(int j = 0; j < roi.cols - 1; j++)
                glcm.at<uchar>(roi.at<uchar>(j, i), roi.at<uchar>(j + 1, i - 1))++;
        break;

    default:
        qDebug() << QString("ERROR in calc_glcm(): No such Direct.");
        break;
    }

    Mat glcm_dst;

    normalize_mat(glcm, glcm_dst);

    glcm_dst.copyTo(dst);
}
//=======================================================================================
void GlcmBuilder::normalize_mat(Mat &src, Mat &dst)
{
    Mat tmp;
    src.convertTo(tmp, CV_32F);

    float sum = 0;

    for(int i = 0; i < tmp.rows; i++)
        for(int j = 0; j < tmp.cols; j++)
            sum += tmp.at<float>(j, i);

    if(sum == 0)
        sum = 1;

    for(int i = 0; i < tmp.rows; i++)
        for(int j = 0; j < tmp.cols; j++)
            tmp.at<float>(j, i) /= sum;

    tmp.copyTo(dst);
}
//=======================================================================================
void GlcmBuilder::calc_evalue(Mat &src, TextureValues &evalue, bool to_check)
{
    if (to_check)
    {
        float sum = 0;

        for(int i = 0; i < src.rows; i++)
            for(int j = 0; j < src.cols; j++)
                sum += src.at<float>(j, i);

        if(sum < 0.99 || sum > 1.01)
        {
            qDebug() << QString("ERROR in calc_evalue(): "
                                "Sum of the Mat is not equal to 1.00.");
            return ;
        }
    }

    evalue.contrast = 0;
    evalue.correlation = 0;
    evalue.energy = 0;
    evalue.homogeneity = 0;

    Scalar loc_mean, loc_std;
    meanStdDev(src, loc_mean, loc_std);

    for(int i = 0; i < src.rows; i++)
    {
        for(int j = 0; j < src.cols; j++)
        {
            evalue.contrast += (pow((i - j), 2) * src.at<float>(j, i) );
            evalue.correlation += src.at<float>(j, i) * ((i - loc_mean[0]) *
                                  (j - loc_mean[0])) / (pow(loc_std[0], 2));
            evalue.energy += pow(src.at<float>(j, i), 2);
            evalue.homogeneity += (src.at<float>(j, i) / (1 + fabs((float)(i - j))) );
        }
    }
}
//=======================================================================================
