#include<iostream>
using namespace std;

//List ADT
template<class E>
class List
{
private:
	void operator = (const List&) {} //protect assignment
	List(const List&) {}     //protect copy constructor
public:
	List() {}                //default constructor
	virtual ~List() {}       //base destructor
	virtual void clear() = 0;
	virtual void insert(const E& it) = 0;     //insert it in current position
	virtual void append(const E& it) = 0;     //append it at the end of list
	virtual E remove() = 0;                   //remove and return the current element
	virtual void ToStart() = 0;           //set curr to the start
	virtual void ToEnd() = 0;             //set curr to the end
	virtual void prev() = 0;              //move curr to one step left
	virtual void next() = 0;              //move curr to one step right
	virtual int len()const = 0;               //return the number of elements
	virtual int curr()const = 0;              //return current position
	virtual void moveTo(int pos) = 0;         //move curr to pos
	virtual const E& get()const = 0;          //return the current element

	virtual E& operator[](int n)const = 0;     //overload [] to get current element easily
	virtual void print()const = 0;			//print list contents
};

//Arrayy-based list implementation
template<class E>
class AList :public List<E>
{
private:
	int Max;        //size of array
	int Len;        //number of elements
	int fence;       //current position
	E* BaseArray;
public:
	AList(int size = 10)
	{
		Max = size;
		Len = fence = 0;
		BaseArray = new E[Max];
	}

	~AList() { delete[] BaseArray; }

	void incre()        //increase the size of list
	{
		E* temp = BaseArray;
		Max += 10;
		BaseArray = new E[Max];
		for (int i = 0; i<Len; i++)
		{
			BaseArray[i] = temp[i];
		}
		delete[] temp;
	}

	void clear()        //reinitialize the list
	{
		delete[] BaseArray;     //remove the array
		Len = fence = 0;             //reset the size
		BaseArray = new E[Max];   //recreate array
	}

	void insert(const E& it)
	{
		if (Len >= Max)incre();
		for (int i = Len; i>fence; i--)    //shift up
		{
			BaseArray[i] = BaseArray[i - 1];    //to make room
		}
		BaseArray[fence] = it;
		Len++;      //increase size
	}

	void append(const E& it)
	{
		if (Len >= Max)incre();
		BaseArray[Len++] = it;
	}

	E remove()
	{
		if (fence < 0 || fence >= Len)
		{
			cerr << "\nNo element\n";
			abort();
		}
		//Assert((Curr >= 0) && (Curr<Len), "No element");
		E it = BaseArray[fence];       //copy
		for (int i = fence; i<Len - 1; i++)    //shift down
		{
			BaseArray[i] = BaseArray[i + 1];
		}
		Len--;      //decrease size
		return it;
	}

	void ToStart() { fence = 0; }
	void ToEnd() { fence = Len; }

	void prev() { if (fence != 0)fence--; }
	void next() { if (fence<Len)fence++; }

	int len()const { return Len; }
	int curr()const { return fence; }

	void moveTo(int pos)
	{
		if (pos < 0 || pos > Len)
		{
			cerr << "\nPosition out of range\n";
			abort();
		}
		//Assert((pos >= 0) && (pos <= Len), "Pos out of range");
		fence = pos;
	}

	const E& get()const
	{
		if (fence < 0 || fence >= Len)
		{
			cerr << "\nNo current element\n";
			abort();
		}
		//Assert((Curr >= 0) && (Curr<Len), "No current element");
		return BaseArray[fence];
	}

	E& operator[](int n)const
	{
		if (n < 0 || n >= Len)
		{
			cerr << "\nIndex out of range\n";
			abort();
		}
		//Assert((n >= 0) && (n <= Len), "Pos out of range");
		return BaseArray[n];
	}

	void print()const		//print list contents
	{
		cout << '[';
		if (Len != 0)
			cout << BaseArray[0];
		for (int i = 1; i<Len; i++)
		{
			cout << ", " << BaseArray[i];
		}
		cout << "]\n";
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

//Linked list implementation
template<class E>
class LList :public List<E>
{
private:
	Link<E>* head;
	Link<E>* tail;
	Link<E>* fence;
	int Len;		//size of list

	void init()		//Initialization helper
	{
		fence = tail = head = new Link<E>;
		Len = 0;
	}

	void removeAll()		//clear helper
	{
		while (head != NULL)
		{
			fence = head;
			head = head->next;
			delete fence;
		}
	}

public:
	LList() { init(); }
	~LList() { removeAll(); }

	void clear() { removeAll(); init(); }

	void insert(const E& it)
	{
		fence->next = new Link<E>(it, fence->next);
		if (tail == fence)
			tail = fence->next;		//New tail
		Len++;
	}

	void append(const E& it)
	{
		tail = tail->next = new Link<E>(it, NULL);
		Len++;
	}

	E remove()		//remove and return current element
	{
		if (fence->next == NULL)
		{
			cerr << "\nNo element\n";
			abort();
		}
		E it = fence->next->elem;		//remember value
		Link<E>* temp = fence->next;		//remember link node
		if (tail == fence->next)tail = fence;		//reset tail
		fence->next = fence->next->next;		//remove form list
		delete temp;						//reclaim space
		Len--;
		return it;
	}

	void ToStart() { fence = head; }	//place fence at front
	void ToEnd() { fence = tail; }		//place fence at the end

	void prev()		//move one step prev
	{
		if (fence == head)return;	//No previous element
		Link<E>* temp = head;
		while (temp->next != fence) temp = temp->next;
		fence = temp;
	}

	void next() { if (fence != tail)fence = fence->next; }		//move one step next

	int len()const { return Len; }		//return the number of elements

	int curr()const		//return the position of current element
	{
		Link<E>* temp = head;
		int i;
		for (i = 0; fence != temp; i++)
			temp = temp->next;
		return i;
	}

	void moveTo(int pos)
	{
		if (pos<0 || pos>Len)
		{
			cerr << "\nPosition out of range\n";
			abort();
		}
		fence = head;
		for (int i = 0; i < pos; i++)
			fence = fence->next;
	}

	const E& get()const		//return current element
	{
		if (fence->next == NULL)
		{
			cerr << "\nNo value\n";
			abort();
		}
		return fence->next->elem;
	}

	E& operator[](int n)const
	{
		if (n<0 || n>Len)
		{
			cerr << "\nPosition out of range\n";
			abort();
		}
		Link<E>* temp = head;
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
		cout << '[';
		temp = head;
		if (temp->next != NULL)
		{
			cout << temp->next->elem;;
			temp = temp->next;
		}
		while (temp->next != NULL)
		{
			cout << ", " << temp->next->elem;;
			temp = temp->next;
		}
		cout << "]\n";
	}
};

int main()
{
	AList<int> A;
	for (int i = 0; i<50; i++)
	{
		A.append(i + 1);
	}
	A.print();
	

	LList<int> L;
	for (int i = 0; i<20; i++)
	{
		L.append(i + 1);
	}
	L.print();
	
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

	for (A.ToStart(); A.curr()<A.len(); A.next())
	{
		int it;
		it = A.get();
		cout << it << '\t';
	}
	cout << endl;

	for (L.ToStart(); L.curr()<L.len(); L.next())
	{
		int it;
		it = L.get();
		cout << it << '\t';
	}
	cout << endl;
	
	system("pause");
	return 0;
}