#include "writepipe.h"

using namespace std;

void WritePipe::
run(){

    while( pipeState != State:: Done){

      // Do Write

        if( pipeState == State:: Idle){

            pipeState = State:: Busy;

            tik = timeNow();

            fwrite( dataChunk.data(), 1, dataChunk.size(), stdout);
            errorNote( stdout, "writePipe");

            tik = timeNow() - tik;

          // Last write

            if( dataChunk.size() < bytesToRead){

                pipeState = State:: Done; } else{

              // Expect more data

                pipeState = State:: Ready; }}

      // Keep running

        msleep( 1'000); }}

void WritePipe::
putData( vector< char> const & chunkOfData){

    dataChunk.clear();
    dataChunk.resize( chunkOfData.size());
    move( chunkOfData.begin(), chunkOfData.end(), dataChunk.begin());

    pipeState = State:: Idle; }

WritePipe::
WritePipe( QObject * parent): BasePipe( parent) {

  // Prevent 'write' until data available

    pipeState = State:: Ready;

    msleep( 500);

  // Set 'stdout' to Binary

    _setmode( _fileno( stdout), _O_BINARY);
}
