#ifndef DATAPARSER_H
#define DATAPARSER_H

#include "container.h"

class DataParser
{
public:

    static void parse_all(Dataset *dataset);

    //===================================================================================

private:

    static void parse_group(std::string subpath, std::vector<cv::Mat> &group);

};

#endif // DATAPARSER_H
