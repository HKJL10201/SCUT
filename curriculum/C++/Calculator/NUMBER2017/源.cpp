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
		if (n == '-')		//��һ����������븺�����Ǻ�saΪ'-'������Ϊ'+'
			sa = '-';
		if (n >= '0'&&n <= '9')
		{
			s->num = n;		//��̬�������һ����
			j++;		//�����һ�����ĳ���
			s->next = new list;
			s = s->next;
		}
		cin.get(n);
	}
	delete s;
	s = NULL;
	s = hd1;
	ch = new char[j];		//����һ����������浽�ַ�������
	for (int i = 0; i < j; i++)
	{
		ch[i] = s->num;
		s = s->next;
	}
	a = new int[j];		//����һ�������ַ�����浽int������
	for (int i = 0; i < j; i++)
	{
		a[i] = ch[i] - 48;
	}
	char sign;		//���������
	do {
		cout << "Please enter operator ('+'or'-'):" << endl;
		cin >> sign;
	} while (sign != '+'&&sign != '-');
	cout << "Please enter the second number (End with '='):" << endl;		//�ظ������һ�����Ĳ���������ڶ���������'='����
	cin.get(m);
	p = new list; hd2 = p;
	while (m != '=')
	{
		if (m == '-')		//�ڶ�����������븺�����Ǻ�sbΪ'-'������Ϊ'+'
			sb = '-';
		if (m >= '0'&&m <= '9')
		{
			p->num = m;		//��̬������ڶ�����
			k++;		//����ڶ������ĳ���
			p->next = new list;
			p = p->next;
		}
		cin.get(m);
	}
	delete p;
	p = NULL;
	p = hd2;
	CH = new char[k];
	for (int i = 0; i < k; i++)		//���ڶ�����������浽�ַ�������
	{
		CH[i] = p->num;
		p = p->next;
	}
	b = new int[k];
	for (int i = 0; i < k; i++)		//���ڶ��������ַ�����浽int������
	{
		b[i] = CH[i] - 48;
	}
	if ((sign == '+' && ((sa == '+'&&sb == '+') || (sa == '-'&&sb == '-'))) || (sign == '-' && ((sb == '-'&&sa == '+') || (sa == '-'&&sb == '+'))))		//����ֵ��ӵ����
	{
		if (j >= k)		//��һ�����ȵڶ������������
		{
			int n = j - 1;
			for (int m = k - 1; m >= 0; m--)		//�Ҷ������
			{
				a[n] += b[m];
				n--;
			}
		loop1:		//ѭ�������ܽ�λ����Ҫ�ٴν�λ
			for (int i = 1; i < j; i++)		//��λѭ��
			{
				if (a[i] > 9)
				{
					a[i] -= 10;
					a[i - 1] += 1;
				}
			}
			for (int i = 1; i < j; i++)
			{
				if (a[i] > 9)		//ѭ������������������κ�һ��������9��ѭ����λ
					goto loop1;
			}
			cout << "The calculation result:" << endl;
			if ((sa == '-'&&sb == '-') || (sa == '-'&&sign == '-'))		//�����ӡ�-����
				cout << '-';
			for (int i = 0; i < j; i++)
				cout << a[i];
		}
		else		//��һ�����ȵڶ������̵����
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
	if (sa == '+' && ((sign == '+'&&sb == '-') || (sign == '-'&&sb == '+')))		//����ֵ��������
	{
		int f = 0;
		if (j == k)		//������������ȵ����
		{
			for (int i = 0; i < j - 1; i++)		//�����Ƚ�
			{
				if (a[i] > b[i])		//�жϵ�һ��������ֵ�Ƿ���ڵڶ�������f=1
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
	if (sa == '-' && ((sign == '+'&&sb == '+') || (sign == '-'&&sb == '-')))		//����ֵ��������
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