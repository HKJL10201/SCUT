class Person
{
	String Name;
	int Age;
}
class Teacher extends Person
{
	final String status = "Teacher";
	public Teacher(String n,int a) 
	{
		Name=n;
		Age=a;
	}
	void Intro()
	{
		System.out.println("姓名："+Name+"\t年龄："+Age+"\t身份："+status);
	}
}
class Student extends Person
{
	final String status = "Student";
	public Student(String n,int a) 
	{
		Name=n;
		Age=a;
	}
	void Intro()
	{
		System.out.println("姓名："+Name+"\t年龄："+Age+"\t身份："+status);
	}
}
public class Inherit 
{
	public static void main(String[] args)
	{
		Student a,b,c;
		Teacher A,B,C;
		a=new Student("Alice",17);
		b=new Student("Bobby",18);
		c=new Student("Cindy", 19);
		A=new Teacher("Allan", 36);
		B=new Teacher("Benny", 28);
		C=new Teacher("Charles", 42);
		a.Intro();
		b.Intro();
		c.Intro();
		A.Intro();
		B.Intro();
		C.Intro();
	}
}
