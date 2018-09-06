//
// Created by Olav Markus Sjursoe on 14/08/18.
//

#ifndef ASSIGNMENT_1_HUFFMAN_H
#define ASSIGNMENT_1_HUFFMAN_H

#include <string>
#include <iostream>
#include <queue>
#include <map>

struct Node {
    char data;
    unsigned int freq;
    Node* left;
    Node* right;

    Node(char data, unsigned int freq)
    {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

struct compare {
    bool operator()(Node* l, Node* r)
    {
        return (l->freq > r->freq);
    }
};

class Huffman {
public:
    void SaveCodes(struct Node *root, std::string str);

    std::map<char, std::string>  BuildTree();
    std::map<char, std::string>  BuildTree(std::map<char, int> freq);

    bool Decode(std::string s, unsigned char &c) const;

    unsigned int getTotFreq() const;

private:
    std::priority_queue<Node*, std::vector<Node*>, compare> minHeap;
    std::map<char, std::string> codes;
    std::map<char, int> freqMap;

};


#endif //ASSIGNMENT_1_HUFFMAN_H
