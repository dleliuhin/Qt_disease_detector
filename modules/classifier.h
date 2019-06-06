#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "dataparser.h"
#include "container.h"
#include "imageprocessing.h"

class Classifier
{
public:

    static void to_train(Groups &plants);

    //-----------------------------------------------------------------------------------

    static void to_test();

//private:

};

#endif // CLASSIFIER_H
