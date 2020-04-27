using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

using Airport_ver1._0.FileIO;

namespace Airport_ver1._0.Login
{
    public class LoginProgram
    {
        string InputUsername;
        string InputPassword;

        UsernamePasswordIO io;

        public LoginProgram(string InputUsername, string InputPassword)
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

        /*public string Login()
        {
            if (io.IsUsernameExist(InputUsername))
            {
                string CorrectPassword = io.GetCorrectPassword(InputUsername);
                if (CorrectPassword == InputPassword)
                {
                    return "Login successfully";
                }
                else
                {
                    return "Incorrect username or password";
                }
            }
            else
            {
                return "Username does not exist";
            }
        }*/

        public string Login()
        {
            string root = Split_Class.Get_root(io.ROOT);
            string dir = Split_Class.Find_dir(InputUsername, root);
            string tmpUN, tmpPW;
            StreamReader f = new StreamReader(dir);
            while ((tmpUN = f.ReadLine()) != null)
            {
                tmpPW = f.ReadLine();
                if (InputUsername == tmpUN)
                {
                    if (InputPassword == tmpPW)
                    {
                        f.Close();
                        return "Login successfully";
                    }
                    else
                    {
                        f.Close();
                        return "Incorrect username or password";
                    }
                }
            }
            f.Close();
            return "Username does not exist";
        }
    }
}
