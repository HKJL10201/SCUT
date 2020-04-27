#include<iostream>
#include<fstream>
#include<string>
using namespace std;
struct USER
{
	string username, password;
	double money = 0;
};
USER Login()
{
	string mode;
	fstream file;
	const string filename = "TestUNandPW.txt";
	USER U;

	cout << "欢迎使用一个没什么用的购物模拟系统。\n";
	file.open(filename, ios::in);
	if (!file)		//文件是否打开
	{
		fstream F;
		F.open(filename, ios::out);
		if (!F)
		{
			cerr << "File could not open.\n";
			abort();
		}
		F.close();
	}
	cout << "已有用户：\n";
	while (!file.eof())		//显示已有用户名
	{
		file >> U.username >> U.password >> U.money;
		if (file.eof())
			break;
		cout << U.username << '\t';
	}
	cout << endl;
	file.close();

	cout << "Login or Register? (L/R)" << endl;
	while (cin >> mode)
	{
		if (mode == "R" || mode == "r")		//注册模式
		{
			file.open(filename, ios::out | ios::app);

			if (!file)		//文件是否打开
			{
				cerr << "File could not open.\n";
				abort();
			}

			cout << "Please input username:";
			while (cin >> U.username)		//重名检测
			{
				int success = 1;
				string tempUN = U.username;
				fstream tempfile(filename, ios::in);
				if (!tempfile)		//文件是否打开
				{
					cerr << "File could not open.\n";
					abort();
				}
				tempfile.seekg(0, ios::beg);
				while (!tempfile.eof())
				{
					tempfile >> U.username >> U.password >> U.money;
					if (U.username == tempUN)
					{
						success = 0;
						tempfile.close();
						cout << "用户名已存在！\n";
						break;
					}
				}
				if (success)
				{
					U.username = tempUN;
					tempfile.close();
					break;
				}
				cout << "Please input username:";
			}
			cout << "Please input password:";
			cin >> U.password;
			file << U.username << '\t' << U.password << '\t' << U.money <<endl;
			file.close();
			cout << "用户：" << U.username << " 已成功注册！\n";

			file.open(U.username + ".txt", ios::out);		//建立空文档
			if (!file)		//文件是否打开
			{
				cerr << "File could not open.\n";
				abort();
			}
			file.close();
			file.open(U.username + "History.txt", ios::out);		//建立空文档
			if (!file)		//文件是否打开
			{
				cerr << "File could not open.\n";
				abort();
			}
			file.close();
		}
		if (mode == "L" || mode == "l")		//登录模式
		{
			file.open(filename, ios::in);
			if (!file)		//文件是否打开
			{
				cerr << "File could not open." << endl;
				abort();
			}
			//file.seekg(0, ios::beg);

			cout << "Please input username:";
			cin >> U.username;
			cout << "Please input password:";
			cin >> U.password;
			string tempUN, tempPW;
			tempUN = U.username; tempPW = U.password;
			int success = 0;

			while (!file.eof())		//匹配用户名和密码
			{
				file >> U.username >> U.password >> U.money;
				if (U.username == tempUN && U.password == tempPW)
				{
					cout << "success!\n";
					file.close();
					success = 1;
					break;
				}
			}
			if (!success)
			{
				cout << "Username or password is wrong.\n";
				file.close();
			}
			else
			{
				file.close();
				break;
			}
		}
		cout << "Login or Register? (L/R)" << endl;
	}
	return U;
}
struct good
{
	string name;
	double price;
	int amount;
	string describe;
	string user;
};
void showGood(good G)		//显示商品
{
	cout << "【" << G.name << "】\n￥" << G.price << "\t\tAmount:" << G.amount << "\n" << G.describe << "\nBy " << G.user << endl;

	cout << endl;
	return;
}
void CartShowGood(good G)
{
	cout << "【" << G.name << "】\tBy " << G.user << "\n单价：￥" << G.price << "\t购买数量：" << G.amount << "\n总价：￥" << G.price*G.amount << endl;

	cout << endl;
	return;
}
void showAll()
{
	fstream merchanList;
	string filename = "TestMerchandise.txt";
	good G;
	merchanList.open(filename, ios::in);
	if (!merchanList)		//文件是否打开
	{
		cerr << "File could not open.\n";
		abort();
	}

	while (!merchanList.eof())		//显示所有商品
	{
		merchanList >> G.name >> G.price >> G.amount >> G.describe >> G.user;
		if (merchanList.eof())
			break;
		showGood(G);
	}
	merchanList.close();
	return;
}
void showMain()
{
	cout << "\n[主菜单]\nA:显示所有商品\nS:搜索商品\nG:购物车\nM:我的商品\nW:我的钱包\nH:购买记录\nC:退出登录\nE:关闭系统\n";
	return;
}
int main()
{
	USER user = Login();
	fstream merchanList;
	const string filename = "TestMerchandise.txt";
	const string tempChangeFile = "tempFile.txt";
	good G;
	string mode;

	merchanList.open(filename, ios::in);		//第一次打开，创建空文档
	if (!merchanList)		//文件是否打开
	{
		fstream F;
		F.open(filename, ios::out);
		if (!F)
		{
			cerr << "File could not open.\n";
			abort();
		}
		F.close();
	}
	merchanList.close();

	begin:
	cout << "Welcome to the Market, " << user.username << "!\n";
	//cout << "There are all goods:\n\n";
	//showAll();

	showMain();
	while (cin >> mode)
	{
		if (mode == "A")
			showAll();

		if (mode == "S")		//搜索
		{
			string searchMode;
			const string headline = "\n[搜索]\nA:按商品名称搜索\nB:按用户名搜索\nE:返回\n";
			cout << headline;
			while (cin >> searchMode)
			{
				if (searchMode == "A")
				{
					cout << "Input name of the good:";
					cin >> G.name;
					merchanList.open(filename, ios::in);
					if (!merchanList)		//文件是否打开
					{
						cerr << "File could not open.\n";
						abort();
					}

					int success = 0;
					string tempName = G.name;
					while (!merchanList.eof())		//匹配商品名称
					{
						merchanList >> G.name >> G.price >> G.amount >> G.describe >> G.user;
						if (merchanList.eof())
							break;
						if (G.name == tempName)
						{
							success = 1;
							showGood(G);
							break;		//不能显示同名商品，如果有，只能显示第一个
						}
					}
					if (!success)
						cout << "No such goods!\n";
					merchanList.close();

					if (success)
					{
						string SSmode;
						cout << "\nA:加入购物车\nE:返回\n";
						while (cin >> SSmode)
						{
							if (SSmode == "A")		//加入购物车
							{
								fstream tempfile(user.username + ".txt", ios::in);	//重名检测
								if (!tempfile)		//文件是否打开
								{
									cerr << "File could not open.\n";
									abort();
								}
								while (!tempfile.eof())
								{
									tempfile >> G.name >> G.price >> G.amount >> G.describe >> G.user;
									if (tempfile.eof())
										break;
									if (G.name == tempName)		//重名检测
									{
										success = 0;
										cout << "【" << tempName << "】已在购物车中！\n";
										break;
									}
								}
								tempfile.close();
								if (!success)
									break;

								int tempAmount = G.amount;
								cout << "请输入购买数量：\n";
								while (cin >> G.amount)		//非法检测
								{
									if (G.amount > tempAmount)
										cout << "超出商品总数！\n";
									else
										if (G.amount <= 0)
											cout << "请输入正整数！\n";
										else
											break;
									cout << "请输入购买数量：\n";
								}
								merchanList.open(user.username + ".txt", ios::out | ios::app);
								if (!merchanList)		//文件是否打开
								{
									cerr << "File could not open.\n";
									abort();
								}
								merchanList << G.name << '\t' << G.price << '\t' << G.amount << '\t' << G.describe << '\t' << G.user << '\n';
								merchanList.close();

								cout << "【" << G.name << "】x" << G.amount << "已成功添加至购物车！\n";
								break;
							}
							if (SSmode == "E")
								break;
							cout << "\nA:加入购物车\nE:返回\n";
						}
					}
				}

				if (searchMode == "B")
				{
					cout << "Input the username:";
					cin >> G.user;
					merchanList.open(filename, ios::in);
					if (!merchanList)		//文件是否打开
					{
						cerr << "File could not open.\n";
						abort();
					}

					int success = 0;
					string tempName = G.user;
					while (!merchanList.eof())		//匹配用户名称
					{
						merchanList >> G.name >> G.price >> G.amount >> G.describe >> G.user;
						if (merchanList.eof())
							break;
						if (G.user == tempName)
						{
							success = 1;
							showGood(G);
						}
					}
					if (!success)
						cout << "No such goods!\n";
					merchanList.close();
				}
				if (searchMode == "E")
					break;
				cout << headline;
			}
		}
	
		if (mode == "G")		//购物车
		{
			merchanList.open(user.username + ".txt", ios::in);
			if (!merchanList)		//文件是否打开
			{
				cerr << "File could not open.\n";
				abort();
			}

			int success = 0;
			int sumGood = 0;
			double SumPrice = 0;
			while (!merchanList.eof())
			{
				merchanList >> G.name >> G.price >> G.amount >> G.describe >> G.user;
				if (merchanList.eof())
					break;
				SumPrice += G.price*G.amount;
				sumGood++;
				CartShowGood(G);
				success = 1;
			}
			if (success)
			{
				cout << "共 " << sumGood << " 件商品\t总计：￥" << SumPrice << endl;
			}
			else
				cout << "购物车为空！\n";
			merchanList.close();

			string Gmode;
			cout << "\n[购物车]\nS:显示购物车\nA:结算\nB:编辑\nE:返回\n";
			while (cin >> Gmode)
			{
				if (Gmode == "S")		//显示购物车
				{
					merchanList.open(user.username + ".txt", ios::in);
					if (!merchanList)		//文件是否打开
					{
						cerr << "File could not open.\n";
						abort();
					}

					int Ssuccess = 0;
					int SsumGood = 0;
					double SumPrice = 0;
					while (!merchanList.eof())
					{
						merchanList >> G.name >> G.price >> G.amount >> G.describe >> G.user;
						if (merchanList.eof())
							break;
						SumPrice += G.price*G.amount;
						SsumGood++;
						CartShowGood(G);
						Ssuccess = 1;
					}
					if (Ssuccess)
					{
						cout << "共 " << SsumGood << " 件商品\t总计：￥" << SumPrice << endl;
					}
					else
						cout << "购物车为空！\n";
					merchanList.close();
				}

				if (Gmode == "A")		//结算
				{
					merchanList.open(user.username + ".txt", ios::in);
					if (!merchanList)		//文件是否打开
					{
						cerr << "File could not open.\n";
						abort();
					}

					success = 0;
					sumGood = 0;
					SumPrice = 0;
					while (!merchanList.eof())
					{
						merchanList >> G.name >> G.price >> G.amount >> G.describe >> G.user;
						if (merchanList.eof())
							break;
						SumPrice += G.price*G.amount;
						sumGood++;
						success = 1;
					}
					merchanList.close();
					if (!success)
						cout << "购物车为空！\n";
					else
					{
						cout << "您确定要购买购物车中的所有物品吗？\nA:确定\nB:取消\n";
						string GAmode;
						cin >> GAmode;
						if (GAmode == "A")
						{
							cout << "请输入您的密码：";
							cin >> GAmode;
							if (GAmode == user.password)
							{
								if (user.money < SumPrice)
									cout << "账户余额不足！\n";
								else
								{
									

									fstream tempchange;
									
									//******************************************减数量的代码*******************************************************************//
									//写入temp
									merchanList.open(filename, ios::in);
									if (!merchanList)		//文件是否打开
									{
										cerr << "File could not open.\n";
										abort();
									}
									tempchange.open(tempChangeFile, ios::out);
									if (!tempchange)		//文件是否打开
									{
										cerr << "File could not open.\n";
										abort();
									}
									fstream CartFile;

									while (!merchanList.eof())		//匹配商品名称
									{
										merchanList >> G.name >> G.price >> G.amount >> G.describe >> G.user;
										if (merchanList.eof())
											break;
										CartFile.open(user.username + ".txt", ios::in);
										if (!CartFile)		//文件是否打开
										{
											cerr << "File could not open.\n";
											abort();
										}
										good CG;
										while (!CartFile.eof())
										{
											CartFile >> CG.name >> CG.price >> CG.amount >> CG.describe >> CG.user;
											if (CartFile.eof())
												break;
											if (G.name == CG.name)		//减去商品列表中已被购买的数量
											{
												G.amount -= CG.amount;
												break;
											}
										}
										CartFile.close();

										tempchange << G.name << '\t' << G.price << '\t' << G.amount << '\t' << G.describe << '\t' << G.user << '\n';
									}
									merchanList.close();
									tempchange.close();

									//temp写入文件
									merchanList.open(filename, ios::out);
									if (!merchanList)		//文件是否打开
									{
										cerr << "File could not open.\n";
										abort();
									}
									tempchange.open(tempChangeFile, ios::in);
									if (!tempchange)		//文件是否打开
									{
										cerr << "File could not open.\n";
										abort();
									}

									while (!tempchange.eof())		//复制文件
									{
										tempchange >> G.name >> G.price >> G.amount >> G.describe >> G.user;
										if (tempchange.eof())
											break;

										merchanList << G.name << '\t' << G.price << '\t' << G.amount << '\t' << G.describe << '\t' << G.user << '\n';
									}
									merchanList.close();
									tempchange.close();


									USER U;

									//******************************************卖家加钱的代码*******************************************************************//
									//写入temp
									merchanList.open("TestUNandPW.txt", ios::in);
									if (!merchanList)		//文件是否打开
									{
										cerr << "File could not open.\n";
										abort();
									}
									tempchange.open(tempChangeFile, ios::out);
									if (!tempchange)		//文件是否打开
									{
										cerr << "File could not open.\n";
										abort();
									}

									while (!merchanList.eof())		//匹配用户名称
									{
										merchanList >> U.username >> U.password >> U.money;
										if (merchanList.eof())
											break;
										CartFile.open(user.username + ".txt", ios::in);
										if (!CartFile)		//文件是否打开
										{
											cerr << "File could not open.\n";
											abort();
										}
										while (!CartFile.eof())
										{
											CartFile >> G.name >> G.price >> G.amount >> G.describe >> G.user;
											if (CartFile.eof())
												break;
											if (U.username == G.user)		//给卖家加钱
											{
												U.money += G.price*G.amount;
											}
										}
										CartFile.close();

										tempchange << U.username << '\t' << U.password << '\t' << U.money << '\n';
									}
									merchanList.close();
									tempchange.close();

									//temp写入文件
									merchanList.open("TestUNandPW.txt", ios::out);
									if (!merchanList)		//文件是否打开
									{
										cerr << "File could not open.\n";
										abort();
									}
									tempchange.open(tempChangeFile, ios::in);
									if (!tempchange)		//文件是否打开
									{
										cerr << "File could not open.\n";
										abort();
									}

									while (!tempchange.eof())		//复制文件
									{
										tempchange >> U.username >> U.password >> U.money;
										if (tempchange.eof())
											break;

										merchanList << U.username << '\t' << U.password << '\t' << U.money << '\n';
									}
									merchanList.close();
									tempchange.close();


									//购物车写入购买记录*********************************************************************************
									CartFile.open(user.username + ".txt", ios::in);
									if (!CartFile)		//文件是否打开
									{
										cerr << "File could not open.\n";
										abort();
									}
									tempchange.open(user.username + "History.txt", ios::out | ios::app);
									if (!tempchange)		//文件是否打开
									{
										cerr << "File could not open.\n";
										abort();
									}

									while (!CartFile.eof())		//复制文件
									{
										CartFile >> G.name >> G.price >> G.amount >> G.describe >> G.user;
										if (CartFile.eof())
											break;

										tempchange << G.name << '\t' << G.price << '\t' << G.amount << '\t' << G.describe << '\t' << G.user << '\n';
									}
									CartFile.close();
									tempchange.close();



									CartFile.open(user.username + ".txt", ios::out);		//清空购物车
									if (!CartFile)		//文件是否打开
									{
										cerr << "File could not open.\n";
										abort();
									}
									CartFile.close();


									//****************************扣钱*******************************//
									merchanList.open("TestUNandPW.txt", ios::in);		//更新余额状态
									if (!merchanList)		//文件是否打开
									{
										cerr << "File could not open.\n";
										abort();
									}
									while (!merchanList.eof())		//匹配用户名称
									{
										merchanList >> U.username >> U.password >> U.money;
										if (merchanList.eof())
											break;
										if (U.username == user.username)
										{
											user = U;
											break;
										}
									}
									merchanList.close();
									user.money -= SumPrice;		//扣钱

									//文件写入temp
									merchanList.open("TestUNandPW.txt", ios::in);
									if (!merchanList)		//文件是否打开
									{
										cerr << "File could not open.\n";
										abort();
									}
									tempchange.open(tempChangeFile, ios::out);
									if (!tempchange)		//文件是否打开
									{
										cerr << "File could not open.\n";
										abort();
									}

									while (!merchanList.eof())		//匹配用户名称
									{
										merchanList >> U.username >> U.password >> U.money;
										if (merchanList.eof())
											break;
										if (U.username != user.username)
										{
											tempchange << U.username << '\t' << U.password << '\t' << U.money << '\n';
										}
										else
											tempchange << user.username << '\t' << user.password << '\t' << user.money << '\n';
									}
									merchanList.close();
									tempchange.close();

									//temp写入文件
									merchanList.open("TestUNandPW.txt", ios::out);
									if (!merchanList)		//文件是否打开
									{
										cerr << "File could not open.\n";
										abort();
									}
									tempchange.open(tempChangeFile, ios::in);
									if (!tempchange)		//文件是否打开
									{
										cerr << "File could not open.\n";
										abort();
									}

									while (!tempchange.eof())		//复制文件
									{
										tempchange >> U.username >> U.password >> U.money;
										if (tempchange.eof())
											break;

										merchanList << U.username << '\t' << U.password << '\t' << U.money << '\n';
									}
									merchanList.close();
									tempchange.close();

									cout << "\n[购买成功！]\n感谢您的购买，" << user.username << "！\n账户余额：" << user.money << endl;
								}
							}
						}
					}
				}

				if (Gmode == "B")
				{
					cout << "\n[编辑购物车]\nA:删除物品\nB:更改数量\nE:返回\n";
					string GBmode;
					while (cin >> GBmode)
					{
						if (GBmode == "A")		//删除商品
						{
							string goon = "A";
							fstream tempchange;

							string tempname;
							while (goon != "E")
							{
								if (goon == "A")
								{
									cout << "请输入商品名称：";
									cin >> tempname;

									//文件写入temp
									merchanList.open(user.username + ".txt", ios::in);
									if (!merchanList)		//文件是否打开
									{
										cerr << "File could not open.\n";
										abort();
									}
									tempchange.open(tempChangeFile, ios::out);
									if (!tempchange)		//文件是否打开
									{
										cerr << "File could not open.\n";
										abort();
									}

									int Bsuccess = 0;
									while (!merchanList.eof())		//匹配商品名称
									{
										merchanList >> G.name >> G.price >> G.amount >> G.describe >> G.user;
										if (merchanList.eof())
											break;
										if (G.name != tempname)
										{
											tempchange << G.name << '\t' << G.price << '\t' << G.amount << '\t' << G.describe << '\t' << G.user << '\n';
										}
										else
											Bsuccess = 1;
									}
									merchanList.close();
									tempchange.close();

									//temp写入文件
									merchanList.open(user.username + ".txt", ios::out);
									if (!merchanList)		//文件是否打开
									{
										cerr << "File could not open.\n";
										abort();
									}
									tempchange.open(tempChangeFile, ios::in);
									if (!tempchange)		//文件是否打开
									{
										cerr << "File could not open.\n";
										abort();
									}

									while (!tempchange.eof())		//复制文件
									{
										tempchange >> G.name >> G.price >> G.amount >> G.describe >> G.user;
										if (tempchange.eof())
											break;

										merchanList << G.name << '\t' << G.price << '\t' << G.amount << '\t' << G.describe << '\t' << G.user << '\n';
									}
									merchanList.close();
									tempchange.close();

									if (Bsuccess)
										cout << "【" << tempname << "】已从购物车移除.\n";
									else
										cout << "您的购物车中不存在此商品！\n";
								}

								cout << "\n[删除物品]\nA:继续删除\nE:退出\n";
								cin >> goon;
							}
						}

						if (GBmode == "B")		//更改数量
						{
							string tempname;

							cout << "请输入商品名称：";
							cin >> tempname;

							merchanList.open(user.username + ".txt", ios::in);
							if (!merchanList)		//文件是否打开
							{
								cerr << "File could not open.\n";
								abort();
							}

							int success = 0;
							while (!merchanList.eof())		//匹配商品名称
							{
								merchanList >> G.name >> G.price >> G.amount >> G.describe >> G.user;
								if (merchanList.eof())
									break;
								if (G.name == tempname)
								{
									success = 1;
									break;
								}
							}
							merchanList.close();

							if(!success)
								cout << "您的购物车中不存在此商品！\n";
							else
							{
								CartShowGood(G);

								merchanList.open(filename, ios::in);
								if (!merchanList)		//文件是否打开
								{
									cerr << "File could not open.\n";
									abort();
								}
								while (!merchanList.eof())		//匹配商品名称
								{
									merchanList >> G.name >> G.price >> G.amount >> G.describe >> G.user;
									if (merchanList.eof())
										break;
									if (G.name == tempname)
									{
										break;
									}
								}
								merchanList.close();

								int tempAmount = G.amount;
								cout << "请输入商品数量：\n";
								while (cin >> G.amount)		//非法检测
								{
									if (G.amount > tempAmount)
										cout << "超出商品总数！\n";
									else
										if (G.amount <= 0)
											cout << "请输入正整数！\n";
										else
											break;
									cout << "请输入购买数量：\n";
								}

								
								fstream tempchange;

								//文件写入temp
								merchanList.open(user.username + ".txt", ios::in);
								if (!merchanList)		//文件是否打开
								{
									cerr << "File could not open.\n";
									abort();
								}
								tempchange.open(tempChangeFile, ios::out);
								if (!tempchange)		//文件是否打开
								{
									cerr << "File could not open.\n";
									abort();
								}

								good tempG = G;

								while (!merchanList.eof())		//匹配商品名称
								{
									merchanList >> G.name >> G.price >> G.amount >> G.describe >> G.user;
									if (merchanList.eof())
										break;
									if (G.name == tempname)
									{
										tempchange << tempG.name << '\t' << tempG.price << '\t' << tempG.amount << '\t' << tempG.describe << '\t' << tempG.user << '\n';
									}
									else
									{
										tempchange << G.name << '\t' << G.price << '\t' << G.amount << '\t' << G.describe << '\t' << G.user << '\n';
									}
								}
								merchanList.close();
								tempchange.close();

								//temp写入文件
								merchanList.open(user.username + ".txt", ios::out);
								if (!merchanList)		//文件是否打开
								{
									cerr << "File could not open.\n";
									abort();
								}
								tempchange.open(tempChangeFile, ios::in);
								if (!tempchange)		//文件是否打开
								{
									cerr << "File could not open.\n";
									abort();
								}

								while (!tempchange.eof())		//复制文件
								{
									tempchange >> G.name >> G.price >> G.amount >> G.describe >> G.user;
									if (tempchange.eof())
										break;

									merchanList << G.name << '\t' << G.price << '\t' << G.amount << '\t' << G.describe << '\t' << G.user << '\n';
								}
								merchanList.close();
								tempchange.close();

								cout << "更改成功！\n";
							}
						}

						if (GBmode == "E")		//返回
							break;
						cout << "\n[编辑购物车]\nA:删除物品\nB:更改数量\nE:返回\n";
					}
				}

				if (Gmode == "E")		//返回
					break;
				cout << "\n[购物车]\nS:显示购物车\nA:结算\nB:编辑\nE:返回\n";
			}
		}
		
		if (mode == "M")		//我的商品
		{
			merchanList.open(filename, ios::in);
			if (!merchanList)		//文件是否打开
			{
				cerr << "File could not open.\n";
				abort();
			}

			int success = 0;
			while (!merchanList.eof())		//匹配用户名称
			{
				merchanList >> G.name >> G.price >> G.amount >> G.describe >> G.user;
				if (merchanList.eof())
					break;
				if (G.user == user.username)
				{
					success = 1;
					showGood(G);
				}
			}
			if (!success)
				cout << "您未添加商品！\n";
			merchanList.close();

			const string headline = "\n[我的商品]\nA:添加商品\nS:显示我的商品\nB:编辑我的商品\nD:删除商品\nE:返回\n";
			string myMode;
			cout << headline;
			while (cin >> myMode)
			{
				if (myMode == "A")		//添加商品
				{
					merchanList.open(filename, ios::out | ios::app);
					if (!merchanList)		//文件是否打开
					{
						cerr << "File could not open.\n";
						abort();
					}

					string goon = "A";

					while (goon != "E")		//添加商品
					{
						if (goon == "A")
						{
							cout << "Input name of your good:";
							while (cin >> G.name)		//商品重名检测
							{
								string tempname = G.name;
								fstream temp(filename, ios::in);
								if (!temp)		//文件是否打开
								{
									cerr << "File could not open.\n";
									abort();
								}
								int rename = 0;
								while (!temp.eof())
								{
									temp >> G.name >> G.price >> G.amount >> G.describe >> G.user;
									if (temp.eof())
										break;
									if (G.name == tempname)
									{
										rename = 1;
										cout << "【" << G.name << "】已存在！\n";
										break;
									}
								}
								if (!rename)
								{
									G.name = tempname;
									break;
								}
								cout << "Input name of your good:";
							}
							cout << "Input price:";
							cin >> G.price;
							cout << "Input amount:";
							cin >> G.amount;
							cout << "Describe your good:\n";
							cin >> G.describe;
							G.user = user.username;
							merchanList << G.name << '\t' << G.price << '\t' << G.amount << '\t' << G.describe << '\t' << G.user << '\n';
							cout << "Your good has been added!\n\n";
						}

						cout << "A:Continue adding.\nE:Finish adding.\n";		//继续或离开
						cin >> goon;
					}
					merchanList.close();
				}
				if (myMode == "S")		//显示我的商品
				{
					merchanList.open(filename, ios::in);
					if (!merchanList)		//文件是否打开
					{
						cerr << "File could not open.\n";
						abort();
					}

					int success = 0;
					while (!merchanList.eof())		//匹配用户名称
					{
						merchanList >> G.name >> G.price >> G.amount >> G.describe >> G.user;
						if (merchanList.eof())
							break;
						if (G.user == user.username)
						{
							success = 1;
							showGood(G);
						}
					}
					if (!success)
						cout << "您未添加商品！\n";
					merchanList.close();
				}
				if (myMode == "B")		//编辑商品
				{
					string goon = "A";
					while (goon != "E")
					{
						if (goon == "A")
						{
							string tempname;
							cout << "Input name of your good:";
							cin >> tempname;
							merchanList.open(filename, ios::in);
							if (!merchanList)		//文件是否打开
							{
								cerr << "File could not open.\n";
								abort();
							}

							int success = 0;
							while (!merchanList.eof())		//匹配商品名称
							{
								merchanList >> G.name >> G.price >> G.amount >> G.describe >> G.user;
								if (merchanList.eof())
									break;
								if (G.name == tempname)
								{
									success = 1;
									break;
								}
							}
							if (!success)
							{
								cout << "No such goods!\n";
								merchanList.close();
								break;
							}
							merchanList.close();

							if (G.user != user.username)
							{
								cout << "您不能编辑其他用户的商品！\n";
								break;
							}

							showGood(G);

							string Demode;
							cout << "\n[编辑模式]\nA:修改名称\nB:修改价格\nC:修改数量\nD:修改描述\nE:取消\n";
							while (cin >> Demode)
							{
								if (Demode == "A")
								{
									cout << "[修改商品名称]\n原名称：" << G.name << "\n输入新名称：";
									cin >> G.name;
								}
								if (Demode == "B")
								{
									cout << "[修改商品价格]\n原价格：" << G.price << "\n输入新价格：";
									cin >> G.price;
								}
								if (Demode == "C")
								{
									cout << "[修改商品数量]\n原数量：" << G.amount << "\n输入新数量：";
									cin >> G.amount;
								}
								if (Demode == "D")
								{
									cout << "[修改商品描述]\n原描述：" << G.describe << "\n输入新描述：";
									cin >> G.describe;
								}
								if (Demode == "E")
									break;

								fstream tempchange;
								//文件写入temp
								merchanList.open(filename, ios::in);
								if (!merchanList)		//文件是否打开
								{
									cerr << "File could not open.\n";
									abort();
								}
								tempchange.open(tempChangeFile, ios::out);
								if (!tempchange)		//文件是否打开
								{
									cerr << "File could not open.\n";
									abort();
								}

								good tempG = G;

								while (!merchanList.eof())		//匹配商品名称
								{
									merchanList >> G.name >> G.price >> G.amount >> G.describe >> G.user;
									if (merchanList.eof())
										break;
									if (G.name == tempname)
									{
										tempchange << tempG.name << '\t' << tempG.price << '\t' << tempG.amount << '\t' << tempG.describe << '\t' << tempG.user << '\n';
									}
									else
									{
										tempchange << G.name << '\t' << G.price << '\t' << G.amount << '\t' << G.describe << '\t' << G.user << '\n';
									}
								}
								merchanList.close();
								tempchange.close();

								//temp写入文件
								merchanList.open(filename, ios::out);
								if (!merchanList)		//文件是否打开
								{
									cerr << "File could not open.\n";
									abort();
								}
								tempchange.open(tempChangeFile, ios::in);
								if (!tempchange)		//文件是否打开
								{
									cerr << "File could not open.\n";
									abort();
								}

								while (!tempchange.eof())		//复制文件
								{
									tempchange >> G.name >> G.price >> G.amount >> G.describe >> G.user;
									if (tempchange.eof())
										break;

									merchanList << G.name << '\t' << G.price << '\t' << G.amount << '\t' << G.describe << '\t' << G.user << '\n';
								}
								merchanList.close();
								tempchange.close();

								cout << "编辑成功！\n";
								break;
							}
						}

						cout << "\n[编辑商品]\nA:继续编辑\nE:退出\n";
						cin >> goon;
					}

				}
				if (myMode == "D")		//删除商品
				{
					string goon = "A";
					fstream tempchange;
					
					string tempname;
					while (goon != "E")
					{
						if (goon == "A")
						{
							cout << "Input name of your good:";
							cin >> tempname;

							//文件写入temp
							merchanList.open(filename, ios::in);
							if (!merchanList)		//文件是否打开
							{
								cerr << "File could not open.\n";
								abort();
							}
							tempchange.open(tempChangeFile, ios::out);
							if (!tempchange)		//文件是否打开
							{
								cerr << "File could not open.\n";
								abort();
							}

							int success = 0;
							while (!merchanList.eof())		//匹配商品名称
							{
								merchanList >> G.name >> G.price >> G.amount >> G.describe >> G.user;
								if (merchanList.eof())
									break;
								if (G.user != user.username || G.name != tempname)
								{
									tempchange << G.name << '\t' << G.price << '\t' << G.amount << '\t' << G.describe << '\t' << G.user << '\n';
								}
								else
									success = 1;
							}
							merchanList.close();
							tempchange.close();

							//temp写入文件
							merchanList.open(filename, ios::out);
							if (!merchanList)		//文件是否打开
							{
								cerr << "File could not open.\n";
								abort();
							}
							tempchange.open(tempChangeFile, ios::in);
							if (!tempchange)		//文件是否打开
							{
								cerr << "File could not open.\n";
								abort();
							}

							while (!tempchange.eof())		//复制文件
							{
								tempchange >> G.name >> G.price >> G.amount >> G.describe >> G.user;
								if (tempchange.eof())
									break;

								merchanList << G.name << '\t' << G.price << '\t' << G.amount << '\t' << G.describe << '\t' << G.user << '\n';
							}
							merchanList.close();
							tempchange.close();

							if (success)
								cout << "【" << tempname << "】已从您的商品中删除.\n";
							else
								cout << "您的账户中不存在此商品！\n";
						}

						cout << "\n[删除]\nA:继续删除\nE:退出\n";
						cin >> goon;
					}
				}
				if (myMode == "E")		//退出
					break;
				cout << headline;
			}
		}

		if (mode == "W")		//钱包
		{
			cout << "\n[钱包]\n账户余额：" << user.money << "\nA:充值\nE:返回\n";
			string wMode;
			while (cin >> wMode)
			{
				if (wMode == "A")
				{
					cout << "请输入充值金额：";
					double InMoney;
					cin >> InMoney;

					cout << "输入您的密码：";
					string tempPassWord;
					cin >> tempPassWord;
					if (tempPassWord != user.password)
						break;

					user.money += InMoney;
					if (user.money < 0)
						user.money = 0;

					fstream tempchange;
					USER U;

					//文件写入temp
					merchanList.open("TestUNandPW.txt", ios::in);
					if (!merchanList)		//文件是否打开
					{
						cerr << "File could not open.\n";
						abort();
					}
					tempchange.open(tempChangeFile, ios::out);
					if (!tempchange)		//文件是否打开
					{
						cerr << "File could not open.\n";
						abort();
					}

					while (!merchanList.eof())		//匹配用户名称
					{
						merchanList >> U.username >> U.password >> U.money;
						if (merchanList.eof())
							break;
						if (U.username!=user.username)
						{
							tempchange << U.username << '\t' << U.password << '\t' << U.money << '\n';
						}
						else
							tempchange << user.username << '\t' << user.password << '\t' << user.money << '\n';
					}
					merchanList.close();
					tempchange.close();

					//temp写入文件
					merchanList.open("TestUNandPW.txt", ios::out);
					if (!merchanList)		//文件是否打开
					{
						cerr << "File could not open.\n";
						abort();
					}
					tempchange.open(tempChangeFile, ios::in);
					if (!tempchange)		//文件是否打开
					{
						cerr << "File could not open.\n";
						abort();
					}

					while (!tempchange.eof())		//复制文件
					{
						tempchange >> U.username >> U.password >> U.money;
						if (tempchange.eof())
							break;

						merchanList << U.username << '\t' << U.password << '\t' << U.money << '\n';
					}
					merchanList.close();
					tempchange.close();

					cout << "充值成功！\n";
				}
				if (wMode == "E")
					break;
				cout << "\n[钱包]\n账户余额：" << user.money << "\nA:充值\nE:返回\n";
			}
		}

		if (mode == "H")		//交易记录
		{
			merchanList.open(user.username + "History.txt", ios::in);
			if (!merchanList)		//文件是否打开
			{
				cerr << "File could not open.\n";
				abort();
			}

			int success = 0;
			while (!merchanList.eof())		//遍历
			{
				merchanList >> G.name >> G.price >> G.amount >> G.describe >> G.user;
				if (merchanList.eof())
					break;
				CartShowGood(G);
				success = 1;
			}
			if (!success)
				cout << "您购买任何商品！\n";
			merchanList.close();
		}

		if (mode == "C")		//更改用户
		{
			user = Login();
			goto begin;
		}

		if (mode == "E")		//退出
			break;

		showMain();
	}
	return 0;
}