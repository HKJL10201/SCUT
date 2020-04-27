#include<iostream>
using namespace std;

//Stack ADT
template<class E>
class Stack
{
private:
	void operator =(const Stack&) {}	//protect assignment
	Stack(const Stack&) {}		//protect copy constructor
public:
	Stack() {}			//default constructor
	virtual ~Stack() {}		//base destructor
	virtual void clear() = 0;
	virtual void push(const E& it) = 0;		//push it onto the top of the stack
	virtual E pop() = 0;					//remove and return the element on top
	virtual const E& topVal()const = 0;		//return a copy of the top element
	virtual int len()const = 0;				//return the number of elements

	virtual E& operator[](int n)const = 0;     //overload [] to get current element easily
	virtual void print()const = 0;			//print stack contents
};

//Array-based stack implementation
template<class E>
class AStack :public Stack<E>
{
private:
	int Max;		//size of stack
	int top;		//index of top element
	E *BaseArray;

public:
	AStack(int size = 10)
	{
		Max = size;
		top = 0;
		BaseArray = new E[size];
	}

	~AStack() { delete[] BaseArray; }

	void incre()        //increase the size of list
	{
		E* temp = BaseArray;
		Max += 10;
		BaseArray = new E[Max];
		for (int i = 0; i<top; i++)
		{
			BaseArray[i] = temp[i];
		}
		delete[] temp;
	}

	void clear() { top = 0; }		//Reinitialize

	void push(const E& it)		//put it on stack
	{
		if (top >= Max)incre();
		BaseArray[top++] = it;
	}

	E pop()		//pop top element
	{
		if (top == 0)
		{
			cerr << "\nStack is empty\n";
			abort();
		}
		return BaseArray[--top];
	}

	const E& topVal()const		//return top element
	{
		if (top == 0)
		{
			cerr << "\nStack is empty\n";
			abort();
		}
		return BaseArray[top - 1];
	}

	int len()const { return top; }		//return length

	E& operator[](int n)const
	{
		if (n < 0 || n >= top)
		{
			cerr << "\nIndex out of range\n";
			abort();
		}
		//Assert((n >= 0) && (n <= Top), "Pos out of range");
		return BaseArray[n];
	}

	void print()const		//print list contents
	{
		cout << '[';
		if (top != 0)
			cout << BaseArray[0];
		for (int i = 1; i<top; i++)
		{
			cout << ", " << BaseArray[i];
		}
		cout << endl;
	}
};

//singly linked list node with freelist support
template<class E>
class Link
{
private:
	static Link<E>* freelistHead;
public:
	E elem;
	Link *next;

	Link(const E& elemval, Link* nextval = NULL)
	{
		elem = elemval;
		next = nextval;
	}
	Link(Link* nextval = NULL) { next = nextval; }

	void* operator new(size_t)
	{
		if (freelistHead == NULL)
			return ::new Link;		//create space
		Link<E>* temp = freelistHead;		//can take from freelist
		freelistHead = freelistHead->next;
		return temp;		//return the link
	}

	void operator delete(void* p)
	{
		((Link<E>*)p)->next = freelistHead;		//put on freelist
		freelistHead = (Link<E>*)p;
	}
};
//the freelist head pointer is actually created here
template<class E>
Link<E>* Link<E>::freelistHead = NULL;

//Linked stack implementation
template<class E>
class LStack :public Stack<E>
{
private:
	Link<E>* top;		//pointer to the first element
	int size;			//number of elements

public:
	LStack(int sz = 0)
	{
		top = NULL;
		size = 0;
	}
	~LStack() { clear(); }

	void clear()		//reinitialize
	{
		while (top != NULL)
		{
			Link<E>* temp = top;
			top = top->next;
			delete temp;
		}
		size = 0;
	}

	void push(const E& it)		//put it on stack
	{
		top = new Link<E>(it, top);
		size++;
	}

	E pop()		//remove it from stack
	{
		if (top == NULL)
		{
			cerr << "\nStack is empty\n";
			abort();
		}
		E it = top->elem;
		Link<E>* temp = top->next;
		delete top;
		top = temp;
		size--;
		return it;
	}

	const E& topVal()const		//return top value
	{
		if (top == NULL)
		{
			cerr << "\nStack is empty\n";
			abort();
		}
		return top->elem;
	}

	int len()const { return size; }		//return length

	E& operator[](int n)const
	{
		if (n<0 || n>size)
		{
			cerr << "\nPosition out of range\n";
			abort();
		}
		Link<E>* temp = top;
		for (int i = 0; i < size - 1 - n; i++)
			temp = temp->next;
		return temp->elem;
	}

	void print()const		//print list contents
	{
		Link<E>* temp = top;
		if (temp != NULL)
		{
			cout << temp->elem;;
			temp = temp->next;
		}
		while (temp != NULL)
		{
			cout << ", " << temp->elem;;
			temp = temp->next;
		}
		cout << "]\n";
	}
};

int main()
{
	AStack<int> A;
	for (int i = 0; i<50; i++)
	{
		A.push(i + 1);
	}
	
	A.print();

	LStack<int> L;
	for (int i = 0; i<20; i++)
	{
		L.push(i + 1);
	}
	L.print();


	for (int i = 0; i < 10; i++)
	{
		A.pop();
	}
	for (int i = 0; i < 5; i++)
	{
		L.pop();
	}

	for (int i = 0; i < A.len(); i++)
	{
		cout << A[i] << ' ';
	}
	cout << endl;
	for (int i = 0; i < L.len(); i++)
	{
		cout << L[i] << ' ';
	}
	cout << endl;

	system("pause");
	return 0;
}