using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

using Airport_ver1._0.FileIO;

namespace Airport_ver1._0.Register
{
    class RegisterProgram
    {
        string InputUsername;
        string InputPassword;

        UsernamePasswordIO io;

        public RegisterProgram(string InputUsername, string InputPassword)
        {
            this.InputUsername = InputUsername;
            this.InputPassword = InputPassword;
            io = new UsernamePasswordIO();
        }

        public void Update(string InputUsername, string InputPassword)
        {
            this.InputUsername = InputUsername;
            this.InputPassword = InputPassword;
        }

        /*public string Register()
        {
            if (io.IsUsernameExist(InputUsername))
            {
                return "Username already exists";
            }
            else
            {
                io.InsertUser(InputUsername, InputPassword);
                return "Register sucessfully";
            }
        }*/


        public string Register()
        {
            string root = Split_Class.Get_root(io.ROOT);
            string dir = Split_Class.Find_dir(InputUsername, root);
            string tmpUN, tmpPW;
            StreamReader r = new StreamReader(dir);
            while ((tmpUN = r.ReadLine()) != null)
            {
                tmpPW = r.ReadLine();
                if (InputUsername == tmpUN)
                {
                    r.Close();
                    return "Username already exists";
                }
            }
            r.Close();
            StreamWriter w = new StreamWriter(dir, append: true);
            w.WriteLine(InputUsername);
            w.WriteLine(InputPassword);
            w.Close();
            int lines = Resort(dir);
            string newroot = null;
            if (lines >= io.M)
            {
                newroot = Split_Class.Split(root, dir, root, io.M);
            }
            if (newroot != null)
            {
                root = newroot;
                w = new StreamWriter(io.ROOT);
                w.WriteLine(newroot);
                w.Close();
            }

            /*下面创建用户文件*/
            FileStream fs=File.Create(".\\Data\\UsersTicketsData" + "\\" + InputUsername + ".txt");
            fs.Close();
            return "Register successfully";
        }

        private static int Resort(string filename)
        {
            List<Tuple<string, string>> L = new List<Tuple<string, string>>();

            StreamReader f = new StreamReader(filename);
            Tuple<string, string> t;
            string tmp1 = "", tmp2 = "";
            while ((tmp1 = f.ReadLine()) != null)
            {
                tmp2 = f.ReadLine();
                t = new Tuple<string, string>(tmp1, tmp2);
                L.Add(t);
            }
            f.Close();
            L.Sort();       //May cause problems

            StreamWriter w = new StreamWriter(filename);
            foreach (Tuple<string, string> i in L)
            {
                w.WriteLine(i.Item1);
                w.WriteLine(i.Item2);
            }   //这里结束之后文件清空了
            w.Close();
            return L.Count;
        }
    }
}