#include <bits/stdc++.h>
using namespace std;
 

void heapify(int arr[], int N, int i)
{
 
    int largest = i;
 
    int l = 2 * i + 1;
 
    int r = 2 * i + 2;
 
    if (l < N && arr[l] > arr[largest])
        largest = l;
 

    if (r < N && arr[r] > arr[largest])
        largest = r;
 

    if (largest != i) {
        swap(arr[i], arr[largest]);

        heapify(arr, N, largest);
    }
}
 

void heapSort(int arr[], int N)
{
 
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(arr, N, i);
 

    for (int i = N - 1; i > 0; i--) {

        swap(arr[0], arr[i]);
 
        heapify(arr, i, 0);
    }
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

bool check_median(int arr[],int N,int K,int median){
    int check[N];

    if(arr[0] >= median) check[0] = 1;
    else check[0] = -1;

    for(int i=1;i<N;i++){
        if(arr[i] >= median){
            check[i] = 1;
        }
        else check[i] = -1;

        check[i] += check[i-1];
    }

    
    if(check[K-1] > 0) return true;
    int min = 0;

    for(int j=K;j<N;j++){
        if(check[j] > 0) return true;

        else{
            if(min > check[j-K]) min = check[j-K];

            if(check[j] - min > 0) return true;  
        }
    }
    return false;
    
}

int main()
{

    
    int N = readLong();
    int K = readLong();
    if(K > 200000 || N > 200000 || K < 1 || N < 1 || N < K  ) return 0;
    int arr[N];  
    int arr2[N];
    for(int i =0;i<N;i++){
        arr[i] = readLong();
        if(arr[i] > N || arr[i] < 1) return 0;
        arr2[i] = arr[i];
    }   

    heapSort(arr2,N);

    int left = 0;
    int right = N;
    int mid = (left + right) / 2;
    int median = arr2[0];
    bool b;
    while(left <= right){
        b = check_median(arr,N,K,arr2[mid]);
        if(b){
            median = arr2[mid];
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
        mid = (left + right) / 2;
    

    }
    cout << median << endl;
    return 0;
}