#ifndef TEXT_H
#define TEXT_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Text {
    vector<string> contents;

    Text(vector<string> lines) {
        contents = lines;
    }

public:
    static Text* parseFromString(string src) {
        vector<string> lines;

        int newline = -1;
        while ((newline = src.find('\n')) != -1) {
            lines.push_back(src.substr(0, newline + 1));
            src = src.substr(newline + 1);
        }
        if (src.length() > 0) {
            lines.push_back(src);
        }


        return new Text(lines);
    }

    string toString() {
        string res;
        int sz = contents.size();
        for (int i = 0; i < sz - 1; i++) {
            res += contents.at(i);
        }

        if (contents.size()) {
            res += contents.at(contents.size() - 1);
        }

        res += '\0';

        return res;
    }
};

#endif // TEXT_H
