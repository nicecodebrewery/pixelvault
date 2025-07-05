#include "../scripts/encode.h"

int main(int argc, char const *argv[])
{
    encode("image2.bmp","res.bmp","large.txt");
    decode("res.bmp");
    return 0;
}
