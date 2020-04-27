#pragma once
#include"dsbh.h"

int toInt(string s);
string plus_one(string num);
string get_filename(string filename);
string get_short_filename(string filename);
string read(fstream &f);
string find(string target, string filename);
bool append(string newline, string filename);
vector<string> read_tuple(fstream &f, int flag);
vector<vector<string>> read_all(string filename, int flag);
bool resort(string filename, int flag);
string devide(string filename, int flag);
string create(string filename);
int count_lines(string filename);
string split(string filename, string target, string root, int M);