//
// Created by Olav Markus Sjursoe on 7/09/18.
//

#include <algorithm>

#include "bwt.h"
#include "encoder.h"
#include "util.h"


/**
 *
 * @param d delimiter
 * @param folderPath index folder path
 * @param inputPath input text path
 * @param outputPath output text path
 */
void Encoder::encode(const char &d, const std::string &folderPath,
                     const char *inputPath, const std::string &outputPath)
{
    Util util;
    BWT bwt;

    // Read the entire input file
    std::string s = util.get_file_contents(inputPath);

    // Replaces all delimiters with $ before transforming
    if (d != '$')
        std::replace(s.begin(), s.end(), d, '$');

    // Encode
    std::vector<int> suffixArray = bwt.build_suffix_array(s);

    if (d != '$')
        std::replace(s.begin(), s.end(), '$', d);

    // Construct last column of BWT from suffix array in linear time
    std::string encoded;

    // positions of delimiters in the last column L of the bwt,
    // with same order as delimiters in L
    std::vector<int> lpos;
    // positions of delimiters in orginal text, with same
    // order as delimiters in the original text
    std::vector<int> tpos;
    // Mappings between tpos and lpos
    std::vector<int> pos;


    for (size_t i = 0; i < s.length(); ++i)
    {
        int bwtIndex = suffixArray[i] - 1;

        if (bwtIndex < 0)
            bwtIndex = s.length() - 1;

        if(s[bwtIndex] == d)
            lpos.push_back(bwtIndex);

        if(s[i] == d)
            tpos.push_back(i);

        encoded.append(s.substr(bwtIndex, 1));
    }

    util.write_encoded_file(outputPath, encoded);

    for (unsigned int i = 0; i < tpos.size(); i ++)
    {
        std::vector<int>::iterator it = std::find(lpos.begin(), lpos.end(), tpos[i]);
        int index = std::distance(lpos.begin(), it);
        pos.push_back(index);
    }

    util.write_pos_info(outputPath, pos);
}


