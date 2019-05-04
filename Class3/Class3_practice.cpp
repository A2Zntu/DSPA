#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Page 5
class Entity
{
private:
  string id;
  bool isOn; 
  bool isSer; // means nothing if isOn == false
  double lon;
  double lat;
public: 
  Entity(string id, bool isOn, bool isSer, double lon, double lat);
  void print();
};



// Page 6

Entity::Entity(string id, bool isOn, bool isSer, double lon, double lat)
  : id(id), isOn(isOn), isSer(isSer), lon(lon), lat(lat)
{
}

void Entity::print()
{
  cout << this->id << ": " << this->isOn << " " << this->isSer
       << " (" << this->lon << ", " << this->lat << ")" << endl;
}



// Page 7

int main()
{
  Entity a("5HE-313", true, true, 0, 0);
  a.print();
  return 0;
}



// Page 8

class Car : public Entity
{
private:
public:
  Car(string id, bool isOn, bool isSer, double lon, double lat);
};

Car::Car(string id, bool isOn, bool isSer, double lon, double lat)
  : id(id), isOn(isOn), isSer(isSer), lon(lon), lat(lat)
{
}



// Page 9

int main()
{
  Car a("5HE-313", true, true, 0, 0);
  a.print();
  return 0;
}



// Page 10

class Car : public Entity
{
private:
public:
  Car(string id, bool isOn, bool isSer, double lon, double lat);
  void print(); 
};



// Page 11 

int main()
{
  Car* cars[20000] = {0};
  int carCnt = 0;
  cars[0] = new Car("5HE-313", true, true, 0, 0);
  carCnt++;
  cars[1] = new Car("LPA-039", true, false, 1, 1);  
  carCnt++;
  for(int i = 0; i < carCnt; i++)
    cars[i]->print();

  return 0;
}



// Page 12 

class CarArray
{
private:
  int capacity; // initialize it to 20000; may change later
  int cnt;
  Car* cars; 
public:
  CarArray();
  // CarArray(const CarArray& ca);  // not needed
  // operator=(const CarArray& ca); // in this problem
  ~CarArray();
  void add();
  void print();
};



// Page 13

CarArray::CarArray()
{
  this->cnt = 0;
  this->capacity = 20000;
  this->cars = new Car[this->capacity];
}



// Page 14

class CarArray
{
private:
  int capacity; // initialize it to 20000; may change later
  int cnt;
  Car** carPtr; 
public:
  CarArray();
  // CarArray(const CarArray& ca);  // not needed
  // operator=(const CarArray& ea); // in this problem
  ~CarArray();
  void add();
  void print();
};



// Page 15

CarArray::CarArray()
{
  this->cnt = 0;
  this->capacity = 20000;
  this->carPtr = new Car*[this->capacity];
}

CarArray::~CarArray()
{
  for(int i = 0; i < this->cnt; i++)
    delete this->carPtr[i];
  delete [] this->carPtr;
}



// Page 16

int main()
{
  CarArray ca;
  ca.add("5HE-313", true, true, 0, 0);
  ca.add("LPA-039", true, false, 1, 1);  
  ca.print();
  
  return 0;
}



// Page 17

int main()
{
  Car c("5HE-313", true, false, 0, 0);
  c.print();
  
  Passenger p("B90705023", true, false, 0, 0);
  p.print();

  return 0;
}



// Page 19

class CarArray : public EntityArray
{
};

class PassengerArray : public EntityArray
{
};



// Page 20 

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



