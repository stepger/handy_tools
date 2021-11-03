#ifndef READPIPE_H
#define READPIPE_H

#include "basepipe.h"

class ReadPipe : public BasePipe{
    Q_OBJECT

    size_t bytesGot, totalBytes{};
    std:: vector< char> totalData;

    FILE * dataStream{ stdin};

    void run() override;
    ~ReadPipe() override;

public:
    explicit ReadPipe( QObject *parent = nullptr,
                       std:: string filePath = "");

    std:: vector< char> takeData();

public slots:

};

#endif // READPIPE_H
