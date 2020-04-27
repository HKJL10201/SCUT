using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


using Airport_ver1._0.Tickets;

namespace Airport_ver1._0.FileIO
{
    class UsersTicketsIO :TicketsIO
    {
        private string DataPath = @".\Data\UsersTicketsData";
        string Username;

        List<Ticket> UsersTicket_List;  //Amended by Lee

        public UsersTicketsIO(string Username)
        {
            this.Username = Username;
            DataPath += @"\" + Username + ".txt";
            UsersTicket_List = new List<Ticket>();
            UsersTicket_List = ReadAll();
        }

        public string Append(Ticket ticket)//**************************zeng增
        {
            int target = Sort_Search.Binary_search_FlightNumber(UsersTicket_List, UsersTicket_List.Count, ticket.FlightNumber);
            if (target == UsersTicket_List.Count) //列表中没有这张票
            {
                UsersTicket_List.Add(ticket);
            }
            else
            {
                UsersTicket_List[target].Allowance = (int.Parse(UsersTicket_List[target].Allowance)
                            + int.Parse(ticket.Allowance)).ToString();
            }
            Rewrite();

            /*在对应的机票文件中增加项*/
            string filePath = @".\Data\UsersTicketsData\Tickets\" + ticket.FlightNumber + ".txt";
            StreamWriter streamWriter = new StreamWriter(filePath, true);
            streamWriter.WriteLine(Username);
            return "Append successfully";

            //以下注释是你原来的代码
            /*List<Ticket> tickets = new List<Ticket>();
            StreamReader Reader = new StreamReader(DataPath);
            Ticket tmpticket;

            int haveput = 0;

            do
            {
                tmpticket = Ticket.Read(Reader);
                if (!tmpticket.isNull())
                {
                    if (tmpticket.FlightNumber != ticket.FlightNumber)
                        tickets.Add(tmpticket);
                    else if(haveput == 0)
                    {
                        Ticket newticket = tmpticket;
                        newticket.Allowance = (int.Parse(newticket.Allowance)
                            + int.Parse(ticket.Allowance)).ToString();
                        tickets.Add(newticket);
                        haveput = 1;
                    }
                }
                else
                    break;

            } while (true);

            Reader.Close();

            if (haveput == 0)
            {
                tickets.Add(ticket);
            }

            StreamWriter streamWriter = new StreamWriter(DataPath,false);

            foreach (Ticket t in tickets)
            {
                t.Write(streamWriter);
            }

            streamWriter.Close();*/
        }

        public List<Ticket> ReadAll()
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
        }

        public new string Delete(Ticket ticket)//*****************************shan删
        {
            int target = Sort_Search.Binary_search_FlightNumber(UsersTicket_List, UsersTicket_List.Count, ticket.FlightNumber);
            if (target == UsersTicket_List.Count) //列表中没有这张票
            {
                Console.WriteLine("没有此票，删除失败");
                return "没有此票，删除失败";
            }
            else
            {
                UsersTicket_List.Remove(ticket);
            }
            Rewrite();

            return "Delete successfully";

            //以下注释是你原来的代码
            /*List<Ticket> tickets = new List<Ticket>();
            StreamReader Reader = new StreamReader(DataPath);
            Ticket tmpticket;

            do
            {
                tmpticket = Ticket.Read(Reader);
                if (!tmpticket.isNull())
                {
                    if(tmpticket.FlightNumber!= ticket.FlightNumber)
                        tickets.Add(tmpticket);
                    else
                    {
                        ;
                    }
                }
                else
                    break;

            } while (true);

            Reader.Close();

            Rewrite();

            L = ReadAll();*/
        }

        public new void Rewrite()//**************************************************重写列表至文件
        {
            Console.WriteLine("Rewrite");
            StreamWriter w = new StreamWriter(DataPath, false);
            foreach (Ticket t in UsersTicket_List)
            {
                Console.WriteLine(t.MyToString());
                t.Write(w);
            }
            w.Close();
            return;
        }

        public new string Update(Ticket oldone, Ticket newone)//**************************gai改
        {
            int target = Sort_Search.Binary_search_FlightNumber(UsersTicket_List, UsersTicket_List.Count, oldone.FlightNumber);
            if (target == UsersTicket_List.Count) //列表中没有这张票
            {
                Console.WriteLine("没有此票，更新失败");
                return "没有此票，更新失败";
            }
            else
            {
                UsersTicket_List[target].Copy(newone);
            }
            Rewrite();

            return "Update successfully";

            //以下注释是你原来的代码
            /*List<Ticket> tickets = new List<Ticket>();
            StreamReader Reader = new StreamReader(DataPath);
            Ticket tmpticket;

            do
            {
                tmpticket = Ticket.Read(Reader);
                if (!tmpticket.isNull())
                {
                    if (tmpticket.FlightNumber != oldone.FlightNumber)
                        tickets.Add(tmpticket);
                    else
                    {
                        tickets.Add(newone);
                    }
                }
                else
                    break;

            } while (true);

            Reader.Close();

            Rewrite();

            L = ReadAll();*/
        }

        public void Standby(string fn)
        {
            string filePath = @".\Data\UsersTicketsData\Tickets\" + fn + "_Standby.txt";
            StreamWriter streamWriter = new StreamWriter(filePath, true);
            streamWriter.WriteLine(Username);
        }
    }
}
