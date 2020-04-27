class Atom {					//父类：原子类
	public void Chemical()
	{
		System.out.println("摩尔质量");		//定义Chemical方法显示摩尔质量
	}
}

class Fe extends Atom			//子类：铁类继承原子类
{
	Fe() 	//子类构造方法，显示子类名称
	{
		System.out.print("铁：");
	}
	public void Chemical()					//显示铁元素的摩尔质量
	{
		System.out.println("56g/mol");
	}
}
class Cu extends Atom			//子类：铜类继承原子类
{
	Cu()	//子类构造方法，显示子类名称
	{
		System.out.print("铜：");
	}
	public void Chemical()					//显示铜元素的摩尔质量
	{
		System.out.println("63.5g/mol");
	}
}
public class mole {
	public static void main(String[] args)
	{
		Chemical(new Fe());		//传入子类参数
		Chemical(new Cu());
	}
	public static void Chemical(Atom a)		//方法的参数是父类：原子类
	{
		a.Chemical();
	}
}