#ifndef WRITEPIPE_H
#define WRITEPIPE_H

#include "basepipe.h"

class WritePipe : public BasePipe{
    Q_OBJECT

    std:: vector< char> dataChunk{};

    void run() override;

public:
    explicit WritePipe( QObject *parent = nullptr);

    void putData( std:: vector< char> const & chunkOfData);
};

#endif // WRITEPIPE_H
