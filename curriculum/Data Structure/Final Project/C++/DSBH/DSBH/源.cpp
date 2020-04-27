#include"dsbh.h"
#include"split.h"

const string ROOT = "./UserData/root.txt";
const int M = 1000;
string the_root;
void init()
{
	fstream FS;
	FS.open(ROOT, ios::in);
	FS >> the_root;
	FS.close();
}

int resort(string filename)
{
	vector<pair<string, string>> V;
	fstream f;
	f.open(filename, ios::in);
	pair<string, string> P;
	while (f >> P.first >> P.second)
	{
		V.push_back(P);
	}
	f.close();
	sort(V.begin(), V.end());

	f.open(filename, ios::out);
	for (auto i : V)
	{
		f << i.first << "\t" << i.second << "\n";
	}
	f.close();
	return V.size();
}
string find_dir(string username, string root)
{
	int div = root.find_last_of('/');
	string dir = root.substr(0, div);
	div = dir.find_last_of('/');
	string num = dir.substr(div + 1);
	while (num != "1")
	{
		fstream f;
		f.open(root, ios::in);
		string result = "";
		string tmp = "";
		while (f >> tmp)
		{
			if (get_short_filename(tmp) > username)
				break;
			result = tmp;
		}
		int *a,*b;
		f.close();
		root = result;

		div = root.find_last_of('/');
		dir = root.substr(0, div);
		div = dir.find_last_of('/');
		num = dir.substr(div + 1);
	}
	return root;
}
bool regist(string username, string password)
{
	string dir = find_dir(username, the_root);
	fstream f;
	string tmpUN, tmpPW;
	f.open(dir, ios::in);
	while (f >> tmpUN >> tmpPW)
	{
		if (username == tmpUN)
		{
			cerr << "用户名已存在！\n";
			f.close();
			return false;
		}
	}
	f.close();
	f.open(dir, ios::app);
	f << username << "\t" << password << endl;
	f.close();
	int lines = resort(dir);
	string newroot = "";
	if (lines >= M)
		newroot = split(the_root, dir, the_root, M);
	if (newroot != "")
	{
		the_root = newroot;
		f.open(ROOT, ios::out);
		f << newroot << endl;
		f.close();
	}
	cout << "You have registered successfully!\n";
	return true;
}
bool login(string username, string password)
{
	string dir = find_dir(username, the_root);
	fstream f;
	string tmpUN, tmpPW;
	f.open(dir, ios::in);
	while (f >> tmpUN >> tmpPW)
	{
		if (username == tmpUN && password == tmpPW)
		{
			cout << "登录成功！\n";
			f.close();
			return true;
		}
	}
	f.close();
	cout << "用户名或密码错误！\n";
	return false;
}
int main()
{
	init();
	while (1)
	{
		cout << "Welcome to flight tickets booking system!\n\n";
		cout << "L:Login\nR:Resgiter\nE:Exit\n\n";
		string choose;
		cin >> choose;
		if (choose == "L")
		{
			//Login();
			string username, password;

			cout << "Please input your Username:";
			cin >> username;
			cout << "Please input your password:";
			cin >> password;
			login(username, password);
		}
		if (choose == "R")
		{
			//Register();
			string username, password;

			cout << "Please input your Username:";
			cin >> username;
			cout << "Please input your password:";
			cin >> password;
			regist(username, password);
		}
		if (choose == "E")
			break;
	}
	//resort();
	/*
	for (int i = 0; i < 1000; i++)
		regist(to_string(i + 1), to_string(i + 1));*/
	return 0;
}