#include <iostream>

#include <QDebug>

#include <opencv/highgui.h>

#include "modules/container.h"
#include "modules/classifier.h"
#include "modules/dataparser.h"

using namespace std;
using namespace cv;

int main()
{
    qDebug() << QString("System started!");

    Container::Groups plants;

    Container::Dataset dataset;
    DataParser::parse_all(&dataset);

    auto glcm = Glcm::get_one_channel(dataset.h.at(0),
                                      Container::CHANNEL_R);

    auto gray = Glcm::get_gray_magnitude(glcm, Container::GRAY_8);

    return 0;
}
