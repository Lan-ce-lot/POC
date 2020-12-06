//
// Created by Lance on 2020/12/5.
//

#include <bits/stdc++.h>
#include "grammar_2.h"

using namespace std;
const int MAXX = 550;
grammar G;

/**
 * ��FIRSTVT
 */
map<char, set<char> > FIRSTVT;
map<pair<char, char>, bool> F;
stack<pair<char, char> > S;

void insert(char P, char a) {
    if (!F[{P, a}]) {
        F[{P, a}] = 1;
        S.push({P, a});
    }
}

void getFIRSTVT(grammar G) {
    FIRSTVT.clear();
    F.clear();
    for (auto vn : G.Vn)
        for (auto a : G.P[vn])
            if (is_Vt(a[0]))
                insert(vn, a[0]);
            else if (is_Vt(a[1]))
                insert(vn, a[1]);

    while (!S.empty()) {
        auto top = S.top();
        S.pop();
        for (auto vn : G.Vn)
            for (auto a : G.P[vn])
                if (a[0] == top.first)
                    insert(vn, top.second);
    }
    // ��ά����תΪ����
    for (auto vn : G.Vn)
        for (auto vt : G.Vt)
            if (F[{vn, vt}])
                FIRSTVT[vn].insert(vt);
    // ��ӡ
    cout << "FIRSTVT����:" << endl;
    for (auto it : FIRSTVT) {
        cout << "FIRSTVT(" << it.first << ')' << " : ";
        for (auto setIt : it.second)
            cout << setIt << ' ';
        puts("");
    }
    puts("");
}

/**
 * ��LASTVT
 */
map<char, set<char> > LASTVT;
void getLASTVT(grammar G) {
    LASTVT.clear();
    F.clear();
    for (auto vn : G.Vn)
        for (auto a : G.P[vn])
            if (is_Vt(a[a.size() - 1]))
                insert(vn, a[a.size() - 1]);
            else if (is_Vt(a[a.size() - 2]))
                insert(vn, a[a.size() - 2]);

    while (!S.empty()) {
        auto top = S.top();
        S.pop();
        for (auto vn : G.Vn)
            for (auto a : G.P[vn])
                if (a[a.size() - 1] == top.first)
                    insert(vn, top.second);
    }
    // ��ά����תΪ����
    for (auto vn : G.Vn)
        for (auto vt : G.Vt)
            if (F[{vn, vt}])
                LASTVT[vn].insert(vt);
    // ��ӡ
    cout << "LASTVT����:" << endl;
    for (auto it : LASTVT) {
        cout << "LASTVT(" << it.first << ')' << " : ";
        for (auto setIt : it.second)
            cout << setIt << ' ';
        puts("");
    }
    puts("");
}


/**
 * �������ȹ�ϵ��
 */
map<pair<char, char>, char> relationshipTable;
void getPriorityRelationshipTable(grammar G) {
    for (auto vn : G.Vn) {
        for (auto x : G.P[vn]) {

            for (int i = 0; i < x.size() - 1; i++) {
                // Xi��Xi+1��Ϊ�ս��, ��Xi=Xi+1
                if (is_Vt(x[i]) && is_Vt(x[i + 1]))
                    relationshipTable[{x[i], x[i + 1]}] = '=';
                // i��n-2��Xi��Xi+2��Ϊ�ս������Xi+1Ϊ���ս��, ��Xi=Xi+2:
                if (i <= x.size() - 2 && is_Vt(x[i]) && is_Vt(x[i + 2]) && !is_Vt(x[i + 1]))
                    relationshipTable[{x[i], x[i + 2]}] = '=';
                // XiΪ�ս����Xi+1Ϊ���ս��Xi<FIRSTVT(Xi+1)
                if (is_Vt(x[i]) && !is_Vt(x[i + 1]))
                    for (auto it : FIRSTVT[x[i + 1]])
                        relationshipTable[{x[i], it}] = '<';
                // XiΪ���ս����Xi+1Ϊ�ս��LASTVT(Xi)>Xi+1
                if (!is_Vt(x[i]) && is_Vt(x[i + 1]))
                    for (auto it : LASTVT[x[i]])
                        relationshipTable[{it, x[i + 1]}] = '>';
            }
        }
    }
    // ��ӡ
    cout << "���ȹ�ϵ��\n   ";
    for (auto x : G.Vt) cout << x << "  ";
    puts("");
    for (auto x : G.Vt) {
        cout << x << "  ";
        for (auto y : G.Vt) {
            cout << relationshipTable[{x, y}] << "  ";
        }
        cout << '\n';
    }

}

/**
 * ������ȷ���
 */
void ERROR() {
    cout << "������!!!!!!!!!!" << endl;
}

void operatorPrecedenceAnalysis(grammar G, string str) {
    str = str + "#";
    // top ָ��ջ����jָ����ӽ�ջ�����ս��
    int top = 1, j = 0, index = 0;
    char a;
    char S[MAXX];
    S[top] = '#';
    while (true) {
        a = str[index++];
        j = (is_Vt(S[top]) ? top : top - 1);
        while (relationshipTable[{S[j], a}] == '>') {
            while (true) {
                char Q = S[j];
                j = (is_Vt(S[j - 1] ? j - 1 : j - 2));

                if (relationshipTable[{S[j], Q}] == '<') {
                    break;
                }
            }
            /**
             * ��Լ
             * S[j + 1]...S[k]��Լ��N
             */
            top = j + 1;
            S[top] = G.S;
        }
        if (relationshipTable[{S[j], a}] == '<' || relationshipTable[{S[j], a}] == '=') {
            top++;
            S[top] = a;
        } else ERROR();
        if (a == '#') break;
    }
}

////�õ����ȹ�ϵ
//int relate(int a, int b) {
//    map<char, int> M{
//            {'>', 1},
//            {'<', -1},
//            {'=', 0},
//            {'2', 2},
//            {'3', 3},
//            {'4', 4}};
//    return M[relation[--a][--b]];
//}

int main() {
    G = grammar_read("D:\\work\\clion\\POC\\sy3\\1.txt");

    getFIRSTVT(G);
    getLASTVT(G);
    getPriorityRelationshipTable(G);
    operatorPrecedenceAnalysis(G, "i+i");
    return 0;
}
