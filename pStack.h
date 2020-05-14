template <typename T>
class pStack
{
private:

	struct element
	{
		T value;
		element* next;
	};

	size_t size;
	size_t limit;
	element* first;

public:

	pStack();
	pStack(const size_t& max_size);
	pStack(const pStack<T>& item1, const pStack<T>& item2);
	~pStack();

	void push(const T& value);
	void merge(const pStack<T>& item);
	void merge(const pStack<T>& item1, const pStack<T>& item2);

	T top();
	T pop();
	bool empty();
};

template <typename T>
pStack<T>::pStack()
{
	first = 0;
	this->size = 0;
	this->limit = 10;
}

template <typename T>
pStack<T>::pStack(const size_t& max_size)
{
	first = 0;
	this->size = 0;
	this->limit = max_size;
}

template <typename T>
pStack<T>::pStack(const pStack<T>& item1, const pStack<T>& item2)
{
	first = 0;
	this->size = 0;
	this->limit = item1.limit + item2.limit;

	pStack<T>* tempStack = new pStack<T>(item1.size + item2.size);
	const element* source = item1.first;

	while (source)
	{
		tempStack->push(source->value);
		source = source->next;
	}

	source = item2.first;

	while (source)
	{
		tempStack->push(source->value);
		source = source->next;
	}

	source = tempStack->first;

	while (source)
	{
		push(source->value);
		source = source->next;
	}

	delete tempStack;
}

template <typename T>
pStack<T>::~pStack()
{
	if (!first) return;
	element* temp = first;
	element* delTemp = 0;
	do
	{
		delTemp = temp;
		temp = temp->next;
		delete[] delTemp;
	} while (temp->next);
}

template <typename T>
void pStack<T>::push(const T& value)
{
	if (size >= limit) throw("stack overflow");
	element* temp = new element;
	temp->value = value;
	temp->next = first;
	first = temp;
	size++;
}

template <typename T>
void pStack<T>::merge(const pStack<T>& item)
{
	if (this->limit - this->size < item.size) throw("not enough stack size to merge");

	pStack<T>* tempStack = new pStack<T>(item.size + this->size);
	const element* source;

	while (!empty())
	{
		tempStack->push(pop());
	}

	source = item.first;

	while (source)
	{
		tempStack->push(source->value);
		source = source->next;
	}

	while (!empty()) pop();

	source = tempStack->first;

	while (source)
	{
		push(source->value);
		source = source->next;
	}

	delete tempStack;
}

template <typename T>
void pStack<T>::merge(const pStack<T>& item1, const pStack<T>& item2)
{
	if (this->limit - this->size < item1.size + item2.size) throw("not enough stack size to merge");

	pStack<T>* tempStack = new pStack<T>(item1.size + item2.size);
	const element* source = item1.first;

	while (source)
	{
		tempStack->push(source->value);
		source = source->next;
	}

	source = item2.first;

	while (source)
	{
		tempStack->push(source->value);
		source = source->next;
	}

	source = tempStack->first;

	while (source)
	{
		push(source->value);
		source = source->next;
	}

	delete tempStack;
}

template <typename T>
T pStack<T>::top()
{
	return first->value;
}

template <typename T>
T pStack<T>::pop()
{
	if (!first) throw("stack empty before pop");
	element* temp = first;
	T value = first->value;
	first = temp->next;
	delete temp;
	size--;
	return value;
}

template <typename T>
bool pStack<T>::empty()
{
	return (size == 0);
}