#ifndef _COMPRESS_H_
#define _COMPRESS_H_

#include <iostream>
#include <string>
#include "huffman.h"

class compress {
public:
    compress() = delete;

    static void zip(const std::string& ifile, const std::string& ofile);
    static void unzip(const std::string& ifile, const std::string& ofile);

private:
    static void genbuffer(char* buf, const string& sbuf, int count = bufsize);
    const static int bufsize = 512;
};

void debug(huffman_tree* t) {
    using namespace std;

    string ss = "System need to be reboot!";
    for(auto i : ss) {
        cout << t->getCode(i) << endl;
    }
}
void compress::zip(const string& ifile, const string& ofile) {
    std::ifstream fin(ifile);
    fin.seekg(0, fin.end);
    auto length = fin.tellg();
    fin.seekg(0, fin.beg);
    std::string content(length, '\0');
    fin.read(&content[0], length);

    auto tree = huffman_tree(content);
    std::ofstream fout(ofile, std::ios::binary);

    std::string buf;
    char binbuf[bufsize];

    for(auto i : content) {
        buf += tree.getCode(i);
        if(buf.size() > bufsize * 8) {
            genbuffer(binbuf, buf);
            fout.write(binbuf, sizeof(binbuf));
            buf = string(buf.begin() + bufsize * 8, buf.end());
        }
    }

    buf += tree.getCode(0);
    buf += tree.getCode(0);

    genbuffer(binbuf, buf, buf.size() / 8);
    fout.write(binbuf, buf.size() / 8);

    tree.save(ofile + ".tree");

    fin.close();
    fout.close();
}

void compress::unzip(const string& ifile, const string& ofile) {
    auto tree = huffman_tree(ifile + ".tree", 0);
    tree.reset();
    std::ifstream fin(ifile, std::ios::binary);
    std::ofstream fout(ofile);
    char ch;
    bool end = false;
    while(!end && fin.read(&ch, sizeof(char))) {
        char ans;
        bool ret = false;
        for(int i = 0; i != 8; ++i) {
            if((ch >> (8 - i - 1)) & 1) {
                ret = tree.goRight(ans);
            } else {
                ret = tree.goLeft(ans);
            }
            if(ret) {
                tree.reset();
                if(ans == 0) {
                    end = true;
                    break;
                }
                ret = false;
                fout << ans;
            }
        }
    }
    fin.close();
    fout.close();
}

void compress::genbuffer(char* buf, const string& sbuf, int count) {
    for(int i = 0; i != count; ++i) {
        int sum = 0;
        for(int j = 1; j != 8; ++j) {
            sum = sum * 2 + sbuf[j + i * 8] - '0';
        }
        if(sbuf[i * 8] == '1') {
            sum -= (1 << 7);
        }
        buf[i] = sum;
    }
}

#endif
