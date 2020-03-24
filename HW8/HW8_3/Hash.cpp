// C++ code
#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

struct dict {                       // self-defined dictionary
	string key;                     //  key  for Name (eg:Jordan)
	string value;                   // value for Team (eg:Bulls)
	dict():key(""),value("") {};
	dict(string Key, string Value):key(Key),value(Value) {};
};

class HashChain_std {
	private:
		int size,                // size of table
		    count;               // count: number of data

		vector<list<dict> > table;            // hash table with linked list

		size_t PreHashing(string key_str);       // turn string_type_key to int_type_key
		int HashFunction(string key_str);     // using Division method

	public:
		HashChain_std() {};
		HashChain_std(int m):size(m),count(0) {
			table.resize(size);               // allocate memory for each slot
		}

		void Insert(dict data);
		void Delete(string key);
		string Search(string key);
		void DisplayTable();
};

string HashChain_std::Search(string key_str) {
	// two steps: 1. get index from hash function
	//            2. traversal in linked list
	int index = HashFunction(key_str);
	for (list<dict>::iterator itr = table[index].begin(); itr != table[index].end(); itr++) {
		if ((*itr).key == key_str) {
			return (*itr).value;
		}
	}
	return "not defined";
}

void HashChain_std::Delete(string key_str) {
	// two steps: 1. get index from hash function
	//            2. traversal in linked list
	int index = HashFunction(key_str);
	for (list<dict>::iterator itr = table[index].begin(); itr != table[index].end(); itr++) {
		if ((*itr).key == key_str) {
			table[index].erase(itr);
		}
	}
}

void HashChain_std::Insert(dict data) {
	// two steps: 1. get index from hash function
	//            2. insert data at the front of linked list
	int index = HashFunction(data.key);
	table[index].push_front(data);
}

static const size_t InitialFNV = 2166136261U;
static const size_t FNVMultiple = 16777619;

//int HashChain_std::PreHashing(string key_str) {
//	// if   key_str = Jordan, exp = 9
//	// then key_int = ASCII(J)*9^5+ASCII(o)*9^4+ASCII(r)*9^3
//	//               +ASCII(d)*9^2+ASCII(a)*9^1+ASCII(n)*9^0
//
//	int exp = 9,        // choose randomly
//	    key_int = 0,
//	    p = 1;
//
//	for (int i = (int)key_str.size()-1; i >= 0; i--) {
//		key_int += key_str[i]*p;
//		p *= exp;
//	}
//	return key_int;
//}

size_t HashChain_std::PreHashing(string key_str) {
	size_t hash = InitialFNV; 
	for (int i = 0; i < key_str.length(); i++){
		hash = hash^(key_str[i]); 
		hash = hash * FNVMultiple; 
	}	
	return hash; 
}


int HashChain_std::HashFunction(string key_str) {

	return (PreHashing(key_str) % this->size);     // Division method
}

void HashChain_std::DisplayTable() {

	for (int i = 0; i < table.size(); i++) {
		cout << "slot#" << i << ": ";
		for (list<dict>::iterator itr = table[i].begin(); itr != table[i].end(); itr++) {
			cout << "(" << (*itr).key << "," << (*itr).value << ") ";
		}
		cout << endl;
	}
	cout << endl;
}


//=========================================================================
//                        Main Function
//=========================================================================



int main() {


	HashChain_std hash(101);

	string line;
	string semicolon = ";";

	while(getline(cin, line)) {
		string type = "", var = ""; // var = key, type = value

		size_t found = 0;
		size_t end = 0;


		if(line.find(semicolon) != string::npos) {

			found = line.find_last_of(" ");
			type = line.substr(0, found);
			var = line.substr(found+1);
			var = var.substr(0, var.size()-1);
//			cout << "Type: " << type << " Var: " << var << endl;
			hash.Insert(dict(var,type));
		} else {
			var = line;
			cout << hash.Search(var) << endl;
			
		}

		if(cin.eof())
			break;

	}

	//hash.DisplayTable();

	return 0;
}
