#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <array>
#include <fstream>
#include <string>
#include "huffman.h"

using std::string;
using std::array;

class huffman_tree {
    struct ht_node {
        char ch;
        unsigned frequent;
        ht_node* lchild;
        ht_node* rchild;
        string code;

        ht_node(char _ch, unsigned _frequent, ht_node* _lchild = nullptr,
                ht_node* _rchild = nullptr)
            : ch(_ch), frequent(_frequent), lchild(_lchild), rchild(_rchild) {}
    };

public:
    huffman_tree(const string& str);
    huffman_tree(const string& file, int);
    ~huffman_tree();

    void save(const string& filename) const;

    const string& getCode(char ch) const;

    bool goLeft(char& out) {
        pos = pos->lchild;
        if(pos->lchild == nullptr && pos->rchild == nullptr) {
            out = pos->ch;
            return true;
        } else {
            out = -1;
            return false;
        }
    }

    bool goRight(char& out) {
        pos = pos->rchild;
        if(pos->lchild == nullptr && pos->rchild == nullptr) {
            out = pos->ch;
            return true;
        } else {
            out = -1;
            return false;
        }
    }

    void reset() { pos = root; }

private:
    ht_node* root = nullptr;
    ht_node* buf = nullptr;
    ht_node* pos;
    array<string, 128> list;

    void build_tree(unsigned* freq);
    void build_list();
    void safe_free(ht_node* root);
};

#endif
