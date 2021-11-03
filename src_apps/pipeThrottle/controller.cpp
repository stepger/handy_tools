#include "controller.h"

#include <QDebug>

using namespace std;

void Controller::
managePipes(){

  // Cooldown countdown

    if( readPipe-> currentState() == State:: Cooldown){

        cerr<< "cooldown "<< cooldownCounter<< endl;

        cooldownCounter --;

        if( cooldownCounter < 0){

            cooldownCounter = 30;

            readPipe-> setState( State:: Ready); }}

  // Data collected in the readPipe, write it

    if( readPipe-> currentState() == State:: Ready){

        // Prevent read and this fork
        readPipe-> setState( State:: Busy);

      // writePipe ready to accept data

        if( writePipe-> currentState() == State:: Ready){

            // Protect this fork
            writePipe-> setState( State:: Busy);

          // Get data from readPipe to writePipe

            writePipe-> putData( readPipe-> takeData());

            readPipe-> setState( State:: Idle); } else

          // Check again if writePipe ready for data

            readPipe-> setState( State:: Ready); }

  // Last data Write

    if( readPipe-> currentState() == State:: Done){

        if( writePipe-> currentState() == State:: Ready){

            writePipe-> setState( State:: Busy);

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
