#include"dsbh.h"

int toInt(string s) {
	int ans = 0;
	sscanf_s(s.c_str(), "%d", &ans);
	return ans;
}
string plus_one(string num)
{
	return num = to_string(toInt(num) + 1);
}
string get_filename(string filename)
{
	if (filename.find_last_of('/') == -1)
		return filename;
	int div = filename.find_last_of('/');
	string fn = filename.substr(div + 1);
	return fn;
}
string get_short_filename(string filename)
{
	if (filename.find_last_of('/') == -1)
		return filename;
	int div = filename.find_last_of('/');
	string fn = filename.substr(div + 1);
	int dot = fn.find_last_of('.');
	fn = fn.substr(0, dot);
	return fn;
}
string find(string target, string filename)
{
	fstream f;
	f.open(filename, ios::in);
	string result = "";
	string tmp = "";
	while (f >> tmp)
	{
		if (get_short_filename(tmp) > get_short_filename(target))
			break;
		result = tmp;
	}
	f.close();
	return result;
}
bool append(string newline, string filename)
{
	fstream f;
	f.open(filename, ios::app);
	if (!f)
		return false;
	f << newline << endl;
	f.close();
	return true;
}
vector<string> read_tuple(fstream &f, int flag)
{
	vector<string> v;
	string fn;
	f >> fn;
	v.push_back(fn);
	if (flag)
	{
		f >> fn;
		v.push_back(fn);
	}
	return v;
}
vector<vector<string>> read_all(string filename, int flag)
{
	fstream f;
	vector<vector<string>> v;
	f.open(filename, ios::in);
	while (!f.eof())
	{
		if (f.eof())
			break;
		v.push_back(read_tuple(f, flag));
	}
	f.close();
	return v;
}
bool resort(string filename,int flag)
{
	fstream f;
	vector<vector<string>> v = read_all(filename, flag);
	sort(v.begin(), v.end());

	f.open(filename, ios::out);
	if (!f)		
		return false;
	for (auto i : v)
	{
		for (auto j : i)
			f << j << '\t';
		f << endl;
	}
	f.close();
	return true;
}
string devide(string filename, int flag)
{
	vector<vector<string>> v = read_all(filename, flag);
	fstream f;
	f.open(filename, ios::out);
	for (int i = 0; i < v.size() / 2; i++)
	{
		for (auto j : v[i])
			f << j << '\t';
		f << endl;
	}
	f.close();

	int div = filename.find_last_of('/');
	string dir = filename.substr(0, div + 1);
	string newfile = get_short_filename(v[v.size() / 2][0]);
	newfile = dir + newfile + ".txt";
	f.open(newfile, ios::out);
	for (int i = v.size() / 2; i < v.size(); i++)
	{
		for (auto j : v[i])
			f << j << '\t';
		f << endl;
	}
	f.close();
	return newfile;
}

string create(string filename)
{
	int div = filename.find_last_of('/');
	string dir = filename.substr(0, div);
	div = dir.find_last_of('/');
	string num = dir.substr(div + 1);
	dir = dir.substr(0, div + 1);
	num = plus_one(num);
	dir += num;
	_mkdir(dir.c_str());
	return dir;
}
int count_lines(string filename)
{
	int lines = 0;
	fstream f;
	char line[512];
	f.open(filename, ios::in);
	while (!f.eof())
	{
		if (f.eof())
			break;
		f.getline(line, 512, '\n');
		lines++;
	}
	f.close();
	return lines;
}
string split(string filename, string target, string root, int M)
{
	int flag = 0;
	if (filename != target)		//如果当前文件名不是目标文件名
	{
		flag = 0;
		string next = find(target, filename);	//在当前文件中寻找目标文件的所在文件名
		string newfile = split(next, target, root, M);		//在所在文件中继续搜索
		if (newfile != "")
		{
			append(newfile, filename);
			resort(filename, flag);
		}
	}
	else
		flag = 1;
	
	if (count_lines(filename) >= M)
	{
		string newfile = devide(filename, flag);
		if (filename == root)
		{
			string newdir = create(filename);
			string fn = get_filename(filename);
			newdir = newdir + '/' + fn;
			append(filename, newdir);
			append(newfile, newdir);
			return newdir;
		}
		else
		{
			return newfile;
		}
	}
	else
	{
		return "";
	}
}