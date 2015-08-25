#include <iostream>

using namespace std;

// Cheese
class AbstractProductA {
public:
	virtual string getProductName() = 0;
};

// Parmegiano
class ProductA1 : public AbstractProductA {
	string getProductName() { return "Product A1"; }
};

// Mozarella
class ProductA2 : public AbstractProductA {
	string getProductName() { return "Product A2"; }
};

//------------------------------------------------------------------------------

// Sauce
class AbstractProductB {
public:
	virtual string getProductName() = 0;
};

// Marinara
class ProductB1 : public AbstractProductB {
	string getProductName() { return "Product B1"; }
};

// Plum Sauce
class ProductB2 : public AbstractProductB {
	string getProductName() { return "Product B2"; }
};

//------------------------------------------------------------------------------

// Pizza Ingredients Factory
class AbstractFactory {
public:
	virtual AbstractProductA* createProductA() = 0;
	virtual AbstractProductB* createProductB() = 0;
};

// NY Pizza Ingredient Factory
class ConcreteFactoryA : public AbstractFactory {
public:
	AbstractProductA* createProductA() { return new ProductA1(); }
	AbstractProductB* createProductB() { return new ProductB1(); }
};

// Chicago Ingredient FActore
class ConcreteFactoryB : public AbstractFactory {
public:
	AbstractProductA* createProductA() { return new ProductA2(); }
	AbstractProductB* createProductB() { return new ProductB2(); }

};

//------------------------------------------------------------------------------

// Pizza
class ClientInterface {
protected:
	string productName;
	AbstractProductA* productA;
	AbstractProductB* productB;
	
public:
	~ClientInterface() {}
	virtual void compose() = 0;
	void anOperation() { cout << "Some operation in " << productName << endl; }
	string getProduct() { return productName; }
	void setProduct(string name) { this->productName = name; }
};


// Pizza Margarita
class ClientA : public ClientInterface {
	AbstractFactory* factory;
public:
	ClientA(AbstractFactory* factory) { this->factory = factory; }
	void compose() {
		cout << "Compose " << getProduct() << endl;
		productA = factory->createProductA();
		productB = factory->createProductB();
	}
};

// Pizza Marinara
class ClientB : public ClientInterface {
	AbstractFactory* factory;
public:
	ClientB(AbstractFactory* factory) { this->factory = factory; }
	void compose() {
		cout << "Compose " << getProduct() << endl;
		productB = factory->createProductB();
	}
};

//------------------------------------------------------------------------------

// Pizza Store
class CreatorAbstract {
public:
	virtual ClientInterface* factoryMethod(int type) = 0;
	ClientInterface* createProduct(int type) {
		ClientInterface* product = factoryMethod(type);

		product->compose();
		product->anOperation();		// place any operations on the product here

		return product;
	}
};

// New York Pizza Store
class ConcreteCreatorA : public CreatorAbstract {
public:
	ClientInterface* factoryMethod(int type) {

		ClientInterface* product;
		AbstractFactory* factory = new ConcreteFactoryA();

		if (type == 'A') {
			product = new ClientA(factory);
			product->setProduct("Factory A Product A");
		}
		else if (type == 'B') {
			product = new ClientB(factory);
			product->setProduct("Factory A Product B");
		}
		
		return product;
	}
};

// Chicago Pizza Store
class ConcreteCreatorB : public CreatorAbstract {
public:
	ClientInterface* factoryMethod(int type) {

		ClientInterface* product;
		AbstractFactory* factory = new ConcreteFactoryB();

		if (type == 'A') {
			product = new ClientA(factory);
			product->setProduct("Factory B Product A");
		}
		else if (type == 'B') {
			product = new ClientB(factory);
			product->setProduct("Factory B Product B");
		}

		return product;
	}
};

//------------------------------------------------------------------------------

int main() {

	CreatorAbstract* client = new ConcreteCreatorA();

	ClientInterface* product = client->createProduct('B');
	cout << product->getProduct() << endl;

	client = new ConcreteCreatorB();

	product = client->createProduct('A');
	cout << product->getProduct() << endl;

	return 0;
}
