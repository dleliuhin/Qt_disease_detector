#include "dataparser.h"

using namespace std;
using namespace cv;

//=======================================================================================

//=======================================================================================
void DataParser::parse_all(Dataset *dataset)
{
    auto im_path = "Healthy/*.jpg";
    parse_group(im_path, dataset->h);

    auto im_path1 = "Diseased_1/*.jpg";
    parse_group(im_path1, dataset->nh1);

    auto im_path2 = "Diseased_2/*.jpg";
    parse_group(im_path2, dataset->nh2);

    auto im_path3 = "Diseased_3/*.jpg";
    parse_group(im_path3, dataset->nh3);

    auto im_path4 = "Diseased_4/*.jpg";
    parse_group(im_path4, dataset->nh4);

    auto im_path5 = "Diseased_5/*.jpg";
    parse_group(im_path5, dataset->nh5);

    auto im_path6 = "Diseased_6/*.jpg";
    parse_group(im_path6, dataset->nh6);

    auto im_path7 = "Diseased_7/*.jpg";
    parse_group(im_path7, dataset->nh7);

    auto im_path8 = "Diseased_8/*.jpg";
    parse_group(im_path8, dataset->nh8);

    auto im_path9 = "Diseased_9/*.jpg";
    parse_group(im_path9, dataset->nh9);

    auto im_path10 = "Diseased_10/*.jpg";
    parse_group(im_path10, dataset->nh10);
}
//=======================================================================================
void DataParser::parse_group(string subpath, vector<Mat> &group)
{
    string im_path = "../Qt_disease_detector/dataset/Wheat/Train/";

    vector<cv::String> fn;
    glob(im_path + subpath, fn, false);

    size_t count = fn.size();

    for (size_t i = 0; i < count; i++)
    {
        auto cur = imread(fn[i]);
        cur.convertTo(cur, CV_RGB2BGR);
        group.push_back(cur);
    }
}
//=======================================================================================
