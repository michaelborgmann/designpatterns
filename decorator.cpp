#include <iostream>
 
using namespace std;

class Component {					// component interface
	public:
		virtual ~Component() {}
		virtual void Operation() = 0;
};

class ConcreteComponent : public Component {		// concrete component
	public:
		void Operation() { cout << "Concrete\n"; }
};

class Decorator : public Component {			// decorator interface
};

class ConcreteDecoratorA : public Decorator {
		Component* component;
	public:
		ConcreteDecoratorA(Component* component) : component(component) {}
		void Operation() {
			cout << "Decorator A\n";
			component->Operation();
		}
};

class ConcreteDecoratorB : public Decorator {
		Component* component;
	public:
		ConcreteDecoratorB(Component* component) : component(component) {}
		void Operation() {
			cout << "Decorator B\n";
			component->Operation();
		}
};

// testdrive
int main() {

	Component* component = new ConcreteComponent();
	component = new ConcreteDecoratorA(component);
	component = new ConcreteDecoratorB(component);
	component->Operation();
}
