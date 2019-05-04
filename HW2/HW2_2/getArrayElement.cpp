# include <iostream>
# include<stdexcept>
using namespace std;

template <typename keyType>
keyType getArrayElement(const keyType* array, int len, int index) throw(out_of_range);
 // const the array, so developer can't change array

int main() {
	int len = 0;
	cin >> len;
	double* array = new double[len]; // we use pointer to do DMA
	for(int i = 0; i < len; i ++)
		cin >> array[i];
	int index = 0;
	cin >> index;
	
	try {
		double result = getArrayElement(array, len, index);
		cout << result << endl;
	} catch(out_of_range e) {
		cout << e.what();
	}
	return 0;
}
template <typename keyType>
keyType getArrayElement(const keyType* array, int len, int index) throw(out_of_range) {
	if(0 <= index && index < len)
		return array[index];
	else if(index < 0)
		return array[len + index]; 
	throw out_of_range("The index is wrong!");
}
