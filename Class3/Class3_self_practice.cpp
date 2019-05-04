#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Page 5
class Entity {
	protected:
		string id;
		bool isOn;
		bool isSer; // means nothing if isOn == false
		double lon;
		double lat;
	public:
		Entity(string id, bool isOn, bool isSer, double lon, double lat);
		virtual void print();
};



// Page 6

Entity::Entity(string id, bool isOn, bool isSer, double lon, double lat)
	: id(id), isOn(isOn), isSer(isSer), lon(lon), lat(lat) {
}

void Entity::print() {
	cout << this->id << ": " << this->isOn << " " << this->isSer
	     << " (" << this->lon << ", " << this->lat << ")" << endl;
}



//===================================================

class Car : public Entity {
	private:
	public:
		Car(string id, bool isOn, bool isSer, double lon, double lat);
		void print() const;
};

Car::Car(string id, bool isOn, bool isSer, double lon, double lat)
	: Entity(id, isOn, isSer, lon, lat) {
}


void Car::print() const {
	cout << this -> id << ": ";
	if(this -> isOn == true) {
		cout << "online" << " ";
		if(this -> isSer == true) {
			cout << "in Service" << " ";

		} else {
			cout << "empty" << " ";
		}
		cout << " (" << this->lon << ", " << this->lat << ")" << endl;
	} else {
		cout << " offline";
	}

}


//================================================
class Passenger : public Entity {
	private:
	public:
		Passenger(string id, bool isOn, bool isSer, double lon, double lat);
		void print() const;
};


Passenger::Passenger(string id, bool isOn, bool isSer, double lon, double lat)
	: Entity(id, isOn, isSer, lon, lat) {
}


void Passenger::print() const {
	cout << this -> id << ": ";
	if(this -> isOn == true) {
		cout << "online" << " ";
		if(this -> isSer == true) {
			cout << "in Service" << " ";

		} else {
			cout << "waiting" << " ";
		}
		cout << " (" << this->lon << ", " << this->lat << ")" << endl;
	} else {
		cout << " offline";
	}

}
//================================================

class EntityArray {
	protected:
		int capacity; // initialize it to 20000; may change later
		int cnt;
		Entity** entityPtr;
	public:
		EntityArray();
		// CarArray(const CarArray& ca);  // not needed
		// operator=(const CarArray& ca); // in this problem
		~EntityArray();
		void add(string id, bool isOn, bool isSer, double lon, double lat);
		void print();
};

EntityArray::EntityArray() {
	this->cnt = 0;
	this->capacity = 20000;
	this->entityPtr = new Entity*[this->capacity];
}

EntityArray::~EntityArray() {
	for(int i = 0; i < this->cnt; i++)
		delete this-> entityPtr[i];
	delete [] this-> entityPtr;
}

void EntityArray:: add(string id, bool isOn, bool isSer, double lon, double lat) {
	this -> entityPtr[this -> cnt] = new Entity(id, isOn, isSer, lon, lat);
	this -> cnt++;

}

void EntityArray:: print() {
	for(int i = 0; i < this-> cnt; i++) {
		this -> entityPtr[i] -> print();
	}

}

class CarArray : public EntityArray {
public:
	void add(string id, bool isOn, bool isSer, double lon, double lat);
};

class PassengerArray : public EntityArray {
public:
	void add(string id, bool isOn, bool isSer, double lon, double lat);
};

void CarArray :: add(string id, bool isOn, bool isSer, double lon, double lat){
	this -> entityPtr[this -> cnt] = new Car(id, isOn, isSer, lon, lat);
}

void PassengerArray :: add(string id, bool isOn, bool isSer, double lon, double lat){
	this -> entityPtr[this -> cnt] = new Passenger(id, isOn, isSer, lon, lat);
}



// =============================================

int main()
{

  CarArray ca;
  ca.add("5HE-313", true, true, 0, 0);
  ca.add("LPA-039", true, false, 1, 1);  
  ca.print(); // it works

  PassengerArray pa;
  pa.add("B90705023", true, true, 0, 0);
  pa.add("R94725008", true, false, 1, 1);  
  pa.print(); // it works
  
  return 0;
}

