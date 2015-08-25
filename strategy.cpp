#include <iostream>
 
using namespace std;
 
class StrategyInterface {							// strategy interface
public:
	~StrategyInterface() {};
	virtual void execute() = 0;	
};
 
class ConcreteStrategyA : public StrategyInterface {				// concrete strategy
public:
	virtual void execute() { cout << "Called strategy A\n"; }
};
 
class ConcreteStrategyB : public StrategyInterface {				// concrete strategy
public:
	virtual void execute() { cout << "Called strategy B\n"; }
};
 
class Context {								// class using strategy
protected:
	StrategyInterface* strategy;
public:
	Context() {}
	Context(StrategyInterface* behavior) : strategy(behavior) {}
	virtual ~Context() {}
	void execute() { strategy->execute(); }					// delegate to strategy
	void setStrategy(StrategyInterface* behavior) { strategy = behavior; }	// dynamically set strategy
	virtual void display() { cout << "default context\n"; }
};
 
class SubContext : public Context {						// reimplementation of context
public:
	SubContext() { strategy = new ConcreteStrategyB(); }
	~SubContext() {}
	void display() { cout << "sub context\n"; }
};
 
int main() {
 
	ConcreteStrategyA a;
	ConcreteStrategyB b;
 
	Context* context = new Context(&b);
	context->display();
	context->execute();
 
	context = new SubContext();
	context->display();
	context->execute();
 
	context->setStrategy(&a);
	context->execute();
	context->display();
 
	delete context;
 
	return 0;
}
