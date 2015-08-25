#include <iostream>

using namespace std;

class AbstractClass {
public:
	void templateMethod() {
		primitiveOperation1();
		primitiveOperation2();
		concreteOperation();
		hook();
	}

	virtual void primitiveOperation1() = 0;
	virtual void primitiveOperation2() = 0;

	void concreteOperation() { cout << "Concrete Operation\n"; }

 	virtual void hook() { cout << "Abstract Hook\n"; }
};

class ConcreteClass : public AbstractClass {
public:
	void primitiveOperation1() { cout << "Primitive Operation 1\n"; }
	void primitiveOperation2() { cout << "Primitive Operation 2\n"; }
	void hook() { cout << "Concrete Hook\n"; }
};

int main() {

	AbstractClass* concrete = new ConcreteClass();
	concrete->templateMethod();

	return 0;
}
