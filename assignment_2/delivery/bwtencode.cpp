#include <iostream>

#include "encoder.h"


int main(int argc, char* argv[])
{
    if (argc < 5)
    {
        std::cerr << "Usage: " << argv[0] << " 'delimiter' tmp_folder input_file output_file" << std::endl;
        exit(1);
    }

    std::string str = argv[1];
    char d;

    if (str.find("\\n") != std::string::npos)
        d = '\n';
    else
        d = str[1];

    Encoder encoder;
    encoder.encode(d, argv[2], argv[3], argv[4]);

    return 0;
}

