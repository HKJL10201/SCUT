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

	cout << "��ӭʹ��һ��ûʲô�õĹ���ģ��ϵͳ��\n";
	file.open(filename, ios::in);
	if (!file)		//�ļ��Ƿ��
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
	cout << "�����û���\n";
	while (!file.eof())		//��ʾ�����û���
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
		if (mode == "R" || mode == "r")		//ע��ģʽ
		{
			file.open(filename, ios::out | ios::app);

			if (!file)		//�ļ��Ƿ��
			{
				cerr << "File could not open.\n";
				abort();
			}

			cout << "Please input username:";
			while (cin >> U.username)		//�������
			{
				int success = 1;
				string tempUN = U.username;
				fstream tempfile(filename, ios::in);
				if (!tempfile)		//�ļ��Ƿ��
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
						cout << "�û����Ѵ��ڣ�\n";
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
			cout << "�û���" << U.username << " �ѳɹ�ע�ᣡ\n";

			file.open(U.username + ".txt", ios::out);		//�������ĵ�
			if (!file)		//�ļ��Ƿ��
			{
				cerr << "File could not open.\n";
				abort();
			}
			file.close();
			file.open(U.username + "History.txt", ios::out);		//�������ĵ�
			if (!file)		//�ļ��Ƿ��
			{
				cerr << "File could not open.\n";
				abort();
			}
			file.close();
		}
		if (mode == "L" || mode == "l")		//��¼ģʽ
		{
			file.open(filename, ios::in);
			if (!file)		//�ļ��Ƿ��
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

			while (!file.eof())		//ƥ���û���������
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
void showGood(good G)		//��ʾ��Ʒ
{
	cout << "��" << G.name << "��\n��" << G.price << "\t\tAmount:" << G.amount << "\n" << G.describe << "\nBy " << G.user << endl;

	cout << endl;
	return;
}
void CartShowGood(good G)
{
	cout << "��" << G.name << "��\tBy " << G.user << "\n���ۣ���" << G.price << "\t����������" << G.amount << "\n�ܼۣ���" << G.price*G.amount << endl;

	cout << endl;
	return;
}
void showAll()
{
	fstream merchanList;
	string filename = "TestMerchandise.txt";
	good G;
	merchanList.open(filename, ios::in);
	if (!merchanList)		//�ļ��Ƿ��
	{
		cerr << "File could not open.\n";
		abort();
	}

	while (!merchanList.eof())		//��ʾ������Ʒ
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
	cout << "\n[���˵�]\nA:��ʾ������Ʒ\nS:������Ʒ\nG:���ﳵ\nM:�ҵ���Ʒ\nW:�ҵ�Ǯ��\nH:�����¼\nC:�˳���¼\nE:�ر�ϵͳ\n";
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

	merchanList.open(filename, ios::in);		//��һ�δ򿪣��������ĵ�
	if (!merchanList)		//�ļ��Ƿ��
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

		if (mode == "S")		//����
		{
			string searchMode;
			const string headline = "\n[����]\nA:����Ʒ��������\nB:���û�������\nE:����\n";
			cout << headline;
			while (cin >> searchMode)
			{
				if (searchMode == "A")
				{
					cout << "Input name of the good:";
					cin >> G.name;
					merchanList.open(filename, ios::in);
					if (!merchanList)		//�ļ��Ƿ��
					{
						cerr << "File could not open.\n";
						abort();
					}

					int success = 0;
					string tempName = G.name;
					while (!merchanList.eof())		//ƥ����Ʒ����
					{
						merchanList >> G.name >> G.price >> G.amount >> G.describe >> G.user;
						if (merchanList.eof())
							break;
						if (G.name == tempName)
						{
							success = 1;
							showGood(G);
							break;		//������ʾͬ����Ʒ������У�ֻ����ʾ��һ��
						}
					}
					if (!success)
						cout << "No such goods!\n";
					merchanList.close();

					if (success)
					{
						string SSmode;
						cout << "\nA:���빺�ﳵ\nE:����\n";
						while (cin >> SSmode)
						{
							if (SSmode == "A")		//���빺�ﳵ
							{
								fstream tempfile(user.username + ".txt", ios::in);	//�������
								if (!tempfile)		//�ļ��Ƿ��
								{
									cerr << "File could not open.\n";
									abort();
								}
								while (!tempfile.eof())
								{
									tempfile >> G.name >> G.price >> G.amount >> G.describe >> G.user;
									if (tempfile.eof())
										break;
									if (G.name == tempName)		//�������
									{
										success = 0;
										cout << "��" << tempName << "�����ڹ��ﳵ�У�\n";
										break;
									}
								}
								tempfile.close();
								if (!success)
									break;

								int tempAmount = G.amount;
								cout << "�����빺��������\n";
								while (cin >> G.amount)		//�Ƿ����
								{
									if (G.amount > tempAmount)
										cout << "������Ʒ������\n";
									else
										if (G.amount <= 0)
											cout << "��������������\n";
										else
											break;
									cout << "�����빺��������\n";
								}
								merchanList.open(user.username + ".txt", ios::out | ios::app);
								if (!merchanList)		//�ļ��Ƿ��
								{
									cerr << "File could not open.\n";
									abort();
								}
								merchanList << G.name << '\t' << G.price << '\t' << G.amount << '\t' << G.describe << '\t' << G.user << '\n';
								merchanList.close();

								cout << "��" << G.name << "��x" << G.amount << "�ѳɹ���������ﳵ��\n";
								break;
							}
							if (SSmode == "E")
								break;
							cout << "\nA:���빺�ﳵ\nE:����\n";
						}
					}
				}

				if (searchMode == "B")
				{
					cout << "Input the username:";
					cin >> G.user;
					merchanList.open(filename, ios::in);
					if (!merchanList)		//�ļ��Ƿ��
					{
						cerr << "File could not open.\n";
						abort();
					}

					int success = 0;
					string tempName = G.user;
					while (!merchanList.eof())		//ƥ���û�����
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
	
		if (mode == "G")		//���ﳵ
		{
			merchanList.open(user.username + ".txt", ios::in);
			if (!merchanList)		//�ļ��Ƿ��
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
				cout << "�� " << sumGood << " ����Ʒ\t�ܼƣ���" << SumPrice << endl;
			}
			else
				cout << "���ﳵΪ�գ�\n";
			merchanList.close();

			string Gmode;
			cout << "\n[���ﳵ]\nS:��ʾ���ﳵ\nA:����\nB:�༭\nE:����\n";
			while (cin >> Gmode)
			{
				if (Gmode == "S")		//��ʾ���ﳵ
				{
					merchanList.open(user.username + ".txt", ios::in);
					if (!merchanList)		//�ļ��Ƿ��
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
						cout << "�� " << SsumGood << " ����Ʒ\t�ܼƣ���" << SumPrice << endl;
					}
					else
						cout << "���ﳵΪ�գ�\n";
					merchanList.close();
				}

				if (Gmode == "A")		//����
				{
					merchanList.open(user.username + ".txt", ios::in);
					if (!merchanList)		//�ļ��Ƿ��
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
						cout << "���ﳵΪ�գ�\n";
					else
					{
						cout << "��ȷ��Ҫ�����ﳵ�е�������Ʒ��\nA:ȷ��\nB:ȡ��\n";
						string GAmode;
						cin >> GAmode;
						if (GAmode == "A")
						{
							cout << "�������������룺";
							cin >> GAmode;
							if (GAmode == user.password)
							{
								if (user.money < SumPrice)
									cout << "�˻����㣡\n";
								else
								{
									

									fstream tempchange;
									
									//******************************************�������Ĵ���*******************************************************************//
									//д��temp
									merchanList.open(filename, ios::in);
									if (!merchanList)		//�ļ��Ƿ��
									{
										cerr << "File could not open.\n";
										abort();
									}
									tempchange.open(tempChangeFile, ios::out);
									if (!tempchange)		//�ļ��Ƿ��
									{
										cerr << "File could not open.\n";
										abort();
									}
									fstream CartFile;

									while (!merchanList.eof())		//ƥ����Ʒ����
									{
										merchanList >> G.name >> G.price >> G.amount >> G.describe >> G.user;
										if (merchanList.eof())
											break;
										CartFile.open(user.username + ".txt", ios::in);
										if (!CartFile)		//�ļ��Ƿ��
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
											if (G.name == CG.name)		//��ȥ��Ʒ�б����ѱ����������
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

									//tempд���ļ�
									merchanList.open(filename, ios::out);
									if (!merchanList)		//�ļ��Ƿ��
									{
										cerr << "File could not open.\n";
										abort();
									}
									tempchange.open(tempChangeFile, ios::in);
									if (!tempchange)		//�ļ��Ƿ��
									{
										cerr << "File could not open.\n";
										abort();
									}

									while (!tempchange.eof())		//�����ļ�
									{
										tempchange >> G.name >> G.price >> G.amount >> G.describe >> G.user;
										if (tempchange.eof())
											break;

										merchanList << G.name << '\t' << G.price << '\t' << G.amount << '\t' << G.describe << '\t' << G.user << '\n';
									}
									merchanList.close();
									tempchange.close();


									USER U;

									//******************************************���Ҽ�Ǯ�Ĵ���*******************************************************************//
									//д��temp
									merchanList.open("TestUNandPW.txt", ios::in);
									if (!merchanList)		//�ļ��Ƿ��
									{
										cerr << "File could not open.\n";
										abort();
									}
									tempchange.open(tempChangeFile, ios::out);
									if (!tempchange)		//�ļ��Ƿ��
									{
										cerr << "File could not open.\n";
										abort();
									}

									while (!merchanList.eof())		//ƥ���û�����
									{
										merchanList >> U.username >> U.password >> U.money;
										if (merchanList.eof())
											break;
										CartFile.open(user.username + ".txt", ios::in);
										if (!CartFile)		//�ļ��Ƿ��
										{
											cerr << "File could not open.\n";
											abort();
										}
										while (!CartFile.eof())
										{
											CartFile >> G.name >> G.price >> G.amount >> G.describe >> G.user;
											if (CartFile.eof())
												break;
											if (U.username == G.user)		//�����Ҽ�Ǯ
											{
												U.money += G.price*G.amount;
											}
										}
										CartFile.close();

										tempchange << U.username << '\t' << U.password << '\t' << U.money << '\n';
									}
									merchanList.close();
									tempchange.close();

									//tempд���ļ�
									merchanList.open("TestUNandPW.txt", ios::out);
									if (!merchanList)		//�ļ��Ƿ��
									{
										cerr << "File could not open.\n";
										abort();
									}
									tempchange.open(tempChangeFile, ios::in);
									if (!tempchange)		//�ļ��Ƿ��
									{
										cerr << "File could not open.\n";
										abort();
									}

									while (!tempchange.eof())		//�����ļ�
									{
										tempchange >> U.username >> U.password >> U.money;
										if (tempchange.eof())
											break;

										merchanList << U.username << '\t' << U.password << '\t' << U.money << '\n';
									}
									merchanList.close();
									tempchange.close();


									//���ﳵд�빺���¼*********************************************************************************
									CartFile.open(user.username + ".txt", ios::in);
									if (!CartFile)		//�ļ��Ƿ��
									{
										cerr << "File could not open.\n";
										abort();
									}
									tempchange.open(user.username + "History.txt", ios::out | ios::app);
									if (!tempchange)		//�ļ��Ƿ��
									{
										cerr << "File could not open.\n";
										abort();
									}

									while (!CartFile.eof())		//�����ļ�
									{
										CartFile >> G.name >> G.price >> G.amount >> G.describe >> G.user;
										if (CartFile.eof())
											break;

										tempchange << G.name << '\t' << G.price << '\t' << G.amount << '\t' << G.describe << '\t' << G.user << '\n';
									}
									CartFile.close();
									tempchange.close();



									CartFile.open(user.username + ".txt", ios::out);		//��չ��ﳵ
									if (!CartFile)		//�ļ��Ƿ��
									{
										cerr << "File could not open.\n";
										abort();
									}
									CartFile.close();


									//****************************��Ǯ*******************************//
									merchanList.open("TestUNandPW.txt", ios::in);		//�������״̬
									if (!merchanList)		//�ļ��Ƿ��
									{
										cerr << "File could not open.\n";
										abort();
									}
									while (!merchanList.eof())		//ƥ���û�����
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
									user.money -= SumPrice;		//��Ǯ

									//�ļ�д��temp
									merchanList.open("TestUNandPW.txt", ios::in);
									if (!merchanList)		//�ļ��Ƿ��
									{
										cerr << "File could not open.\n";
										abort();
									}
									tempchange.open(tempChangeFile, ios::out);
									if (!tempchange)		//�ļ��Ƿ��
									{
										cerr << "File could not open.\n";
										abort();
									}

									while (!merchanList.eof())		//ƥ���û�����
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

									//tempд���ļ�
									merchanList.open("TestUNandPW.txt", ios::out);
									if (!merchanList)		//�ļ��Ƿ��
									{
										cerr << "File could not open.\n";
										abort();
									}
									tempchange.open(tempChangeFile, ios::in);
									if (!tempchange)		//�ļ��Ƿ��
									{
										cerr << "File could not open.\n";
										abort();
									}

									while (!tempchange.eof())		//�����ļ�
									{
										tempchange >> U.username >> U.password >> U.money;
										if (tempchange.eof())
											break;

										merchanList << U.username << '\t' << U.password << '\t' << U.money << '\n';
									}
									merchanList.close();
									tempchange.close();

									cout << "\n[����ɹ���]\n��л���Ĺ���" << user.username << "��\n�˻���" << user.money << endl;
								}
							}
						}
					}
				}

				if (Gmode == "B")
				{
					cout << "\n[�༭���ﳵ]\nA:ɾ����Ʒ\nB:��������\nE:����\n";
					string GBmode;
					while (cin >> GBmode)
					{
						if (GBmode == "A")		//ɾ����Ʒ
						{
							string goon = "A";
							fstream tempchange;

							string tempname;
							while (goon != "E")
							{
								if (goon == "A")
								{
									cout << "��������Ʒ���ƣ�";
									cin >> tempname;

									//�ļ�д��temp
									merchanList.open(user.username + ".txt", ios::in);
									if (!merchanList)		//�ļ��Ƿ��
									{
										cerr << "File could not open.\n";
										abort();
									}
									tempchange.open(tempChangeFile, ios::out);
									if (!tempchange)		//�ļ��Ƿ��
									{
										cerr << "File could not open.\n";
										abort();
									}

									int Bsuccess = 0;
									while (!merchanList.eof())		//ƥ����Ʒ����
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

									//tempд���ļ�
									merchanList.open(user.username + ".txt", ios::out);
									if (!merchanList)		//�ļ��Ƿ��
									{
										cerr << "File could not open.\n";
										abort();
									}
									tempchange.open(tempChangeFile, ios::in);
									if (!tempchange)		//�ļ��Ƿ��
									{
										cerr << "File could not open.\n";
										abort();
									}

									while (!tempchange.eof())		//�����ļ�
									{
										tempchange >> G.name >> G.price >> G.amount >> G.describe >> G.user;
										if (tempchange.eof())
											break;

										merchanList << G.name << '\t' << G.price << '\t' << G.amount << '\t' << G.describe << '\t' << G.user << '\n';
									}
									merchanList.close();
									tempchange.close();

									if (Bsuccess)
										cout << "��" << tempname << "���Ѵӹ��ﳵ�Ƴ�.\n";
									else
										cout << "���Ĺ��ﳵ�в����ڴ���Ʒ��\n";
								}

								cout << "\n[ɾ����Ʒ]\nA:����ɾ��\nE:�˳�\n";
								cin >> goon;
							}
						}

						if (GBmode == "B")		//��������
						{
							string tempname;

							cout << "��������Ʒ���ƣ�";
							cin >> tempname;

							merchanList.open(user.username + ".txt", ios::in);
							if (!merchanList)		//�ļ��Ƿ��
							{
								cerr << "File could not open.\n";
								abort();
							}

							int success = 0;
							while (!merchanList.eof())		//ƥ����Ʒ����
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
								cout << "���Ĺ��ﳵ�в����ڴ���Ʒ��\n";
							else
							{
								CartShowGood(G);

								merchanList.open(filename, ios::in);
								if (!merchanList)		//�ļ��Ƿ��
								{
									cerr << "File could not open.\n";
									abort();
								}
								while (!merchanList.eof())		//ƥ����Ʒ����
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
								cout << "��������Ʒ������\n";
								while (cin >> G.amount)		//�Ƿ����
								{
									if (G.amount > tempAmount)
										cout << "������Ʒ������\n";
									else
										if (G.amount <= 0)
											cout << "��������������\n";
										else
											break;
									cout << "�����빺��������\n";
								}

								
								fstream tempchange;

								//�ļ�д��temp
								merchanList.open(user.username + ".txt", ios::in);
								if (!merchanList)		//�ļ��Ƿ��
								{
									cerr << "File could not open.\n";
									abort();
								}
								tempchange.open(tempChangeFile, ios::out);
								if (!tempchange)		//�ļ��Ƿ��
								{
									cerr << "File could not open.\n";
									abort();
								}

								good tempG = G;

								while (!merchanList.eof())		//ƥ����Ʒ����
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

								//tempд���ļ�
								merchanList.open(user.username + ".txt", ios::out);
								if (!merchanList)		//�ļ��Ƿ��
								{
									cerr << "File could not open.\n";
									abort();
								}
								tempchange.open(tempChangeFile, ios::in);
								if (!tempchange)		//�ļ��Ƿ��
								{
									cerr << "File could not open.\n";
									abort();
								}

								while (!tempchange.eof())		//�����ļ�
								{
									tempchange >> G.name >> G.price >> G.amount >> G.describe >> G.user;
									if (tempchange.eof())
										break;

									merchanList << G.name << '\t' << G.price << '\t' << G.amount << '\t' << G.describe << '\t' << G.user << '\n';
								}
								merchanList.close();
								tempchange.close();

								cout << "���ĳɹ���\n";
							}
						}

						if (GBmode == "E")		//����
							break;
						cout << "\n[�༭���ﳵ]\nA:ɾ����Ʒ\nB:��������\nE:����\n";
					}
				}

				if (Gmode == "E")		//����
					break;
				cout << "\n[���ﳵ]\nS:��ʾ���ﳵ\nA:����\nB:�༭\nE:����\n";
			}
		}
		
		if (mode == "M")		//�ҵ���Ʒ
		{
			merchanList.open(filename, ios::in);
			if (!merchanList)		//�ļ��Ƿ��
			{
				cerr << "File could not open.\n";
				abort();
			}

			int success = 0;
			while (!merchanList.eof())		//ƥ���û�����
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
				cout << "��δ�����Ʒ��\n";
			merchanList.close();

			const string headline = "\n[�ҵ���Ʒ]\nA:�����Ʒ\nS:��ʾ�ҵ���Ʒ\nB:�༭�ҵ���Ʒ\nD:ɾ����Ʒ\nE:����\n";
			string myMode;
			cout << headline;
			while (cin >> myMode)
			{
				if (myMode == "A")		//�����Ʒ
				{
					merchanList.open(filename, ios::out | ios::app);
					if (!merchanList)		//�ļ��Ƿ��
					{
						cerr << "File could not open.\n";
						abort();
					}

					string goon = "A";

					while (goon != "E")		//�����Ʒ
					{
						if (goon == "A")
						{
							cout << "Input name of your good:";
							while (cin >> G.name)		//��Ʒ�������
							{
								string tempname = G.name;
								fstream temp(filename, ios::in);
								if (!temp)		//�ļ��Ƿ��
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
										cout << "��" << G.name << "���Ѵ��ڣ�\n";
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

						cout << "A:Continue adding.\nE:Finish adding.\n";		//�������뿪
						cin >> goon;
					}
					merchanList.close();
				}
				if (myMode == "S")		//��ʾ�ҵ���Ʒ
				{
					merchanList.open(filename, ios::in);
					if (!merchanList)		//�ļ��Ƿ��
					{
						cerr << "File could not open.\n";
						abort();
					}

					int success = 0;
					while (!merchanList.eof())		//ƥ���û�����
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
						cout << "��δ�����Ʒ��\n";
					merchanList.close();
				}
				if (myMode == "B")		//�༭��Ʒ
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
							if (!merchanList)		//�ļ��Ƿ��
							{
								cerr << "File could not open.\n";
								abort();
							}

							int success = 0;
							while (!merchanList.eof())		//ƥ����Ʒ����
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
								cout << "�����ܱ༭�����û�����Ʒ��\n";
								break;
							}

							showGood(G);

							string Demode;
							cout << "\n[�༭ģʽ]\nA:�޸�����\nB:�޸ļ۸�\nC:�޸�����\nD:�޸�����\nE:ȡ��\n";
							while (cin >> Demode)
							{
								if (Demode == "A")
								{
									cout << "[�޸���Ʒ����]\nԭ���ƣ�" << G.name << "\n���������ƣ�";
									cin >> G.name;
								}
								if (Demode == "B")
								{
									cout << "[�޸���Ʒ�۸�]\nԭ�۸�" << G.price << "\n�����¼۸�";
									cin >> G.price;
								}
								if (Demode == "C")
								{
									cout << "[�޸���Ʒ����]\nԭ������" << G.amount << "\n������������";
									cin >> G.amount;
								}
								if (Demode == "D")
								{
									cout << "[�޸���Ʒ����]\nԭ������" << G.describe << "\n������������";
									cin >> G.describe;
								}
								if (Demode == "E")
									break;

								fstream tempchange;
								//�ļ�д��temp
								merchanList.open(filename, ios::in);
								if (!merchanList)		//�ļ��Ƿ��
								{
									cerr << "File could not open.\n";
									abort();
								}
								tempchange.open(tempChangeFile, ios::out);
								if (!tempchange)		//�ļ��Ƿ��
								{
									cerr << "File could not open.\n";
									abort();
								}

								good tempG = G;

								while (!merchanList.eof())		//ƥ����Ʒ����
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

								//tempд���ļ�
								merchanList.open(filename, ios::out);
								if (!merchanList)		//�ļ��Ƿ��
								{
									cerr << "File could not open.\n";
									abort();
								}
								tempchange.open(tempChangeFile, ios::in);
								if (!tempchange)		//�ļ��Ƿ��
								{
									cerr << "File could not open.\n";
									abort();
								}

								while (!tempchange.eof())		//�����ļ�
								{
									tempchange >> G.name >> G.price >> G.amount >> G.describe >> G.user;
									if (tempchange.eof())
										break;

									merchanList << G.name << '\t' << G.price << '\t' << G.amount << '\t' << G.describe << '\t' << G.user << '\n';
								}
								merchanList.close();
								tempchange.close();

								cout << "�༭�ɹ���\n";
								break;
							}
						}

						cout << "\n[�༭��Ʒ]\nA:�����༭\nE:�˳�\n";
						cin >> goon;
					}

				}
				if (myMode == "D")		//ɾ����Ʒ
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

							//�ļ�д��temp
							merchanList.open(filename, ios::in);
							if (!merchanList)		//�ļ��Ƿ��
							{
								cerr << "File could not open.\n";
								abort();
							}
							tempchange.open(tempChangeFile, ios::out);
							if (!tempchange)		//�ļ��Ƿ��
							{
								cerr << "File could not open.\n";
								abort();
							}

							int success = 0;
							while (!merchanList.eof())		//ƥ����Ʒ����
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

							//tempд���ļ�
							merchanList.open(filename, ios::out);
							if (!merchanList)		//�ļ��Ƿ��
							{
								cerr << "File could not open.\n";
								abort();
							}
							tempchange.open(tempChangeFile, ios::in);
							if (!tempchange)		//�ļ��Ƿ��
							{
								cerr << "File could not open.\n";
								abort();
							}

							while (!tempchange.eof())		//�����ļ�
							{
								tempchange >> G.name >> G.price >> G.amount >> G.describe >> G.user;
								if (tempchange.eof())
									break;

								merchanList << G.name << '\t' << G.price << '\t' << G.amount << '\t' << G.describe << '\t' << G.user << '\n';
							}
							merchanList.close();
							tempchange.close();

							if (success)
								cout << "��" << tempname << "���Ѵ�������Ʒ��ɾ��.\n";
							else
								cout << "�����˻��в����ڴ���Ʒ��\n";
						}

						cout << "\n[ɾ��]\nA:����ɾ��\nE:�˳�\n";
						cin >> goon;
					}
				}
				if (myMode == "E")		//�˳�
					break;
				cout << headline;
			}
		}

		if (mode == "W")		//Ǯ��
		{
			cout << "\n[Ǯ��]\n�˻���" << user.money << "\nA:��ֵ\nE:����\n";
			string wMode;
			while (cin >> wMode)
			{
				if (wMode == "A")
				{
					cout << "�������ֵ��";
					double InMoney;
					cin >> InMoney;

					cout << "�����������룺";
					string tempPassWord;
					cin >> tempPassWord;
					if (tempPassWord != user.password)
						break;

					user.money += InMoney;
					if (user.money < 0)
						user.money = 0;

					fstream tempchange;
					USER U;

					//�ļ�д��temp
					merchanList.open("TestUNandPW.txt", ios::in);
					if (!merchanList)		//�ļ��Ƿ��
					{
						cerr << "File could not open.\n";
						abort();
					}
					tempchange.open(tempChangeFile, ios::out);
					if (!tempchange)		//�ļ��Ƿ��
					{
						cerr << "File could not open.\n";
						abort();
					}

					while (!merchanList.eof())		//ƥ���û�����
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

					//tempд���ļ�
					merchanList.open("TestUNandPW.txt", ios::out);
					if (!merchanList)		//�ļ��Ƿ��
					{
						cerr << "File could not open.\n";
						abort();
					}
					tempchange.open(tempChangeFile, ios::in);
					if (!tempchange)		//�ļ��Ƿ��
					{
						cerr << "File could not open.\n";
						abort();
					}

					while (!tempchange.eof())		//�����ļ�
					{
						tempchange >> U.username >> U.password >> U.money;
						if (tempchange.eof())
							break;

						merchanList << U.username << '\t' << U.password << '\t' << U.money << '\n';
					}
					merchanList.close();
					tempchange.close();

					cout << "��ֵ�ɹ���\n";
				}
				if (wMode == "E")
					break;
				cout << "\n[Ǯ��]\n�˻���" << user.money << "\nA:��ֵ\nE:����\n";
			}
		}

		if (mode == "H")		//���׼�¼
		{
			merchanList.open(user.username + "History.txt", ios::in);
			if (!merchanList)		//�ļ��Ƿ��
			{
				cerr << "File could not open.\n";
				abort();
			}

			int success = 0;
			while (!merchanList.eof())		//����
			{
				merchanList >> G.name >> G.price >> G.amount >> G.describe >> G.user;
				if (merchanList.eof())
					break;
				CartShowGood(G);
				success = 1;
			}
			if (!success)
				cout << "�������κ���Ʒ��\n";
			merchanList.close();
		}

		if (mode == "C")		//�����û�
		{
			user = Login();
			goto begin;
		}

		if (mode == "E")		//�˳�
			break;

		showMain();
	}
	return 0;
}