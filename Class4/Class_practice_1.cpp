# include<iostream>
using namespace std;

template <typename KeyType>
class MyVector2D {

		template <typename KeyType1, typename KeyType2>
		friend bool operator==(const MyVector2D<KeyType1>& u, const MyVector2D<KeyType2>& v);

	private:
		KeyType x;
		KeyType y;
	public:
		MyVector2D() : x(0), y(0) {}
		MyVector2D(KeyType x, KeyType y) : x(x), y(y) {}
		void print() const;
		bool operator==(const MyVector2D& v) const;
};

template <typename KeyType>
void MyVector2D<KeyType>::print() const {
	cout << "(" << this->x
	     << ", " << this->y << ")\n";
}

template <typename KeyType>
bool MyVector2D<KeyType>::operator==
(const MyVector2D& v) const {
	if(this->x == v.x
	        && this->y == v.y)
		return true;
	else
		return false;
}


template <typename KeyType1, typename KeyType2>
bool operator==(const MyVector2D<KeyType1>& u, const MyVector2D<KeyType2>& v) {
	if(u.x == v.x && u.y == v.y)
		return true;
	else
		return false;
}


int main() {
	MyVector2D<double> u(1.2, 2.3);
	MyVector2D<double> v(1.4, 2.6);
	u.print();
	v.print();

	if(u == v)
		cout << "Equal!\n";
	else
		cout << "Unequal!\n";

	return 0;
}


