#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <ctime>
#include "bwt.h"
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
        d = str.at(3);

    std::clock_t begin = std::clock();

    Encoder encoder;
    encoder.encode(d, argv[2], argv[3], argv[4]);

    std::clock_t end = clock();

    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Time elapsed: " << elapsed_secs << " sec" << std::endl;

    return 0;
}

