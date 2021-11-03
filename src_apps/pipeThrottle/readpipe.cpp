#include "readpipe.h"

using namespace std;

void ReadPipe::
run(){

    while( pipeState != State:: Done){

      // Do Read

        if( pipeState == State:: Idle){

            pipeState = State:: Busy;

            char buffer[ bytesToRead];

            tik = timeNow();

            bytesGot = fread( buffer, 1, bytesToRead, dataStream);
            errorNote( dataStream, "readPipe");

            tik = timeNow() - tik;

          // Collect data

            if( bytesGot > 0){

                totalBytes += bytesGot;
                cerr<< "read: total "<< totalBytes<< endl;

                totalData.insert( totalData.end(), buffer, buffer + bytesGot); }

          // enter Cooldown

            if(  tik > 300){

                cerr<< "read delay "<< tik<< endl;
                pipeState = State:: Cooldown; } else{

          // It is last read

            if( bytesGot < bytesToRead){

                pipeState = State:: Done; } else{

              // Expect more data

                pipeState = State:: Ready; }}}

      // Keep running

        msleep( 1'000); }}

vector< char> ReadPipe::
takeData(){

  // Take out chunk of totalData

    size_t chunkSize{ bytesToRead};

    if( totalData.size() < bytesToRead){

        chunkSize = totalData.size(); }

    vector< char>:: iterator itBegin{ totalData.begin()},
            itEnd{ itBegin + chunkSize};

    vector< char> chunkOfData( chunkSize);
    move( itBegin, itEnd, chunkOfData.begin());

    totalData.erase( itBegin, itEnd);

    return chunkOfData; }

ReadPipe::
ReadPipe(QObject *parent, std:: string filePath) : BasePipe(parent){

  // Use 'file' for input data

    if( filePath.size() > 0){

        if( ! ( dataStream = fopen( filePath.c_str(), "rb"))){

            cerr<< "file NOT openned."<< endl; }} else{

      // Use stdin, and set to Binary

        _setmode( _fileno( dataStream), _O_BINARY); }}

ReadPipe:: ~ReadPipe(){

    fclose( dataStream);
}
