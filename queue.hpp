#pragma once
#include "list.hpp"

enum status {
	empty, active
};


enum completion {
	none, success, fail
};


template <typename T>
class queue {
private:
	twoWayList<T>* container;
	status current;
	completion operationStatus;
	static int open;
public:
	queue<T>() :current(empty), operationStatus(none) { container = new twoWayList<T>(); open++; };
	queue<T>(const queue<T>& toCopy) :current(toCopy.current), operationStatus(toCopy.operationStatus) { container = toCopy.container; };
	~queue<T>() { delete container; open--; };
	inline unsigned int size() const { return container->get_size(); };
	inline int opened() const { return open; };
	T back();
	T front();
	void push_back(const T& toAdd);
	void pop_front();
	void get_status();
	void get_operationStatus();
	queue<T>& operator=(const queue<T>& toAssign);
	template <typename Y> friend std::ostream& operator<<(std::ostream& out, const queue<Y>& toPrint);
};


template <typename T> T queue<T>::back() {
	try {
		T temp = container->get_back();
		operationStatus = success;
		return temp;
	}
	catch (const std::logic_error& error) {
		std::cerr << error.what() << std::endl;
		operationStatus = fail;
	}
}


template <typename T> T queue<T>::front() {
	try {
		T temp = container->get_front();
		operationStatus = success;
		return temp;
	}
	catch (const std::logic_error& error) {
		std::cerr << error.what() << std::endl;
		operationStatus = fail;
	}
}


template <typename T> void queue<T>::push_back(const T& toAdd) {
	container->push_back(toAdd);
	operationStatus = success;
	current = active;
}


template <typename T> void queue<T>::pop_front() {
	try {
		container->pop_front();
		if (container->get_size() == 0) current = empty;
		operationStatus = success;
	}
	catch (const std::logic_error& error) {
		std::cerr << error.what() << std::endl;
		operationStatus = fail;
	}
}


template <typename T> void queue<T>::get_status() {
	if (current == empty) std::cout << "Queue is empty." << std::endl;
	else std::cout << "Queue stores elements." << std::endl;
	operationStatus = success;
}


template <typename T> void queue<T>::get_operationStatus() {
	switch (operationStatus)
	{
	case none:
		std::cout << "No operations made yet" << std::endl;
		operationStatus = success;
		break;
	case success:
		std::cout << "Last operation was successful" << std::endl;
		operationStatus = success;
		break;
	case fail:
		std::cout << "Last operation failed" << std::endl;
		operationStatus = success;
		break;
	}
}


template <typename T> queue<T>& queue<T>::operator=(const queue<T>& toAssign) {
	if (this == &toAssign) return *this;
	container = toAssign.container;
	current = toAssign.current;
	operationStatus = toAssign.operationStatus;
	return *this;
}


template <typename Y> std::ostream& operator<<(std::ostream& out, const queue<Y>& toPrint) {
	return out << *toPrint.container << std::endl;
}