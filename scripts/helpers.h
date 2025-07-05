#include <iostream>
#include <string>
#include <fstream>
using namespace std;

unsigned int getLittleEndian(char * arr,int a,int b,int c,int d){
    return (unsigned int)(static_cast<uint8_t>(arr[a]) | (static_cast<uint8_t>(arr[b]) << 8) | (static_cast<uint8_t>(arr[c]) << 16) | (static_cast<uint8_t>(arr[d]) << 24));
}

void getDetails(string filename,int * result){
    ifstream file;
    char header[54];
    file.open("image.bmp",ios::binary | ios::in);
    file.read(header,54);
    result[0]  = getLittleEndian(header,2,3,4,5);
    result[1]  = getLittleEndian(header,10,11,12,13);
    result[2]  = getLittleEndian(header,18,19,20,21);
    result[3]  = getLittleEndian(header,22,23,24,25);
    result[4]  = getLittleEndian(header,28,29,30,31);
    file.close();
}