#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>
#include "../scripts/makebigendian.h"
using namespace std;

int main(int argc, char const *argv[])
{
    ifstream file;
    char header[54];
    file.open("image.bmp",ios::binary | ios::in);
    file.read(header,54);
    unsigned int filesize = getLittleEndian(header,2,3,4,5);
    file.close();

    char* data = new char[filesize];
    ifstream file2;
    file2.open("image.bmp",ios::binary | ios::in);
    if (!file2) {
        cerr << "Error reading file\n";
        return 1;
    }
    file2.read(data,filesize);
    unsigned int pixeloffset = getLittleEndian(data,10,11,12,13);
    unsigned int width = getLittleEndian(data,18,19,20,21);
    unsigned int height = getLittleEndian(data,22,23,24,25);
    unsigned int bitsperpixel = getLittleEndian(data,28,29,30,31);

    cout<<"File size: " << filesize <<"\n"; 
    cout<<"Pixel Offset: " << pixeloffset <<"\n"; 
    cout<<"width: " << width <<"\n";
    cout<<"height: " << height <<"\n";
    cout<<"Bits Per Pixel: " << bitsperpixel <<"\n";

    //cout<< "First pixel: " <<(unsigned int) data[pixeloffset]<<" " <<(unsigned int) data[pixeloffset + 1] <<" " <<(unsigned int) data[pixeloffset + 2]<<"\n";
    for (int i = 1; i < width * height * bitsperpixel; i++)
    {
        if (i%4 == 0)
        {
            cout<<',';
            continue;
        }
        
        cout<<( unsigned int ) data[pixeloffset+i-1] <<" ";
    }
    delete[] data;
    return 0;
}