#include<iostream>
using namespace std;
struct list
{
	char num;
	list *next;
};
list *hd1 = NULL;
list *hd2 = NULL;
int main()
{
	list *s,*p;
	int *a, *b;
	int j = 0; int k = 0;
	char *ch, *CH, n, m;
	char sa = '+'; char sb = '+';
	cout << "Please enter the first number:" << endl;
	cin.get(n);
	s = new list; hd1 = s;
	while (n != '\n')
	{
		if (n == '-')		//第一个数如果输入负数，记号sa为'-'，否则为'+'
			sa = '-';
		if (n >= '0'&&n <= '9')
		{
			s->num = n;		//动态链表储存第一个数
			j++;		//计算第一个数的长度
			s->next = new list;
			s = s->next;
		}
		cin.get(n);
	}
	delete s;
	s = NULL;
	s = hd1;
	ch = new char[j];		//将第一个数从链表存到字符数组中
	for (int i = 0; i < j; i++)
	{
		ch[i] = s->num;
		s = s->next;
	}
	a = new int[j];		//将第一个数从字符数组存到int数组中
	for (int i = 0; i < j; i++)
	{
		a[i] = ch[i] - 48;
	}
	char sign;		//输入运算符
	do {
		cout << "Please enter operator ('+'or'-'):" << endl;
		cin >> sign;
	} while (sign != '+'&&sign != '-');
	cout << "Please enter the second number (End with '='):" << endl;		//重复储存第一个数的操作来储存第二个数，以'='结束
	cin.get(m);
	p = new list; hd2 = p;
	while (m != '=')
	{
		if (m == '-')		//第二个数如果输入负数，记号sb为'-'，否则为'+'
			sb = '-';
		if (m >= '0'&&m <= '9')
		{
			p->num = m;		//动态链表储存第二个数
			k++;		//计算第二个数的长度
			p->next = new list;
			p = p->next;
		}
		cin.get(m);
	}
	delete p;
	p = NULL;
	p = hd2;
	CH = new char[k];
	for (int i = 0; i < k; i++)		//将第二个数从链表存到字符数组中
	{
		CH[i] = p->num;
		p = p->next;
	}
	b = new int[k];
	for (int i = 0; i < k; i++)		//将第二个数从字符数组存到int数组中
	{
		b[i] = CH[i] - 48;
	}
	if ((sign == '+' && ((sa == '+'&&sb == '+') || (sa == '-'&&sb == '-'))) || (sign == '-' && ((sb == '-'&&sa == '+') || (sa == '-'&&sb == '+'))))		//绝对值相加的情况
	{
		if (j >= k)		//第一个数比第二个数长的情况
		{
			int n = j - 1;
			for (int m = k - 1; m >= 0; m--)		//右对齐相加
			{
				a[n] += b[m];
				n--;
			}
		loop1:		//循环：可能进位后需要再次进位
			for (int i = 1; i < j; i++)		//进位循环
			{
				if (a[i] > 9)
				{
					a[i] -= 10;
					a[i - 1] += 1;
				}
			}
			for (int i = 1; i < j; i++)
			{
				if (a[i] > 9)		//循环条件：如果数组中任何一个数大于9，循环进位
					goto loop1;
			}
			cout << "The calculation result:" << endl;
			if ((sa == '-'&&sb == '-') || (sa == '-'&&sign == '-'))		//负数加‘-’号
				cout << '-';
			for (int i = 0; i < j; i++)
				cout << a[i];
		}
		else		//第一个数比第二个数短的情况
		{
			int n = k - 1;
			for (int m = j - 1; m >= 0; m--)
			{
				b[n] += a[m];
				n--;
			}
		loop2:
			for (int i = 1; i < k; i++)
			{
				if (b[i] > 9)
				{
					b[i] -= 10;
					b[i - 1] += 1;
				}
			}
			for (int i = 1; i < k; i++)
			{
				if (b[i] > 9)
					goto loop2;
			}
			cout << "The calculation result:" << endl;
			if ((sa == '-'&&sb == '-') || (sa == '-'&&sign == '-'))
				cout << '-';
			for (int i = 0; i < k; i++)
				cout << b[i];
		}
	}
	cout << endl;
	if (sa == '+' && ((sign == '+'&&sb == '-') || (sign == '-'&&sb == '+')))		//绝对值相减的情况
	{
		int f = 0;
		if (j == k)		//两个数长度相等的情况
		{
			for (int i = 0; i < j - 1; i++)		//左对齐比较
			{
				if (a[i] > b[i])		//判断第一个数绝对值是否大于第二个数：f=1
				{
					f = 1;
					break;
				}
			}
			if (j == 1)
				f = 1;
			for (int i = 0; i < j; i++)
			{
				if (a[i] == b[i] && i != j - 1)
					continue;
				else
					if (a[i] == b[i])
						f = 1;
					else
						break;
			}
		}
		if (j > k || f)
		{
			int n = j - 1;
			for (int m = k - 1; m >= 0; m--)
			{
				a[n] -= b[m];
				n--;
			}
		loop3:
			for (int i = 1; i < j; i++)
			{
				if (a[i] < 0)
				{
					a[i] += 10;
					a[i - 1] -= 1;
				}
			}
			for (int i = 1; i < j; i++)
			{
				if (a[i] < 0)
					goto loop3;
			}
			cout << "The calculation result:" << endl;
			int fa = 0;
			for (int i = 0; i < j - 1; i++)
			{
				if (a[i] != 0)
					fa = 1;
				if (fa)
					cout << a[i];
			}
			cout << a[j - 1];
		}
		else
		{
			int n = k - 1;
			for (int m = j - 1; m >= 0; m--)
			{
				b[n] -= a[m];
				n--;
			}
		loop4:
			for (int i = 1; i < k; i++)
			{
				if (b[i] < 0)
				{
					b[i] += 10;
					b[i - 1] -= 1;
				}
			}
			for (int i = 1; i < k; i++)
			{
				if (b[i] < 0)
					goto loop4;
			}
			cout << "The calculation result:" << endl;
			cout << '-';
			int fa = 0;
			for (int i = 0; i < k - 1; i++)
			{
				if (b[i] != 0)
					fa = 1;
				if (fa)
					cout << b[i];
			}
			cout << b[k - 1];
		}
	}
	if (sa == '-' && ((sign == '+'&&sb == '+') || (sign == '-'&&sb == '-')))		//绝对值相减的情况
	{
		int f = 0;
		if (j == k)
		{
			for (int i = 0; i < j - 1; i++)
			{
				if (b[i] > a[i])
				{
					f = 1;
					break;
				}
			}
			if (j == 1)
				f = 1;
			for (int i = 0; i < j; i++)
			{
				if (a[i] == b[i] && i != j - 1)
					continue;
				else
					if (a[i] == b[i])
						f = 1;
					else
						break;
			}
		}
		if (k > j || f)
		{
			int n = k - 1;
			for (int m = j - 1; m >= 0; m--)
			{
				b[n] -= a[m];
				n--;
			}
		loop5:
			for (int i = 1; i < k; i++)
			{
				if (b[i] < 0)
				{
					b[i] += 10;
					b[i - 1] -= 1;
				}
			}
			for (int i = 1; i < k; i++)
			{
				if (b[i] < 0)
					goto loop5;
			}
			cout << "The calculation result:" << endl;
			int fa = 0;
			for (int i = 0; i < k - 1; i++)
			{
				if (b[i] != 0)
					fa = 1;
				if (fa)
					cout << b[i];
			}
			cout << b[k - 1];
		}
		else
		{
			int n = j - 1;
			for (int m = k - 1; m >= 0; m--)
			{
				a[n] -= b[m];
				n--;
			}
		loop6:
			for (int i = 1; i < j; i++)
			{
				if (a[i] < 0)
				{
					a[i] += 10;
					a[i - 1] -= 1;
				}
			}
			for (int i = 1; i < j; i++)
			{
				if (a[i] < 0)
					goto loop6;
			}
			cout << "The calculation result:" << endl;
			cout << '-';
			int fa = 0;
			for (int i = 0; i < j - 1; i++)
			{
				if (a[i] != 0)
					fa = 1;
				if (fa)
					cout << a[i];
			}
			cout << a[j - 1];
		}
	}
	cout << endl;
	system("pause");
	return 0;
}