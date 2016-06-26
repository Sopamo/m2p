//
//  main.cpp
//  m2p
//
//  Created by Paul Mohr on 25.06.16.
//  Copyright © 2016 Sopamo GmbH. All rights reserved.
//  You may only use this code for private usage. You may only use this code for legal activities according to your country's laws.

#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <math.h>
#include <sodium.h>

#include "lodepng.h"

#define ADDITIONAL_DATA (const unsigned char *) ""
#define ADDITIONAL_DATA_LEN 0


void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
{
    //Encode the image
    unsigned error = lodepng::encode(filename, image, width, height);
    
    //if there's an error, display it
    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

std::vector<unsigned char> decodeOneStep(const char* filename)
{
    std::vector<unsigned char> image; //the raw pixels
    unsigned width, height;
    
    //decode
    unsigned error = lodepng::decode(image, width, height, filename);
    
    //if there's an error, display it
    if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    return image;
}

void encode(const char* inputFile, const char * outputDir) {
    
    // Read the data
    std::ifstream input(inputFile, std::ios::binary);
    std::vector<char> buffer((
                              std::istreambuf_iterator<char>(input)),
                             (std::istreambuf_iterator<char>()));
    
    if(!input) {
        std::cout << "Could not read file \n";
        return;
    }
    
    
    // Write the data to image files
    unsigned maxSize = 4096 * 4096 * 4;
    unsigned extension = 0;
    while(buffer.size() > maxSize*extension) {
        
        // Generate image dimensions
        unsigned width = sqrt(maxSize / 4), height = width;
        
        // Setup the image vector
        std::vector<unsigned char> image;
        image.resize(width * height * 4);
        
        // Iterate over the pixels and fill them with data
        for(unsigned y = 0; y < height; y++) {
            for(unsigned x = 0; x < width; x++) {
                int idx = 4 * width * y + 4 * x;
                for(unsigned p = 0; p <4;p++) {
                    long value;
                    unsigned pos = maxSize * extension + idx + p;
                    
                    if(pos > buffer.size()) {
                        value = 0;
                    } else {
                        value = (long)buffer[pos];
                    }
                    
                    image[idx + p] = value;
                }
            }
        }
        
        // Generate the part's filename
        char * filename = new char[5000];
        std::string output = std::string(outputDir) + std::string("/out%d.png");
        sprintf(filename, output.data(),extension);
        encodeOneStep(filename, image, width, height);
        std::cout << "Saved part " << extension << "\n";
        extension++;
    }
    
    // We are done, close the input file
    input.close();
    
}

void decode(const char * storagePath) {
    
    // Read file data
    std::vector<unsigned char> data;
    std::string imageFile = std::string(storagePath) + std::string("/out0.png");
    std::vector<unsigned char> imgdata = decodeOneStep(imageFile.data());
    
    // Generate file path
    std::ofstream movieFile;
    std::string movieFilePath = std::string(storagePath) + std::string("/output.avi");
    
    // Write the data
    std::ofstream outfile (movieFilePath,std::ofstream::binary);
    outfile.write ((char *)imgdata.data(),imgdata.size());
    outfile.close();
    
    std::cout << "Done with decoding\n";
}

int main(int argc, const char * argv[]) {
    
    // Init sodium (currently not in use)
    sodium_init();
    if(sodium_init()) {
        std::cout << "Starting to encode ...\n";
        encode(argv[1], argv[2]);
        std::cout << "Starting to decode ...\n";
        decode(argv[2]);
    }
    
    return 0;
}