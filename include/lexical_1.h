//
// Created by Lance on 2020/12/16.
//

#ifndef POC_LEXICAL_1_H
#define POC_LEXICAL_1_H
#include<bits/stdc++.h>
using namespace std;
// ******************************************************************
// 词法分析器模块
// ******************************************************************
const int KEY_LEN = 25;
const int SYMBOLS_LEN = 19;
string key[] = {"if", "then", "else", "while", "do",
                "auto", "break", "char", "const","continue",
                "default", "double","float", "for","int",
                "long", "return", "signed","sizeof", "static",
                "struct", "switch", "typedef", "unsigned", "void"};

char symbols[SYMBOLS_LEN] = {'+', '-', '*', '/', '>',
                             '<', '=', '(', ')', ';',
                             '^', '[', ']', '"', '\'',
                             '{', '}', ','};
const int CHECK_1_LEN = 4;
const int CHECK_2_LEN = 13;
char check_1[] = {'>', '<', '=', '/'};
char check_2[] = {'(', ')', ';', '[', ']', '"', '\'', '{', '}', ',', '*', '+', '-'};
map<char, string> M{{'>', "="},
                    {'<', "="},
                    {'=', "=="},
                    {'/', "/"}};

bool IsSymbols(char c) {
    for (int i = 0; i < SYMBOLS_LEN; i++)
        if (symbols[i] == c)
            return true;
    return false;
}

// 判断关键字
bool IsKey(string c) {
    for (int i = 0; i < KEY_LEN; i++)
        if (key[i] == c)
            return true;
    return false;
}
// 判断是否为字母
bool IsLetter(char c) {
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

//判断是否为a~f字母
bool IsA_F(char c) {
    return c >= 'a' && c <= 'f' || c >= 'A' && c <= 'F';
}

//判断是否为数字
bool IsDigit(char c) {
    return c >= '0' && c <= '9';
}

string lexical(string str) {
    string res;
    char ch;
    int index = -1;
    int l = str.size();
    while (++index < l) {
        ch = str[index];
        string tem;
        if (ch != ' ' && ch != '\t' && ch != '\n') {
            if (IsLetter(ch) || ch == '_') {
                tem += ch;
                while (ch = str[++index], index < l && (IsLetter(ch) || ch == '_' || IsDigit(ch))) {
                    tem += ch;
                }
                index--;
                if (IsKey(tem)) cout << '<' << tem << " , " << "->" << endl;
                else cout << '<' << "0" << " , " << tem << '>' << endl;
                tem = "i";
            } else if (IsDigit(ch)) {
                if (ch == '0') {
                    ch = str[index++];
                    if (ch >= '0' && ch <= '7') {
                        while(ch >= '0' && ch <= '7') {
                            tem += ch;
                            ch = str[index++];
                        }
                        index--;
                        cout<<"<2 , " << tem << ">" <<endl;
                        tem = "i";
                    } else if (ch == 'x'){
                        ch = str[index++];
                        while(IsDigit(ch) || IsA_F(ch)) {
                            tem += ch;
                            ch = str[index++];
                        }
                        index--;
                        cout<<"<3 , " << tem << ">" <<endl;
                    }
                } else {
                    while (IsDigit(ch)) {
                        tem += ch;
                        ch = str[++index];
                    }
                    index--;
                    cout<<"<1 , " << tem << ">" <<endl;
                    tem = "i";
                }
            } else {
                bool flag = false;
                for (int i = 0; i < CHECK_2_LEN; i++) {
                    if (ch == check_2[i]) {
                        cout << "<" << ch << " , ->" << endl;tem += ch;
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    for (int i = 0; i < CHECK_1_LEN; i++) {
                        if (ch == check_1[i]) {
                            string follow = M[ch];
                            tem += ch;
                            ch=str[++index];
                            if (follow.find(ch) != string::npos) {
                                flag = true;
                                cout << "<" << tem + ch << " , ->" << endl;tem += ch;
                            } else {
                                flag = true;
                                cout << "<" << tem << " , ->" << endl;tem += ch;
                            }
                            index--;
                            break;
                        }
                    }
                }
                if (!flag)
                    cout << "<" << ch << " ,无法识别该字符>" << endl;
            }
            res += tem;
        }
    }
    return res;
}
#endif //POC_LEXICAL_1_H
