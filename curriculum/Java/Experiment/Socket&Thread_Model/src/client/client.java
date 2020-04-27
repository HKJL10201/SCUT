package client;
import javax.swing.*;
import java.io.*;
import java.net.*;
import java.awt.*;
import java.awt.event.*;

public class client {

	//界面组件
	JButton[] button = new JButton[9];
	JButton start=new JButton();
	JButton quit=new JButton();
	JTextArea text = new JTextArea();
	
	//功能组件
	Socket server = null;//服务器
	int[] count = new int[9];//统计井字棋状态
	chess startplaying;
	
	
	
	buttonlistener[] listener = new buttonlistener[9];
	quitlistener qtlistener = new quitlistener();
	startlistener stlistener = new startlistener();
	
	static int interrupt_judge=0;//落子判断
	boolean ready = false;//判断玩家是否 准备好
	
	
	//内部类
	private class count_chess
	{
		Socket client = null;
		public count_chess(Socket s) throws IOException
		{
			client = s;
		}
		public count_chess()
		{
			
		}
		
		public void run()
		{
			
		}
		
		public int judge()
		{
			for(int i =0;i<9;i++)
			{
				switch(i){
				case 0:{
					if(count[i]!=0)
					{
						if((count[0]==1&&count[1]==1&&count[2]==1)||
							(count[0]==1&&count[3]==1&&count[6]==1)||
							(count[0]==1&&count[4]==1&&count[8]==1))
							return 1;
						else if((count[0]==2&&count[1]==2&&count[2]==2)||
								(count[0]==2&&count[3]==2&&count[6]==2)||
								(count[0]==2&&count[4]==2&&count[8]==2))
								return 2;
					}
					break;
				}
				case 1:
				{
					if(count[1]==1&&count[4]==1&&count[7]==1) return 1;
					else if(count[1]==2&&count[4]==2&&count[7]==2) return 2;
					break;
				}
				case 2:
				{
					if((count[2]==1&&count[4]==1&&count[6]==1)||
						(count[2]==1&&count[5]==1&&count[8]==1))	return 1;
					else if((count[2]==1&&count[4]==1&&count[6]==1)||
							(count[2]==1&&count[5]==1&&count[8]==1)) return 2;
					break;
				
				}
				case 3:
				{
					if(count[3]==1&&count[4]==1&&count[5]==1) return 1;
					else if(count[3]==2&&count[4]==2&&count[5]==2) return 2;
					break;
				}
				case 4:
				{
					if(count[6]==1&&count[7]==1&&count[8]==1) return 1;
					else if(count[6]==2&&count[7]==2&&count[8]==2) return 2;
					break;
				}
				default:break;
				}
			}
			return 0;
		}
	}
	
	
	class buttonlistener implements ActionListener
	{
		public int i = 0;//默认未落子
		public void actionPerformed(ActionEvent e)
		{
			i = 1;
			for(int j = 0;j<9;j++)
			{
				button[j].setEnabled(false);//限制落子
			}
			interrupt_judge=1;
		}
	}
	class quitlistener implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			try{
		
			server.close();
			
		}catch(IOException ioe)
		{
			ioe.printStackTrace();
			System.out.println("关闭服务器失败，鬼才知道是什么原因");
		}
		}
	}
	class startlistener implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			ready = true;
			start.setEnabled(false);
		}
	}
	
	class chess extends Thread//弄个线程专门管下棋
	{
		
		
		count_chess jud = new count_chess();
		public chess() throws IOException
		{
			//text.append("至少进入chess()了吧，143");
			
			
			//start();
		}
		public void run()
		{
			for(int i =0;i<9;i++)
				button[i].setEnabled(false);
			
			text.append("进入房间。"+"\r\n");
			
			
			try {
				server = new Socket("127.0.0.1",12349);
			} catch (UnknownHostException e3) {
				// TODO Auto-generated catch block
				e3.printStackTrace();
			} catch (IOException e3) {
				// TODO Auto-generated catch block
				e3.printStackTrace();
			}
			
			
			
			text.append("请耐心等待游戏开始......"+"\r\n");
			
			
			String ready_signal = null;
			
		
			
			
			text.append("游戏开始。你先落子。"+"\r\n");
			
			
			String save = "000000000";//储存客户端传过来的数组信息
			String input = "000000000";//储存自己的数组信息，用来发送给客户端
			
			//client_cin.readline()接收从客户端传来的信息
			//client_cout.print(input)发送给客户端信息
			/*
			try{
			save = server_cin.readLine();//读取客户端的信息
			}
			catch(IOException e)
			{
				System.out.println("client的save读取出错");
			}
			*/
			while(save != null && !save.trim().equals("quit"))
			{
			//把客户端信息输入到数组中
			for(int i = 0;i<9;i++)
			{
				count[i] = Integer.parseInt(save.substring(i, i+1)) ;//字符串中的字符逐个转换为数字，填进count里面
				if(count[i]==0)
					button[i].setEnabled(true);
				if(count[i]==1) button[i].setText("O");
				else if(count[i]==2) button[i].setText("X");
			}
			input = "";
			//if(interrupt_judge == 0) text.append("进入落子判断循环"+"\r\n");
			while(interrupt_judge==0)
			{
				try {
					sleep(500);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				if(interrupt_judge ==1) {
					text.append("你已落子"+"\r\n");
					break;
				}
			}
			
			
			
			for(int i = 0;i<9;i++)
			{
				if(count[i]==0) count[i]=listener[i].i;
				if(count[i]==1) button[i].setText("O");
				else if(count[i]==2) button[i].setText("X");
				input+=count[i];
			}
			
			
			
			try {
				server = new Socket("127.0.0.1",12349);
			} catch (UnknownHostException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			
			
		
			server_cout.println(input);
			//text.append("客户端已发送信息，信息："+input+"\r\n");
			server_cout.flush();
			
			//String temp = "0";
			
			//强行发送连接
			//while(temp.equals("0")){
				//text.append("客户端已进入连接判断循环"+"\r\n");
				
				
				//try {
				//	sleep(3000);
				//} catch (InterruptedException e) {
					// TODO Auto-generated catch block
				//	e.printStackTrace();
				//}
				
				
				
			try {
				
				server = new Socket("127.0.0.1",12349);
				//text.append("客户端已重新建立连接"+"\r\n");
				
				//temp = server_cin.readLine();
				
				//text.append("已收到服务端确认信息，信息为："+temp+"\r\n");
				/*
				server_cout.println(temp);
				text.append("已向服务端发送确认信息"+"\r\n");
				
				*/
			} catch (UnknownHostException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			
			
			try{
			save = server_cin.readLine();
			//text.append("客户端已接收到信息，信息为："+save+"\r\n");
			
			}catch(IOException e)
			{
				System.out.println("client的save读取出错");
			}
			interrupt_judge = 0;
			/*
			if(save.equals("平局")||save.equals("你已获胜！")||save.equals("你输了！"))
			{
				text.append(save);
				for(int i =0;i<9;i++)
					button[i].setEnabled(false);
				break;
				
			}*/
			text.append("判断");
			if(save.substring(0,1)=="7")
			{
				text.append("平局");
				for(int i =0;i<9;i++)
					button[i].setEnabled(false);
				break;
			}
			else if(save.substring(0,1)=="9")
			{
				text.append("你已获胜！");
				for(int i =0;i<9;i++)
					button[i].setEnabled(false);
				break;
			}
			else if(save.substring(0,1)=="8")
			{
				text.append("你输了！");
				for(int i =0;i<9;i++)
					button[i].setEnabled(false);
				break;
			}
		}
			
			
			
			
			//程序执行完之后,关闭所有东西
			try{
			server_cin.close();
			server_cout.close();
			client_cin.close();
			server.close();
			}catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	
	}
	
	
	
	
	//输入输出流
	BufferedReader server_cin;//读取服务端传来的数据
	PrintWriter server_cout;//输出服务端传来的数据
	BufferedReader client_cin;//读取键盘数据
	
	//操作方法
	public void setframe()//创建界面
	{
		JFrame ui = new JFrame();
		ui.setTitle("井字棋对战(客户端)");
		//关闭方式
		ui.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		JPanel centerpanel = new JPanel();
		ui.getContentPane().add(centerpanel, BorderLayout.CENTER);//采用默认布局
		quit.addActionListener(qtlistener);
		start.addActionListener(stlistener);
		
		//运用BOX布局
		Box[] box_vert = new Box[3];
		Box box = Box.createHorizontalBox();
		for(int i =0;i<3;i++ )
		{
			box_vert[i] = Box.createVerticalBox();
			for(int j =0;j<3;j++ )
			{
				button[j+3*i] = new JButton(" ");
				listener[j+3*i] = new buttonlistener();
				
				//监听器注册到按钮上
				button[j+3*i].addActionListener(listener[j+3*i]);
				
				//panel.add(button[j]);
				
				//添加按钮
				box_vert[i].add(button[j+3*i]);
				//设置垂直间距
				box_vert[i].add(Box.createVerticalStrut(20));
				
			}
			box.add(box_vert[i]);
			box.add(Box.createHorizontalStrut(20));
		}
		centerpanel.add(box);
		
		JPanel southpanel = new JPanel();
		ui.getContentPane().add(southpanel,BorderLayout.SOUTH);
		

		JPanel toppanel = new JPanel();
		JLabel label = new JLabel("井字棋大战");
		toppanel.add(label);
		ui.getContentPane().add(toppanel,BorderLayout.NORTH);
		
		JPanel eastpanel = new JPanel();
		

		JScrollPane textscroll = new JScrollPane();
		textscroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
		textscroll.setViewportView(text);
		
		text.setRows(20);
		text.setColumns(20);
		eastpanel.add(text);
		eastpanel.add(textscroll);
		
		ui.getContentPane().add(eastpanel,BorderLayout.EAST);
	
		
		start = new JButton("开始游戏");
		quit = new JButton("退出游戏");
		Box box_south = Box.createHorizontalBox();
		box_south.add(start);
		box_south.add(Box.createHorizontalStrut(10));
		box_south.add(quit);
		
		southpanel.add(box_south);
		
		
		
		//（x位置，y位置，长，宽），根据像素确定位置，坐标原点左上角
		ui.setBounds(400,400,550,400);
		ui.setVisible(true);
		
	}
	public client() throws IOException
	{
		//text.append("client()，297"+"\r\n");
		this.startplaying = new chess();
	}
	public void	set_stream() throws IOException
	{
		server_cin = new BufferedReader(new InputStreamReader(server.getInputStream()));//用于接收服务端信息
		server_cout = new PrintWriter(server.getOutputStream());//用于输出服务端信息
		client_cin = new BufferedReader(new InputStreamReader(System.in));//用于接收键盘输入信息
	}
	public void set_server()
	{
		try
		{
			server = new Socket("127.0.0.1",12349);
			//text.append("服务器指向成功，145"+"\r\n");
			
		}catch(Exception e)
		{
			System.out.println("请求接受失败");
			//text.append("服务器指向失败，150"+"\r\n");
			System.exit(-1);
		
		}
	}
	public static void main(String[] args) throws IOException
	{
		client game_client = new client();
		game_client.setframe();
		game_client.set_server();
		game_client.set_stream();
		game_client.startplaying.run();
		
	}
}
