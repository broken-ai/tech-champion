#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>


template <typename T> std::string to_string(const T &input) {
    std::ostringstream ss;
    ss << input;
    return ss.str();
}

const std::string getExtension(const std::string &inputFileName) {
    std::string extension = "";
    bool inExtension = false;

    for (int i = 0; i < inputFileName.length(); i++) {
        if (inputFileName[i] == '.') {
            inExtension = true;
            continue;
        }
        if (inExtension) {
            extension += inputFileName[i];
        }
    }

    return extension;
}

int main(const int argc, const char** argv) {

    // Check the number of arguments
    if (argc < 2) {
        std::cout << "Error: no input file provided." << std::endl;
        system("pause");
        return EXIT_FAILURE;
    }

    // Check file extension
    std::string inputFileName = to_string(argv[1]);
    std::string extension = getExtension(inputFileName);

    if (extension != "png") {
        std::cout << "Error: input image must be .png type." << std::endl;
        system("pause");
        return EXIT_FAILURE;
    }

    std::string outLine = "";
    unsigned int imageWidth;
    unsigned int imageHeight;
    sf::Color pixelColor;
    sf::Image workpiece;
    sf::Texture helper;
    std::ofstream output;

    if (!workpiece.loadFromFile(inputFileName)) {
        std::cout << "Error: unable to open image file." << std::endl;
        system("pause");
        return EXIT_FAILURE;
    }

    if (!helper.loadFromImage(workpiece)) {
        std::cout << "Error: unable to create texture." << std::endl;
        system("pause");
        return EXIT_FAILURE;
    }

    imageWidth = helper.getSize().x;
    imageHeight = helper.getSize().y;

    if (imageWidth != 320 || imageHeight % 32 != 0) {
        std::cout << "Error: invalid image dimensions." << std::endl;
        std::cout << "Image width must be exactly 320 pixels." << std::endl;
        std::cout << "Image height must be a multiple of 32 pixels." << std::endl;
        return 1;
    }
    output.open("mask.msk");

    for (unsigned int i = 0; i < imageHeight; i++) {
        for (unsigned int j = 0; j < imageWidth; j++) {
            pixelColor = workpiece.getPixel(j, i);
            if (pixelColor.a == 255) {
                outLine.append("1");
            }
            else {
                outLine.append("0");
            }
        }

        outLine.append("\n");
        output << outLine;
        outLine = "";
    }

    output.close();
    return EXIT_SUCCESS;
}
