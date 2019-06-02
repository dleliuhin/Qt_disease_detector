#include <iostream>

#include <QDebug>

#include "modules/container.h"

using namespace std;

int main()
{
    qDebug() << QString("System started!");

    Container::Groups plants;

    return 0;
}
