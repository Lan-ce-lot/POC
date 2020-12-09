#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<stack>
#include <algorithm>

using namespace std;
#define debug(a) cout << "*" << a << "*" << endl

struct grammar {
    string Vn;		//Vn  文法的非终结符号集合
    string Vt;		//Vt  文法的终结符号集合
    char S{};			//S   开始符号
    map<char, vector<string> > P;//P   产生式
};

// 文法打印函数
void print_G(grammar g) {
    cout << "文法 " << endl;
    for (int i = 0; i < g.Vn.size(); i++) {
        char c = g.Vn[i];cout << c << "->";
        for (int j = 0; j < g.P[c].size(); j++) {
            if (j != 0) {
                cout << '|' ;
            }
            cout << g.P[c][j] ;
        }
        puts("");
    }
    cout << "开始符   " << g.S << endl;
    cout << "非终结符 " << g.Vn << endl;
    cout << "终结符   " << g.Vt << endl;
}

// 判断一个字符串是否有字符c
bool exitV(string str, char c) {
    for (auto i : str)
        if (i == c)
            return true;
    return false;
}

bool is_Vt(char c) {
    string Vt = "!@$%^&*()_+-={}[]<>?/";
    for (int i = 0; i < Vt.size(); i++) {
        if (Vt[i] == c) return true;
    }
    if (c >= 'a' && c <= 'z') return true;
    return false;
}

// 用于读取一个非空格字符
char GetBC(FILE* fpi) {
    char ch;
    do {
        ch = fgetc(fpi);
    } while (ch == ' ');
    return ch;
}

// 用于消除左递归
// 获取一个新的非终结符
char get_Vn(string str) {
    for (int i = 0; i < 26; i++) {
        char c = (i + 'A');
        if (!exitV(str, c)) return c;
    }
    return ' ';
}

// 检查产生式右半部是否存在
bool check_Vn_repeat(string s, vector<string> str) {
    for (auto it : str) {
        if (s == it) {
            return true;
        }
    }
    return false;
}

// ******************************************************************
// 化简模块
// ******************************************************************
map<char, bool> vis;
// 深度优先搜索，通过判断对开始符而言非终结符是否可达，来判断非终结符的产生式是否多余
void dfs(grammar g, char c, string &res) {
    for (int i = 0; i < g.P[c].size(); i++) {
        for (int j = 0; j < g.P[c][i].size(); j++) {
            char tem_c = g.P[c][i][j];
            if (tem_c >= 'A' && tem_c <= 'Z' && vis[tem_c] == 0) {
                vis[tem_c] = true;
                res += tem_c;
                dfs(g, tem_c, res);
            }
        }
    }
}

void simplify(grammar &g) {
    string tem = ""; // 记录开始符可达的终结符
    vis.clear();
    tem += g.S;
    vis[g.S] = true;
    for (int i = 0; i < g.P[g.S].size(); i++) {

        for (int j = 0; j < g.P[g.S][i].size(); j++) {
            char c = g.P[g.S][i][j];
            if (vis[c] == 0 && c >= 'A' && c <= 'Z') {
                tem += c;
                vis[c] = true;
            }
        }
    }
    string st = tem;
    for (int i = 0; i < tem.size(); i++)
        dfs(g, tem[i], st);

    for (int i = 0; i < g.Vn.size(); i++) {
        if (!exitV(st, g.Vn[i])) {
            g.P[g.Vn[i]].clear();
        }
    }
    g.Vn = st;
    puts("\n化简");
    print_G(g);
}

// ******************************************************************
// 消除左递归
// ******************************************************************
void remove_left_recursion(grammar &g) {
    // 替换
    grammar new_g;
    new_g.S = g.S, new_g.Vn = g.Vn, new_g.Vt = g.Vt;

    for (int i = 0; i < g.Vn.size(); i++) {
        char c = g.Vn[i]; // pi
        for (int j = 0; j <= i - 1; j++) {

            char tem = g.Vn[j]; // pj target
            for (int k = 0; k < g.P[c].size(); k++) {
                if (g.P[c][k].find(tem, 0) == 0) {
                    for (int z = 0; z < g.P[tem].size(); z++) {
                        new_g.P[c].push_back(g.P[tem][z] + g.P[c][k].substr(1, g.P[c][k].size() - 1));
                    }
                }
                else if (!check_Vn_repeat(g.P[c][k], new_g.P[c])) {

                    new_g.P[c].push_back(g.P[c][k]);
                }

            }
            g.P[c] = new_g.P[c];
            new_g.P[c].clear();
        }

        // 消除直接左递归
        map<char, vector<string> > tem_p;
        int tem_len = g.Vn.size();
        for (int z = 0; z < tem_len; z++) {
            tem_p.clear();
            char c = g.Vn[z];
            for (int j = 0; j < g.P[c].size(); j++) {
                if (g.P[c][j][0] == c) {
                    char new_c = get_Vn(g.Vn);
                    g.Vn += new_c;
                    for (int k = 0; k < g.P[c].size(); k++) {
                        if (k != j && g.P[c][k][0] != c) {
                            g.P[c][k] += new_c;
                            tem_p[c].push_back(g.P[c][k]);
                        } else if (g.P[c][k][0] == c) {
                            g.P[new_c].push_back(g.P[c][k].substr(1, g.P[c][k].size() - 1) + new_c);
                        }
                    }

                    g.P[new_c].push_back("@");
                    if (!exitV(g.Vt, '@')) {
                        g.Vt += "@";
                    }
                    g.P[c].clear();
                    g.P[c] = tem_p[c];
                    break;
                }
            }
        }

    }
    print_G(g);
    // 化简
    simplify(g);
}

//E->T|E+T;
//T->F|T*F;
//F->i|(E);


// ******************************************************************
// 消除回溯
// 提取左因子
// ******************************************************************
void remove_left_gene(grammar &g) {
    map<char, vector<int> > m;
    for (int i = 0; i < g.Vn.size(); i++) {
        char c = g.Vn[i];
        m.clear();
        for (int j = 0; j < g.P[c].size(); j++) {
            m[g.P[c][j][0]].push_back(j);
        }

        for (auto it : m) {
            if (it.second.size() >= 2) {
                char new_Vn = get_Vn(g.Vn);
                g.Vn += new_Vn;
//				debug(new_Vn);
                for (auto it1 : it.second) {
                    string str = g.P[c][it1].substr(1, g.P[c][it1].size() - 1);
                    g.P[new_Vn].push_back(str);

                }
                for (auto it1 : it.second) {
                    g.P[c].erase(g.P[c].begin() + it1);
                }
                string s(1,new_Vn);
                g.P[c].push_back(it.first + s);
            }
        }
    }
    print_G(g);
//    simplify(g);
}


// ******************************************************************
// 读入一句
// ******************************************************************
void scanG(FILE* fpi, grammar &g) {
    if (feof(fpi))		return;

    char ch;
    char start;// 记录产生式开头的非终结符
    string tem;// 记录对应候选式

    ch = GetBC(fpi);
    if (ch >= 'A' && ch <= 'Z') {
        start = ch;
        if (!exitV(g.Vn, ch)) {
            g.Vn += ch;
//			count_Vn++;
            ch = GetBC(fpi);
            if (ch == '-' && GetBC(fpi) == '>') {
                while (true) {
                    ch = GetBC(fpi);
                    if (ch == ';' || ch == '\n') break;
                    if (is_Vt(ch) && !exitV(g.Vt, ch)) { //
                        g.Vt += ch;
                    }
                    if (ch == '|') {
                        g.P[start].push_back(tem);
                        tem = "";
                    } else tem += ch;
                }
            }
            g.P[start].push_back(tem);
        } else {
            ch = GetBC(fpi);
            if (ch == '-' && GetBC(fpi) == '>') {
                while (true) {
                    ch = GetBC(fpi);
                    if (ch == ';' || ch == '\n') break;
                    if (ch >= 'a' && ch <= 'z' && !exitV(g.Vt, ch)) { //
                        g.Vt += ch;
                    }
                    if (ch == '|') {
                        g.P[start].push_back(tem);
                        tem = "";
                    } else tem += ch;
                }
            }
            g.P[start].push_back(tem);
        }
    }
}

// ******************************************************************
// 求FIRST集
// ******************************************************************
map<char, set<char> > FIRST;
void getFIRST(grammar g) {
    // 如果符号是一个终结符
    for (int i = 0; i < g.Vt.size(); i++) {
        FIRST[g.Vt[i]].insert(g.Vt[i]);
    }
    // 如果一个符号是一个非终结符号
    // X->a..., 把a加入FIRST(X), 若X->@, 把@也加入FIRST(X)               1
    // X->Y..., 把FIRST(Y)/@加入FIRST(X)                               2
    // X->Y1Y2Y3...Yi...Yk, FIRST(Yi)都含@, 则把FIRST(Yi)/@加入FIRST(X) 3
    // 若都有@, 则把@也加入 FIRST(X)                                     4

    map<char, set<char> > copy = FIRST; // FIRST集的拷贝
    while (true) {

        for (int i = 0; i < g.Vn.size(); i++) {
            char c = g.Vn[i];
            for (int j = 0; j < g.P[c].size(); j++) {
                for (int k = 0; k < g.P[c][j].size(); k++) {
                    bool have_empty = false;
                    char tem = g.P[c][j][k];
                    // 1
                    if (k == 0 && is_Vt(tem)) {
                        FIRST[c].insert(tem);
                        break;
                    } else if (exitV(g.Vn, tem)) {
                        for (auto it : FIRST[tem])
                            if (it != '@') FIRST[c].insert(it);
                            else have_empty = true;
                        if (!have_empty) break;
                    }
                    if (k == g.P[c][j].size() - 1 && exitV(g.Vn, tem) && have_empty) {
                        FIRST[c].insert('@');
                    }
                }
            }
        }
        if (copy == FIRST) break;
        copy = FIRST;
    }
    puts("\nFIRST集");
    for (auto it : FIRST) {
        cout << it.first << ":";
        for (auto itm : it.second)
            cout << itm << ' ';
        puts("");
    }
}

// ******************************************************************
// 求FOLLOW集
// ******************************************************************
map<char, set<char> > FOLLOW;
void getFOLLOW(grammar g) {
    // # 至于 FOLLOW(S)
    FOLLOW[g.S].insert('#');
    // A->aBb, 把FIRST(b)\@加入FOLLOW(B)
    // A->aB, 或A->aBb而b=>@(FIRST[b]包含@), 把FOLLOW(A)加入FOLLOW(B)
    map<char, set<char> > copy = FOLLOW;
    while (true) {
        for (int i = 0; i < g.Vn.size(); i++) {
            char c = g.Vn[i];
            for (int j = 0; j < g.P[c].size(); j++) {
                for (int k = 0; k < g.P[c][j].size(); k++) {
                    char tem = g.P[c][j][k];
                    if (k < g.P[c][j].size() - 1 && exitV(g.Vn, tem)) {
                        for (auto it : FIRST[g.P[c][j][k + 1]])
                            if (it != '@')
                                FOLLOW[tem].insert(it);
                    }
                    if (k == g.P[c][j].size() - 1 && exitV(g.Vn, tem)) {
                        for (auto it : FOLLOW[c])
                            FOLLOW[tem].insert(it);
                    }
                    if (k < g.P[c][j].size() - 1 && exitV(g.Vn, tem)) {
                        if (FIRST[g.P[c][j][k + 1]].count('@')) {
                            for (auto it : FOLLOW[c])
                                FOLLOW[tem].insert(it);
                        }
                    }
                }
            }
        }
        if (copy == FOLLOW) break;
        copy = FOLLOW;
    }

    puts("\nFOLLOW集");
    for (auto it : FOLLOW) {
        cout << it.first << ":";
        for (auto itm : it.second)
            cout << itm << ' ';
        puts("");
    }
}

// ******************************************************************
// 建预测分析表
// ******************************************************************

// 非终结符 终结符 产生式
map<pair<char, char>, string> table;

void getTable(grammar g) {
// A->a FIRST(a)
// A->@ FOLLOW(A)
    g.Vt += '#';
    for (int i = 0; i < g.Vn.size(); i++) {
        char vn = g.Vn[i];
        for (int j = 0; j < g.P[vn].size(); j++) {
            char tem = g.P[vn][j][0];
            if (tem != '@')
                for (auto it : FIRST[tem])
                    table[{vn, it}] = g.P[vn][j];
            else
                for (auto it : FOLLOW[vn])
                    table[{vn, it}] = g.P[vn][j];
        }
    }
    cout << "\n  ";
    for (int i = 0; i < g.Vt.size(); i++) {
        printf("%-7c", g.Vt[i]);
    }
    puts("");
    for (int i = 0; i < g.Vn.size(); i++) {
        cout << g.Vn[i] << ":";
        for (int j = 0; j < g.Vt.size(); j++) {
            cout.width(7);
            cout.setf(ios::left);
            cout << table[{g.Vn[i], g.Vt[j]}];
        }
        puts("");
    }

}
bool error(string str) {
//    cout << "出错啦!!!!!!!!!!!!!!!!!" << endl;
    cout << str << endl;
    return false;
}

// ******************************************************************
// 预测分析
// ******************************************************************
bool analysis(grammar g, string str) {
    str += '#';
    // 1.top = a = '#',分析成功
    // 2.top = a != '#', STACK.pop(), index++
    // 3.top是非终结符
    // 若table[top, a]存放一个产生式, STACK.pop(), 产生式右部反序进栈, (若右为空则不推什么进栈)
    // 若table[top, a]存放出错标志则调用ERROR
    stack<char> STACK;
    int index = 0;
    STACK.push('#');
    STACK.push(g.S);
    bool flag = true;
    while (flag) {
        char top = STACK.top();
        if (is_Vt(top)) {
            if (top == str[index]) {
                STACK.pop();
                index++;
            } else {
                return error(str);
            }
        } else if (top == '#') {
            if (top == str[index]) flag = false;
            else {
                return error(str);
            }
        } else if (!table[{top, str[index]}].empty()) {
            STACK.pop();
            string tem = table[{top, str[index]}];
            reverse(tem.begin(), tem.end());
            if (tem != "@")
                for (int i = 0; i < tem.size(); i++)
                    STACK.push(tem[i]);
        } else {
            return error(str);
        }


    }
    cout << str << endl;
    return true;
}

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

int main() {

    FILE * fpin;

    while (true) {
        if((fpin=fopen(R"(D:\work\clion\POC\sy2\sy2.txt)","r"))!=NULL) break;
        else {
            cout<<"文件路径错误\n";return 0;
        }
    }
    grammar g;

    char ch;
    do {
        ch = GetBC(fpin);
    } while (ch <= 'A' || ch >= 'Z');
    g.S = ch;
    fseek(fpin, -1L, 1);

    while (!feof(fpin)) {
        scanG(fpin, g);
    }
    print_G(g);
    puts("\n消除左递归");

    remove_left_recursion(g);

    puts("\n提取左因子");
    remove_left_gene(g);

    // 读入句子
    getFIRST(g);
    getFOLLOW(g);
    getTable(g);

    FILE* fpin2;
    if((fpin2=fopen(R"(D:\work\clion\POC\sy2\jz.txt)","r"))==NULL) {
        cout<<"文件路径错误\n";
        return 0;
    }
    string str = "";
    vector<string> query, copy;
    while ((ch) != EOF) {
        str = "";
        while ((ch = GetBC(fpin2)) != ';') {
            if (ch == EOF) break;
            str += ch;
        }
        query.push_back(str);
        if (ch == EOF) break;
        ch = GetBC(fpin2);
    }

//    string test_in;

    copy = query;
    for (auto &it : query) it = lexical(it);

    for (int i = 0; i < query.size(); i++) {
        cout << copy[i] << endl;
        cout << (analysis(g, query[i]) ? "正确" : "错误") << endl;
    }
    return 0;
}
