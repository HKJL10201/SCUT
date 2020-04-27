using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;

namespace Airport_ver1._0.FileIO
{
    class UsernamePasswordIO
    {
        public string ROOT = "./UserData/root.txt";
        public int M = 1000;

        /*string DataPath = @"../Data/UsernamePasswordData.txt";
        
        public bool IsUsernameExist(string InputUsername)
        {
            StreamReader Reader = new StreamReader(DataPath);

            string ReadString = Reader.ReadLine();
            string CurrentUsername;
            string CurrentPassword;

            while (ReadString != null)
            {
                CurrentUsername = ReadString;
                CurrentPassword = Reader.ReadLine();
                if (CurrentUsername == InputUsername)
                {
                    Reader.Close();
                    return true;
                }
                ReadString = Reader.ReadLine();
            }

            Reader.Close();
            return false;
        }

        public string GetCorrectPassword(string InputUsername)
        {
            StreamReader Reader = new StreamReader(DataPath);

            string ReadString = Reader.ReadLine();
            string CurrentUsername;
            string CurrentPassword;

            while (ReadString != null)
            {
                CurrentUsername = ReadString;
                CurrentPassword = Reader.ReadLine();
                if (CurrentUsername == InputUsername)
                {
                    Reader.Close();
                    return CurrentPassword;
                }
                ReadString = Reader.ReadLine();
            }

            Reader.Close();
            return null;
        }


        public string InsertUser(string InputUsername,string InputPassword)
        {
            /*if (IsUsernameExist(InputUsername))
            {
                return "Username already exists";
            }*/

            /*StreamWriter Writer = new StreamWriter(DataPath,true);
            Writer.WriteLine(InputUsername);
            Writer.WriteLine(InputPassword);
            
            Writer.Close();
            return "User insert successfully";
        }*/
    }
    

    class Split_Class
    {
        public static string Get_root(string ROOT)
        {
            StreamReader f = new StreamReader(ROOT);
            string root = f.ReadLine();
            f.Close();
            return root;
        }
        public static string Find_dir(string username, string root)
        {
            string[] s = root.Split(new char[2] { '/', '.' });
            string num = s[s.Length - 3];
            while (num != "1")
            {
                StreamReader f = new StreamReader(root);
                string result = "", tmp = "";
                while ((tmp = f.ReadLine()) != null)
                {
                    if (Get_short_filename(tmp).CompareTo(username) == 1)
                        break;
                    result = tmp;
                }
                f.Close();
                root = result;

                s = root.Split(new char[2] { '/', '.' });
                num = s[s.Length - 3];
            }
            return root;
        }
        private static string Plus_one(string num)
        {
            return (int.Parse(num) + 1).ToString();
        }
        private static string Get_filename(string filename)
        {
            if (!filename.Contains("/"))
            {
                return filename;
            }
            string[] s = filename.Split('/');
            string fn = s[s.Length - 1];
            return fn;
        }
        public static string Get_short_filename(string filename)
        {
            if (!filename.Contains("/"))
            {
                return filename;
            }
            string[] s = filename.Split(new char[2] { '/', '.' });
            string fn = s[s.Length - 2];
            return fn;
        }
        private static string Find(string target, string filename)
        {
            StreamReader f = new StreamReader(filename);
            string result = "", tmp = "";
            while ((tmp = f.ReadLine()) != null)
            {
                if (Get_short_filename(tmp).CompareTo(Get_short_filename(target)) == 1)
                {
                    break;
                }
                result = tmp;
            }
            f.Close();
            return result;
        }
        private static void Append(string newline, string filename)
        {
            StreamWriter w = new StreamWriter(filename, append: true);
            w.WriteLine(newline);
            w.Close();
            return;
        }
        /*private static List<string> Read_tuple(StreamReader f,int flag)
        {
            List<string> L = new List<string>();
            string fn = f.ReadLine();
            L.Add(fn);
            if (flag != 0) 
            {
                fn=f.ReadLine();
                L.Add(fn);
            }
            return L;
        }*/
        private static List<string> Read_all(string filename)
        {
            List<string> L = new List<string>();
            StreamReader f = new StreamReader(filename);
            string fn = "";
            while ((fn = f.ReadLine()) != null)
            {
                L.Add(fn);
            }
            f.Close();
            return L;
        }
        private static List<Tuple<string, string>> Read_all_user(string filename)
        {
            List<Tuple<string, string>> L = new List<Tuple<string, string>>();
            StreamReader f = new StreamReader(filename);
            string un = "", pw = "";
            while ((un = f.ReadLine()) != null)
            {
                pw = f.ReadLine();
                Tuple<string, string> t = new Tuple<string, string>(un, pw);
                L.Add(t);
            }
            f.Close();
            return L;
        }
        private static void Resort(string filename, int flag)
        {
            if (flag == 0)
            {
                List<string> L = Read_all(filename);
                L.Sort();       //Here may exist problems

                StreamWriter w = new StreamWriter(filename);
                foreach (string line in L)
                {
                    w.WriteLine(line);
                }
                w.Close();
                return;
            }
            else if (flag == 1)
            {
                List<Tuple<string, string>> L = Read_all_user(filename);
                L.Sort();       //Here may exist problems

                StreamWriter w = new StreamWriter(filename);
                foreach (Tuple<string, string> t in L)
                {
                    w.WriteLine(t.Item1);
                    w.WriteLine(t.Item2);
                }
                w.Close();
                return;
            }
            else return;
        }
        private static string Divide(string filename, int flag)
        {
            if (flag == 0)
            {
                List<string> L = Read_all(filename);
                StreamWriter w = new StreamWriter(filename);
                for (int i = 0; i < L.Count / 2; i++)
                {
                    w.WriteLine(L[i]);
                }
                w.Close();

                int div = filename.LastIndexOf('/');
                string dir = filename.Substring(0, div + 1);
                string newfile = Get_short_filename(L[L.Count / 2]);
                newfile = dir + newfile + ".txt";
                w = new StreamWriter(newfile);
                for (int i = L.Count / 2; i < L.Count; i++)
                {
                    w.WriteLine(L[i]);
                }
                w.Close();
                return newfile;
            }
            else if (flag == 1)
            {
                List<Tuple<string, string>> L = Read_all_user(filename);
                StreamWriter w = new StreamWriter(filename);
                for (int i = 0; i < L.Count / 2; i++)
                {
                    w.WriteLine(L[i].Item1);
                    w.WriteLine(L[i].Item2);
                }
                w.Close();

                int div = filename.LastIndexOf('/');
                string dir = filename.Substring(0, div + 1);
                string newfile = Get_short_filename(L[L.Count / 2].Item1);
                newfile = dir + newfile + ".txt";
                w = new StreamWriter(newfile);
                for (int i = L.Count / 2; i < L.Count; i++)
                {
                    w.WriteLine(L[i].Item1);
                    w.WriteLine(L[i].Item2);
                }
                w.Close();
                return newfile;
            }
            else
                return null;
        }
        private static string Create(string filename)
        {
            int div = filename.LastIndexOf('/');
            string dir = filename.Substring(0, div);
            div = dir.LastIndexOf('/');
            string num = dir.Substring(div + 1);
            dir = dir.Substring(0, div + 1);
            num = Plus_one(num);
            dir += num;
            if (!Directory.Exists(dir))
            {
                Directory.CreateDirectory(dir);
            }
            return dir;
        }
        private static int Count_lines(string filename, int flag)
        {
            int lines = 0;
            StreamReader f = new StreamReader(filename);
            while (f.ReadLine() != null)
            {
                if (flag != 0)
                {
                    f.ReadLine();
                }
                lines++;
            }
            f.Close();
            return lines;
        }

        public static string Split(string filename, string target, string root, int M)
        {
            int flag = 0;
            if (filename != target)
            {
                string next = Find(target, filename);
                string newfile = Split(next, target, root, M);
                if (newfile != null)
                {
                    Append(newfile, filename);
                    Resort(filename, flag);
                }
            }
            else
            {
                flag = 1;
            }

            if (Count_lines(filename, flag) >= M)
            {
                string newfile = Divide(filename, flag);
                if (filename == root)
                {
                    string newdir = Create(filename);
                    string fn = Get_filename(filename);
                    newdir = newdir + '/' + fn;
                    Append(filename, newdir);
                    Append(newfile, newdir);
                    return newdir;
                }
                else
                {
                    return newfile;
                }
            }
            else
            {
                return null;
            }
        }
    }
}
