#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

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
bool IsKey(string str) {
    for (int i = 0; i < KEY_LEN; i++)
        if (key[i] == str)
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

void scan(FILE *fpin) {
    char ch;
    while ((ch = fgetc(fpin)) != EOF) {
        string tem = "";
        if (ch != ' ' && ch != '\t' && ch != '\n') {

            if (IsLetter(ch) || ch == '_') {
                tem += ch;
                while ((ch = fgetc(fpin)) != EOF && (IsLetter(ch) || ch == '_' || IsDigit(ch))) {
                    tem += ch;
                }
                fseek(fpin, -1L, SEEK_CUR);
                if (IsKey(tem)) cout << '<' << tem << " , " << "->" << endl;
                else cout << '<' << "0" << " , " << tem << '>' << endl;
            } else if (IsDigit(ch)) {
                if (ch == '0') {
                    ch = fgetc(fpin);
                    if (ch >= '0' && ch <= '7') {
                        while (ch >= '0' && ch <= '7') {
                            tem += ch;
                            ch = fgetc(fpin);
                        }
                        fseek(fpin, -1L, 1);
                        cout << "<2 , " << tem << ">" << endl;
                    } else if (ch == 'x') {
                        ch = fgetc(fpin);
                        while (IsDigit(ch) || IsA_F(ch)) {
                            tem += ch;
                            ch = fgetc(fpin);
                        }
                        fseek(fpin, -1L, 1);
                        cout << "<3 , " << tem << ">" << endl;
                    }
                } else {
                    while (IsDigit(ch)) {
                        tem += ch;
                        ch = fgetc(fpin);
                    }
                    fseek(fpin, -1L, 1);
                    cout << "<1 , " << tem << ">" << endl;
                }
            }
            else {
                bool flag = false;
                for (int i = 0; i < CHECK_2_LEN; i++) {
                    if (ch == check_2[i]) {
                        cout << "<" << ch << " , ->" << endl;
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    for (int i = 0; i < CHECK_1_LEN; i++) {
                        if (ch == check_1[i]) {
                            string follow = M[ch];
                            tem += ch;
                            ch = fgetc(fpin);
                            if (follow.find(ch) != string::npos) {
                                flag = true;
                                cout << "<" << tem + ch << " , ->" << endl;
                            } else {
                                flag = true;
                                cout << "<" << tem << " , ->" << endl;
                                fseek(fpin, -1L, SEEK_CUR);
                            }
//
                            break;
                        }
                    }
                }
                if (!flag)
                    cout << "<" << ch << " ,无法识别该字符>" << endl;
            }
        }
    }
}

int main() {
    FILE *fpin;
    cout << "词法分析器输出：" << endl;
    while (true) {
        if ((fpin = fopen(R"(D:\work\clion\POC\sy1\1.txt)", "r")) != nullptr)
            break;
        else
            cout << "文件路径错误\n";
        return 0;
    }
    printf("0.标识符 1.十进制 2.八进制 3:十六进制\n");
    scan(fpin);
//   system("pause");
    fclose(fpin);
    return 0;
}
