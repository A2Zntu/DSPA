// ===========================================================================
// Character, Warrior, Wizard, and Team
// ===========================================================================
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Character {
	protected:
		static const int EXP_LV = 100;
		string name;
		int level;
		int exp;
		int power;
		int knowledge;
		int luck;
		void levelUp(int pInc, int kInc, int lInc);
	public:
		Character(string n, int lv, int po, int kn, int lu);
		virtual void beatMonster(int exp) = 0;
		virtual void print();
		string getName();
		int getLevel();
};

Character::Character(string n, int lv, int po, int kn, int lu)
	: name(n), level(lv), exp(pow(lv - 1, 2) * EXP_LV), power(po), knowledge(kn), luck(lu) {
}

void Character::print() {
	cout << this->name
	     << ": Level " << this->level << " (" << this->exp << "/" << pow(this->level, 2) * EXP_LV
	     << "), " << this->power << "-" << this->knowledge << "-" << this->luck << "\n";
}

void Character::levelUp(int pInc, int kInc, int lInc) {
	this->level++;
	this->power += pInc;
	this->knowledge += kInc;
	this->luck += lInc;
}

string Character::getName() {
	return this->name;
}

int Character::getLevel() {
	return this->level;
}









class Warrior : public Character {
	private:
		static const int PO_LV = 10;
		static const int KN_LV = 5;
		static const int LU_LV = 5;
	public:
		Warrior(string n) : Character(n, 1, PO_LV, KN_LV, LU_LV) {}
		Warrior(string n, int lv) : Character(n, lv, lv * PO_LV, lv * KN_LV, lv * LU_LV) {}
		void print() {
			cout << "Warrior ";
			Character::print();
		}
		void beatMonster(int exp) {
			this->exp += exp;
			while(this->exp >= pow(this->level, 2) * EXP_LV)
				this->levelUp(PO_LV, KN_LV, LU_LV);
		}
};

class Wizard : public Character {
	private:
		static const int PO_LV = 4;
		static const int KN_LV = 9;
		static const int LU_LV = 7;
	public:
		Wizard(string n) : Character(n, 1, PO_LV, KN_LV, LU_LV) {}
		Wizard(string n, int lv) : Character(n, lv, lv * PO_LV, lv * KN_LV, lv * LU_LV) {}
		void print() {
			cout << "Wizard ";
			Character::print();
		}
		void beatMonster(int exp) {
			this->exp += exp;
			while(this->exp >= pow(this->level, 2) * EXP_LV)
				this->levelUp(PO_LV, KN_LV, LU_LV);
		}
};
















//=====================================================
// oop(p. 49)

class Team {
	private:
		int memberCount;
		Character* member[10];
	public:
		Team();
		~Team();
		void addWarrior(string name, int lv);
		void addWizard(string name, int lv);
		void memberBeatMonster(string name, int exp);
		void printMember(string name);
};






//======================================================
//opp(p. 50)


Team::Team() {
	this->memberCount = 0;
	for(int i = 0; i < 10; i++)
		member[i] = nullptr;
}

Team::~Team() {
	for(int i = 0; i < this->memberCount; i++)
		delete this->member[i];
}

void Team::addWarrior(string name, int lv) {
	if(memberCount < 10) {
		member[memberCount] = new Warrior(name, lv);
		memberCount++;
	}
}

void Team::addWizard(string name, int lv) {
	if(memberCount < 10) {
		member[memberCount] = new Wizard(name, lv);
		memberCount++;
	}
}




//======================================================
//opp(p. 51)

void Team::memberBeatMonster
(string name, int exp) {
	for(int i = 0; i < this->memberCount; i++) {
		if(this->member[i]->getName() == name) {
			this->member[i]->beatMonster(exp);
			break;
		}
	}
}

void Team::printMember(string name) {
	for(int i = 0; i < this->memberCount; i++) {
		if(this->member[i]->getName() == name) {
			this->member[i]->print();
			break;
		}
	}
}
// ===========================================================================
// End of Character, Warrior, Wizard, and Team
// ===========================================================================

int main() {
	Character* c[3];
	c[0] = new Warrior("Alice", 10);
	c[1] = new Wizard("Sophie", 8);
	c[2] = new Warrior("Amy", 12);
	c[0]->beatMonster(10000);

	for(int i = 0; i < 3; i++)
		c[i]->print();
	Team myteam;

	myteam.addWarrior(c[0]->getName(), c[0]->getLevel());
	myteam.addWarrior(c[1]->getName(), c[1]->getLevel());
	myteam.addWarrior(c[2]->getName(), c[2]->getLevel());
	myteam.printMember("Alice");

	}

	for(int i = 0; i < 3; i++)
		delete c[i];
	return 0;
}

