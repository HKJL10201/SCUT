class stu{
	String[] info;
}

public class Student {
	public static void main(String[] args) {
		int size=3;
		stu[] Students=new stu[size];
		
		for(int i=0;i<size;i++)
		{
			Students[i] = new stu();
			Students[i].info=new String[3];
		}
		
		
		Students[0].info[0]="Alice";
		Students[0].info[1]="17001";
		Students[0].info[2]="201709";
		
		Students[1].info[0]="Bob";
		Students[1].info[1]="18002";
		Students[1].info[2]="201809";
		
		Students[2].info[0]="Cindy";
		Students[2].info[1]="19003";
		Students[2].info[2]="201908";
		
		
		System.out.println("姓名\t学号\t入学年月");
		
		for(int i=0;i<3;i++) 
		{
			for(int j=0;j<3;j++)
				System.out.print(Students[i].info[j]+'\t');
			System.out.println();
		}
		
		}
}
