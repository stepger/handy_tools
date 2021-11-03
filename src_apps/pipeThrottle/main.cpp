#include <QCoreApplication>

#include "controller.h"

int main(int argc, char *argv[]){

    QCoreApplication a(argc, argv);

    std:: string filePath{};

    if( argc > 1){

        filePath = argv[ 1]; }

    new Controller( & a, filePath);

    return a.exec();
}
