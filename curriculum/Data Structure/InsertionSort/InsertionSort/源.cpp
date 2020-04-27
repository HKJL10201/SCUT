#include<iostream>
using namespace std;

template<class E>
void inssort(E A[], int n)
{
	for (int i = 1; i < n; i++)
		for (int j = i; (j > 0) && (A[j] < A[j - 1]); j--)
			Swap<E>(A, j, j - 1);
}
template<class E>
void Swap(E A[], int i, int j)
{
	E temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}
