#include <vector>
#include <iostream>
using namespace std;

const int VERY_LARGE = 9999; 
long int memo [VERY_LARGE] = {1, 1}; 


long int catalanNum(long int n) {
	if(n == 0 || n == 1)
		return 1;
	int res_num = 0;
	for(int i = 0; i < n; i++) {
		int frontNum = 0;
		if(memo[i] == 0)
			frontNum = memo[i];
		else {
			frontNum = catalanNum(i);
			memo[i] = frontNum; 
		}
		int backNum = 0; 
		if(memo[n-i-1] == 0)
			backNum = memo[n-i-1]; 
		else{
			backNum = catalanNum(n-i-1); 
			memo[n-i-1] = backNum; 
		}
		res_num += frontNum * backNum; 
	}
	memo[n] = res_num; 
	return res_num;
}

int main() {

	for(int i = 0; i < 10; i++) {
		long int ans = catalanNum(i);
		cout << ans << " ";

	}
}
