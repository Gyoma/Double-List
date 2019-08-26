#include "DoubleList.h"

Node::Node(int Val, Node* Prev, Node* Next, Node* ptrForThis, bool toTheEnd) :
	value(Val),
	previous(Prev),
	next(Next)
{
	if (ptrForThis != nullptr)
		(toTheEnd ? ptrForThis->next : ptrForThis->previous) = this;
}

Node::Node(const Node& object)
{
	if (this != &object)
	{
		value = object.value;
		next = object.next;
		previous = object.previous;
	}
}

Node& Node::operator=(const Node& object)
{
	if (this != &object)
	{
		value = object.value;
		next = object.next;
		previous = object.previous;
	}
	return *this;
}

int Node::get_value()
{
	return value;
}

Node* Node::get_next()
{
	return next;
}

Node* Node::get_previous()
{
	return previous;
}

void Node::set_value(int Value)
{
	value = Value;
}

void Node::set_next(Node* Next)
{
	next = Next;
}

void Node::set_previous(Node* Previous)
{
	previous = Previous;
}

DoubleList::DoubleList() :
	head(new Node),
	tail(new Node)
{
	head->set_next(tail);
	tail->set_previous(head);
	Size = 0;
}

DoubleList::DoubleList(int num, ...) :
	head(new Node),
	tail(new Node)
{
	head->set_next(tail);
	tail->set_previous(head);
	Size = 0;
	if (num > 0)
	{
		int param;
		va_list argptr;

		va_start(argptr, num);

		for (; num; num--)
		{
			param = va_arg(argptr, int);
			push_back(param);
		}

		va_end(argptr);
	}
}

DoubleList::DoubleList(const DoubleList& object) :
	head(new Node),
	tail(new Node)
{
	head->set_next(tail);
	tail->set_previous(head);
	Size = 0;

	*this = object;
}

void DoubleList::push_front(int value)
{
	head->set_next(new Node(value, head, head->get_next(), head->get_next(), false));
	Size++;
}

void DoubleList::push_back(int value)
{
	tail->set_previous(new Node(value, tail->get_previous(), tail, tail->get_previous()));
	Size++;
}

void DoubleList::push_key(int key, int value)
{
	Node* temp = head->get_next();
	for (; temp->get_value() != key && temp != tail; temp = temp->get_next());
	if (temp != tail)
	{
		temp->set_next(new Node(value, temp, temp->get_next(), temp->get_next(), false));
		Size++;
	}
	else
		push_back(value);
}

void DoubleList::push_index(int index, int value)
{
	Node* temp = head->get_next();
	for (int count = 0; count < index && temp != tail; temp = temp->get_next(), count++);
	if (temp != tail)
	{
		temp->set_previous(new Node(value, temp->get_previous(), temp, temp->get_previous()));
		Size++;
	}
	else
		push_back(value);
}

void DoubleList::pop_front()
{
	if (head->get_next() != tail)
	{
		Node* temp = head->get_next();
		head->set_next(temp->get_next());
		temp->get_next()->set_previous(head);
		Size--;
		delete temp;
	}
	//cout << head->next->previous << ' ' << head;
}

void DoubleList::pop_back()
{
	if (head->get_next() != tail)
	{
		Node* temp = tail->get_previous();
		tail->set_previous(temp->get_previous());
		temp->get_previous()->set_next(tail);
		Size--;
		delete temp;
	}
}

void DoubleList::pop_key(int key)
{
	Node* temp = head->get_next();
	for (; temp->get_value() != key && temp != tail; temp = temp->get_next());
	if (temp != tail)
	{
		temp->get_previous()->set_next(temp->get_next());
		temp->get_next()->set_previous(temp->get_previous());
		Size--;
		delete temp;
	}
}

void DoubleList::pop_index(int index)
{
	Node* temp = head->get_next();
	for (int count = 0; count != index && temp != tail; temp = temp->get_next(), count++);
	if (temp != tail)
	{
		temp->get_previous()->set_next(temp->get_next());
		temp->get_next()->set_previous(temp->get_previous());
		Size--;
		delete temp;
	}
}

Node& DoubleList::find(int key)
{
	tail->set_value(0);
	Node* ptr = head->get_next();
	for (; ptr->get_value() != key && ptr != tail; ptr = ptr->get_next());
	return *ptr;
}

void DoubleList::copy()
{
	Node* theEnd = tail->get_previous();
	for (Node* ptr = head->get_next(); ptr != theEnd->get_next(); ptr = ptr->get_next())
		push_back(ptr->get_value());
}

void DoubleList::clear()
{
	while (head->get_next() != tail)
		pop_back();
}

void DoubleList::print()
{
	for (Node* temp = head->get_next(); temp != tail; temp = temp->get_next())
		std::cout << temp->get_value() << ' ';
}

int DoubleList::size()
{
	return Size;
}

void DoubleList::add(int num, ...)
{
	int param;
	va_list argptr;

	va_start(argptr, num);

	for (; num; num--)
	{
		param = va_arg(argptr, int);
		push_back(param);
	}

	va_end(argptr);
}

void DoubleList::del(int num, ...)
{
	int param;
	va_list argptr;

	va_start(argptr, num);

	for (; num; num--)
	{
		param = va_arg(argptr, int);
		pop_key(param);
	}

	va_end(argptr);
}

void DoubleList::set(int size, int limit)
{
	for (int i = 0; i < size; i++)
		push_back((rand() % limit) * (rand() % 2 ? 1 : -1));
}

void DoubleList::set(int* mas, int size)
{
	for (int i = 0; i < size; i++)
		push_back(mas[i]);
}

void DoubleList::set(const char *name)
{
	std::ifstream file(name);
	if (file.is_open())
	{
		int num;
		while (!file.eof())
		{
			file >> num;
			push_back(num);
		}
	}
	file.close();
}

DoubleList& DoubleList::operator=(const DoubleList& object)
{
	if (this != &object)
	{
		this->clear();
		for (Node* temp = object.head->get_next(); temp != object.tail; temp = temp->get_next())
			this->push_back(temp->get_value());
	}
	return *this;
}

DoubleList& DoubleList::operator+=(const DoubleList& object)
{
	for (Node* temp = object.head->get_next(); temp != object.tail; temp = temp->get_next())
		this->push_back(temp->get_value());
	return *this;
}

DoubleList& DoubleList::operator-=(const DoubleList& object)
{
	for (Node* temp = object.head->get_next(); temp != object.tail; temp = temp->get_next())
		pop_key(temp->get_value());
	return *this;
}

Node& DoubleList::operator[](int ind)
{
	head->set_value(0);
	tail->set_value(0);
	Node* ptr = head;
	if (ind >= 0)
	{
		ptr = ptr->get_next();
		for (int count = 0; count < ind && ptr != tail; ptr = ptr->get_next(), count++);
	}
	return *ptr;
}

DoubleList DoubleList::operator+(const DoubleList& object)
{
	DoubleList temp(*this);
	temp += object;
	return temp;
}

DoubleList DoubleList::operator-(const DoubleList& object)
{
	DoubleList temp(*this);
	temp -= object;
	return temp;
}

std::istream& operator >> (std::istream &s, DoubleList &object)
{
	int value = 0;
	s >> value;
	object.push_back(value);
	return s;
}

std::ostream& operator << (std::ostream &s, DoubleList &object)
{
	for (Node* temp = object.head->get_next(); temp != object.tail; temp = temp->get_next())
		s << temp->get_value() << ' ';
	return s;
}

DoubleList::~DoubleList()
{
	while (head != nullptr)
	{
		tail = head;
		head = head->get_next();
		delete tail;
	}
}