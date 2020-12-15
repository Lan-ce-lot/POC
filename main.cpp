#include<fstream>
#include<queue>
#include<set>
#include<string>
#include<map>
#include<iostream>
using namespace std;

struct Grammer {
    set<char> Vn;//终结符
    set<char> Vt;//非终结符
    char S;
    map<char, string> grammer_map;
};

void read(Grammer &g)
{
    //Grammer g;
    ifstream readFile("E:\\编译原理\\g2.txt");
    string s, t, tmp1, tmp2, tmp3;
    queue<string> q;
    while (getline(readFile, s))
    {
        q.push(s);
    }

    while (!q.empty())
    {
        t = q.front();
        q.pop();
        for (int i = 0; i < t.length(); i++)
        {
            if (t[i] <= 'z'&&t[i] >= 'a')
            {
                if (g.Vn.find(t[i]) == g.Vn.end())//重复的终结符不要放入Vn中
                {
                    g.Vn.insert(t[i]);
                }
            }
            if (t[i] <= 'Z'&&t[i] >= 'A')
            {
                if (g.Vt.find(t[i]) == g.Vt.end())//重复的非终结符不要放入Vt中
                {
                    g.Vt.insert(t[i]);
                }
                if (i == 0)
                {
                    if (g.grammer_map.find(t[i]) == g.grammer_map.end())
                    {
                        tmp1 = t.substr(3, t.length() - 4);
                        g.grammer_map[t[i]] = tmp1;
                    }
                    else
                    {
                        tmp1 = t.substr(3, t.length() - 4);
                        tmp2 = g.grammer_map[t[i]];
                        tmp3 = tmp2 + "|" + tmp1;
                        g.grammer_map[t[i]] = tmp3;
                    }
                }
            }
        }
    }
}

string substitution(string t1, string t2)
{
    vector<string> s;
    int t=0;
    for (int i = 0; i < t1.length(); i++)
    {
        if (t1[i] == '|')
        {
            string tmp = t1.substr(t, i - t);
            t = i+1;
            s.push_back(tmp);
        }
    }
    s.push_back(t1.substr(t, t1.length() - t));
    vector<string>::iterator it;
    string t3;
    for (it = s.begin(); it != s.end(); )
    {
        t3+= (*it) + t2;
        it++;
        if (it != s.end())
            t3 += "|";
    }
    //cout<<t3<< endl;
    return t3;
}

//顺序是Q，R，S
void Elimination(Grammer g)
{
    //代入
    set<char>::iterator it1, it2;
    string tmp,sub_string1,sub_string2, sub_string3,result;
    for (it1 = g.Vt.begin(); it1 != g.Vt.end(); it1++)
    {
        tmp = g.grammer_map[*it1];
        for (int i = 0; i < tmp.length(); i++)
        {
            if (g.grammer_map.find(tmp[i]) != g.grammer_map.end())//有没有相应的非终结符
            {
                int t=i;//用来定位|的位置
                while (tmp[t] != '|')
                    t++;
                sub_string1 = tmp.substr(t, tmp.length() - t);
                sub_string2 = tmp.substr(i+1,t-i-1);
                sub_string3 = g.grammer_map[tmp[i]];
                result = substitution(sub_string3, sub_string2) + sub_string1;
                g.grammer_map[*it1] = result;
            }
        }
    }
    //消除左递归
    map<char, string>::iterator it;
    for (it = g.grammer_map.begin(); it != g.grammer_map.end(); it++)
    {
        int flag = false;//是否出现左递归的标志
        int t = 0;
        string t1 = (*it).second;
        //t是非终结符的位置，i是‘|’的位置
        int i;
        for (i = 0; i < t1.length(); i++)
        {
            if (t1[i] == '|')
            {
                string tmp = t1.substr(t, i - t);
                if (t1[0] == (*it).first)//出现了左递归
                {
                    flag = true;
                    break;
                }
                t = i + 1;
            }
        }
        if (flag)
        {
            char replace;
            while (1)
            {
                int j = 1;
                if (g.grammer_map.find((*it).first + j) == g.grammer_map.end())
                {
                    replace = (*it).first + j;
                    break;
                }
                j++;
            }
            //t是非终结符的位置，i是‘|’的位置
            sub_string1 = t1.substr(i + 1, t1.length() - i);//后半部分
            sub_string2 = t1.substr(t + 1, i - t - 1);
            string tmp2;
            tmp2.push_back(replace);
            g.grammer_map[(*it).first] = substitution(sub_string1, tmp2);
            result = sub_string2 + replace + "|@";
            g.grammer_map[replace] = result;
        }
    }
    //map<char, string>::iterator it;
    for (it = g.grammer_map.begin(); it != g.grammer_map.end(); it++)
    {
        cout << (*it).first << "->" << (*it).second << endl;
    }
}

int main()
{
    Grammer g;
    read(g);
    //map<char, string>::iterator it;
    //for (it = g.grammer_map.begin(); it != g.grammer_map.end(); it++)
    //cout << (*it).first << "->" << (*it).second<<endl;
    Elimination(g);
//	system("pause");
    return 0;
}

