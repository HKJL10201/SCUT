#include<iostream>
#include<time.h>
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

	void setVal(const E& it)
	{
		fence->next->elem = it;
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


template<class E>
void mergesort_A(E A[], E temp[], int left, int right)
{
	int mid = (left + right) / 2;
	if (left == right)return;
	mergesort_A<E>(A, temp, left, mid);
	mergesort_A<E>(A, temp, mid + 1, right);
	int i, j, k;
	for (i = mid; i >= left; i--) temp[i] = A[i];
	for (j = 1; j <= right - mid; j++)
		temp[right - j + 1] = A[j + mid];

	for (i = left, j = right, k = left; k <= right; k++)
		if (temp[i] < temp[j]) A[k] = temp[i++];
		else A[k] = temp[j--];
}

template<class E>
void mergesort_L(LList<E> &A, LList<E> &temp, int left, int right)
{
	int mid = (left + right) / 2;
	if (left == right)return;
	mergesort_L<E>(A, temp, left, mid);
	mergesort_L<E>(A, temp, mid + 1, right);
	A.moveTo(mid);
	temp.moveTo(mid);
	int i, j, k;
	for (i = mid; i >= left; i--)
	{
		temp.setVal(A.get());
		A.prev();
		temp.prev();
	}
	A.moveTo(mid + 1);
	temp.moveTo(right);
	for (j = 1; j <= right - mid; j++)
	{
		temp.setVal(A.get());
		A.next();
		temp.prev();
	}

	for (i = left, j = right, k = left; k <= right; k++)
	{
		A.moveTo(k);
		if (temp[i] < temp[j])
			A.setVal(temp[i++]);
		else 
			A.setVal(temp[j--]);
	}
}

int main()
{
	const int n = 100;		//测试列表的数据量为10000
	int a[n];
	int at[n] = { 0 };		//atemp全为0
	for (int i = 0; i < n; i++)		//初始化数组a，10000~1
		a[i] = n - i;
	clock_t t1, t2, t3, t4;		//时间戳
	double toa, tol;			//耗时
	t1 = clock();
	mergesort_A<int>(a, at, 0, n - 1);		//Runing Array-based version of Mergesort
	t2 = clock();
	toa = (double)(t2 - t1) / CLOCKS_PER_SEC;
	cout << t1 << ' ' << t2 << "\nTime cost:" << toa << "s\n";		//输出时间戳和耗时

	LList<int> A, AT;
	for (int i = 0; i < n; i++)		//初始化链表A和Atemp
	{
		A.append(n - i);		//10000~1
		AT.append(0);			//全为0
	}
	t3 = clock();
	mergesort_L<int>(A, AT, 0, n - 1);		//Runing Linked list-based version of Mergesort
	t4 = clock();
	tol = (double)(t4 - t3) / CLOCKS_PER_SEC;
	//A.print();
	cout << t3 << ' ' << t4 << "\nTime cost:" << tol << "s\n";		//输出时间戳和耗时
	system("pause");
	return 0;
}