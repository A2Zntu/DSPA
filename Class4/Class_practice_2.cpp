# include<iostream>
# include<stdexcept>
#include<vector>
using namespace std;

class Entity {
	protected:
		string id;
		bool isOn;
		bool isSer;
		double lon;
		double lat;
	public:
		Entity(string id, bool isOn, bool isSer, double lon, double lat);
		void print();
};


Entity::Entity(string id, bool isOn, bool isSer, double lon, double lat)
	: id(id), isOn(isOn), isSer(isSer), lon(lon), lat(lat) {
}


void Entity::print() {
	cout << this->id << ": " << this->isOn << " " << this->isSer
	     << " (" << this->lon << ", " << this->lat << ")" << endl;
}


class Car : public Entity {
	private:
	public:
		Car(string id, bool isOn, bool isSer,
		    double lon, double lat);
		void print();
};


Car::Car(string id, bool isOn, bool isSer,
         double lon, double lat)
	: Entity(id, isOn, isSer, lon, lat) {
}


void Car::print() {
	cout << this->id << ": ";
	if(this->isOn == true) {
		if(this->isSer == true)
			cout << "in-service, (";
		else
			cout << "empty, (";
		cout << this->lon << ", "
		     << this->lat << ")";
	} else
		cout << "offline";
	cout << endl;
}


class Passenger : public Entity {
	private:
	public:
		Passenger(string id, bool isOn, bool isSer,
		          double lon, double lat);
		void print();
};


Passenger::Passenger(string id, bool isOn,
                     bool isSer,
                     double lon, double lat)
	: Entity(id, isOn, isSer, lon, lat) {
}


void Passenger::print() {
	cout << this->id << ": ";
	if(this->isOn == true) {
		if(this->isSer == true)
			cout << "in-service, (";
		else
			cout << "waiting, (";
		cout << this->lon << ", "
		     << this->lat << ")";
	} else
		cout << "offline";
	cout << endl;
}
//======================================================================================
// entityarray
//======================================================================================

template <typename keyType> // return a keyType obj
class EntityArray {
	protected:
		//keyType** entityPtr;
		vector<keyType> entities;
	public:
		EntityArray();
		~EntityArray();
		bool add(string id, bool isOn, bool isSer, double lon, double lat) throw(overflow_error);
		void print() noexcept;
};

template <typename keyType>
EntityArray<keyType>::EntityArray() {
}

template <typename keyType>
EntityArray<keyType>::~EntityArray() {
}

template <typename keyType>
bool EntityArray<keyType>::add(string id, bool isOn, bool isSer, double lon, double lat)
throw(overflow_error) {
	if(this->entities.size() < this->entities.max_size()) {
		keyType e(id, isOn, isSer, lon, lat);
		this->entities.push_back(e);
		return true; 

	}
	throw overflow_error("Something wrong!");
}


template <typename keyType>
void EntityArray<keyType>::print() noexcept {
	for(int i = 0; i < this->entities.size(); i++)
		this->entities[i].print();
}


//======================================================================================
// main function
//======================================================================================
int main() {
	try {

		EntityArray<Car> ca;
		ca.add("5HE-313", true, true, 0, 0);  // 5HE-313: 1 1 (0, 0)
		ca.add("LPA-039", true, false, 1, 1); // LPA-039: 1 0 (1, 1)
		ca.print();

		EntityArray<Passenger> pa;
		pa.add("B90705023", true, true, 0, 0);  // B90705023: 1 1 (0, 0)
		pa.add("R94725008", true, false, 1, 1); // R94725008: 1 0 (1, 1)
		pa.print();
	} catch(overflow_error e) {
		cout << e.what();
	}
	return 0;
}

