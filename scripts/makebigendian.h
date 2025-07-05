#include <iostream>


unsigned int getLittleEndian(char * arr,int a,int b,int c,int d){
    return (unsigned int)(static_cast<uint8_t>(arr[a]) | (static_cast<uint8_t>(arr[b]) << 8) | (static_cast<uint8_t>(arr[c]) << 16) | (static_cast<uint8_t>(arr[d]) << 24));
}

