#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
// Menu Component
class Component {
public: 
	virtual void add(Component*) { throw; }
	virtual void remove(Component*) { throw; }
	virtual Component* getChild(int i) { throw; }
	virtual string getName() { throw; }
	virtual bool isChecked() { throw; }
	virtual string getDescription() { throw; }
	virtual void print() { throw; }
};
 
// Menu Composite
class Composite : public Component {
	string name;
	vector<Component*> children;
	vector<Component*>::iterator position;
public:
	Composite(string name) { this->name = name; }
 
	void add(Component* component) {
		position = find(children.begin(), children.end(), component);
		if (position == children.end()) children.push_back(component);
	}
 
	void remove(Component* component) {
		position = find(children.begin(), children.end(), component);
		if (position != children.end()) children.erase(position);
	}
	Component* getChild(int i) {
		return children[i];
	}
	string getName() { return name; }
	void print() {
		cout << endl << "#### " << name << " ####" << endl;
		int size = children.size();
		for (int i = 0; i < size; i++) children[i]->print();
 
	}
};
 
// Menu Item
class Leaf : public Component {
	string name;
	bool checked;
public:
	Leaf(string name, bool checked ) { this->name = name; this->checked = checked; }
	string getName() { return name; }
	bool isChecked() { return checked; }
	void print() { cout << "[" << (checked ? "X" : " ") << "] Component Leaf: " << getName() << endl; }
};
 
// Waitress
class Client {
	Component* tree;
public:
	Client(Component* tree) { this->tree = tree; }
	void printAll() { tree->print(); }
};
 
int main() {
 
	Component* root = new Composite("Tree Root");
	Component* compositeA = new Composite("Composite A");
	Component* compositeB = new Composite("Composite B");
	Component* compositeC = new Composite("Composite C");
	Component* compositeD = new Composite("Composite D");
 
	root->add(compositeA);
	root->add(compositeB);
	root->add(compositeD);
 
	compositeA->add(new Leaf("Leaf1", true));
	compositeB->add(new Leaf("Leaf2", false));
	compositeB->add(compositeC);
	compositeC->add(new Leaf("Leaf3", true));
	compositeD->add(new Leaf("Leaf4", false));
 
	Client* client = new Client(root);
	client->printAll();
 
	return 0;
}
