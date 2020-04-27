import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.awt.*;
import javax.swing.*;
class FamilyName
{
	char c;
	int n;
	String[] NameList;
	FamilyName()
	{
		c='\0';
		n=0;
		NameList = new String[64];
	}
}
public class Names 
{
	static String output="";
	public static void main(String[] args)
	{
		FamilyName[] Fn = new FamilyName[64];
		for(int i=0;i<64;i++)
			Fn[i]=new FamilyName();
		Scanner s = null;
		try
		{
			s = new Scanner(new File("./src/Names.txt"));
			while(s.hasNextLine())
			{
				String name = s.nextLine();
				char c = name.charAt(0);
				int success=0;
				for(int i=0;i<64;i++)
				{
					if(c==Fn[i].c)
					{
						Fn[i].NameList[Fn[i].n]=name;
						Fn[i].n++;
						success=1;
						break;
					}
				}
				if(success==0)
				{
					for(int i=0;i<64;i++)
					{
						if(Fn[i].c=='\0')
						{
							Fn[i].NameList[Fn[i].n]=name;
							Fn[i].c=c;
							Fn[i].n=1;
							break;
						}
					}
				}
			}
		}
		catch(FileNotFoundException e)
		{
			e.printStackTrace();
		}
		finally
		{
			if(s!=null)
				s.close();
		}
		for(int i=0;i<64;i++)
		{
			if(Fn[i].c!='\0')
			{
				output+=Fn[i].c+":"+Fn[i].n+"ÈË";
				for(int j=0;j<Fn[i].n;j++)
					output+="\t"+Fn[i].NameList[j];
				output+="\n";
			}
			else
				break;
		}
		CreatFrame("Name");
	}
	static void CreatFrame(String title)
	{
		JFrame jf = new JFrame(title);
		Container C = jf.getContentPane();
		JTextArea t=new JTextArea(output);
		C.add(t);
		jf.setVisible(true);
		jf.setSize(600, 800);
		jf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	}
}
