class Atom {					//���ࣺԭ����
	public void Chemical()
	{
		System.out.println("Ħ������");		//����Chemical������ʾĦ������
	}
}

class Fe extends Atom			//���ࣺ����̳�ԭ����
{
	Fe() 	//���๹�췽������ʾ��������
	{
		System.out.print("����");
	}
	public void Chemical()					//��ʾ��Ԫ�ص�Ħ������
	{
		System.out.println("56g/mol");
	}
}
class Cu extends Atom			//���ࣺͭ��̳�ԭ����
{
	Cu()	//���๹�췽������ʾ��������
	{
		System.out.print("ͭ��");
	}
	public void Chemical()					//��ʾͭԪ�ص�Ħ������
	{
		System.out.println("63.5g/mol");
	}
}
public class mole {
	public static void main(String[] args)
	{
		Chemical(new Fe());		//�����������
		Chemical(new Cu());
	}
	public static void Chemical(Atom a)		//�����Ĳ����Ǹ��ࣺԭ����
	{
		a.Chemical();
	}
}