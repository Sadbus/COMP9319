#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

std::string compute_suffix_array(const std::string &s)
{
    const int n = static_cast<int>(s.size());
    std::vector<std::string> v;

    // Adds all the suffixes to a vector
    for(int i = 0; i < n; i++)
    {
        v.push_back(s.substr(i, n));
    }

    // Sorts all the suffixes
    // TODO: Replace with bucket sort
    // O(n log n)
    std::sort(v.begin(), v.end());

    int arr[n];

    // Takes the number of characters and subtracts the size of the suffix.
    // This gives us the start position of the suffix. Also subtracts 1 to get the BWT
    for (int i = 0; i < n; i++)
    {
        arr[i] = static_cast<int>((n - v[i].size()) - 1);
        if (arr[i] < 0)
        {
            arr[i] = n - 1;
        }
    }

    std::string bwt;

    // Creates the bwt from the suffix array
    for (int i = 0; i < n; i++)
    {
        bwt.append(s.substr(arr[i], 1));
    }

    return bwt;
}


void bucket_sort(int a[], const int n)
{
    int i, j, k, buckets[10];

    for (int i = 0; i < 10; i++)
        buckets[i] = 0;

    for (i = 0; i < n; ++i)
        ++buckets[a[i]];

    for (i = 0, j = 0; j < 10; ++j)
        for (k = buckets[j]; k > 0; --k)
            a[i++] = j;
}

std::string get_file_contents(const char *filename)
{
    std::FILE *fp = std::fopen(filename, "rb");
    if (fp)
    {
        std::string contents;
        std::fseek(fp, 0, SEEK_END);
        contents.resize(std::ftell(fp));
        std::rewind(fp);
        std::fread(&contents[0], 1, contents.size(), fp);
        std::fclose(fp);
        return(contents);
    }
    throw(errno);
}

void write_encoded_file(const std::string &path, const std::string &s)
{
    std::fstream file(path, std::ios::out | std::ios::binary);
    file << s;
    file.close();
}

void encode(const std::string &d, const std::string &folderPath, const char* inputPath, const std::string &outputPath)
{
    // Read the entire input file
    std::string s = get_file_contents(inputPath);

    // Encode
    std::string encoded = compute_suffix_array(s);

    //
    write_encoded_file(outputPath, encoded);
}



int main(int argc, char* argv[])
{
    if (argc < 5)
    {
        std::cerr << "Usage: " << argv[0] << " 'delimiter' tmp_folder input_file output_file" << std::endl;
        exit(1);
    }

    std::string d = argv[1];
    std::string delim = d.substr(1, d.size()-2);

    //encode(delim, argv[2], argv[3], argv[4]);

    int i, a[] = {3, 6, 5, 1, 8, 4, 3, 1}, n = 8;

    std::cout << "Before sorting: " << std::endl;
    for (i = 0; i < n; ++i)
        std::cout << a[i] << " ";

    bucket_sort(a, n);

    std::cout << std::endl << "After sorting: " << std::endl;

    for (i = 0; i < n; ++i)
        std::cout << a[i] << " ";


    return 0;
}