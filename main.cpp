#include <iostream>

#include <QDebug>

#include <opencv/highgui.h>

#include "modules/classifier.h"
#include "modules/container.h"
#include "modules/dataparser.h"
#include "modules/glcmbuilder.h"

using namespace std;
using namespace cv;

int main()
{
    qDebug() << QString("System started!");

    Groups plants;

    Dataset dataset;
    DataParser::parse_all(&dataset);

    auto glcm = GlcmBuilder::get_one_channel(dataset.h.at(0), CHANNEL_R);

    auto magn = GlcmBuilder::get_gray_magnitude(glcm, GRAY_8);

    GlcmBuilder::calc_image_textures(magn, GRAY_8, true);

    TextureValues tvalues;

    GlcmBuilder::calc_texture_evalue(magn, tvalues, GRAY_8);

    qDebug() << QString(" Contrast: ") << tvalues.contrast;
    qDebug() << QString(" Correlation: ") << tvalues.correlation;
    qDebug() << QString(" Energy: ") << tvalues.energy;
    qDebug() << QString(" Homogeneity: ") << tvalues.homogeneity;

    return 0;
}
