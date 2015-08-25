#include <iostream>

using namespace std;

class Singleton {
private:
	static Singleton* uniqueInstance;
	Singleton () { cout << "Singleton created\n"; }
	~Singleton() { cout << "Destroy Singleton\n"; }
public:
	static Singleton* getInstance() {
		if (!uniqueInstance) {
			cout << "Instantiate singleton\n";
			uniqueInstance = new Singleton();
		}
		else cout << "Access singleton\n";
		return uniqueInstance;
	}
};

Singleton* Singleton::uniqueInstance = new Singleton::Singleton();

int main() {

	Singleton* singleton;
	singleton = Singleton::getInstance();
	singleton = Singleton::getInstance();

	return 0;
}
