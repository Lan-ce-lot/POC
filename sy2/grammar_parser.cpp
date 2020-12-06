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
    string Vn;		//Vn  �ķ��ķ��ս���ż���
    string Vt;		//Vt  �ķ����ս���ż���
    char S{};			//S   ��ʼ����
    map<char, vector<string> > P;//P   ����ʽ
};

// �ķ���ӡ����
void print_G(grammar g) {
    cout << "�ķ� " << endl;
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
    cout << "��ʼ��   " << g.S << endl;
    cout << "���ս�� " << g.Vn << endl;
    cout << "�ս��   " << g.Vt << endl;
}

// �ж�һ���ַ����Ƿ����ַ�c
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

// ���ڶ�ȡһ���ǿո��ַ�
char GetBC(FILE* fpi) {
    char ch;
    do {
        ch = fgetc(fpi);
    } while (ch == ' ');
    return ch;
}

// ����������ݹ�
// ��ȡһ���µķ��ս��
char get_Vn(string str) {
    for (int i = 0; i < 26; i++) {
        char c = (i + 'A');
        if (!exitV(str, c)) return c;
    }
    return ' ';
}

// ������ʽ�Ұ벿�Ƿ����
bool check_Vn_repeat(string s, vector<string> str) {
    for (auto it : str) {
        if (s == it) {
            return true;
        }
    }
    return false;
}

// ******************************************************************
// ����ģ��
// ******************************************************************
map<char, bool> vis;
// �������������ͨ���ж϶Կ�ʼ�����Է��ս���Ƿ�ɴ���жϷ��ս���Ĳ���ʽ�Ƿ����
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
    string tem = ""; // ��¼��ʼ���ɴ���ս��
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
    puts("\n����");
    print_G(g);
}

// ******************************************************************
// ������ݹ�
// ******************************************************************
void remove_left_recursion(grammar &g) {
    // �滻
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

        // ����ֱ����ݹ�
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
    // ����
    simplify(g);
}

//E->T|E+T;
//T->F|T*F;
//F->i|(E);


// ******************************************************************
// ��������
// ��ȡ������
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
// ����һ��
// ******************************************************************
void scanG(FILE* fpi, grammar &g) {
    if (feof(fpi))		return;

    char ch;
    char start;// ��¼����ʽ��ͷ�ķ��ս��
    string tem;// ��¼��Ӧ��ѡʽ

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
// ��FIRST��
// ******************************************************************
map<char, set<char> > FIRST;
void getFIRST(grammar g) {
    // ���������һ���ս��
    for (int i = 0; i < g.Vt.size(); i++) {
        FIRST[g.Vt[i]].insert(g.Vt[i]);
    }
    // ���һ��������һ�����ս����
    // X->a..., ��a����FIRST(X), ��X->@, ��@Ҳ����FIRST(X)               1
    // X->Y..., ��FIRST(Y)/@����FIRST(X)                               2
    // X->Y1Y2Y3...Yi...Yk, FIRST(Yi)����@, ���FIRST(Yi)/@����FIRST(X) 3
    // ������@, ���@Ҳ���� FIRST(X)                                     4

    map<char, set<char> > copy = FIRST; // FIRST���Ŀ���
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
    puts("\nFIRST��");
    for (auto it : FIRST) {
        cout << it.first << ":";
        for (auto itm : it.second)
            cout << itm << ' ';
        puts("");
    }
}

// ******************************************************************
// ��FOLLOW��
// ******************************************************************
map<char, set<char> > FOLLOW;
void getFOLLOW(grammar g) {
    // # ���� FOLLOW(S)
    FOLLOW[g.S].insert('#');
    // A->aBb, ��FIRST(b)\@����FOLLOW(B)
    // A->aB, ��A->aBb��b=>@(FIRST[b]����@), ��FOLLOW(A)����FOLLOW(B)
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

    puts("\nFOLLOW��");
    for (auto it : FOLLOW) {
        cout << it.first << ":";
        for (auto itm : it.second)
            cout << itm << ' ';
        puts("");
    }
}

// ******************************************************************
// ��Ԥ�������
// ******************************************************************

// ���ս�� �ս�� ����ʽ
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
//    cout << "������!!!!!!!!!!!!!!!!!" << endl;
    cout << str << endl;
    return false;
}

// ******************************************************************
// Ԥ�����
// ******************************************************************
bool analysis(grammar g, string str) {
    str += '#';
    // 1.top = a = '#',�����ɹ�
    // 2.top = a != '#', STACK.pop(), index++
    // 3.top�Ƿ��ս��
    // ��table[top, a]���һ������ʽ, STACK.pop(), ����ʽ�Ҳ������ջ, (����Ϊ������ʲô��ջ)
    // ��table[top, a]��ų�����־�����ERROR
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
// �ʷ�������ģ��
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

// �жϹؼ���
bool IsKey(string c) {
    for (int i = 0; i < KEY_LEN; i++)
        if (key[i] == c)
            return true;
    return false;
}
// �ж��Ƿ�Ϊ��ĸ
bool IsLetter(char c) {
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

//�ж��Ƿ�Ϊa~f��ĸ
bool IsA_F(char c) {
    return c >= 'a' && c <= 'f' || c >= 'A' && c <= 'F';
}

//�ж��Ƿ�Ϊ����
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
                    cout << "<" << ch << " ,�޷�ʶ����ַ�>" << endl;
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
            cout<<"�ļ�·������\n";return 0;
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
    puts("\n������ݹ�");

    remove_left_recursion(g);

    puts("\n��ȡ������");
    remove_left_gene(g);

    // �������
    getFIRST(g);
    getFOLLOW(g);
    getTable(g);

    FILE* fpin2;
    if((fpin2=fopen(R"(D:\work\clion\POC\sy2\jz.txt)","r"))==NULL) {
        cout<<"�ļ�·������\n";
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

    string test_in;

    copy = query;
    for (auto &it : query) it = lexical(it);
    
    for (int i = 0; i < query.size(); i++) {
        cout << copy[i] << endl;
        cout << (analysis(g, query[i]) ? "��ȷ" : "����") << endl;
    }
    return 0;
}