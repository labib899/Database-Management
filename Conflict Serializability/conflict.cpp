#include <bits/stdc++.h>
using namespace std;

vector<set<int>> graph;
vector<int> color;
bool cycle=false;

void dfs(int node,int p)
{
    color[node]=1;
    for(auto c:graph[node])
    {
        if(color[c]==1) 
        {
            cycle=true;
            cout<<"detected cycle from node "<<node<<" to node "<<c<<endl;
        }
        if(color[c]==0) dfs(c,node);
    }
    color[node]=2;
}


int main()
{
    freopen("input2.txt", "r", stdin);
	vector<pair<int,string>> trans;
	while (true)
	{
		string str; cin>>str;
        if(str=="end") break;
        int tid; cin>>tid;
        trans.push_back({tid,str});
	}

	set<int> s;
	for (int i = 0; i < trans.size(); i++) s.insert(trans[i].first);
    int n=s.size();
	graph.resize(n+1);
    color.resize(n+1,0);

	for (int i = 0; i < trans.size(); i++)
	{   
        int tid1=trans[i].first;
        char operation1=trans[i].second[0];
        string data1=trans[i].second.substr(1);
		for (int j = i + 1; j < trans.size(); j++)
		{   
            int tid2=trans[j].first;
            char operation2=trans[j].second[0];
            string data2=trans[j].second.substr(1);
			if (data1!=data2) continue; 
			else
			{
				if (operation1 == 'r' and operation2 == 'r') continue;
				else
				{
					if(tid1!=tid2) graph[tid1].insert(tid2);
				}
			}
		}
	}

    cycle=false;
    for(int i=1;i<=n;i++)
    {
        if(color[i]==0) dfs(i,-1);
    }
    if(cycle) cout<<"Contains cycle"<<endl;
    else cout<<"Does not contain cycle"<<endl;

    // for(int i=1;i<=n;i++)
    // {
    //     cout<<"node i: "<<i<<endl;
    //     for(auto x:graph[i]) cout<<x<<" ";
    //     cout<<endl;
    // }
}