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

bool BasePipe:: isReady() const{

    return matchState( State:: Ready); }

bool BasePipe:: isDone() const{

    return matchState( State:: Done); }

bool BasePipe:: isCooldown() const{

    return matchState( State:: Cooldown); }

bool BasePipe:: matchState( State const & state) const{

    return currentState() == state; return false; }

void BasePipe:: setIdle(){

    setState( State:: Idle); }

void BasePipe:: setBusy(){

    setState( State:: Busy); }

void BasePipe:: setReady(){

    setState( State:: Ready); }

BasePipe::
BasePipe( QObject * parent): QThread( parent){

}
