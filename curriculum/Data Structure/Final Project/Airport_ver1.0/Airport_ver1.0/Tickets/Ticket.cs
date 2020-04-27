using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.IO;

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

        public Ticket(string flightNumber)
        {
            //规定航班号不能重复，可以唯一标识
            FlightNumber = flightNumber;
        }
        

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
            Ticket ticket=new Ticket();
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

                Console.WriteLine(ticket.Origin);
            }
            return ticket;
        }

        public void Write(StreamWriter streamWriter)
        {
            streamWriter.WriteLine(Origin);
            streamWriter.WriteLine(Terminal);
            streamWriter.WriteLine(Date);
            streamWriter.WriteLine(BeginTime);
            streamWriter.WriteLine(EndTime);
            streamWriter.WriteLine(Price);
            streamWriter.WriteLine(Capacity);
            streamWriter.WriteLine(Allowance);
            streamWriter.WriteLine(FlightNumber);
            streamWriter.WriteLine(Aircraft_Type);

            return;
        }

        public ListViewItem ToListViewItem()
        {
            ListViewItem listViewItem=new ListViewItem(FlightNumber);
            listViewItem.SubItems.Add(Origin);
            listViewItem.SubItems.Add(Terminal);
            listViewItem.SubItems.Add(Date);
            listViewItem.SubItems.Add(BeginTime);
            listViewItem.SubItems.Add(EndTime);
            listViewItem.SubItems.Add(Price);
            listViewItem.SubItems.Add(Capacity);
            listViewItem.SubItems.Add(Allowance);
            listViewItem.SubItems.Add(Aircraft_Type);

            return listViewItem;
        }

        public void FromListViewItem(ListViewItem listViewItem)
        {
            FlightNumber=listViewItem.SubItems[0].Text;
            Origin = listViewItem.SubItems[1].Text;
            Terminal = listViewItem.SubItems[2].Text;
            Date = listViewItem.SubItems[3].Text;
            BeginTime = listViewItem.SubItems[4].Text;
            EndTime = listViewItem.SubItems[5].Text;
            Price = listViewItem.SubItems[6].Text;
            Capacity = listViewItem.SubItems[7].Text;
            Allowance = listViewItem.SubItems[8].Text;
            Aircraft_Type = listViewItem.SubItems[9].Text;

            return ;
        }

        public void FromListViewItem()
        {

        }

        public bool isNull()
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

        public override bool Equals(Object other)
        {
            //this非空，obj如果为空，则返回false
            if (ReferenceEquals(null, other)) return false;

            //如果类型不同，则必然不相等
            if (other.GetType() != this.GetType()) return false;

            //如果为同一对象，必然相等
            if (ReferenceEquals(this, other)) return true;

            return FlightNumber == ((Ticket)other).FlightNumber;
        }

        //实现Equals重写同时，必须重写GetHashCode
        public override int GetHashCode()
        {
            return (FlightNumber != null ? StringComparer.InvariantCulture.GetHashCode(FlightNumber) : 0);
        }

        public string MyToString()
        {
            return "Ticket: "+FlightNumber+" "+Origin+" "+Terminal+" "+Date;
        }


        //*****************************************************************************
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
}
