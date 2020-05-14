/*
Шаблонный класс стека pStack
*/
template <typename T>
class pStack
{
// Приватные свойства и методы класса
private: 

	/*
	struct element - структура для хранения каждого элемента стека
	T value - данные, которые будут храниться в стеке
	element* next- указатель на следующий элемент стека

	size_t size - размер стека (количество элементов в стеке)
	size_t limit - максимальный размер стека
	element* first - указатель на первый элемент стека
	*/

	struct element
	{
		T value;
		element* next;
	};

	size_t size;
	size_t limit;
	element* first;

// Публичные свойства и методы класса
public:

	/*
	Конструктор по умолчанию.
	При создании элемента максимальный размер стека приравнивается к 10.
	*/
	pStack();
	/*
	Конструктор, в качестве параметра принимает максимальный размер массива.
	*/
	pStack(const size_t& max_size);
	/*
	Конструктор, в качестве параметров принимает два стека и объединяет их в один.
	В полученном стеке элементы будут расположены в следующем порядке:
	Сначала все элементы стека item1, после него все элементы стека item2.
	*/
	pStack(const pStack<T>& item1, const pStack<T>& item2);
	/*
	Деструктор, освобождает память во время удаления объекта.
	*/
	~pStack();

	/*
	Данный метод принимает в качестве параметра значение и помещает его в
	верхнюю часть стека.
	*/
	void push(const T& value);
	/*
	Данный метод объединяет два стека,
	элементы стека item помещаются после элементов исходного стека
	*/
	void merge(const pStack<T>& item);
	/*
	Метод объединения двух стеков в имеющийся.
	Первыми в полученном стеке будут элементы стека item1,
	далее будут идти элементы стека item2.
	*/
	void merge(const pStack<T>& item1, const pStack<T>& item2);
	
	/*
	Метод возвращает значение самого верхнего элемента стека.
	*/
	T top();
	/*
	Метод возвращает значение самого верхнего элемента стека,
	а также удаляет сам элемент из стека.
	*/
	T pop();
	/*
	Метод вернёт true, если стек пуст, либо false, если в стеке имеются элементы.
	*/
	bool empty();
};

template <typename T>
pStack<T>::pStack()
{
	first = 0;
	this->size = 0;
	// Максимальный размер по умолчанию равен 10, но его можно изменить.
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

	//Объявляется новый стек для временного хранения элементов
	pStack<T>* tempStack = new pStack<T>(item1.size + item2.size);

	// Объявляется указатель на первый элемент стека item1.
	const element* source = item1.first;

	// В цикле элементы из стека temp1 копируются во временный стек
	while (source)
	{
		tempStack->push(source->value);
		source = source->next;
	}

	// Указателю присваивается ссылка на первый элемент стека item2.
	source = item2.first;

	// В цикле элементы из стека temp1 копируются во временный стек
	while (source)
	{
		tempStack->push(source->value);
		source = source->next;
	}

	// Указателю присваивается ссылка на первый элемент временного стека.
	source = tempStack->first;

	// В цикле элементы временного стека копируются в исходный стек.
	while (source)
	{
		push(source->value);
		source = source->next;
	}

	// Удаление временного стека.
	delete tempStack;
}

template <typename T>
pStack<T>::~pStack()
{
	// Если элементов в стеке нет - ничего не удаляется.
	if (!first) return;
	// Объявляются временные указатели.
	element* temp = first;
	element* delTemp = 0;
	// В цикле поочерёдно удаляются все элементы стека.
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
	// Если размер стека превышает максимальный - выбрасывается исключение.
	if (size >= limit) throw("stack overflow");
	// Создаётся временная переменная.
	element* temp = new element;
	// Полю value присваивается значение из параметра.
	temp->value = value;
	// Указатель на следующий элемент копируется из указателя на первый элемент.
	temp->next = first;
	// Указателю на первый элемент присваивается адрес нового элемента
	first = temp;
	// Увеличивается размер стека
	size++;
}

template <typename T>
void pStack<T>::merge(const pStack<T>& item)
{
	// Выбрасывается исключение, если для новых элеметов в исходном стеке не хватает места.
	if (this->limit - this->size < item.size) throw("not enough stack size to merge");

	//Объявляется новый стек для временного хранения элементов
	pStack<T>* tempStack = new pStack<T>(item.size + this->size);

	// Объявляется указатель.
	const element* source;

	// В цикле элементы из исходного стека переносятся во временный стек
	while (!empty())
	{
		tempStack->push(pop());
	}

	// Указателю присваивается ссылка на первый элемент стека item.
	source = item.first;

	// В цикле элементы из стека temp копируются во временный стек.
	while (source)
	{
		tempStack->push(source->value);
		source = source->next;
	}

	// Указателю присваивается ссылка на первый элемент исходного стека.
	source = tempStack->first;

	// В цикле элементы временного стека копируются в исходный стек.
	while (source)
	{
		push(source->value);
		source = source->next;
	}

	// Удаление временного стека.
	delete tempStack;
}

template <typename T>
void pStack<T>::merge(const pStack<T>& item1, const pStack<T>& item2)
{
	if (this->limit - this->size < item1.size + item2.size) throw("not enough stack size to merge");

	pStack<T>* tempStack = new pStack<T>(item1.size + item2.size);
	const element* source = item1.first;

	// В цикле элементы из стека temp1 копируются во временный стек
	while (source)
	{
		tempStack->push(source->value);
		source = source->next;
	}

	source = item2.first;

	// В цикле элементы из стека temp2 копируются во временный стек
	while (source)
	{
		tempStack->push(source->value);
		source = source->next;
	}

	source = tempStack->first;

	// В цикле элементы временного стека копируются в исходный стек.
	while (source)
	{
		push(source->value);
		source = source->next;
	}

	// Удаление временного стека.
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
	// Если стек пуст - выбрасывается исключение.
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