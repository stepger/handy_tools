#include "controller.h"

#include <QDebug>

using namespace std;

void Controller::
managePipes(){

  // Cooldown countdown

    if( readPipe-> isCooldown()){

        cerr<< "cooldown "<< cooldownCounter<< endl;

        -- cooldownCounter ;

        if( cooldownCounter < 0){

            cooldownCounter = 30;

            readPipe-> setReady(); }}

  // Data collected in the readPipe, write it

    if( readPipe-> isReady()){

        // Prevent read and this fork
        readPipe-> setBusy();

      // writePipe ready to accept data

        if( writePipe-> isReady()){

            // Protect this fork
            writePipe-> setBusy();

          // Get data from readPipe to writePipe

            writePipe-> putData( readPipe-> takeData());

            readPipe-> setIdle(); } else

          // Check again if writePipe ready for data

            readPipe-> setReady(); }

  // Last data Write

    if( readPipe-> isDone()){

        if( writePipe-> isReady()){

            writePipe-> setBusy();

          // Get data from readPipe to writePipe

            writePipe-> putData( readPipe-> takeData()); }}

  // Theards finished

    if( readPipe-> isFinished() && writePipe-> isFinished()){

        cerr<< "allDone - exit."<< endl;

        exit( 0); }}

Controller::
Controller(QObject *parent, string filePath) : QObject(parent){

  // Setting 'readPipe/writePipe' and 'ticker'

    readPipe = new ReadPipe( this, filePath);

        readPipe-> start();

    writePipe = new WritePipe( this);

        writePipe-> start();

    timer = new QTimer( this);

        connect( timer, & QTimer:: timeout, this, & Controller::
                                managePipes);
        timer-> start( 1'000);
}
