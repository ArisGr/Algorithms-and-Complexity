#include <bits/stdc++.h> 
using namespace std; 

int gcd(int a, int b) 
{ 

    int result = min(a, b); 
    while (result > 0) { 
        if (a % result == 0 && b % result == 0) { 
            break; 
        } 
        result--; 
    } 
  

    return result; 
} 
  

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


class DSU { 
    int* parent; 
    int* rank; 
  
public: 
    DSU(int n) 
    { 
        parent = new int[n]; 
        rank = new int[n]; 
  
        for (int i = 0; i < n; i++) { 
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
    vector<vector<double> > edgelist; 
    int V; 
    double a;
    double b;
    double c;
  
public: 
    Graph(int V) { this->V = V; } 

    double profit() {return this->a; } 
    double weight() {return this->b; } 

    void addEdge(double x, double y, double w,double p,double st,double c) 
    { 
        edgelist.push_back({ st, p, w, x, y }); 
        this->c = c;
    } 
  
    bool kruskals_mst() 
    { 

        sort(edgelist.begin(), edgelist.end());
        reverse(edgelist.begin(),edgelist.end());
  

        DSU s(V); 
        double con;
        double weights= 0;
        double profits = 0;

        for (auto edge : edgelist) {
            double st = edge[0]; 
            double p = edge[1];
            double w = edge[2]; 
            double x = edge[3]; 
            double y = edge[4]; 
            con = this->c;

            if (s.find(x) != s.find(y)) { 
                s.unite(x, y); 
                weights +=  w; 
                profits += p;

            } 
        } 
        double dam = profits - (con*weights); 
        if(dam >= 0) {
            this->a = profits;
            this->b = weights;
            return true;
        }
        else return false;
    } 
}; 
  

int main() 
{ 
    int N = readLong();
    int K = readLong();
    double a,b = 0;
    double x[K],y[K],p[K],w[K];
    double s[K];
    Graph g(K);
    for(int i=0; i<K; i++){
        x[i] = readLong();
        y[i] = readLong();
        p[i] = readLong();
        w[i] = readLong();
        if(x[i] > 50000 || x[i]<1) return 0;
        if(y[i] > 200000 || y[i]<1) return 0;
        if(p[i] > 200 || p[i]<1) return 0;
        if(w[i] > 200 || w[i]<1) return 0;
    }

    double left = 0;
    bool bo;
    double right = 200;
    double mid = (left + right) / 2;

    while(left <= right){
        for(int i=0;i<K;i++){
            s[i] = p[i] - (mid*w[i]);
            g.addEdge(x[i],y[i],w[i],p[i],s[i],mid);
        }
        bo = g.kruskals_mst();
        if(bo){
            left = mid + 0.0000001;
            a = g.profit();
            b = g.weight();
        }
        else{
            right = mid - 0.0000001;
        }
        mid = (left + right) / 2;
    }
    cout << a/gcd(a,b) << " " << b/gcd(a,b) << endl;
    return 0; 
}