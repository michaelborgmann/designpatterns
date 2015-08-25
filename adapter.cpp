#include <iostream>

using namespace std;

// Duck interface
class TargetInterface {
public:
	virtual void request() = 0;
};

// Turkey
class Adaptee {
public:
	void specificRequest() { cout << "Adaptee request\n"; }
};

// Turkey Adapter
class Adapter : public TargetInterface {
private:
	Adaptee* adaptee;
public:
	Adapter(Adaptee* adaptee) { this->adaptee = adaptee; }
	void request() { adaptee->specificRequest(); }
};

int main() {

	Adaptee* adaptee = new Adaptee();
	TargetInterface* adapter = new Adapter(adaptee);
	adapter->request();

	return 0;
}
