#include <iostream>
#include <vector>
 
using namespace std;
 
// Iterator Interface
template <class T>
class IteratorInterface {
public:
	virtual ~IteratorInterface() {}
	virtual bool hasNext() = 0;
	virtual T* next() = 0;
};
 
// Menu Item
class Item {
	string name;
public:
	Item(string name) { this->name = name; }
	string getItem() { return name; }
};
 
// Diner Menu Iterator & Pancake House Menu Iterator
template <class T>
class ConcreteIterator : public IteratorInterface<T> {
	vector<T>* items;
	int position;
public:
	ConcreteIterator(vector<T>* items) : position(0) { this->items = items; }
	bool hasNext() { return (position < items->size()) ? true : false; }
	T* next() { return &items->at(position++); }
};
 
// Menu Interface
template <class T>
class AggregateInterface {
public:
	virtual ~AggregateInterface() {}
	virtual IteratorInterface<T>* createIterator() = 0;
};
 
// Diner Menu & Pancake House Menu
template <class T>
class ConcreteAggregate : public AggregateInterface<T> {
	vector<T> items;
public:
	ConcreteAggregate() {
		items.push_back(T("Item 1"));
		items.push_back(T("Item 2"));
	}
 
	IteratorInterface<T>* createIterator() { return new ConcreteIterator<T>(&items); }
};
 
// Waitress
template <class T>
class Client {
	vector< AggregateInterface<T>* >* aggregates;
	int position;
	void printItems(IteratorInterface<T>* iterator) {
		while (iterator->hasNext()) {
			T* item = iterator->next();
			cout << item->getItem() << endl;
		}
	}
public:
	Client(vector< AggregateInterface<T>* >* aggregates) : position(0) { this->aggregates = aggregates; }
	void printItems() {
		while (position < aggregates->size()) {
			AggregateInterface<T>* aggregate = aggregates->at(position++);
			printItems(aggregate->createIterator());
		}
	}
};
 
 
int main() {
 
	vector< AggregateInterface<Item>* > aggregates;
 
	AggregateInterface<Item>* aggregate = new ConcreteAggregate<Item>();
	aggregates.push_back(aggregate);
 
	Client<Item>* client = new Client<Item>(&aggregates);
	client->printItems();
 
	return 0;
}
