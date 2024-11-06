#include <bits/stdc++.h>
#include <vector>
#include <cmath>
using namespace std;


class DSU { 
    int* parent; 
    int* rank; 
  
public: 
    DSU(int n) 
    { 
        parent = new int[n+1];  
        rank = new int[n+1];     
  
        for (int i = 1; i <= n; i++) {  
            parent[i] = -1; 
            rank[i] = 1; 
        } 
    } 
  
    int find(int i) 
    { 
        if (parent[i] == -1) 
            return i; 
  
        return parent[i] = find(parent[i]); 
    } 
  

    void unite(int x, int y) 
    { 
        int s1 = find(x); 
        int s2 = find(y); 
  
        if (s1 != s2) { 
            if (rank[s1] < rank[s2]) { 
                parent[s1] = s2; 
            } 
            else if (rank[s1] > rank[s2]) { 
                parent[s2] = s1; 
            } 
            else { 
                parent[s2] = s1; 
                rank[s1] += 1; 
            } 
        } 
    } 
}; 
  
class Graph { 
    vector<vector<int> > edgelist; 
    int V; 
  
public: 
    Graph(int V) { this->V = V; } 
  

    void addEdge(int x, int y, int w) 
    { 
        edgelist.push_back({ w, x, y }); 
    } 
  
    void kruskals_mst(vector<int> &edg) 
    { 
    
        sort(edgelist.begin(), edgelist.end()); 
  

        DSU s(V); 
        int ans = 0; 

        for (auto edge : edgelist) { 
            int w = edge[0]; 
            int x = edge[1]; 
            int y = edge[2]; 
  

            if (s.find(x) != s.find(y)) { 
                s.unite(x, y); 
                ans += w; 
                edg.push_back(w);
            } 
        } 
    } 
}; 

#define BSIZE 1<<15
char buffer[BSIZE];
long bpos = 0L, bsize = 0L; 
long readLong()
{
	long d = 0L, x = 0L;
	char c;

	while (1)
  {
		if (bpos >= bsize)
    {
			bpos = 0;
			if (feof(stdin)) return x;
			bsize = fread(buffer, 1, BSIZE, stdin);
		}
		c = buffer[bpos++];
		if (c >= '0' && c <= '9') { x = x*10 + (c-'0'); d = 1; }
		else if (d == 1) return x;
	} 
	return -1;
}

int merge(int* parent, int x)
{
    if (parent[x] == x)
        return x;
    return merge(parent, parent[x]);
}
 
int connectedcomponents(int n, vector<vector<int> >& edges, Graph &g)
{
    int check = 0, nod = 0, prev_nod = 0;
    int parent[n+1]; 
    for (int i = 1; i <= n; i++) { 
        parent[i] = i; 
    }
    for (auto x : edges) {
        parent[merge(parent, x[0])] = merge(parent, x[1]);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) { 
        ans += (parent[i] == i);
    }
    for (int i = 1; i <= n; i++) { 
        parent[i] = merge(parent, parent[i]);
    }
    map<int, list<int> > m;
    for (int i = 1; i <= n; i++) {
        m[parent[i]].push_back(i);
    }
    for (auto it = m.begin(); it != m.end(); it++) {
        list<int> l = it->second;
        for (auto x : l) {
            nod = x;
        }
        if(check == 0){
            check = 1;
            prev_nod = nod;
        }
        else{
            g.addEdge(prev_nod, nod, -2100000000);
        }

    }
    return ans;
}
 
int main()
{

    int N = readLong();
	int M = readLong();
    int K = readLong();

    if(N < 1 || N > 3*pow(10,5) || M < 1 || M > 3*pow(10,5) || K < 1 || K > 3*pow(10,5)) return 0;

    if(K >= M) {
        cout << "infinity" << endl;
        return 0;
    }
    Graph g(N); 
    vector<int> edging;
	vector<vector<int>> e;
    int first,second,time;
    for(int i =0;i<M;i++){
        first = readLong();
        second = readLong();
        time = readLong();
        if(time > 2*pow(10,9) || time < 1) return 0;
        e.push_back( { first,second});
        g.addEdge(first,second,-time);
    }
    int a = connectedcomponents(N, e, g);
    g.kruskals_mst(edging); 
    for(int i =0; i <edging.size(); i++){
        edging[i] = -edging[i];
    }
    sort(edging.begin(), edging.end());
    if(edging[K] >= 2100000000){
        cout << "infinity" << endl;
        return 0;
    }
    else cout<< edging[K] << endl;

    return 0;
}