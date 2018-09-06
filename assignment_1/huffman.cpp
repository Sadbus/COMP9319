//
// Created by Olav Markus Sjursoe on 14/08/18.
//

#include "huffman.h"


unsigned int Huffman::getTotFreq() const {
    return static_cast<unsigned int>(minHeap.top()->freq);
}

void Huffman::SaveCodes(struct Node *root, std::string str)
{
    if (!root)
        return;

    if (root->data != '$')
    {
        codes[root->data] = str;
    }

    SaveCodes(root->left, str + "0");
    SaveCodes(root->right, str + "1");
}

std::map<char, std::string> Huffman::BuildTree(std::map<char, int> freq)
{
    this->freqMap = freq;
    return BuildTree();
}

std::map<char, std::string> Huffman::BuildTree()
{
        struct Node *left, *right, *top;

        for (auto v = freqMap.begin(); v != freqMap.end(); v++)
            minHeap.push(new Node(v->first, v->second));

        while (minHeap.size() != 1)
        {
            left = minHeap.top();
            minHeap.pop();

            right = minHeap.top();
            minHeap.pop();

            top = new Node('$', left->freq + right->freq);

            top->left = left;
            top->right = right;

            minHeap.push(top);
        }

        SaveCodes(minHeap.top(), "");

        return codes;
}


bool Huffman::Decode(std::string s, unsigned char &c) const
{
    std::string decodedText;
    struct Node* curr = minHeap.top();

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;
    }

    bool found = false;

    if (curr->left == nullptr && curr->right == nullptr)
    {
        found = true;
        c = static_cast<unsigned char>(curr->data);
    }

    return found;
}

