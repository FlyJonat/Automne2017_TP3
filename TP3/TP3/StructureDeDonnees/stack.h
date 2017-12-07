#ifndef _CHAINED_STACK_H_
//Laurent Ricard - 1562287

template <class T>
class Stack
{
	struct Box
	{
		T value;
		Box* next;
		Box(const T& value, Box* next) :value(value), next(next) {}
	};

	Stack(const Stack&) = delete;

	//Representation
	Box *first, *last;
	size_t sz;

public:

	//Constructeur et affectateur
	Stack();
	~Stack();

	//Accesseur
	T& front();
	T& back();
	const T& front() const;
	const T& back() const;

	//Capacite
	bool empty() const;
	size_t size() const;

	//Fonction generatrice
	void push(const T& value);
	void pop();
	void swap(Stack&) noexcept;
};

template<class T>
inline Stack<T>::Stack()
{
	first = nullptr;
	last = nullptr;
	sz = 0;
}

template<class T>
inline Stack<T>::~Stack()
{
	while (first != nullptr)
	{
		pop();
	}
}

template<class T>
inline T & Stack<T>::front()
{
	return first->value;
}

template<class T>
inline T & Stack<T>::back()
{
	return last->value;
}

template<class T>
inline const T & Stack<T>::front() const
{
	const return first->value;
}

template<class T>
inline const T & Stack<T>::back() const
{
	const return last->value;
}

template<class T>
inline bool Stack<T>::empty() const
{
	if (sz <= 0)
	{
		return true;
	}
	return false;
}

template<class T>
inline size_t Stack<T>::size() const
{
	return sz;
}

template<class T>
inline void Stack<T>::push(const T & value)
{
	Box * newBox = new Box(value, nullptr);
	if (last == nullptr)
	{
		last = newBox;
	}
	else
	{
		newBox->next = first;
	}
	first = newBox;
	sz++;
}

template<class T>
inline void Stack<T>::pop()
{
	if (last != nullptr)
	{
		T value = 0;
		value = first->value;
		Box* boxToPop = first;
		first = first->next;
		delete boxToPop;
		if (first == nullptr)
		{
			last = nullptr;
		}
		sz--;
	}
}

template<class T>
inline void Stack<T>::swap(Stack & other) noexcept
{
	Box *firstTemporaire = first;
	Box *lastTemporaire = last;
	size_t szTemporaire = sz;
	first = other.first;
	last = other.last;
	sz = other.sz;
	other.first = firstTemporaire;
	other.last = lastTemporaire;
	other.sz = szTemporaire;
}
#endif // !_CHAINED_STACK_H_