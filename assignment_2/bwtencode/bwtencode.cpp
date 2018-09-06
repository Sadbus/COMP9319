#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

std::string record_delim;
std::string folder_path;
std::string file_path_in;
std::string file_path_out;

struct suffix
{
    int index;
    std::string suff;
};

void print_vector(std::vector<std::vector<std::string>> vec)
{
    int i=0,j=0;
    for ( auto it = vec.begin(); it != vec.end(); ++it, ++i)
        for (auto it2 = it->begin(); it2 != it->end(); ++it2, ++j)
            std::cout << "From node " << i << " to node " << *it2 << std::endl;
}

void rotate(std::string &s, int d)
{
    reverse(s.begin(), s.begin()+d);
    reverse(s.begin()+d, s.end());
    reverse(s.begin(), s.end());
}

/*
 * Function to compute the suffix array in O(n log n)-time.
 *
 */
void compute_suffix_array(const std::string &s)
{
    int n = static_cast<int>(s.size());
    std::vector<std::string> v;


    std::cout << s << std::endl;
    for(int i = 0; i < n; i++)
    {
        std::cout << i;
    }
    std::cout << std::endl;


    for(int i = 0; i < n; i++)
    {
        v.push_back(s.substr(i, n));
    }

    std::cout << std::endl << "Suffixes: " << std::endl;
    for (auto itr = v.begin(); itr != v.end(); itr++)
    {
        std::cout << itr->data() << std::endl;
    }

    //TODO: Replace with bucket sort
    std::sort(v.begin(), v.end());

    std::cout << std::endl << "Sorted: " << std::endl;

    for (auto itr = v.begin(); itr != v.end(); itr++)
    {
        std::cout << itr->data() << std::endl;
    }

    std::cout << std::endl;

    int arr[n];

    std::cout << "Suffix Array = {";
    for (int i = 0; i < n; i++)
    {
        arr[i] = static_cast<int>(n - v[i].size());
        std::cout << arr[i] <<", ";
    }
    std::cout << "}" << std::endl;

    std::cout << "BWT indexes = {";

    int bwtArr[n];
    for (int i = 0; i < n; i++)
    {
        bwtArr[i] = arr[i] - 1;
        if (bwtArr[i] == -1)
            bwtArr[i] = n-1;
        std::cout << bwtArr[i] << ", ";
    }
    std::cout << "}" << std::endl;
}

void build_suffix_array(const std::string &s)
{
    const int n = static_cast<int>(s.size());
    std::vector<std::string> v;

    for(int i = 0; i < n; i++)
    {
        v.push_back(s.substr(i, n));
    }

    //TODO: Replace with bucket sort
    std::sort(v.begin(), v.end());

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = static_cast<int>((n - v[i].size()) - 1);
        if (arr[i] < 0)
        {
            arr[i] = n - 1;
        }
    }

    std::string bwt;

    for (int i = 0; i < n; i++)
    {
        bwt.append(s.substr(arr[i], arr[i]-2));
    }

    std::cout << bwt << std::endl;

    std::cout << s.substr(5) << std::endl;


}

std::string bwt(std::string s)
{
    std::vector<std::string> v;

    for (int i = 0; i < s.size(); i++)
    {
        rotate(s, 1);
        v.push_back(s);
    }

    std::sort(v.begin(), v.end());
    std::string transformed;

    for (int i = 0; i < v.size(); ++i)
    {
        transformed.append(v[i].substr(s.size()-1, s.size()));
    }

    return transformed;
}

void write_file(const std::string &filePath, const std::string &s)
{
    std::ofstream outfile(filePath, std::ios_base::app);

    outfile << s;
    outfile.close();
}


void read_file(const std::string &file_path_in, const std::string &file_path_out, const std::string &delim)
{
    std::vector<std::vector<std::string>> data;
    std::ifstream infile(file_path_in);

    while (infile.is_open())
    {
        std::string s;
        if (!getline(infile, s)) break;

        std::istringstream ss(s);
        std::vector<std::string> record;

        while (ss)
        {
            std::string s;
            if (!getline( ss, s, '|')) break;

            s.append("$");
            compute_suffix_array(s);
            build_suffix_array(s);

            s = bwt(s);
            //record.push_back(s);

            s.append(delim);

            write_file(file_path_out, s);
        }

        data.push_back(record);
    }
    if (!infile.eof())
    {
        std::cerr << "Critical error. Exiting ...";
    }

    infile.close();
}


void encode()
{

}

void handle_args(int argc, char* argv[])
{
    std::string d = argv[1];
    record_delim = d.substr(1, d.size()-2);

    folder_path = argv[2];
    file_path_in = argv[3];
    file_path_out = argv[4];

}


int main(int argc, char* argv[])
{
    //std::cout << "Encoding " << file_path_in << " with delimeter: " << delim << std::endl;
    //std::cout << "Saving to " << file_path_out << " and storing metadata in " << folder_path;

    // Handle arguments
    handle_args(argc, argv);

    // 
    read_file(file_path_in, file_path_out, record_delim);

    return 0;
}

/* Compress s
 * 1. Form S' by concatenating S with EOF (EOF must not be present in S)
 * 2.
 */