#pragma once
#include <iostream>

template <typename X>
struct element {
	X value;
	element<X>* next;
	element<X>* previous;
};


template <typename X>
class twoWayList {
private:
	unsigned int current;
	element<X>* front;
	element<X>* back;
public:
	twoWayList() :current(0) { front = back = nullptr; };
	~twoWayList();
	inline unsigned int get_size() const { return current; };
	void push_front(const X& toAdd);
	void push_back(const X& toAdd);
	void pop_front();
	void pop_back();
	X get_front();
	X get_back();
	template <typename Y> friend std::ostream& operator<<(std::ostream& out, const twoWayList<Y>& toPrint);
};


template <typename X> twoWayList<X>::~twoWayList() {
	element<X>* temp;
	while (front) {
		temp = front->next;
		delete front;
		front = temp;
	}
}


template <typename X> void twoWayList<X>::push_front(const X& toAdd) {
	element<X>* temp = new element<X>{ toAdd,front,nullptr };
	if (front) front->previous = temp;
	front = temp;
	if (!back) back = front;
	current++;
}


template <typename X> void twoWayList<X>::push_back(const X& toAdd) {
	element<X>* temp = new element<X>{ toAdd,nullptr,nullptr };
	if (back) back->next = temp;
	temp->next = nullptr;
	temp->previous = back;
	back = temp;
	if (!front) front = back;
	current++;
}


template <typename X> void twoWayList<X>::pop_front() {
	if (front) {
		front = front->next;
		if (!front) back = nullptr;
		else front->previous = nullptr;
		current--;
	}
	else throw std::logic_error("List is empty, deletion not possible!");
}


template <typename X> void twoWayList<X>::pop_back() {
	element<X>* temp;
	if (back) {
		temp = back;
		if (temp == front) back = front = nullptr;
		else {
			back = back->previous;
			back->next = nullptr;
		}
		current--;
	}
	else throw std::logic_error("List is empty, deletion not possible!");
}


template <typename X> std::ostream& operator<<(std::ostream& out, const twoWayList<X>& toPrint) {
	element<X>* temp;
	if (!toPrint.front) return out << "Container is empty!";
	else {
		if (toPrint.back->next) {
			temp = toPrint.back;
			temp = temp->next;
			out << temp->value << " ";
			temp = toPrint.back;
		}
		temp = toPrint.back;
		while (temp) {
			out << temp->value << " ";
			temp = temp->previous;
		}
		return out;
	}
}


template <typename X> X twoWayList<X>::get_front() {
	if (!front) throw std::logic_error("List is empty, there is no front element!");
	element<X>* temp = front;
	while (temp->previous) {
		temp = temp->previous;
	}
	return temp->value;
}


template <typename X> X twoWayList<X>::get_back() {
	if (!back) throw std::logic_error("List is empty, there is no back element!");
	element<X>* temp = back;
	while (temp->next) {
		temp = temp->next;
	}
	return temp->value;
}