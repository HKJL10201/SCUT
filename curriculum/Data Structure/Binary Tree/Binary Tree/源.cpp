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

	/*bool isEmpty()const
	{
		if (head == tail)
			return true;
		else
			return false;
	}*/
};


//Binary tree node abstract class
template<class E>
class BinNode
{
public:
	virtual ~BinNode() {}		//base destructor
	virtual E& val() = 0;		//return the node's value
	virtual void setVal(const E&) = 0;		//set the node's value
	virtual BinNode* left()const = 0;			//return left child
	virtual void setLeft(BinNode*) = 0;			//set the left child
	virtual BinNode* right()const = 0;			//return right child
	virtual void setRight(BinNode*) = 0;		//set the right child
	virtual bool isLeaf() = 0;			//return true if node is leaf otherwise return false
};

template<class E>
class BinTree
{
public:
	virtual BinNode<E>* getRoot() = 0;
	virtual void preorder(BinNode<E>* subroot) = 0;
	virtual void inorder(BinNode<E>* subroot) = 0;
	virtual void postorder(BinNode<E>* subroot) = 0;
};

template<class E>
class PtrBinNode :public BinNode<E>
{
private:
	E it;				//node's value
	PtrBinNode *lc;		//pointer to left child
	PtrBinNode *rc;		//pointer to right child
public:
	PtrBinNode() { lc = rc = NULL; }
	PtrBinNode(E e,PtrBinNode* l=NULL,PtrBinNode* r=NULL)
	{ it = e; lc = l; rc = r; }
	E& val() { return it; }
	void setVal(const E& e) { it = e; }
	BinNode<E>* left()const			//return left child
	{ return lc; }
	void setLeft(BinNode<E>* b)			//set the left child
	{ lc = (PtrBinNode*)b; }
	BinNode<E>* right()const			//return right child
	{ return rc; }
	void setRight(BinNode<E>* b)			//set the right child
	{ rc = (PtrBinNode*)b; }
	bool isLeaf()
	{ return (lc == NULL) && (rc == NULL); }
};

template<class E>
class LBinTree :public BinTree<E>
{
private:
	PtrBinNode<E>* root;
public:
	LBinTree()
	{
		root = new PtrBinNode<E>;
	}
	BinNode<E>* getRoot() { return root; }
	void preorder(BinNode<E>* subroot)
	{
		if (subroot == NULL)return;
		visit(subroot);
		preorder(subroot->left());
		preorder(subroot->right());
	}
	void inorder(BinNode<E>* subroot)
	{
		if (subroot == NULL)return;
		preorder(subroot->left());
		visit(subroot);
		preorder(subroot->right());
	}
	void postorder(BinNode<E>* subroot)
	{
		if (subroot == NULL)return;
		preorder(subroot->left());
		preorder(subroot->right());
		visit(subroot);
	}
	void visit(BinNode<E>* subroot)const
	{
		cout << subroot->val();
		return;
	}
	void testBuild(const E& a, const E& b, const E& c, const E& d, const E& e, const E& f, const  E& g, const E& h, const  E& i)
	{
		root->setVal(a);											// Structure of this Building example:
		root->setLeft(new PtrBinNode<E>(b));						//              A		
		root->setRight(new PtrBinNode<E>(c));						//             / \		
		root->left()->setRight(new PtrBinNode<E>(d));				//            B   C		
		root->right()->setLeft(new PtrBinNode<E>(e));				//            \   /\	
		root->right()->setRight(new PtrBinNode<E>(f));				//             D E  F	
		root->right()->left()->setLeft(new PtrBinNode<E>(g));		//              /   /\	
		root->right()->right()->setLeft(new PtrBinNode<E>(h));		//             G   H  I	
		root->right()->right()->setRight(new PtrBinNode<E>(i));		//
	}

	int countLeaves(BinNode<E>* subroot)const		//递归法计算叶节点数量
	{
		if (subroot == NULL)
			return 0;
		if (subroot->isLeaf())
			return 1;
		else
			return countLeaves(subroot->left()) + countLeaves(subroot->right());
	}
};

template<class E>
class LayerNode				//二维链表节点类：每一个节点代表二叉树的一层
{
public:
	LayerNode* next;		//下一个节点的指针
	LList<E> subList;		//数据成员：一个链接列表，代表该层次的节点数，简称该层次的子列表

	LayerNode(const E& elemval, LayerNode* nextval = NULL)		//构造函数：传入数据直接添加到子列表
	{
		subList.append(elemval);
		next = nextval;
	}
	LayerNode(LayerNode* nextval = NULL) { next = nextval; }		//无参构造函数
};

template<class E>
class SupList :public LayerNode<E>		//二维链表类
{
private:
	LayerNode<E>* head;		//头指针
	LayerNode<E>* tail;
	LayerNode<E>* fence;
	int layer;		//size of list

	void init()		//Initialization helper
	{
		fence = tail = head = new LayerNode<E>;
		layer = 0;
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
	SupList() { init(); }
	~SupList() { removeAll(); }

	void clear() { removeAll(); init(); }

	void newLayer(const E& it)			//增加二维链表的节点
	{
		tail = tail->next = new LayerNode<E>(it, NULL);
		layer++;
	}

	bool isEmptyLayer(int n)const			//判断第n层是否为空（层次从1开始）
	{
		if (n > layer)
			return true;
		else
			return false;
	}

	void addInLayer(int n, const E& it)			//将数据添加到第n层的子列表中
	{
		if (n<0 || n>layer)
		{
			cerr << "\nPosition out of range\n";
			abort();
		}
		LayerNode<E>* temp = head;
		for (int i = 1; i < n; i++)
			temp = temp->next;
		if (temp->next == NULL)
		{
			cerr << "\nNo value\n";
			abort();
		}
		temp->next->subList.append(it);
	}

	int hight()const { return layer; }		//返回树的高度（即二维链表的节点数）

	void print()const		//打印该二维链表
	{
		LayerNode<E>* temp = head;
		for (int i = 0; i < layer; i++)
		{
			temp->next->subList.print();
			temp = temp->next;
		}
	}
};

template<class E>
class LayerListMaker			//将二叉树转换为二维链表的类
{
public:
	SupList<E> SList;
	void maker(BinNode<E>* root, int lay = 0)		//利用类似前序遍历的递归方法，把二叉树中的数据按层添加到二维链表中
	{
		if (root == NULL)return;
		int layer = lay + 1;			//记录了该层是第几层（从1开始计数）
		if (SList.isEmptyLayer(layer))		//如果该层为空
			SList.newLayer(root->val());		//创建新层次
		else
			SList.addInLayer(layer, root->val());		//否则将数据添加到这一层的子列表中
		maker(root->left(), layer);			//递归调用左子树
		maker(root->right(), layer);		//递归调用右子树
	}
};

int main()
{
	LBinTree<int> a;
	a.testBuild(1, 2, 3, 4, 5, 6, 7, 8, 9);			//构建一棵测试用例的二叉树
	cout << "测试样例：\n     1\n    / \\ \n   2   3\n   \\   /\\ \n    4 5  6\n     /   /\\ \n    7   8  9\n";
	cout << "\n先序遍历：\n";
	a.preorder(a.getRoot());			//先序遍历

	LayerListMaker<int> m;			//创建二维链表对象
	m.maker(a.getRoot());			//将二叉树转换为二维链表
	cout << "\n\n按层打印树节点：\n";
	m.SList.print();		//打印二维链表

	cout << "\n\n树的总高度：";
	cout << m.SList.hight() << endl;

	cout << "\n\n树的叶节点数：";
	cout << a.countLeaves(a.getRoot()) << endl;
	system("pause");
	return 0;
}