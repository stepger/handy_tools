#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <windows.h>

using namespace std;

int errorOccured( FILE * _file){

    if( ferror( _file)){

        // "pipe-throttle: No space left on device"
        perror( "pipe-throttle");

        return 1; } return 0; }

int main( int argc, char * argv[]){

  // Check arguments

    if( argc > 1){

        cerr<< "argc "<< argc<< endl;
        cerr<< "argv "<< argv[ 1]<< endl; }

  // Set Binary std in/out

    _setmode( _fileno( stdin), _O_BINARY);
    _setmode( _fileno( stdout), _O_BINARY);

  // Set data caps

    int bufSize{ 1048576};  // 1mb
    int timePeriod{ 1000};  // 1s
    int bytesCount{}, bytesRead;
    char buf[ bufSize];

  // Process data

    while(( bytesRead = fread( buf, 1, bufSize, stdin)) > 0){

        if( errorOccured( stdin)) break;

        bytesCount += bytesRead;

        cerr<< "bytesCount "<< bytesCount<< endl;

        Sleep( timePeriod);

      // Write to stdout

        fwrite( buf, 1, bytesRead, stdout);

        if( errorOccured( stdout)) break; }

  // Finish

    return 0;
}
