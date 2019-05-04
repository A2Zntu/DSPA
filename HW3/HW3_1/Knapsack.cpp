/* A Naive recursive implementation of 0-1 Knapsack problem */
#include<iostream>
#include<algorithm>
using namespace std;

const int VERY_LARGE = 9999;
long int arr [VERY_LARGE][VERY_LARGE] = {0};

// Returns the maximum value that can be put in a knapsack of capacity W
int knapSack(int W, int wt[], int val[], int n) {
	if (arr[n][W] != 0) 
		return arr[n][W];  
	if (n == 0 || W == 0)
		return 0;

	if (wt[n-1] > W)
		return knapSack(W, wt, val, n-1);

	else {
		int temp1 = knapSack(W, wt, val, n-1);
		int temp2 = val[n-1] + knapSack(W - wt[n-1], wt, val, n-1);
		int res = max(temp1, temp2);

		arr[n][W] = res;
		return res;


	};
}

// Driver program to test above function
int main() {
	int val[] = {60, 70, 110, 40, 40};
	int wt[] = {10, 20, 25, 30, 20};
	int  W = 50;
	int n = sizeof(val)/sizeof(val[0]);
	printf("%d", knapSack(W, wt, val, n));
	return 0;
}
