#include "queue.hpp"

template <typename X> int queue<X>::open = 0;

int main() {
	queue<int>* test = new queue<int>;
	std::cout << *test << std::endl;
	std::cout << test->front() << std::endl;
	for (int i = 15; i <= 20; i++) {
		test->push_back(i);
	}
	std::cout << *test << std::endl;
	std::cout << "Back: " << test->back() << std::endl;
	std::cout << "Front: " << test->front() << std::endl;
	test->pop_front();
	test->pop_front();
	std::cout << *test << std::endl;
	std::cout << "Back: " << test->back() << std::endl;
	std::cout << "Front: " << test->front() << std::endl;
	queue<int>* test2;
	test2 = test;
	std::cout << *test2 << std::endl;
	std::cout << "Size of test2: " << test2->size() << std::endl;
	std::cout << "Back: " << test2->back() << std::endl;
	std::cout << "Front: " << test2->front() << std::endl;
	std::cout << "Last operation status: "; 
	test2->get_operationStatus();
	std::cout << "Queue has status: ";
	test2->get_status();
	std::cout << "Current active classes: " << test->opened() << std::endl;
	queue<int>* test3 = new queue<int>(*test2);
	std::cout << *test3 << std::endl;
	delete test2;
	return 0;
}