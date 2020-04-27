using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace exp1
{
    class Code
    {
        private string filename;
        private string path;

        private List<string> Lines;
        private static List<string> keys;
        private static Dictionary<string, int> wsym;
        private Dictionary<string, int> tags;
        private List<string> Error;

        private char ch;
        private int count_tags;
        private int sym;
        private string a;

        private int line_index;
        private int char_index;

        private static void Init_lib()
        {
            keys.Add("none");
            keys.Add("and");
            keys.Add("array");
            keys.Add("begin");
            keys.Add("bool");
            keys.Add("call");
            keys.Add("case");
            keys.Add("char");
            keys.Add("constant");
            keys.Add("dim");
            keys.Add("do");
            keys.Add("else");
            keys.Add("end");
            keys.Add("false");
            keys.Add("for");
            keys.Add("if");
            keys.Add("input");
            keys.Add("integer");
            keys.Add("not");
            keys.Add("of");
            keys.Add("or");
            keys.Add("output");
            keys.Add("procedure");
            keys.Add("program");
            keys.Add("read");
            keys.Add("real");
            keys.Add("repeat");
            keys.Add("set");
            keys.Add("stop");
            keys.Add("then");
            keys.Add("to");
            keys.Add("true");
            keys.Add("until");
            keys.Add("var");
            keys.Add("while");
            keys.Add("write");
            keys.Add("标识符");
            keys.Add("整数");
            keys.Add("字符常数");
            keys.Add("(");
            keys.Add(")");
            keys.Add("*");
            keys.Add("*/");
            keys.Add("+");
            keys.Add(",");
            keys.Add("-");
            keys.Add(".");
            keys.Add("..");
            keys.Add("/");
            keys.Add("/*");
            keys.Add(":");
            keys.Add(":=");
            keys.Add(";");
            keys.Add("<");
            keys.Add("<=");
            keys.Add("<>");
            keys.Add("=");
            keys.Add(">");
            keys.Add(">=");
            keys.Add("[");
            keys.Add("]");
            for (int i = 0; i < 61; i++)
            {
                wsym.Add(keys[i], i);
            }
        }

        private void Init_file()
        {
            StreamReader f = new StreamReader(path);
            while (!f.EndOfStream)
            {
                Lines.Add(f.ReadLine());
            }
        }

        public Code(string filename) 
        {
            this.filename = filename;
            path = "./" + filename + ".txt";

            Lines = new List<string>();
            keys = new List<string>();
            wsym = new Dictionary<string, int>();
            tags = new Dictionary<string, int>();
            Error = new List<string>();
            Init_lib();

            ch = ' ';
            count_tags = 1;
            sym = 0;
            a = "";

            line_index = 0;
            char_index = -1;

            Init_file();
        }

        public void Show()
        {
            foreach (string s in Lines)
            {
                Console.WriteLine(s);
                Console.WriteLine(s.Length);
            }
        }

        private Tuple<int,int> Next_char_position()
        {
            int row, col;
            if (char_index < Lines[line_index].Length - 1)
            { 
                col = char_index + 1;
                row = line_index;
            }
            else
            {
                row = line_index + 1;
                col = 0;
            }
            return new Tuple<int, int>(row, col);
        }

        private Tuple<int, int> Prev_char_position()
        {
            int row, col;
            if (char_index > 0)
            {
                col = char_index - 1;
                row = line_index;
            }
            else
            {
                row = line_index - 1;
                col = Lines[row].Length - 1;
            }
            return new Tuple<int, int>(row, col);
        }

        private char getchar()
        {
            if (!Is_EOF())
            {
                Tuple<int, int> pos = Next_char_position();
                line_index = pos.Item1;
                char_index = pos.Item2;
                return Lines[line_index][char_index];
            }
            else
                return '\0';
        }

        private bool Is_EOF()
        {
            return line_index == Lines.Count - 1 && Is_end_of_line();
        }

        private bool Is_end_of_line()
        {
            return char_index == Lines[line_index].Length - 1;
        }

        private Tuple<int,int> Get_curr()
        {
            return new Tuple<int, int>(line_index + 1, char_index + 1);
        }

        private Tuple<int, int> abs(Tuple<int, int> t)
        {
            return new Tuple<int, int>(t.Item1 + 1, t.Item2 + 1);
        }

        private void Err(Tuple<int, int> position, int type)
        {
            string wrong_code = position.ToString() + Lines[position.Item1 - 1].Substring(0, position.Item2);
            switch (type)
            {
                case 1: 
                    Error.Add(wrong_code + "<-- 字符串没有以\"\'\"符号结束\n");
                    break;
                case 2:
                    Error.Add(wrong_code + "<-- 注释没有以\"*/\"符号结束\n");
                    break;
                case 3:
                    Error.Add(wrong_code + "<-- " + a + "是非法字符!\n");
                    break;
                case 4:
                    Error.Add(wrong_code + "<-- " + a + "是非法标识符，标识符不能以数字开头!\n");
                    break;
                case 5:
                    Error.Add(wrong_code + "<-- 数字超过最大表示范围!\n");
                    break;
                default:
                    break;
            }
        }

        private void Print_error()
        {
            if (Error.Count != 0)
            {
                Console.WriteLine("\n错误列表：");
                foreach (string s in Error)
                {
                    Console.WriteLine(s);
                }
            }
            else
                Console.WriteLine("\n分析完毕");
        }

        private int Analyse_word()
        {
            a = "";

            while (ch == ' ' || ch == 10 || ch == 13 || ch == 9)        //忽略空格、换行、回车和Tab
            {
                ch = getchar();     //取下一个字符到ch
            }
            if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')       //标识符或保留字以a~z开头
            {
                while (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z' || ch >= '0' && ch <= '9')
                {
                    a += ch;        //标识符或保留字的字母数字串置于字符数组a
                    ch = getchar();     //取下一个字符到ch
                }

                if (wsym.ContainsKey(a))     //是保留字
                {
                    sym = wsym[a];      //置保留字的单词种别至sym
                }
                else    //搜索失败，不是保留字
                {
                    sym = wsym["标识符"];      //置单词种别全局变量sym为ident，即标识符
                    if (!tags.ContainsKey(a))
                    {
                        tags.Add(a, count_tags);       //a加入标识符列表
                        count_tags++;
                    }
                }
            }
            else if (ch >= '0' && ch <= '9')        //检测是否为数字：以0~9开头
            {
                int endline = 0;
                while (ch >= '0' && ch <= '9')
                {
                    a += ch;        //标识符或保留字的字母数字串置于字符数组a
                    if (Is_end_of_line())
                    {
                        endline = 1;
                        ch = getchar();     //取下一个字符到ch
                        break;
                    }
                    ch = getchar();     //取下一个字符到ch
                }
                if (endline == 0 && (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z'))
                {
                    while (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z' || ch >= '0' && ch <= '9')
                    {
                        a += ch;        //标识符或保留字的字母数字串置于字符数组a
                        ch = getchar();     //取下一个字符到ch
                    }
                    Console.Write("\n" + a + "是非法标识符\n标识符不能以数字开头!\n");
                    Err(abs(Prev_char_position()), 4);
                    sym = -1;
                    return 0;
                }
                sym = wsym["整数"];       //置单词种别全局变量sym为number，即无符号整数
                if (a.Length > 2000000000)    //数字超过允许的范围，报错
                {
                    Err(Get_curr(), 5);
                }

                if (!tags.ContainsKey(a))
                {
                    tags.Add(a, count_tags);       //a加入标识符列表
                    count_tags++;
                }
            }
            //不是数字
            else if (ch == '\'')        //检测是否为字符串
            {
                a += ch;        //标识符或保留字的字母数字串置于字符数组a
                ch = getchar();     //取下一个字符到ch
                while (ch != '\'')
                {
                    if (Is_end_of_line())  //报错
                    {
                        Console.Write("\n字符串没有以\"\'\"符号结束\n");
                        Err(Get_curr(), 1);
                        sym = -1;
                        return 0;
                    }
                    a += ch;        //标识符或保留字的字母数字串置于字符数组a
                    ch = getchar();     //取下一个字符到ch
                }
                a += ch;
                ch = getchar();

                sym = wsym["字符常数"];     //置单词种别全局变量sym为字符常数
                if (!tags.ContainsKey(a))
                {
                    tags.Add(a, count_tags);       //a加入标识符列表
                    count_tags++;
                }
            }
            else if (ch == ':')     //检测赋值符号
            {
                ch = getchar();
                if (ch == '=')
                {
                    sym = wsym[":="];   //置单词种别为becomes，即赋值符号
                    ch = getchar();
                }
                else
                {
                    sym = wsym[":"];        //置单词种别为:
                }
            }
            else if (ch == '<')     //检测小于或小于等于符号
            {
                ch = getchar();
                if (ch == '=')
                {
                    sym = wsym["<="];   //置单词种别为leq，即小于等于符号
                    ch = getchar();
                }
                else
                {
                    if (ch == '>')
                    {
                        sym = wsym["<>"];   //置单词种别为不等于符号
                        ch = getchar();
                    }
                    else
                    {
                        sym = wsym["<"];        //置单词种别为lss，即小于符号
                    }
                }
            }
            else if (ch == '>')     //检测小于或大于等于符号
            {
                ch = getchar();
                if (ch == '=')
                {
                    sym = wsym[">="];   //置单词种别为geq，即大于等于符号
                    ch = getchar();
                }
                else
                {
                    sym = wsym[">"];        //置单词种别为gtr，即大于符号
                }
            }
            else if (ch == '.')     //检测.或..符号
            {
                ch = getchar();
                if (ch == '.')
                {
                    sym = wsym[".."];   //置单词种别为..符号
                    ch = getchar();
                }
                else
                {
                    sym = wsym["."];        //置单词种别为.符号
                }
            }
            else if (ch == '/')     //检测/或/*符号
            {
                ch = getchar();
                if (ch == '*')
                {
                    sym = -1;       //none output
                    ch = getchar();
                    while (true)
                    {
                        if (Is_end_of_line() && ch != '/')     //报错
                        {
                            Console.Write("\n注释没有以\"*/\"符号结束\n");
                            Err(Get_curr(), 2);
                            sym = -1;
                            return 0;
                        }
                        if (ch == '*')
                        {
                            ch = getchar();
                            if (Is_end_of_line() && ch != '/')  //报错
                            {
                                Console.Write("\n注释没有以\"*/\"符号结束\n");
                                Err(Get_curr(), 2);
                                sym = -1;
                                return 0;
                            }
                            if (ch == '/')
                                break;
                        }
                        ch = getchar();     //取下一个字符到ch
                    }
                    ch = getchar();
                }
                else
                {
                    sym = wsym["/"];        //置单词种别为/符号
                }
            }
            else
            {       //当符号不满足上述条件时，全部按照单字符号处理
                a += ch;
                ch = getchar();
                if (wsym.ContainsKey(a))
                {
                    sym = wsym[a];
                }
                else
                {
                    Console.Write(a + "是非法字符!\n");
                    Err(abs(Prev_char_position()), 3);
                    sym = -1;
                    return 0;
                }
            }
            return 1;
        }

        public void Analyse()
        {
            while (!Is_EOF()) 
            {
                Analyse_word();
                if (sym == -1) continue;
                if (sym != 36 && sym != 37 && sym != 38)
                {
                    Console.Write("(" + sym + "," + keys[sym] + ")\t");
                }
                else
                {
                    Console.Write("(" + sym + "," + tags[a] + ")\t");
                }
            }
            Print_error();
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("作者：李泰稷\n班级：计科一班\n学号：201730613328\n");
            while (true)
            {
                Console.Write("请输入测试程序名：");
                string title = Console.ReadLine();

                Code C = new Code(title);

                C.Analyse();
            }
        }
    }
}

