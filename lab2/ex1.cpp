#include <climits>
#include <iostream>
using namespace std;


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

int res(int price[], int n, int k)
{

    int profit[k+1],sold[k+1];
    for(int i =0; i<k+1; i++){
        profit[i] = 0;
        sold[i] = INT_MIN;
    }

	for (int j = 0; j < n; j++) {
		for (int i = 1; i <= k; i++) {
			sold[i] = max(sold[i], profit[i - 1] - price[j]);
			profit[i] = max(profit[i], price[j] + sold[i]);
		}
	}

	return profit[k];
}
 
int main()
{

    int N = readLong();
    int K = readLong();

    if(N < 1 || N > 100000 || K < 1 || K > 1000) return 0;
    int arr[N];
    for(int i =0;i<N;i++){
        arr[i] = readLong();
        if(arr[i] < 1 || arr[i] > 10000) return 0;
    }

 
    cout << res(arr, N, K) << endl;
 
    return 0;
}