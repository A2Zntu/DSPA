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
		virtual void print() = 0 ;
};



// Page 6

Entity::Entity(string id, bool isOn, bool isSer, double lon, double lat)
	: id(id), isOn(isOn), isSer(isSer), lon(lon), lat(lat) { // Member initializer
}



// Page 8

class Car : public Entity {
	private:
	public:
		Car(string id, bool isOn, bool isSer, double lon, double lat);
		void print() ;
};

Car::Car(string id, bool isOn, bool isSer, double lon, double lat)
	: Entity(id, isOn, isSer, lon, lat) { //inherence the parent constructor
}

void Car::print()  {
	cout << this->id << " ";
	if(this-> isOn) {
		if(this -> isSer) {
			cout << "online " << "in-service " << this-> lon
			     <<" " << this -> lat << " " << endl;

		} else {
			cout << "online " << "empty " << this-> lon
			     <<" " << this -> lat << " " << endl;
		}
	} else {
		cout << "offline" << " " << endl;
	}
}

//=====================passenger===========================

class Passenger : public Entity {
	private:
	public:
		Passenger(string id, bool isOn, bool isSer, double lon, double lat);
		void print() ;
};

Passenger::Passenger(string id, bool isOn, bool isSer, double lon, double lat)
	: Entity(id, isOn, isSer, lon, lat) { //inherence the parent constructor
}

void Passenger::print(){
	cout << this->id << " ";
	if(this-> isOn) {
		if(this -> isSer) {
			cout << "online " << "in-service " << this-> lon
			     <<" " << this -> lat << " " << endl;

		} else {
			cout << "online " << "waiting " << this-> lon
			     <<" " << this -> lat << " " << endl;
		}
	} else {
		cout << "offline" << " " << endl;
	}
}

//========================entityArray====================

class EntityArray {
	protected:
		int capacity; // initialize it to 20000; may change later
		int cnt;
		Entity** EntityPtr;
	public:
		EntityArray();
		// CarArray(const CarArray& ca);  // not needed
		// operator=(const CarArray& ca); // in this problem
		~EntityArray();
		virtual bool add(string id, bool isOn, bool isSer, double lon, double lat) = 0;
		void print();
};

EntityArray::EntityArray() {
	this -> cnt =  0;
	this -> capacity = 20000;
	this -> EntityPtr = new Entity* [this -> capacity];
}

EntityArray::~EntityArray() {
	for(int i = 0; i < this -> cnt; i++) {
		delete this -> EntityPtr[i];
	}
	delete [] this -> EntityPtr;
}

void EntityArray::print() {
	for(int i = 0; i < this -> cnt; i++ ) {
		this -> EntityPtr[i] -> print();
	}
}

class CarArray : public EntityArray {
	private:
	public:
		bool add(string id, bool isOn, bool isSer, double lon, double lat);

};

bool CarArray::add(string id, bool isOn, bool isSer, double lon, double lat) {
	if(this -> cnt < this -> capacity) {
		this -> EntityPtr[this -> cnt] = new Car(id, isOn, isSer, lon, lat);
		this -> cnt ++;
		return true;
	} else
		return false;
}

class PassengerArray : public EntityArray {
	private:
	public:
		bool add(string id, bool isOn, bool isSer, double lon, double lat);

};

bool PassengerArray::add(string id, bool isOn, bool isSer, double lon, double lat) {
	if(this -> cnt < this -> capacity) {
		this -> EntityPtr[this -> cnt] = new Passenger(id, isOn, isSer, lon, lat);
		this -> cnt ++;
		cout << this -> cnt; 
		return true;
	} else
		return false;
}


//======================== main ===========================

int main() {
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


