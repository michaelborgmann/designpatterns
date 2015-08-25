// framework for the observer pattern
#include <iostream>
#include <deque>
#include <algorithm>
 
using namespace std;
 
class Subject;
 
class Observer {						// observer interface
	public:
		virtual void Update(Subject*) = 0;
};
 
class Subject {							// subject
		typedef deque<Observer*> Observers;		// note: use vector instead to reduce overhead when sorting is rare
		Observers observers;
	public:
		virtual ~Subject() {}
		bool RegisterObserver(Observer* observer) {
			if ((find(observers.begin(), observers.end(), observer)) == observers.end()) {
				observers.push_back(observer);
				return true;
			}
			return false;
		}
 
		bool RemoveObserver(Observer* observer) {
 
			Observers::iterator found = find(observers.begin(), observers.end(), observer);
			if (found != observers.end()) {
				observers.erase(found);
				return true;
			}
			return false;
		}
 
		void NotifyObservers() {
			Observers::iterator observer = observers.begin();
			while (observer != observers.end()) {
				(*observer)->Update(this);
				observer++;
			}
		}
};
 
class ConcreteSubject : public Subject {
	int state;
	public:
		void setState(int state) {
			this->state = state;
			NotifyObservers();
		}
 
		int getState() { return state; }
};
 
class ConcreteObserver : public Observer {
		ConcreteSubject* subject;
	public:
		ConcreteObserver(ConcreteSubject* s) : subject(s) { subject->RegisterObserver(this); }
		~ConcreteObserver() { subject->RemoveObserver(this); }
		void Update(Subject* subject) {
			if (subject == this->subject)
				cout << "State from A: " << this->subject->getState() << endl;
		}
};
 
int main() {
	ConcreteSubject subject;
	ConcreteObserver observer(&subject);
	subject.setState(108);
}
