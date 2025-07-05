#pragma once
#include "../scripts/helpers.h"
#include <cstdint>

int encode(string filename, string outputfile, string secretfilename)
{
    int data[5];
    getDetails(filename, data);
    const std::uint8_t END_MARKER = 255;
    const std::uint8_t MASK_2BIT = 0b00000011;
    const int HEADER_SKIP = data[1];

    ifstream inputFile;
    inputFile.open(filename, ios::binary | ios::in);

    ofstream outputFile;
    outputFile.open(outputfile, ios::binary | ios::out);

    ifstream secretFile;
    secretFile.open(secretfilename, ios::binary | ios::in);

    if (!inputFile || !outputFile || !secretFile) {
        std::cerr << "File error!\n";
        return 1;
    }

    bool isTextOver = false;
    std::uint8_t imageByte;
    for (int i = 0; i < HEADER_SKIP; i++)
    {
        inputFile.get(reinterpret_cast<char&>(imageByte));
        outputFile.write(reinterpret_cast<char*>(&imageByte), 1);
    }

    std::uint8_t secretByte;
    char tmp;
    bool hasSecret = static_cast<bool>(secretFile.get(tmp));
    secretByte = static_cast<std::uint8_t>(tmp);
    int index = 1;
    bool putEndMarker = true;
    while (inputFile.get(reinterpret_cast<char&>(imageByte)))
    {
        if (hasSecret)
        {
            // Embed secret byte bits into the LSBs of image byte
            switch (index % 4)
            {
            case 1:
                imageByte = (imageByte & 0b11111100) | (secretByte & MASK_2BIT);
                break;
            case 2:
                imageByte = (imageByte & 0b11111100) | ((secretByte & 0b00001100) >> 2);
                break;
            case 3:
                imageByte = (imageByte & 0b11111100) | ((secretByte & 0b00110000) >> 4);
                break;
            case 0:
                imageByte = (imageByte & 0b11111100) | ((secretByte & 0b11000000) >> 6);
                if (secretFile.get(tmp)) {
                    secretByte = static_cast<std::uint8_t>(tmp);
                    hasSecret = true;
                } else {
                    hasSecret = false;
                }
                break;
            }
        }
        else if (putEndMarker)
        {
            // Embed end marker bits into the LSBs of image byte
            switch (index % 4)
            {
            case 1:
                imageByte = (imageByte & 0b11111100) | (END_MARKER & 0b00000011);
                break;
            case 2:
                imageByte = (imageByte & 0b11111100) | ((END_MARKER & 0b00001100) >> 2);
                break;
            case 3:
                imageByte = (imageByte & 0b11111100) | ((END_MARKER & 0b00110000) >> 4);
                break;
            case 0:
                imageByte = (imageByte & 0b11111100) | ((END_MARKER & 0b11000000) >> 6);
                putEndMarker = false;
                break;
            }
        }
        outputFile.write(reinterpret_cast<char*>(&imageByte), 1);
        index++;
    }
    inputFile.close();
    outputFile.close();
    secretFile.close();
    return 0;
}


int decode(string filename)
{
    int data[5];
    getDetails(filename, data);
    const std::uint8_t END_MARKER = 255;
    const std::uint8_t MASK_2BIT = 0b00000011;
    const int HEADER_SKIP = data[1];

    ifstream inputFile(filename, ios::binary | ios::in);
    ofstream secretout("decoded_secret.txt", ios::binary | ios::out);

    if (!inputFile || !secretout) {
        std::cerr << "File error!\n";
        return 1;
    }

    std::uint8_t imageByte;
    for (int i = 0; i < HEADER_SKIP; i++) {
        inputFile.get(reinterpret_cast<char&>(imageByte));
    }

    int index = 0;
    std::uint8_t secretByte = 0;
    while (inputFile.get(reinterpret_cast<char&>(imageByte))) {
        // Extract 2 bits from image byte
        std::uint8_t bits = imageByte & MASK_2BIT;
        secretByte |= (bits << (2 * index));
        index++;
        if (index == 4) {
            if (secretByte == END_MARKER)
            {
                break;
            }
            secretout.put(static_cast<char>(secretByte));
            secretByte = 0;
            index = 0;
        }
    }
    inputFile.close();
    secretout.close();
    return 0;
}