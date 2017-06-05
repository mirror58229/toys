#include "huffman.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <fstream>

using std::ofstream;
using std::ifstream;
using std::string;
using std::priority_queue;
using std::queue;
using std::vector;
using std::cout;
using std::endl;


huffman_tree::huffman_tree(const string& str) {
    unsigned freq[128];
    memset(freq, 0, sizeof(freq));
    for(auto i : str) {
        ++freq[size_t(i)];
    }

    build_tree(freq);
    build_list();
}

huffman_tree::huffman_tree(const string& file, int) {
    unsigned freq[128];
    ifstream fin(file, std::ios::binary);
    fin.read(reinterpret_cast<char*>(freq), sizeof(freq));

    build_tree(freq);
    build_list();
}

huffman_tree::~huffman_tree() {
	safe_free(root);
    free(buf);
}

void huffman_tree::safe_free(ht_node* root) {
    if(root->lchild) {
	    safe_free(root->lchild);
    }
    if(root->rchild) {
	    safe_free(root->rchild);
    }
	root->~ht_node();
}


void huffman_tree::build_list() {
    queue<ht_node*> qn;
    qn.push(root);
    while(!qn.empty()) {
        auto now = qn.front();
        qn.pop();
        if(now->lchild) {
            now->lchild->code = now->code + "0";
            qn.push(now->lchild);
        }
        if(now->rchild) {
            now->rchild->code = now->code + "1";
            qn.push(now->rchild);
        }
        if(now->lchild == nullptr && now->rchild == nullptr) {
            list[now->ch] = now->code;
        }
    }
}

const string& huffman_tree::getCode(char ch) const {
    return list[ch];
}

void huffman_tree::save(const string& filename) const {
    unsigned freq[128];
    for(int i = 0; i != 128; ++i) {
        freq[i] = buf[i].frequent;
    }

    ofstream fout(filename, std::ios::binary);
    fout.write(reinterpret_cast<char*>(freq), sizeof(freq));
    fout.close();
}

void huffman_tree::build_tree(unsigned* freq) {
	buf = (ht_node*)malloc(256 * sizeof(ht_node));
	assert(buf);
	for(int i = 0; i != 128; ++i) {
		new(buf + i) ht_node(i, freq[i]);
	}
	auto cmp = [](const ht_node* l, const ht_node* r) {
		return l->frequent > r->frequent;
	};

	priority_queue<ht_node*, vector<ht_node*>, decltype(cmp)> pq(cmp);
	for(int i = 0; i != 128; ++i) {
		pq.push(buf + i);
	}

	int cnt = 128;
	while(pq.size() > 1) {
		auto l = pq.top();
		pq.pop();
		auto r = pq.top();
		pq.pop();
		root = new(buf + cnt) ht_node(-1, l->frequent + r->frequent, l, r);
		pq.push(root);
		++cnt;
	}
}

/* int main() { */
/*     auto t = huffman_tree("AAA"); */
/*     std::cout << t.getCode('A') << std::endl; */
/* } */
