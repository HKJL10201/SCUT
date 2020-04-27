#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<time.h>
#include<cstdlib>
using namespace std;
#define random(a,b) (((double)rand()/RAND_MAX)*(b-a)+a)

struct num
{
	int times;
	int pos;
};

// The Dictionary abstract class.
template <typename Key, typename E>
class Dictionary 
{
private:
	void operator =(const Dictionary&) {}
	Dictionary(const Dictionary&) {}
public:
	Dictionary() {} // Default constructor
	virtual ~Dictionary() {} // Base destructor
	// Reinitialize dictionary
	virtual void clear() = 0;
	// Insert a record
	// k: The key for the record being inserted.
	// e: The record being inserted.
	virtual num insert(const Key& k, const E& e) = 0;
	// Remove and return a record.
	// k: The key of the record to be removed.
	// Return: A maching record. If multiple records match
	// "k", remove an arbitrary one. Return NULL if no record
	// with key "k" exists.
	virtual num remove(const Key& k) = 0;
	// Remove and return an arbitrary record from dictionary.
	// Return: The record removed, or NULL if none exists.
	virtual E removeAny() = 0;
	// Return: A record matching "k" (NULL if none exists).
	// If multiple records match, return an arbitrary one.
	// k: The key of the record to find
	virtual E find(const Key& k) const = 0;
	// Return the number of records in the dictionary.
	virtual int size() = 0;
};

// Container for a key-value pair
template <typename Key, typename E>
class KVpair {
private:
	Key k;
	E e;
public:
	// Constructors
	KVpair() {}
	KVpair(Key kval, E eval)
	{
		k = kval; e = eval;
	}
	KVpair(const KVpair& o) // Copy constructor
	{
		k = o.k; e = o.e;
	}
	void operator =(const KVpair& o) // Assignment operator
	{
		k = o.k; e = o.e;
	}
	// Data member access functions
	Key key() { return k; }
	void setKey(Key ink) { k = ink; }
	E value() { return e; }
};

// Dictionary implemented with a hash table
template <typename Key, typename E>
class hashdict : public Dictionary<Key, E>
{
private:
	KVpair<Key, E>* HT; // The hash table
	int M; // Size of HT
	int currcnt; // The current number of elements in HT
	Key EMPTYKEY; // User-supplied key value for an empty slot
	int p(Key K, int i) const // Probe using linear probing
	{
		srand(M);
		return rand();
	}
	int h(int x) const { return x % M; } // Poor hash function
	int h(char* x) const { // Hash function for character keys
		int i, sum;
		for (sum = 0, i = 0; x[i] != '\0'; i++) sum += (int)x[i];
		return sum % M;
	}
	num hashInsert(const Key&, const E&);
	E hashSearch(const Key&) const;
public:
	hashdict(int sz, Key k) // "k" defines an empty slot
	{
		M = sz;
		EMPTYKEY = k;
		currcnt = 0;
		HT = new KVpair<Key, E>[sz]; // Make HT of size sz
		for (int i = 0; i < M; i++)
			(HT[i]).setKey(EMPTYKEY); // Initialize HT
	}
	~hashdict() { delete[] HT; }
	// Find some record with key value "K"
	void clear()
	{
		currcnt = 0;
		for (int i = 0; i < M; i++)
			(HT[i]).setKey(EMPTYKEY); // Initialize HT
	}
	E find(const Key& k) const
	{
		return hashSearch(k);
	}
	int size() { return currcnt; } // Number stored in table
	// Insert element "it" with Key "k" into the dictionary.
	num insert(const Key& k, const E& it) 
	{
		num t;
		t.times = 0; t.pos = 0;
		//Assert(currcnt < M, "Hash table is full");
		if (currcnt >= M)
		{
			cerr << "Hash table is full\n";
			return t;
		}
		t = hashInsert(k, it);
		currcnt++;
		return t;
	}
	num remove(const Key& k)
	{
		num t;
		t.times = 1;
		t.pos = -1;
		int home; // Home position for k
		int pos = home = h(k); // Initial position is home slot
		for (int i = 1; HT[pos].key() != k && i < M; i++)
		{
			t.times++;
			pos = (home + p(k, i)) % M; // Next on probe sequence
		}
		if (HT[pos].key() == EMPTYKEY)
		{
			cerr << "empty remove\n";
		}
		if ((HT[pos]).key() == k) // Found it
		{
			HT[pos].setKey(EMPTYKEY);
			t.pos = pos;
			currcnt--;
			return t;
			//return (HT[pos]).value();
		}
		else return t; // k not in hash table
	}
	E removeAny()
	{
		for (int i = 0; i < M; i++)
		{
			if (HT[i].key() != EMPTYKEY)
			{
				HT[i].setKey(EMPTYKEY);
				return HT[i].value();
			}
		}
		return NULL;
	}
};

// Insert e into hash table HT
template <typename Key, typename E>
num hashdict<Key, E>::
hashInsert(const Key& k, const E& e) {
	num nm;
	nm.times = 1;
	int home; // Home position for e
	int pos = home = h(k); // Init probe sequence
	for (int i = 1; EMPTYKEY != (HT[pos]).key(); i++)
	{
		pos = (home + p(k, i)) % M; // probe
		nm.times++;
		//Assert(k != (HT[pos]).key(), "Duplicates not allowed");
		if (k == (HT[pos]).key())
		{
			cerr << "Duplicates not allowed\n";
			return nm;
		}
	}
	KVpair<Key, E> temp(k, e);
	HT[pos] = temp;
	nm.pos = pos;
	return nm;
}

// Search for the record with Key K
template <typename Key, typename E>
E hashdict<Key, E>::
hashSearch(const Key& k) const 
{
	int home; // Home position for k
	int pos = home = h(k); // Initial position is home slot
	for (int i = 1; (k != (HT[pos]).key()) && (EMPTYKEY != (HT[pos]).key()); i++)
		pos = (home + p(k, i)) % M; // Next on probe sequence
	if (k == (HT[pos]).key()) // Found it
		return (HT[pos]).value();
	else return NULL; // k not in hash table
}

int main()
{
	fstream fi, fo;
	fi.open("res_in.txt", ios::out);
	fo.open("res_out.txt", ios::out);
	if (!fi)
	{
		cerr << "File could not open.\n";
		abort();
	}
	if (!fo)
	{
		cerr << "File could not open.\n";
		abort();
	}
	for (int z = 0; z < 1; z++)
	{
		srand((int)time(0));
		int n = 100;
		hashdict<int, int> HD(n, -1);
		
		int *x = NULL;
		x = new int[n * 10];
		for (int i = 0; i < n * 10; i++)
		{
			x[i] = i;
		}
		for (int i = 0; i < n*0.25; i++)
		{
			int r = random(i, n * 10 - 1);
			swap(x[i], x[r]);
			num t = HD.insert(x[i], 1);
			fi << i << '\t' << x[i] << '\t' << t.times << '\t' << t.pos << '\t' << (double)HD.size() / n << '\n';
		}
		for (int i = 0; i < n*0.25; i++)
		{
			num t = HD.remove(x[i]);
			fo << i << '\t' << x[i] << '\t' << t.times << '\t' << t.pos << '\t' << (double)HD.size() / n << '\n';
		}
		//system("pause");
	}
	fi.close();
	fo.close();
	return 0;
}