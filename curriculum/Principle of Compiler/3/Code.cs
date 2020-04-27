using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace exp2
{
    class Syms
    {
        private List<Tuple<int, string>> sym;
        private int index;
        private int end_flag;

        public Syms()
        {
            sym = new List<Tuple<int, string>>();
            index = -1;
            end_flag = 0;
        }
        public void Add(int a, string b)
        {
            sym.Add(new Tuple<int, string>(a, b));
        }
        public void MoveOn()
        {
            if (index < sym.Count - 1)
                index++;
            else
                end_flag = 1;
        }
        public int Next()
        {
            if (end_flag == 1)
                return 0;
            MoveOn();
            return sym[index].Item1;
        }
        public string Second()
        {
            return sym[index].Item2;
        }
        public int NextIs()
        {
            if (end_flag == 1)
                return 0;
            return sym[index + 1].Item1;
        }
        public bool IsTheEnd()
        {
            return index == sym.Count - 1;
        }
    }
    class FourTuple
    {
        public string[] S;
        public FourTuple()
        {
            S = new string[4];
        }
        public FourTuple(string sym, string s1, string s2, string t)
        {
            S = new string[4];
            S[0] = sym;
            S[1] = s1;
            S[2] = s2;
            S[3] = t;
        }
        public string Show()
        {
            return "(" + S[0] + ", " + S[1] + ", " + S[2] + ", " + S[3] + ")";
        }
        public void SetForth(string t)
        {
            S[3] = t;
        }
    }
    class TupleTable
    {
        private List<FourTuple> L;
        private int T_index;

        public TupleTable()
        {
            L = new List<FourTuple>();
            T_index = 0;
        }
        public void emit(string sym,string s1,string s2,string t)
        {
            L.Add(new FourTuple(sym, s1, s2, t));
            //Console.WriteLine(L[L.Count - 1].Show());
        }
        public string Tn()
        {
            T_index++;
            return "T" + T_index.ToString();
        }
        public void Show()
        {
            int i = 0;
            foreach (FourTuple t in L)
            {
                Console.WriteLine("(" + i.ToString() + ")\t" + t.Show());
                i++;
            }
        }
        public int nextstat()
        {
            return L.Count;
        }
        public void backpatch(int pointer_start,int target)
        {
            if (pointer_start == 0) return;
            string curr = pointer_start.ToString();
            string next;
            //Console.WriteLine("bp" + pointer_start.ToString());
            while (curr!="$")
            {
                //Console.WriteLine(next);
                next = L[int.Parse(curr)].S[3];
                L[int.Parse(curr)].SetForth(target.ToString());
                curr = next;
            }
        }
        public int merge(int a,int b)
        {
            if (b == 0) return a;
            string next = b.ToString();
            while(L[int.Parse(next)].S[3]!="$")
                next = L[int.Parse(next)].S[3];
            L[int.Parse(next)].SetForth(a.ToString());
            return b;
        }
    }
    class Attr
    {
        public string name;     //变量名
        public string type;     //变量类型
        public string value;    //变量的值（int,char,bool)
        public int val;         //变量的数值（int类型）
        public bool truth;      //变量的真值
        public Attr()
        {
            name = "";
            type = "";
            value = "";
            val = 0;
            truth = false;
        }
        public Attr(string n, string t)
        {
            name = n;
            type = t;
            value = "";
            val = 0;
            truth = false;
        }
        public Attr(string n, string t, string v)
        {
            name = n;
            type = t;
            value = v;
            val = 0;
            truth = false;
            TransValue();
        }
        public void TransValue()
        {
            if(type=="integer")
            {
                val = int.Parse(value);
            }
            else if(type=="bool")
            {
                if (value == "true")
                    truth = true;
                else if (value == "false")
                    truth = false;
            }
        }
        public void Set_val(string v)
        {
            value = v;
            TransValue();
        }
        public string Show()
        {
            return "(" + name + ": " + type + ", " + value + ")";
        }
        public bool IsTrue()
        {
            if (value == "" || val == 0 || truth == false)
                return false;
            else
                return true;
        }
    }
    class AttriTable
    {
        private Dictionary<string, Attr> attrs; //所有变量的属性字典
        private List<string> UndefinedToken;    //已声明但未确定类型的变量
        private List<string> DefinedToken;      //已声明的变量列表
        public AttriTable()
        {
            attrs = new Dictionary<string, Attr>();
            UndefinedToken = new List<string>();
            DefinedToken = new List<string>();
        }
        public bool DefineNew(string name)
        {
            foreach(string n in UndefinedToken) //Redefined
            {
                if (name == n) return false;
            }
            foreach (string n in DefinedToken)  //Redefined
            {
                if (name == n) return false;
            }
            UndefinedToken.Add(name);
            return true;
        }
        public void TypeDefine(string type) //传入变量的类型名
        {
            foreach(string name in UndefinedToken)
            {
                attrs.Add(name, new Attr(name, type));  //将变量名、类型添加到字典
                DefinedToken.Add(name);     //将变量名添加到已声明列表
            }
            UndefinedToken = new List<string>();    //清空未声明列表
        }
        public void Add(string name,string type,string value)    //for temporary variable only
        {
            if (!attrs.ContainsKey(name))
            {
                attrs.Add(name, new Attr(name, type, value));
                DefinedToken.Add(name);
            }
        }
        public void Set_val(string name,string value)
        {
            attrs[name].Set_val(value);
        }
        public bool Is_exist(string name)
        {
            return attrs.ContainsKey(name);
        }
        public Attr GetAttr(string name)
        {
            return attrs[name];
        }
        public bool IsType(string name,string type)
        {
            return attrs[name].type == type;
        }
        public void Show()
        {
            foreach(string n in DefinedToken)
            {
                Console.WriteLine(attrs[n].Show());
            }
        }
    }
    class E
    {
        public int codebegin;   //表达式的起始地址
        public int True;        //真出口地址
        public int False;       //假出口地址
        public E()
        {
            codebegin = 0;
            True = 0;
            False = 0;
        }
        public E(int c,int t,int f)
        {
            codebegin = c;
            True = t;
            False = f;
        }
    }
    class Code
    {
        private string filename;
        private string path;

        private List<string> Lines;
        private static List<string> keys;
        private static Dictionary<string, int> wsym;
        private Dictionary<string, int> tags;
        private List<string> Error;

        private Syms Token;
        private TupleTable Tb;
        private AttriTable AT;

        private char ch;
        private int count_tags;
        private int sym;
        private string a;

        private int line_index;
        private int char_index;

        private string vari;
        private static string Chain_end;

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
            Token = new Syms();
            Tb = new TupleTable();
            AT = new AttriTable();
            Init_lib();

            ch = ' ';
            count_tags = 1;
            sym = 0;
            a = "";

            line_index = 0;
            char_index = -1;

            vari = "";
            Chain_end = "$";

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
        private Tuple<int, int> Next_char_position()
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
        private Tuple<int, int> Get_curr()
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
        public bool NoError()
        {
            return Error.Count == 0;
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
                    if(Is_end_of_line())
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
                    Token.Add(sym, keys[sym]);
                }
                else
                {
                    Console.Write("(" + sym + "," + tags[a] + ")\t");
                    Token.Add(sym, a);
                }
            }
            Print_error();
        }
        //************************************************************************************************
        public void Anal_G()
        {
            PG();
            //AT.Show();
            Tb.Show();
        }
        private bool IsNext(string s)
        {
            return MoveOn() == wsym[s];
        }
        private int MoveOn()
        {
            int i = Token.Next();
            a = Token.Second();
            if (i == 36 || i == 37 || i == 38)
                vari = a;
            return i;
        }
        private void Gerror(string type)
        {
            Console.WriteLine(type);
        }
        private void PG()
        {
            if (IsNext("program") && IsNext("标识符") && IsNext(";"))
            {
                Tb.emit("program", vari, "-", "-");
                VI();
                CS();
                if (IsNext(".") && Token.IsTheEnd())
                {
                    Tb.emit("sys", "-", "-", "-");
                    return;
                }
                else
                    Gerror("NotTheEndError");
            }
            else
                Gerror("ProgramHeadError");
        }
        private void VI()
        {
            if (Token.NextIs() == wsym["begin"]) return;
            else if (IsNext("var")) VD();
            else Gerror("InvalidSyntax");
        }
        private void VD()
        {
            TT();
            if (IsNext(":"))
            {
                T();
                AT.TypeDefine(a);
                if (IsNext(";"))
                {
                    if (Token.NextIs() == wsym["begin"]) return;
                    else VD();
                }
                else Gerror("SentenceEndError");
            }
            else Gerror("VariableDefineError");
        }
        private void TT()
        {
            if (IsNext("标识符"))
            {
                if (!AT.DefineNew(a)) Gerror("RedefineError");//返回false说明重定义错误
                if (Token.NextIs() == wsym[":"]) return;
                else if (IsNext(",")) TT();
                else Gerror("InvalidSyntax");
            }
            else Gerror("InvalidSyntax");
        }
        private void T()
        {
            int t = Token.NextIs();
            if (t == wsym["integer"] || t == wsym["bool"] || t == wsym["char"])
            {
                MoveOn();
                return;
            }
            else Gerror("InvalidType");
        }
        private int CS()
        {
            int chain = 0;
            if (IsNext("begin"))
            {
                chain = ST();
                if (IsNext("end")) return chain;
                else Gerror("SegmentEndError");
            }
            else Gerror("SegmentBeginError");
            return chain;
        }
        private int ST()
        {
            int chain = S();
            if (Token.NextIs() == wsym["end"])
            {
                Tb.backpatch(chain, Tb.nextstat()); 
                return chain;
            }
            else if (IsNext(";"))
            {
                Tb.backpatch(chain, Tb.nextstat()); 
                chain = ST();
            }
            else Gerror("SentenceEndError");
            return chain;
        }
        private int S()
        {
            switch (Token.NextIs())
            {
                case 36: return F();
                case 15: return IF();
                case 34: return WH();
                case 26: return RP();
                default: Gerror("InvalidSyntax");return 0;
            }
        }
        private int F()
        {
            if (IsNext("标识符") && IsNext(":="))
            {
                string tmp = vari;
                if (!AT.Is_exist(tmp))  //存在性检查
                    Gerror("Undefined Variable:" + tmp);
                else
                {
                    Attr at = A();
                    if (AT.IsType(tmp, at.type))    //相容性检查
                    {
                        AT.Set_val(tmp, at.value);
                        Tb.emit(":=", at.name, "-", tmp);
                    }
                    else
                        Gerror("DifferentType");
                }
            }
            else Gerror("InvalidSyntax");
            return 0;
        }
        private int IF()
        {
            int chain = 0;
            if (IsNext("if"))
            {
                E e = B();
                if (IsNext("then"))
                {
                    Tb.backpatch(e.True, Tb.nextstat());
                    int s1 = S();
                    chain = Tb.merge(e.False, s1);
                    if (Token.NextIs() == wsym["else"])
                    {
                        MoveOn();
                        int q = Tb.nextstat();
                        Tb.emit("j", "-", "-", Chain_end);
                        Tb.backpatch(e.False, Tb.nextstat());
                        int tp = Tb.merge(q, s1);
                        int s2 = S();
                        chain = Tb.merge(tp, s2);
                    }
                }
                else Gerror("WithoutThenError");
            }
            else Gerror("InvalidSyntax");
            return chain;
        }
        private int WH()
        {
            int chain = 0;
            if (IsNext("while"))
            {
                int codebegin = Tb.nextstat();
                E e = B();
                if (IsNext("do"))
                {
                    Tb.backpatch(e.True, Tb.nextstat());
                    chain = e.False;
                    int s = S();
                    Tb.backpatch(s, codebegin);
                    Tb.emit("j", "-", "-", codebegin.ToString());
                }
                else Gerror("WithoutDoError");
            }
            else Gerror("InvalidSyntax");
            return chain;
        }
        private int RP()
        {
            int chain = 0;
            if (IsNext("repeat"))
            {
                int codebegin = Tb.nextstat();
                S();
                if (IsNext("until"))
                { 
                    E e = B();
                    Tb.backpatch(e.False, codebegin);
                    chain = e.True;
                }
                else Gerror("WithoutUntilError");
            }
            else Gerror("InvalidSyntax");
            return chain;
        }
        private Attr A()    // A → X { +X | -X } 
        {
            Attr s1 = X();
            int sy = Token.NextIs();
            if (sy == wsym["+"] || sy == wsym["-"])
            {
                MoveOn();
                Attr s2 = A();
                if (s1.type == s2.type)    //相容性检查
                {
                    string tn = Tb.Tn();
                    int num;
                    if (sy == wsym["+"])
                        num = s1.val + s2.val;
                    else num = s1.val - s2.val;
                    AT.Add(tn, s1.type, num.ToString());
                    Tb.emit(keys[sy], s1.name, s2.name, tn);
                    return AT.GetAttr(tn);
                }
                else
                {
                    Gerror("DifferentType");
                    return s2;
                }
            }
            else return s1;
        }
        private Attr X()    // X → Y { *Y | /Y } 
        {
            Attr s1 = Y();
            int sy = Token.NextIs();
            if (sy == wsym["*"] || sy == wsym["/"])
            {
                MoveOn();
                Attr s2 = X();
                if (s1.type == s2.type)    //相容性检查
                {
                    string tn = Tb.Tn();
                    int num = 0;
                    if (sy == wsym["*"])
                        num = s1.val * s2.val;
                    else
                    {
                        if (s2.val != 0)
                            num = s1.val / s2.val;
                        else Gerror("DividedByZero");
                    }
                    AT.Add(tn, s1.type, num.ToString());
                    Tb.emit(keys[sy], s1.name, s2.name, tn);
                    return AT.GetAttr(tn);
                }
                else
                {
                    Gerror("DifferentType");
                    return s2;
                }
            }
            else return s1;
        }
        private Attr Y()    // Y → -Y | (A) | D
        {
            if (Token.NextIs() == wsym["-"])
            {
                MoveOn();
                Attr s = Y();
                if (s.type == "integer")    //相容性检查
                {
                    string tn = Tb.Tn();
                    int num = s.val * (-1);
                    AT.Add(tn, s.type, num.ToString());
                    Tb.emit("@", s.name, "-", tn);
                    return AT.GetAttr(tn);
                }
                else
                {
                    Gerror("NotAnInt");
                    return new Attr("0", "integer", "0");
                }
            }
            else if (Token.NextIs() == wsym["("])
            {
                MoveOn();
                Attr s = A();
                if (Token.NextIs() == wsym[")"])
                {
                    MoveOn();
                    return s;
                }
                else
                {
                    Gerror("WithoutRightBracket");
                    return s;
                }
            }
            else return D();
        }
        private Attr D()
        {
            int d = Token.NextIs();
            if (d == wsym["标识符"] || d == wsym["整数"])
            {
                MoveOn();
                if (AT.Is_exist(vari))  //存在性检查
                    return AT.GetAttr(vari);
                else if (d == wsym["整数"])
                    return new Attr(vari, "integer", vari);
            }
            else Gerror("InvalidSyntax");
            return new Attr("0", "integer", "0");
        }
        private E B()
        {
            E e = new E();
            E e1 = W();
            if (Token.NextIs() == wsym["or"])
            {
                MoveOn();
                E e2 = B();
                e.codebegin = e1.codebegin;
                Tb.backpatch(e1.False, e2.codebegin);
                e.True = Tb.merge(e1.True, e2.True);
                e.False = e2.False;
                return e;
            }
            else
                return e1;
        }
        private E W()
        {
            E e = new E();
            E e1 = Z();
            if (Token.NextIs() == wsym["and"])
            {
                MoveOn();
                E e2 = W();
                e.codebegin = e1.codebegin;
                Tb.backpatch(e1.True, e2.codebegin);
                e.True = e2.True;
                e.False = Tb.merge(e1.False, e2.False);
                return e;
            }
            else
                return e1;
        }
        private E Z()
        {
            E e = new E();
            if (Token.NextIs() == wsym["not"])      //not开头
            {
                MoveOn();
                E et = L();
                e.codebegin = et.codebegin;
                e.True = et.False;
                e.False = et.True;
                return e;
            }
            else if (Token.NextIs() == wsym["("])
            {
                MoveOn();
                e = B();
                if (Token.NextIs() == wsym[")"])
                    MoveOn();
                else 
                    Gerror("WithoutRightBracket");
                return e;
            }
            else 
                return L();
        }
        private E L()
        {
            E e = new E();
            int d = Token.NextIs();
            if (d == wsym["true"] || d == wsym["false"])        //布尔常数
            {
                MoveOn();
                e.codebegin = Tb.nextstat();
                if (d == wsym["true"])
                {
                    e.True = Tb.nextstat();
                    e.False = 0;
                }
                else
                {
                    e.False = Tb.nextstat();
                    e.True = 0;
                }
                Tb.emit("j", "-", "-", Chain_end);
            }
            else       //标识符开头
            {
                Attr at = A();
                e.codebegin = Tb.nextstat();
                if (at.IsTrue())
                {
                    e.True = Tb.nextstat();
                    e.False = 0;
                }
                else
                {
                    e.False = Tb.nextstat();
                    e.True = 0;
                }
                d = Token.NextIs();
                if (d >= 53 && d <= 58)     //如果下一字是关系运算符
                {
                    MoveOn();
                    Attr bt = A();
                    e.codebegin = Tb.nextstat();
                    e.True = Tb.nextstat();
                    e.False = Tb.nextstat() + 1;
                    Tb.emit("j" + keys[d], at.name, bt.name, Chain_end);
                    Tb.emit("j", "-", "-", Chain_end);
                }
                else
                {
                    Tb.emit("j", "-", "-", Chain_end);
                }
            }
            return e;
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
                if (C.NoError())
                    C.Anal_G();
                else
                    Console.WriteLine("有词法错误");
            }
        }
    }
}

