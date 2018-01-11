#include<iostream>
#include<vector>
#include<memory>
#include<stdexcept>
#include<windows.h>
template<typename T>struct Node
{
	Node(T t) :item(t), next(nullptr) {};
	Node() :next(nullptr) {};
public:
	T item;
	std::shared_ptr<Node<T>> next;
};

template<typename T>class Example {
public:
	Example();
	~Example() = default;
	void push(T t);
	T top();
	bool isEmpty();
	std::size_t size();
	T pop();
private:
	std::size_t count;
	std::shared_ptr<Node<T>> first;
};

template<typename T>Example<T>::Example() :count(0) {
	first = std::make_shared<Node<T>>();
	first->next = nullptr;
	//std::cout << first.use_count() << std::endl;
};

template<typename T>void Example<T>::push(T t) {
	std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(t);//根据第一个构造函数，因为接下来的每一个node的item都有内容
	node->next = first->next;
	first->next = node;
	++count;
}

template<typename T>T Example<T>::pop() {
	if (first->next != nullptr) {
		std::shared_ptr<Node<T>> delnode = first->next;
		first->next = first->next->next;
		T item = delnode->item;
		--count;
		delnode->next = nullptr;
		return item;
	}
	else {
		std::cerr << "ERROR：栈为空，无法出栈！" << std::endl;
		throw std::runtime_error("the stack is empty!");
	}
}

template<typename T>T Example<T>::top() {

	if (first->next != nullptr) {
		return first->next->item;
	}
	else {
		std::cerr << "ERROR：栈为空，无法获得栈顶元素！" << std::endl;
		throw std::runtime_error("the stack is empty!");
	}
}

template<typename T>std::size_t Example<T>::size() { return count; }


template<typename T>bool Example<T>::isEmpty() { return count == 0; }

int main() {
	Example<int> e1;
	e1.push(1);
	std::cout << e1.top() << std::endl;
	e1.push(2);
	std::cout << e1.top() << std::endl;
	e1.push(3);
	std::cout << e1.top() << std::endl;
	e1.push(4);
	std::cout << e1.top() << std::endl;
	e1.push(5);
	std::cout << e1.top() << std::endl;
	e1.push(6);
	std::cout << e1.top() << std::endl;
	std::cout << "栈大小为：" << e1.size() << std::endl;

	while (!e1.isEmpty()) {
		std::cout << "出栈元素为：" << e1.pop() << std::endl;
	}
	std::cout << "栈大小为：" << e1.size() << std::endl;
	system("pause");
	return 0;
}