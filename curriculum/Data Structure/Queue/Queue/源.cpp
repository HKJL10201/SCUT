#include<iostream>
using namespace std;

//Queue ADT
template<class E>
class Queue
{
private:
	void operator =(const Queue&) {}	//protect assignment
	Queue(const Queue&) {}		//protect copy constructor

public:
	Queue() {}		//default constructor
	virtual ~Queue() {}		//base destructor
	virtual void clear() = 0;		//reinitialize
	virtual void enqueue(const E&) = 0;		//place  an element at rear
	virtual E dequeue() = 0;		//remove and return the element at front
	virtual const E& frontVal()const = 0;	//return a copy of front element
	virtual int len()const = 0;		//return the number of elements

	virtual E& operator[](int n)const = 0;     //overload [] to get current element easily
	virtual void print()const = 0;			//print list contents
};

//Array-based queue implementation
template<class E>
class AQueue :public Queue<E>
{
private:
	int Max;		//size of queue
	int front;		//index of front element
	int rear;		//index of rear element
	E *BaseArray;

public:
	AQueue(int size = 11)
	{
		Max = size + 1;
		rear = 0;
		front = 1;
		BaseArray = new E[Max];
	}
	~AQueue() { delete[] BaseArray; }

	
	void incre()        //increase the size of Queue
	{
		int length = len();
		E* temp = BaseArray;
		int Min = Max;
		Max += 10;
		BaseArray = new E[Max];
		for (int i = 0; i<length; i++)
		{
			BaseArray[(front + i) % Max] = temp[(front + i) % Min];
		}
		rear = (front + length - 1) % Max;
		delete[] temp;
	}
	

	void clear() { rear = 0; front = 1; }		//reinitialize

	void enqueue(const E& it)				//put it in queue
	{
		if (((rear + 2) % Max) == front)incre();
		rear = (rear + 1) % Max;		//circular increment
		BaseArray[rear] = it;
	}

	E dequeue()				//take element out
	{
		if (len() == 0)
		{
			cerr << "\nQueue is empty\n";
			abort();
		}
		E it = BaseArray[front];
		front = (front + 1) % Max;		//circular increment
		return it;
	}

	const E& frontVal()const			//get front value
	{
		if (len() == 0)
		{
			cerr << "\nQueue is empty\n";
			abort();
		}
		return BaseArray[front];
	}

	int len()const{return ((rear + Max) - front + 1) % Max;}		//return length

	E& operator[](int n)const
	{
		if (n < 0 || n >= len())
		{
			cerr << "\nIndex out of range\n";
			abort();
		}
		//Assert((n >= 0) && (n <= Len), "Pos out of range");
		return BaseArray[(front + n) % Max];
	}

	void print()const		//print list contents
	{
		int length = len();
		cout << "<-";
		if (length != 0)
			cout << BaseArray[front];
		for (int i = 1; i<length; i++)
		{
			cout << "<-" << BaseArray[(front + i) % Max];
		}
		cout << "<-\n";
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

//Linked queue implementation
template<class E>
class LQueue :public Queue<E>
{
private:
	Link<E>* front;
	Link<E>* rear;
	int size;

public:
	LQueue(int sz = 0)
	{
		front = rear = new Link<E>();
		size = sz;
	}
	~LQueue()
	{
		clear();
		delete front;
	}

	void clear()		//clear queue
	{
		while (front->next != NULL)		//delete each link node
		{
			rear = front;
			delete rear;
		}
		rear = front;
		size = 0;
	}

	void enqueue(const E& it)		//put element on rear 
	{
		rear->next = new Link<E>(it, NULL);
		rear = rear->next;
		size++;
	}

	E dequeue()			//remove element from front
	{
		if (size == 0)
		{
			cerr << "\nQueue is empty\n";
			abort();
		}
		E it = front->next->elem;		//store dequeue value
		Link<E>* temp = front->next;	//hold dequeue link
		front->next = temp->next;			//advance front
		if (rear == temp)rear = front;		//dequeue last element
		delete temp;			//delete link
		size--;
		return it;				//return element value
	}

	const E& frontVal()const		//get front element
	{
		if (size == 0)
		{
			cerr << "\nQueue is empty\n";
			abort();
		}
		return front->next->elem;
	}

	int len()const { return size; }

	E& operator[](int n)const
	{
		if (n<0 || n>size)
		{
			cerr << "\nPosition out of range\n";
			abort();
		}
		Link<E>* temp = front;
		for (int i = 0; i < n; i++)
			temp = temp->next;
		if (temp->next == NULL)
		{
			cerr << "\nNo value\n";
			abort();
		}
		return temp->next->elem;
	}

	void print()const		//print list contents
	{
		Link<E>* temp;
		cout << "<-";
		temp = front;
		if (temp->next != NULL)
		{
			cout << temp->next->elem;;
			temp = temp->next;
		}
		while (temp->next != NULL)
		{
			cout << "<-" << temp->next->elem;;
			temp = temp->next;
		}
		cout << "<-\n";
	}
};

int main()
{
	AQueue<int> A;
	for (int i = 0; i<50; i++)
	{
		A.enqueue(i + 1);
	}
	A.print();

	LQueue<int> L;
	for (int i = 0; i < 20; i++)
	{
		L.enqueue(i + 1);
	}
	L.print();

	for (int i = 0; i < 10; i++)
	{
		A.dequeue();
	}
	for (int i = 0; i < 5; i++)
	{
		L.dequeue();
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