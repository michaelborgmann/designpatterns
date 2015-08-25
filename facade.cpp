#include <iostream>

using namespace std;

class Subsystem1 {
public:
	void advanced() { cout << "Subsystem 1 - Adv. Method\n"; }
};

class Subsystem2 {
public:
	void advanced() { cout << "Subsystem 2 - Adv. Method\n"; }
};

class Facade {
	Subsystem1* subsystem1;
	Subsystem2* subsystem2;
public:
	Facade(Subsystem1* subsytem1, Subsystem2* subsystem2) {
		this->subsystem1 = subsystem1;
		this->subsystem2 = subsystem2;
	}
	void simplified() {
		subsystem1->advanced();
		subsystem2->advanced();
	}
};

int main() {

	Facade* facade = new Facade(new Subsystem1, new Subsystem2);
	facade->simplified();

	return 0;
}
