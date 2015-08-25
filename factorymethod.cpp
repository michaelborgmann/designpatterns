#include <iostream>

using namespace std;

class ProductInterface {
protected:
	string productName;
public:
	~ProductInterface() {}
	virtual void anOperation() { std::cout << "Some operation on " << productName << std::endl; }
	virtual string getProduct() { return productName; }
};

//------------------------------------------------------------------------------

class TypeAConcreteProductA : public ProductInterface {
public:
	TypeAConcreteProductA() { productName = "Type A Product A"; }
};

class TypeAConcreteProductB : public ProductInterface {
public:
	TypeAConcreteProductB() { productName = "Type A Product B"; }
};

//------------------------------------------------------------------------------

class TypeBConcreteProductA : public ProductInterface {
public:
	TypeBConcreteProductA() { productName = "Type B Product A"; }
};

class TypeBConcreteProductB : public ProductInterface {
public:
	TypeBConcreteProductB() { productName = "Type B Product B"; }
};

//------------------------------------------------------------------------------

class CreatorAbstract {
public:
	virtual ProductInterface* factoryMethod(int type) = 0;
	ProductInterface* createProduct(int type) {
		ProductInterface* product = factoryMethod(type);

		product->anOperation();		// place any operations on the product here

		return product;
	}
};

//------------------------------------------------------------------------------

class ConcreteCreatorA : public CreatorAbstract {
public:
	ProductInterface* factoryMethod(int type) {
		if (type == 'A') return new TypeAConcreteProductA();
		else if (type == 'B') return new TypeAConcreteProductB();
		else return 0;
	}
};


//------------------------------------------------------------------------------

class ConcreteCreatorB : public CreatorAbstract {
public:
	ProductInterface* factoryMethod(int type) {
		if (type == 'A') return new TypeBConcreteProductA();
		else if (type == 'B') return new TypeBConcreteProductB();
		else return 0;
	}
};

//------------------------------------------------------------------------------

int main() {

	CreatorAbstract* client = new ConcreteCreatorA();

	ProductInterface* product = client->createProduct('B');
	std::cout << product->getProduct() << std::endl;

	client = new ConcreteCreatorB();

	product = client->createProduct('A');
	std::cout << product->getProduct() << std::endl;

	return 0;
}
