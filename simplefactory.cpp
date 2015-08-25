#include <iostream>

using namespace std;

class ProductInterface {
protected:
	string productName;
public:
	~ProductInterface() {}
	virtual void operate() { std::cout << "Some operation on " << productName << std::endl; }
	virtual string getProduct() { return productName; }
};

class ProductA : public ProductInterface {
public:
	ProductA() { productName = "Product A"; }
};

class ProductB : public ProductInterface {
public:
	ProductB() { productName = "Product B"; }
};

class ProductFactory {
public:
	ProductInterface* create(int type) {
		ProductInterface* product;

		if (type == 'A') product = new ProductA();
		else if (type == 'B') product = new ProductB();
		
		return product;
	}
};

class Client {
private:
	ProductFactory* factory;

public:
	Client(ProductFactory* factory) { this->factory = factory; }

	ProductInterface* createProduct(int type) {
		ProductInterface* product;
		product = factory->create(type);

		product->operate();		// place any operations on the product here

		return product;
	}
};

int main() {

	ProductFactory* factory = new ProductFactory();
	Client* client = new Client(factory);

	ProductInterface* product = client->createProduct('B');
	std::cout << product->getProduct() << std::endl;

	return 0;
}
