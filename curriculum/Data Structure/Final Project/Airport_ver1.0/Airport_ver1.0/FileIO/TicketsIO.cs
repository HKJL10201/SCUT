using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;

using Airport_ver1._0.Tickets;

namespace Airport_ver1._0.FileIO
{
    public class TicketsIO
    {
        private static string DataPath = @".\Data\TicketsData.txt";
        //************************************************************************************
        public List<Ticket> L;
        private Dictionary<string, List<Ticket>> D;

        public TicketsIO()
        {
            L = new List<Ticket>();
            D = new Dictionary<string, List<Ticket>>();
            StreamReader f = new StreamReader(DataPath);
            while (!f.EndOfStream)
            {
                Ticket t = Ticket.Read(f);
                if (!t.isNull())
                {
                    L.Add(t);
                    Add_in_Dic(t);
                    Sort_Search.Inssort_FlightNum(L, 0, L.Count - 1);//如果确保了文件顺序是按FN排好的话，这句可省略
                }
            }
            f.Close();
        }

        private string Get_key(string origin, string terminal, string date)
        {
            string res = origin + terminal + date;
            Console.WriteLine("res=" + res);
            return origin + terminal + date;
        }

        private bool Delete_from_Dic(Ticket ticket)
        {
            //Console.WriteLine(ticket.MyToString());
            string key = Get_key(ticket.Origin, ticket.Terminal, ticket.Date);

            //Console.WriteLine("In delete 2");
            if (D.ContainsKey(key))
            {
                //Console.WriteLine("IF1");
                int target = Sort_Search.Binary_search_Date(D[key], D[key].Count, ticket.Date);
                if (target == D[key].Count)
                {
                    //Console.WriteLine("IF2");
                    return false;
                }
                else
                {
                    D[key].Remove(D[key][target]);
                    return true;
                }
            }
            else
            {
                
                Console.WriteLine(D.ToString());
                foreach (string s in D.Keys)
                    Console.WriteLine(s);
                Console.WriteLine("string key="+key);
                Console.WriteLine("IF3");
                return false;
            }
        }

        private string Add_in_Dic(Ticket ticket)
        {
            Ticket t = new Ticket();
            t.Copy(ticket);
            string key = Get_key(t.Origin, t.Terminal, t.Date);
            if (D.ContainsKey(key))
            {
                D[key].Add(t);
                Sort_Search.Qsort_date(D[key], 0, D[key].Count - 1);
            }
            else
            {
                List<Ticket> Li = new List<Ticket> { t };
                D.Add(key, Li);
            }
            return "";
        }


        public void Rewrite()//**************************************************重写列表至文件
        {
            Console.WriteLine("Rewrite");
            StreamWriter w = new StreamWriter(DataPath,false);
            foreach (Ticket t in L)
            {
                Console.WriteLine(t.MyToString());
                t.Write(w);
            }
            w.Close();
            return;
        }


        public string Insert(Ticket ticket)//**************************zeng增
        {
            int target = Sort_Search.Binary_search_FlightNumber(L, L.Count, ticket.FlightNumber);
            if (target != L.Count)
            {
                return "Allready have this ticket, Insert failed. ";
            }
            L.Add(ticket);
            Add_in_Dic(ticket);
            Sort_Search.Qsort_FlightNum(L, 0, L.Count - 1);
            Rewrite();
            return "Insert successfully";
        }

        public string Delete(Ticket ticket)//*****************************shan删
        {
            Console.WriteLine("In delete1");
            int target = Sort_Search.Binary_search_FlightNumber(L, L.Count, ticket.FlightNumber);
            if (target == L.Count)
            {
                Console.WriteLine("F1");
                return "Failed";
            }
            if (!Delete_from_Dic(ticket))
            {
                Console.WriteLine("F2");
                return "Failed";
            }
            L.Remove(L[target]);
            Rewrite();
            return "Delete successfully";
        }

        public string Update(Ticket oldone, Ticket newone)//**************************gai改
        {
            int target = Sort_Search.Binary_search_FlightNumber(L, L.Count, oldone.FlightNumber);
            if (target == L.Count)
                return "Failed";
            if (!Delete_from_Dic(oldone))
                return "Failed";
            Add_in_Dic(newone);
            L[target].Copy(newone);
            Rewrite();
            return "Update successfully";
        }

        public List<Ticket> Search(string origin, string destination, string date)//*****************cha查
        {
            string key = Get_key(origin, destination, date);
            if (!D.ContainsKey(key))
            {
                Console.WriteLine("结果不存在");
                return new List<Ticket>();
            }
            else if (D[key].Count == 0)
            {
                Console.WriteLine("结果不存在");
                return new List<Ticket>();
            }

            //Sort_Search.Qsort_date(D[key], 0, D[key].Count - 1);//???????????
            /*foreach (Ticket t in D[key])
            {
                //t.Show();
            }*/

            return D[key];
        }

        //*********************************************************************
        /*
        public static bool IsTicketExist(Ticket ticket)
        {
            StreamReader Reader = new StreamReader(DataPath);
            Ticket tmpticket;
            do
            {
                tmpticket = Ticket.Read(Reader);
                if (!tmpticket.isNull())
                {
                    //已经重载==号，只判断主码
                    if (tmpticket == ticket)
                    {
                        Reader.Close();
                        return true;
                    }
                }
                else
                    break;

            } while (true);

            Reader.Close();
            return false;
        }
        */

        /*public static List<Ticket> ReadAll()
        {
            List<Ticket> tickets = new List<Ticket>();
            StreamReader Reader = new StreamReader(DataPath);
            Ticket ticket;

            do
            {
                ticket = Ticket.Read(Reader);
                if (!ticket.isNull())
                {
                    tickets.Add(ticket);
                }
                else
                    break;

            } while (true);

            Reader.Close();
            return tickets;
        }*///****************************************lee
        /*
        //写入应该是私有的，由封装的其他接口进入
        private static void WriteAll(List<Ticket> tickets)
        {
            //第二个参数是append，传入false表示全部重写，其实可以缺省
            StreamWriter streamWriter = new StreamWriter(DataPath, false);

            foreach(Ticket ticket in tickets){
                //Ticket的Write方法并不会关闭流
                ticket.Write(streamWriter);
            }

            streamWriter.Close();
            return;
        }

        //写入应该是私有的，由封装的其他接口进入
        private static void Write(Ticket ticket)
        {
            //第二个参数是append，传入true表示尾部追加
            StreamWriter streamWriter = new StreamWriter(DataPath, true);
            ticket.Write(streamWriter);
            streamWriter.Close();
            return;
        }

        public static string Insert(Ticket ticket)
        {
            if (IsTicketExist(ticket))
            {
                return "Allready have this ticket, Insert failed. ";
            }

            //调试时，直接追加到末尾的实现

            Write(ticket);

            return "Insert successfully";

            //真正的实现

            /*
            
            List<Ticket> tickets = new List<Ticket>();

            StreamReader Reader = new StreamReader(DataPath);

            Ticket tmpTicket;
            do
            {
                tmpTicket = Ticket.Read(Reader);
                if (!tmpTicket.isNull())
                {
                    tickets.Add(tmpTicket);
                }
                else
                    break;

            } while (true);

            Reader.Close();

            tickets.Add(ticket);
            //追加到末尾

            return tickets;
            
            */
            /*
        }

        public static string Delete(Ticket ticket)
        {
            //将整个文件读入列表，跳过ticket，并全部写回
            List<Ticket> tickets = new List<Ticket>();
            StreamReader Reader = new StreamReader(DataPath);
            Ticket tmpTicket;

            do
            {
                tmpTicket = Ticket.Read(Reader);
                if (!tmpTicket.isNull())
                {
                    //跳过ticket
                    if (tmpTicket == ticket)
                        continue;
                    else
                        tickets.Add(tmpTicket);
                }
                else
                    break;

            } while (true);

            Reader.Close();

            //全部重写
            WriteAll(tickets);

            return "Delete successfully";


        }

        public static string Update(Ticket ticket)
        {
            //将整个文件读入列表，替换ticket，并全部写回
            List<Ticket> tickets = new List<Ticket>();
            StreamReader Reader = new StreamReader(DataPath);
            Ticket tmpTicket;

            do
            {
                tmpTicket = Ticket.Read(Reader);
                if (!tmpTicket.isNull())
                {
                    //替换ticket，这里重载了==号识别主码
                    if (tmpTicket == ticket)
                    {
                        tickets.Add(ticket);
                    }
                    else
                        tickets.Add(tmpTicket);
                }
                else
                    break;

            } while (true);

            Reader.Close();

            //全部重写
            WriteAll(tickets);

            return "Update successfully";
        }

        //根据用户输入的信息生成一个包含FlightNumber的机票，查询所有符合要求的机票（虽然只有一张)，返回列表
        public static List<Ticket> SearchByFlightNumber(Ticket ticket)
        {
            List<Ticket> tickets=new List<Ticket>();
            return tickets;
        }

        //根据用户输入的信息生成一个包含Origin,Terminal,Date的机票，查询所有符合要求的机票，返回列表
        public static List<Ticket> SearchByOTD(Ticket ticket)
        {
            List<Ticket> tickets=new List<Ticket>();
            return tickets;
        }*/

    }



    public class Sort_Search
    {
        static void Swap(List<Ticket> L, int i, int j)
        {
            Ticket temp = new Ticket();
            temp.Copy(L[i]);
            L[i].Copy(L[j]);
            L[j].Copy(temp);
        }
        public static void Inssort_date(List<Ticket> L, int l, int r)
        {
            for (int i = l + 1; i <= r; i++)
                for (int j = i; (j > l) && (Ticket.Compare_date(L[j], L[j - 1]) == -1); j--)
                    Swap(L, j, j - 1);
        }
        static bool Select(int n)
        {
            if (n <= 4)     //n*(n-1)/2与nlogn交点在3和4之间
                return true;
            else
                return false;
        }
        static int Findpivot_date(List<Ticket> L, int i, int j)
        {
            int m = (i + j) / 2;
            if (Ticket.Compare_date(L[i], L[m]) == 1)
                Swap(L, i, m);
            if (Ticket.Compare_date(L[i], L[j]) == 1)
                Swap(L, i, j);
            if (Ticket.Compare_date(L[m], L[j]) == 1)
                Swap(L, m, j);
            return m;
        }
        static int Partition_date(List<Ticket> L, int l, int r, Ticket pivot)
        {
            do
            {
                while (Ticket.Compare_date(L[l], pivot) == -1)
                    l++;
                while ((r > l) && (Ticket.Compare_date(L[r], pivot) != -1))
                    r--;
                Swap(L, l, r);       //Swap out-of-place values
            } while (l < r);    //Stop when they cross
            return l;       //return first pos on right
        }
        public static void Qsort_date(List<Ticket> L, int i, int j)
        {
            if (j <= i) return;     //List too small
            if (Select(j - i))
                Inssort_date(L, i, j);
            else
            {
                int pivot = Findpivot_date(L, i, j);

                Swap(L, pivot, j);   //Put pivot at end
                                     //k will be first position on right side
                int k = Partition_date(L, i, j, L[j]);
                Swap(L, k, j);       //Put pivot in place
                Qsort_date(L, i, k - 1);
                Qsort_date(L, k + 1, j);
            }
        }

        public static void Inssort_FlightNum(List<Ticket> L, int l, int r)
        {
            for (int i = l + 1; i <= r; i++)
                for (int j = i; (j > l) && (L[j].FlightNumber.CompareTo(L[j - 1].FlightNumber) == -1); j--)
                    Swap(L, j, j - 1);
        }
        static int Findpivot_FlightNum(List<Ticket> L, int i, int j)
        {
            int m = (i + j) / 2;
            if (L[i].FlightNumber.CompareTo(L[m].FlightNumber) == 1)
                Swap(L, i, m);
            if (L[i].FlightNumber.CompareTo(L[j].FlightNumber) == 1)
                Swap(L, i, j);
            if (L[m].FlightNumber.CompareTo(L[j].FlightNumber) == 1)
                Swap(L, m, j);
            return m;
        }
        static int Partition_FlightNum(List<Ticket> L, int l, int r, Ticket pivot)
        {
            do
            {
                while (L[l].FlightNumber.CompareTo(pivot.FlightNumber) == -1)
                    l++;
                while ((r > l) && (L[r].FlightNumber.CompareTo(pivot.FlightNumber) != -1))
                    r--;
                Swap(L, l, r);       //Swap out-of-place values
            } while (l < r);    //Stop when they cross
            return l;       //return first pos on right
        }
        public static void Qsort_FlightNum(List<Ticket> L, int i, int j)
        {
            if (j <= i) return;     //List too small
            if (Select(j - i))
                Inssort_FlightNum(L, i, j);
            else
            {
                int pivot = Findpivot_FlightNum(L, i, j);

                Swap(L, pivot, j);   //Put pivot at end
                                     //k will be first position on right side
                int k = Partition_FlightNum(L, i, j, L[j]);
                Swap(L, k, j);       //Put pivot in place
                Qsort_FlightNum(L, i, k - 1);
                Qsort_FlightNum(L, k + 1, j);
            }
        }


        // Return the position of an element in sorted array "A" of
        // size "n" with value "K". If "K" is not in "A", return
        // the value "n".

        public static int Binary_search_FlightNumber(List<Ticket> L, int n, string Flight_num)
        {
            int l = -1;
            int r = n; // l and r are beyond array bounds
            while (l + 1 != r)
            { // Stop when l and r meet
                int i = (l + r) / 2; // Check middle of remaining subarray
                if (Flight_num.CompareTo(L[i].FlightNumber) == -1) r = i; // In left half
                if (Flight_num == L[i].FlightNumber) return i; // Found it
                if (Flight_num.CompareTo(L[i].FlightNumber) == 1) l = i; // In right half
            }
            return n; // Search value not in A
        }

        public static int Binary_search_Date(List<Ticket> L, int n, string Date)
        {
            int l = -1;
            int r = n; // l and r are beyond array bounds
            while (l + 1 != r)
            { // Stop when l and r meet
                int i = (l + r) / 2; // Check middle of remaining subarray
                if (Date.CompareTo(L[i].Date) == -1) r = i; // In left half
                if (Date == L[i].Date) return i; // Found it
                if (Date.CompareTo(L[i].Date) == 1) l = i; // In right half
            }
            return n; // Search value not in A
        }
    }

}
