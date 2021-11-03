#include "basepipe.h"

using namespace std;

State BasePipe::
currentState() const{

    return pipeState; }

qint64 BasePipe::
timeNow(){

    return QDateTime:: currentMSecsSinceEpoch(); }

void BasePipe::
setState( State const & state){

    pipeState = state; }

void BasePipe::
errorNote( FILE * const handle, string note){

    if( ferror( handle)){

        perror( note.c_str()); }}

BasePipe::
BasePipe( QObject * parent): QThread( parent){

}
