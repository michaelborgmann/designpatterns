#include <iostream>
#include <vector>

using namespace std;

// Burger / Stereo
class ReceiverA {
	string name;
	int state;
	
public:
	ReceiverA(string name) { this->name = name; state = 1; }
	int getState() { return state; }
	void action1() { cout << name << " Action 1\n"; state = 1; }
	void action2() { cout << name << " Action 2\n"; state = 2; }
	
};

// Drink+Ice / Light On+Off
class ReceiverB {
	string name;
public:
	ReceiverB(string name) { this->name = name; }
	void action1() { cout << name << " Action 1\n"; }
	void action2() { cout << name << " Action 2\n"; }
};

//------------------------------------------------------------------------------

class CommandInterface {
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
};

// Order Burger / Stereo All On
class ConcreteCommandA1 : public CommandInterface {
	ReceiverA* receiver;
	int lastState;
public:
	ConcreteCommandA1(ReceiverA* receiver) { this->receiver = receiver; }
	void execute() { lastState = receiver->getState(); receiver->action1(); }
	void undo() { lastState ? receiver->action1() : receiver->action2(); }
};

class ConcreteCommandA2 : public CommandInterface {
	ReceiverA* receiver;
	int lastState;
public:
	ConcreteCommandA2(ReceiverA* receiver) { this->receiver = receiver; }
	void execute() { lastState = receiver->getState(); receiver->action2(); }
	void undo() { lastState ? receiver->action1() : receiver->action2(); }
};

//-----------------------------------------------------

class ConcreteCommandB : public CommandInterface {
	ReceiverB* receiver;
public:
	ConcreteCommandB(ReceiverB* receiver) { this->receiver = receiver; }
	void execute() { receiver->action1(); }
	void undo() { receiver->action2(); }
};

class ConcreteCommandC : public CommandInterface {
	ReceiverB* receiver;
public:
	ConcreteCommandC(ReceiverB* receiver) { this->receiver = receiver; }
	void execute() { receiver->action2(); }
	void undo() { receiver->action1(); }
};


// Null Object
class NoCommand : public CommandInterface {
public:
	void execute() { /* ... nothing ... */ }
	void undo() {}
};

//------------------------------------------------------------------------------

// Waitress / Remote
class Invoker {
	vector<CommandInterface*> commands;
	CommandInterface* undoCommand;
public:
	Invoker() {
		CommandInterface* noCommand = new NoCommand();
		for (int i = 0; i < 4; i++) commands.push_back(noCommand);
		undoCommand = noCommand;
	}

	void setCommand(int position, CommandInterface* command) { commands[position] = command; }
	void executeCommand(int position) { commands[position]->execute(); undoCommand = commands[position]; }
	void executeUndoCommand() { undoCommand->undo(); }
};

int main() {

	ReceiverA* receiverA = new ReceiverA("Receiver A");

	ConcreteCommandA1* commandA1 = new ConcreteCommandA1(receiverA);
	ConcreteCommandA2* commandA2 = new ConcreteCommandA2(receiverA);

	Invoker* client = new Invoker();
	
	client->setCommand(0, commandA1);
	client->setCommand(1, commandA2);

	client->executeCommand(0);
	client->executeCommand(1);
	client->executeUndoCommand();

	return 0;
}
