#ifndef BASEPIPE_H
#define BASEPIPE_H

#include <QThread>
#include <QObject>
#include <QDateTime>

#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <vector>

enum class State{ Idle, Busy, Ready, Done, Cooldown};

class BasePipe : public QThread{
    Q_OBJECT

protected:

    qint64 tik;

    qint64 timeNow();
    size_t const bytesToRead{ 500'000};
    State pipeState{ State:: Idle};
    void errorNote( FILE * const handle, std:: string note);

public:
    explicit BasePipe( QObject *parent = nullptr);
    virtual ~BasePipe() = default;

    State currentState() const;
    void setState( State const &);
    bool isReady() const;
    bool isDone() const;
    bool isCooldown() const;
    bool matchState( State const & state) const;
    void setIdle();
    void setBusy();
    void setReady();

};

#endif // BASEPIPE_H
