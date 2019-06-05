#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <iostream>
#include <vector>

#include <opencv/highgui.h>
#include <opencv2/highgui/highgui.hpp>

#include "container.h"

class DataParser
{
public:
    static void parse_all(Container::Dataset *dataset);

    //===================================================================================

private:
    static void parse_group(std::string subpath,
                            std::vector<cv::Mat> &group);
};

#endif // DATAPARSER_H
