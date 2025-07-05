#include <iostream>
#include <string>
#include <cstdio>  // for std::remove
#include "../scripts/encode.h"


int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage:\n"
                  << "  " << argv[0] << " encode <cover.bmp> <output.bmp> <secret.txt> \n"
                  << "  " << argv[0] << " decode <stego.bmp> \n";
        return 1;
    }

    std::string mode = argv[1];

    if (mode == "encode") {
        if (argc != 5) {
            std::cerr << "Usage: encode <cover.bmp> <output.bmp> <secret.txt>\n";
            return 1;
        }

        std::string cover = argv[2];
        std::string output = argv[3];
        std::string secret = argv[4];



        // Step 2: Encode encrypted file
        int result = encode(cover, output, secret);

        // Step 3: Remove intermediate encrypted file
        //std::remove(encryptedFile.c_str());
        if (result == 0)
        {
            cout << "Success. "<<output <<" saved.";
        }
        
        return result;
    }

    else if (mode == "decode") {
        if (argc != 3) {
            std::cerr << "Usage: decode <stego.bmp> \n";
            return 1;
        }

        std::string stego = argv[2];

        // Step 1: Decode to extract encrypted data
        if (decode(stego) != 0) {
            std::cerr << "Decoding failed.\n";
            return 1;
        }


        std::cout << "Secret message written to decoded_secret.txt" << "\n";
        return 0;
    }

    else {
        std::cerr << "Unknown mode: " << mode << "\n";
        return 1;
    }
}