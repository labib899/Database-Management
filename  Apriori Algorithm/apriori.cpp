#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream inputFile("input.txt");
    int ni, nt, sc; inputFile >> ni >> nt >> sc;
    int trans[nt + 2][ni + 2] = {0};
    for (int i = 1; i <= nt; i++)
    {
        int num; inputFile >> num;
        for (int j = 1; j <= num; j++)
        {
            int item; inputFile >> item;
            trans[i][item] = 1;
        }
    }
    // 1 item
    int C1[ni + 2] = {0};
    for (int i = 1; i <= ni; i++)
    {
        for (int j = 1; j <= nt; j++)
        {
            if (trans[j][i] == 1) C1[i]++;
        }
    }
    int cnt=0;
    for(int i=1;i<=ni;i++)
    {
        if(C1[i]>=sc) 
        {
            cout<<"item: "<<i<<" cnt: "<<C1[i]<<endl;
            cnt++;
        }
    }
    cout<<"1 item, total: "<<cnt<<endl<<endl;
    // 2 items
    set<int> s;
    pair<set<int>, int> ps;
    vector<pair<set<int>, int>> ans;
    for (int i = 1; i <= ni; i++)
    {
        s.insert(i);
        for (int j = i + 1; j <= ni; j++)
        {
            int cnt = 0;
            s.insert(j);
            ps.first = s;
            int flag = 0;
            for (int r = 1; r <= nt; r++)
            {
                for (auto &element : s)
                {
                    if (trans[r][element] == 1) flag=1;
                    else
                    {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1) cnt++;
                flag = 0;
            }
            ps.second = cnt;
            if (cnt >= sc) ans.push_back(ps);
            cnt = 0;
            if (!s.empty())
            {
                auto lastElementIterator = prev(s.end());
                s.erase(lastElementIterator);
            }
        }
        s.clear();
    }
    for(auto x:ans)
    {
        cout<<"items: ";
        for(auto y:x.first) cout<<y<<" ";
        cout<<"cnt: "<<x.second<<endl;
    }
    // 3 or more items
    int len = ans.size();
    int prevlen = 0;
    int sold = 2;
    vector<set<int>> us;
    while (len > prevlen)
    {
        us.clear();
        cout << sold << " items, total: " << len-prevlen << endl << endl;
        set<int> s1,s2;
        for (int i = prevlen; i < len; i++)
        {
            s1 = ans[i].first;
            int n = s1.size();
            for (int j = i + 1; j < len; j++)
            {
                s2 = ans[j].first;
                bool intersect = any_of(s1.begin(), s1.end(),
                                              [&s2](int element)
                                              {
                                                  return s2.find(element) != s2.end();
                                              });
                if (intersect)
                {
                    set_union(s1.begin(), s1.end(), s2.begin(), s2.end(),
                              inserter(s, s.begin()));
                    if(s.size()!=sold+1) continue;
                    int flag = 0, cnt = 0;
                    auto it = find(us.begin(), us.end(), s);
                    if (it == us.end())
                    {
                        us.push_back(s);
                        ps.first = s;
                        for (int r = 1; r <= nt; r++)
                        {
                            for (auto &element : ps.first)
                            {
                                if (trans[r][element] == 1) flag=1;
                                else
                                {
                                    flag = 0;
                                    break;
                                }
                            }
                            if (flag == 1) cnt++;
                            flag = 0;
                        }
                        s.clear();

                        ps.second = cnt;
                        if (cnt >= sc) ans.push_back(ps);
                        cnt = 0;
                    }
                    s.clear();
                }
            }
        }
        prevlen = len;
        len = ans.size();
        if (len > prevlen) sold++;
        for(int i=prevlen;i<len;i++)
        {
            cout<<"items: ";
            for(auto e:ans[i].first) cout<<e<<" ";
            cout<<"cnt: "<<ans[i].second<<endl;
        }
    }
}