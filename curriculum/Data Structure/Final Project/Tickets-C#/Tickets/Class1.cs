using System;
using System.IO;
using System.Collections.Generic;


namespace Airport_ver1._0.Tickets
{
    public class Ticket
    {
        public string FlightNumber;
        public string Origin;
        public string Terminal;
        public string Date;
        public string BeginTime;
        public string EndTime;
        public string Price;
        public string Capacity;
        public string Allowance;
        public string Aircraft_Type;

        public Ticket() { }

        public Ticket(string FlightNumber, string Origin, string Terminal, string Date,
            string BeginTime, string EndTime, string Price, string Capacity, string Allowance,
            string Aircraft_Type)
        {
            this.FlightNumber = FlightNumber;
            this.Origin = Origin;
            this.Terminal = Terminal;
            this.Date = Date;
            this.BeginTime = BeginTime;
            this.EndTime = EndTime;
            this.Price = Price;
            this.Capacity = Capacity;
            this.Allowance = Allowance;
            this.Aircraft_Type = Aircraft_Type;
        }

        public static Ticket Read(StreamReader streamReader)
        {
            Ticket ticket = new Ticket();
            if ((ticket.Origin = streamReader.ReadLine()) != null)
            {
                ticket.Terminal = streamReader.ReadLine();
                ticket.Date = streamReader.ReadLine();
                ticket.BeginTime = streamReader.ReadLine();
                ticket.EndTime = streamReader.ReadLine();
                ticket.Price = streamReader.ReadLine();
                ticket.Capacity = streamReader.ReadLine();
                ticket.Allowance = streamReader.ReadLine();
                ticket.FlightNumber = streamReader.ReadLine();
                ticket.Aircraft_Type = streamReader.ReadLine();
            }
            return ticket;
        }

        public static string Write(Ticket ticket, StreamWriter w)
        {
            w.WriteLine(ticket.Origin);
            w.WriteLine(ticket.Terminal);
            w.WriteLine(ticket.Date);
            w.WriteLine(ticket.BeginTime);
            w.WriteLine(ticket.EndTime);
            w.WriteLine(ticket.Price);
            w.WriteLine(ticket.Capacity);
            w.WriteLine(ticket.Allowance);
            w.WriteLine(ticket.FlightNumber);
            w.WriteLine(ticket.Aircraft_Type);
            return null;
        }

        public bool IsNull()
        {
            if (Origin == null)
                return true;
            else
                return false;
        }


        //规定FlightNumber为主码
        public static bool operator ==(Ticket t1, Ticket t2)
        {
            return t1.FlightNumber == t2.FlightNumber;
        }

        public static bool operator !=(Ticket t1, Ticket t2)
        {
            return t1.FlightNumber != t2.FlightNumber;
        }

        /*public static Ticket operator =(Ticket t1,Ticket t2)
        {
            t1.Origin = t2.Origin;
            t1.Terminal = t2.Terminal;
            t1.Date = t2.Date;
            t1.BeginTime = t2.BeginTime;
            t1.EndTime = t2.EndTime;
            t1.Price = t2.Price;
            t1.Capacity = t2.Capacity;
            t1.Allowance = t2.Allowance;
            t1.FlightNumber = t2.FlightNumber;
            t1.Aircraft_Type = t2.Aircraft_Type;
            return t1;
        }*/

        public void Show()
        {
            Console.WriteLine(FlightNumber + "\t" + Origin + "\t" + Terminal + "\t" + Date + "\t" + BeginTime +
                 "\t" + EndTime + "\t" + Price + "\t" + Capacity + "\t" + Allowance + "\t" + Aircraft_Type);
            return;
        }

        /*public bool Equal_to(Ticket ticket)
        {
            if (this.FlightNumber == ticket.FlightNumber)
                return true;
            else
                return false;
        }*/

        public void Copy(Ticket t)
        {
            Origin = t.Origin;
            Terminal = t.Terminal;
            Date = t.Date;
            BeginTime = t.BeginTime;
            EndTime = t.EndTime;
            Price = t.Price;
            Capacity = t.Capacity;
            Allowance = t.Allowance;
            FlightNumber = t.FlightNumber;
            Aircraft_Type = t.Aircraft_Type;
            return;
        }

        public static int Compare_date(Ticket t1, Ticket t2)
        {
            int result = t1.Date.CompareTo(t2.Date);
            if (result != 0)
                return result;
            else
            {
                result = t1.BeginTime.CompareTo(t2.BeginTime);
                if (result != 0)
                    return result;
                else
                {
                    result = t1.EndTime.CompareTo(t2.EndTime);
                    return result;
                }
            }
        }
        
    }


    class Table
    {
        private List<Ticket> L;
        private Dictionary<string, List<Ticket>> D;
        private string filename;

        private string Get_key(string origin, string terminal, string date)
        {
            return origin + terminal + date;
        }

        public Table(string filename)
        {
            this.filename = filename;
            L = new List<Ticket>();
            D = new Dictionary<string, List<Ticket>>();
            StreamReader f = new StreamReader(filename);
            while (!f.EndOfStream)
            {
                Ticket t = Ticket.Read(f);
                if (!t.IsNull())
                {
                    L.Add(t);
                    Sort_Search.Inssort_FlightNum(L, 0, L.Count - 1);//如果确保了文件顺序是按日期排好的话，这句可省略
                }
                Add_in_Dic(t);
            }
            f.Close();
        }
        
        public void Show_all()
        {
            foreach (Ticket t in L)
                t.Show();
            return;
        }

        public string Insert(Ticket ticket)
        {
            L.Add(ticket);
            Sort_Search.Qsort_FlightNum(L, 0, L.Count - 1);
            Add_in_Dic(ticket);
            StreamWriter w = new StreamWriter(filename, append: true);
            Ticket.Write(ticket, w);
            w.Close();
            return "Insert successfully";
        }

        public string Delete(Ticket ticket)
        {
            if (!Delete_from_Dic(ticket))
                return "failed";
            foreach (Ticket t in L)
            {
                if (t == ticket) 
                {
                    L.Remove(t);
                    break;
                }
            }
            Rewrite();
            return "Delete successfully";
        }

        private bool Delete_from_Dic(Ticket ticket)
        {
            string key = Get_key(ticket.Origin, ticket.Terminal, ticket.Date);
            if (D.ContainsKey(key))
            {
                foreach (Ticket t in D[key])
                {
                    if (t == ticket) 
                    {
                        D[key].Remove(t);
                        return true;
                    }
                }
                return false;
            }
            else
                return false;
        }

        private string Add_in_Dic(Ticket t)
        {
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

        public string Update(Ticket oldone, Ticket newone)
        {
            if (!Delete_from_Dic(oldone))
                return "failed";
            Add_in_Dic(newone);
            foreach (Ticket t in L)
            {
                if (t == oldone) 
                {
                    t.Copy(newone);
                    break;
                }
            }
            Rewrite();
            return "Update successfully";
        }

        public void Rewrite()
        {
            StreamWriter w = new StreamWriter(filename);
            foreach (Ticket t in L)
                Ticket.Write(t, w);
            w.Close();
            return;
        }
        
        public void Search(string origin, string destination, string date)
        {
            string key = Get_key(origin, destination, date);
            if (!D.ContainsKey(key))
            {
                Console.WriteLine("结果不存在");
                return;
            }
            Sort_Search.Qsort_date(D[key], 0, D[key].Count - 1);//???????????
            foreach (Ticket t in D[key])
            {
                t.Show();
            }
            return;
        }
    }

    class Sort_Search
    {
        static void Swap(List<Ticket> L, int i, int j)
        {
            Ticket temp = new Ticket();
            temp.Copy(L[i]);
            L[i].Copy(L[j]);
            L[j].Copy(temp);
        }
        static public void Inssort_date(List<Ticket> L, int l, int r)
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
        static public void Qsort_date(List<Ticket> L, int i, int j)
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

        static public void Inssort_FlightNum(List<Ticket> L, int l, int r)
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
        static public void Qsort_FlightNum(List<Ticket> L, int i, int j)
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
        int Binary_search(List<Ticket> L, int n, string Flight_num)
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
    }

    class Program
    {
        static void Main(string[] args)
        {
            const string FlightData = "./FlightData/FlightData.txt";
            Table T = new Table(FlightData);
            string choose = "";
            while (choose != "E")
            {
                Console.WriteLine("\nWelcome to SCUT!\n\nA:Show all\nS:Search\nI:Insert\nD:Delete\nU:Update\nE:Exit\n");
                choose = Console.ReadLine();
                if (choose == "A")
                {
                    T.Show_all();
                }
                if (choose == "S")
                {
                    Console.WriteLine("Please input your start point:");
                    string origin = Console.ReadLine();
                    Console.WriteLine("Please input your destination:");
                    string destination = Console.ReadLine();
                    Console.WriteLine("Please input the date:");
                    string date = Console.ReadLine();
                    Console.WriteLine("result:");
                    T.Search(origin, destination, date);
                }
                if (choose == "I") 
                {
                    Console.WriteLine("Please input the ticket information:");
                    Ticket ticket = Input_Ticket();
                    Console.WriteLine(T.Insert(ticket));
                }
                if (choose == "D") 
                {
                    Console.WriteLine("Please input the ticket information:");
                    Ticket ticket = Input_Ticket();
                    Console.WriteLine(T.Delete(ticket));
                }
                if (choose == "U") 
                {
                    Console.WriteLine("Please input the old ticket information:");
                    Ticket oldone = Input_Ticket();
                    Console.WriteLine("Please input the new ticket information:");
                    Ticket newone = Input_Ticket();
                    Console.WriteLine(T.Update(oldone, newone));
                }
                if (choose == "E")
                    break;
            }
        }

        static Ticket Input_Ticket()
        {
            Console.WriteLine("Origin:");
            string Origin = Console.ReadLine();
            Console.WriteLine("Terminal:");
            string Terminal = Console.ReadLine();
            Console.WriteLine("Date:");
            string Date = Console.ReadLine();
            Console.WriteLine("BeginTime:");
            string BeginTime = Console.ReadLine();
            Console.WriteLine("EndTime:");
            string EndTime = Console.ReadLine();
            Console.WriteLine("Price:");
            string Price = Console.ReadLine();
            Console.WriteLine("Capacity:");
            string Capacity = Console.ReadLine();
            Console.WriteLine("Allowance:");
            string Allowance = Console.ReadLine();
            Console.WriteLine("FlightNumber:");
            string FlightNumber = Console.ReadLine();
            Console.WriteLine("Aircraft_Type:");
            string Aircraft_Type = Console.ReadLine();

            Ticket ticket = new Ticket(FlightNumber, Origin, Terminal, Date,
            BeginTime, EndTime, Price, Capacity, Allowance, Aircraft_Type);
            return ticket;
        }
    }
}
