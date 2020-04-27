#include<iostream>
#include<time.h>
#include<stack>
using namespace std;

template<class E>
void qsort(E A[], int i, int j)
{
	if (j <= i)return;		//List too small
	int pivot = findpivot(A, i, j);

	Swap<E>(A, pivot, j);	//Put pivot at end
	//k will be first position on right side
	int k = partition<E>(A, i, j, A[j]);
	Swap<E>(A, k, j);		//Put pivot in place
	qsort<E>(A, i, k - 1);
	qsort<E>(A, k + 1, j);
}
template <class E>
int findpivot(E A[], int i, int j)
{
	return (i + j) / 2;
}
template<class E>
int partition(E A[], int l, int r, E& pivot)
{
	do
	{
		while (A[l] < pivot)
			l++;
		while ((r > l) && A[r] >= pivot)
			r--;
		Swap<E>(A, l, r);		//Swap out-of-place values
	} while (l < r);	//Stop when they cross
	return l;		//return first pos on right
}
template<class E>
void Swap(E A[], int i, int j)
{
	E temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}


template<class E>
void qsort_pivot(E A[], int i, int j)
{
	if (j <= i)return;		//List too small
	int pivot = findpivot_new(A, i, j);

	Swap<E>(A, pivot, j);	//Put pivot at end
							//k will be first position on right side
	int k = partition<E>(A, i, j, A[j]);
	Swap<E>(A, k, j);		//Put pivot in place
	qsort_pivot<E>(A, i, k - 1);
	qsort_pivot<E>(A, k + 1, j);
}
template<class E>
int findpivot_new(E A[], int i, int j)
{
	int m = (i + j) / 2;
	if (A[i] > A[m])
		Swap<E>(A, i, m);
	if (A[i] > A[j])
		Swap<E>(A, i, j);
	if (A[m] > A[j])
		Swap<E>(A, m, j);
	return m;
}

template<class E>
void qsort_ins(E A[], int i, int j)
{
	if (j <= i)return;		//List too small
	if (select(j - i))
		inssort<E>(A, i, j);
	else
	{
		int pivot = findpivot(A, i, j);

		Swap<E>(A, pivot, j);	//Put pivot at end
								//k will be first position on right side
		int k = partition<E>(A, i, j, A[j]);
		Swap<E>(A, k, j);		//Put pivot in place
		qsort_ins<E>(A, i, k - 1);
		qsort_ins<E>(A, k + 1, j);
	}
}
template<class E>
void inssort(E A[], int l, int r)
{
	for (int i = l + 1; i <= r; i++)
		for (int j = i; (j > l) && (A[j] < A[j - 1]); j--)
			Swap<E>(A, j, j - 1);
}
bool select(int n)
{
	if (n <= 4)		//n*(n-1)/2与nlogn交点在3和4之间
		return true;
	else
		return false;
}

template<class E>
void qsort_n(E A[], int left, int right) 
{
	if (left >= right) return; 
	stack<int> s; 
	s.push(left); 
	s.push(right); 
	while (!s.empty()) 
	{
		int right = s.top(); 
		s.pop();
		int left = s.top();
		s.pop(); 
		if (left < right) 
		{
			int pivot = findpivot(A, left, right);
			Swap<E>(A, pivot, right);  // Put pivot at end
									 // k will be first position on right side
			int k = partition<E>(A, left, right, A[right]);
			Swap<E>(A, k, right);         // Put pivot in place

			// 左区间
			s.push(left);
			s.push(k - 1);
			// 右区间
			s.push(k + 1);
			s.push(right);
		}
	} 
}

template<class E>
void qsort_fast(E A[], int i, int j)
{
	if (j <= i)return;		//List too small
	if (select(j - i))
		inssort<E>(A, i, j);
	else
	{
		int pivot = findpivot_new(A, i, j);

		Swap<E>(A, pivot, j);	//Put pivot at end
								//k will be first position on right side
		int k = partition<E>(A, i, j, A[j]);
		Swap<E>(A, k, j);		//Put pivot in place
		qsort_ins<E>(A, i, k - 1);
		qsort_ins<E>(A, k + 1, j);
	}
}

int main()
{
	const int n = 100000;		//测试列表的数据量为10000
	int a[n];
	for (int i = 0; i < n; i++)		//初始化数组a，n~1
		a[i] = n - i;
	clock_t t1, t2;		//时间戳
	double cost;			//耗时
	t1 = clock();
	qsort<int>(a, 0, n - 1);
	t2 = clock();
	cost = (double)(t2 - t1) / CLOCKS_PER_SEC;
	cout << t1 << ' ' << t2 << "\nOriginal time cost:" << cost << "s\n";	//输出时间戳和耗时

	for (int i = 0; i < n; i++)		//初始化数组a，n~1
		a[i] = n - i;
	t1 = clock();
	qsort_pivot<int>(a, 0, n - 1);
	t2 = clock();
	cost = (double)(t2 - t1) / CLOCKS_PER_SEC;
	cout << t1 << ' ' << t2 << "\n(a)Time cost:" << cost << "s\n";	//输出时间戳和耗时

	for (int i = 0; i < n; i++)		//初始化数组a，n~1
		a[i] = n - i;
	t1 = clock();
	qsort_ins<int>(a, 0, n - 1);
	t2 = clock();
	cost = (double)(t2 - t1) / CLOCKS_PER_SEC;
	cout << t1 << ' ' << t2 << "\n(b)Time cost:" << cost << "s\n";	//输出时间戳和耗时

	for (int i = 0; i < n; i++)		//初始化数组a，n~1
		a[i] = n - i;
	t1 = clock();
	qsort_n<int>(a, 0, n - 1);
	t2 = clock();
	cost = (double)(t2 - t1) / CLOCKS_PER_SEC;
	cout << t1 << ' ' << t2 << "\n(c)Time cost:" << cost << "s\n";	//输出时间戳和耗时

	for (int i = 0; i < n; i++)		//初始化数组a，n~1
		a[i] = n - i;
	t1 = clock();
	qsort_fast<int>(a, 0, n - 1);
	t2 = clock();
	cost = (double)(t2 - t1) / CLOCKS_PER_SEC;
	cout << t1 << ' ' << t2 << "\n'Fastest' time cost:" << cost << "s\n";	//输出时间戳和耗时

	system("pause");
	return 0;
}
