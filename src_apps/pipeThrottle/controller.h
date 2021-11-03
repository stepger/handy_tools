#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "readpipe.h"
#include "writepipe.h"

#include <QObject>
#include <QTimer>

class Controller : public QObject{
    Q_OBJECT

    ReadPipe * readPipe{};
    WritePipe * writePipe{};
    QTimer * timer{ nullptr};
    int cooldownCounter{ 30};

public:
    explicit Controller( QObject * parent = nullptr,
                         std:: string filePath = "");
signals:

private slots:

    void managePipes();
};

#endif // CONTROLLER_H
