package server;
import javax.swing.*;
import java.io.*;
import java.net.*;
import java.awt.*;
import java.awt.event.*;

public class server extends JFrame{
	
	//界面组件
	JButton[] button = new JButton[9];
	JButton start =new JButton();
	JButton quit=new JButton();
	JTextArea text = new JTextArea();
	
	//功能组件
	ServerSocket server = null;//服务器
	int[] count = new int[9];//统计井字棋状态
	chess startplaying;
	Socket client = null;//客户端
	
	
	buttonlistener[] listener = new buttonlistener[9];
	quitlistener qtlistener = new quitlistener();
	startlistener stlistener = new startlistener();
	
	static int interrupt_judge = 0;//判断是否落子
	boolean ready=false;//判断玩家是否 准备好
	

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
			i = 2;
			
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
		}
	}
	class chess extends Thread//弄个线程专门管下棋
	{
		
		count_chess jud = new count_chess();
		public chess() throws IOException
		{
			
			
			//start();
		}
		public void run()
		{
			for(int i =0;i<9;i++)
				button[i].setEnabled(false);
			text.append("等待玩家连接......"+"\r\n");
			String save = null;//储存客户端传过来的数组信息
			String input = null;//储存自己的数组信息，用来发送给客户端
			
			//client_cin.readline()接收从客户端传来的信息
			//client_cout.print(input)发送给客户端信息
			try {
				client = server.accept();
				text.append("玩家已连接。"+"\r\n");
				
				text.append("请耐心等待游戏开始......"+"\r\n");
				
				text.append("游戏开始。由对方先落子。"+"\r\n");
				save = client_cin.readLine();//读取客户端的信息
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			
			
			
			//text.append("判断有没有跳过"+"\r\n");
			
			
			for(int countnum = 0;save != null && !save.trim().equals("quit") && countnum<5;countnum++)
			{
				text.append("轮到你落子"+"\r\n");
			//把客户端信息输入到数组中
			for(int i = 0;i<9;i++)
			{
				count[i] = Integer.parseInt(save.substring(i, i+1)) ;//字符串中的字符逐个转换为数字，填进count里面
				button[i].setEnabled(false);//关闭按钮
				
			if(count[i]==1) 
				{
				button[i].setText("O");
			
				}
			else if(count[i]==2) 
				{
				button[i].setText("X");
				}
			
			}
			
			//判断是否已经决出胜负
			//没决出胜负judge==0
			if(jud.judge()==0) 
			{
				if(countnum==5){
					text.append("平局");
					client_cout.println("7");
					input = "平局";
					break;
				}
				//根据数组信息解锁可以操作的按钮
				for(int i =0;i<9;i++)
				{
					if(count[i]==0)
						button[i].setEnabled(true);
				}
				while(interrupt_judge == 0)
				{
					//text.append("判断有没有进入判断循环"+"\r\n");
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
			}
			else{
				if(jud.judge()==2) 
					{
					text.append("你已获胜！");
					input = "你输了！";
					break;
					}
				else{
					text.append("你输了！");
					input = "你已获胜！";
					break;
				}
			}
			
			
			if(jud.judge()==0)
			{
				input = "";
				for(int i=0;i<9;i++)
				{
					if(count[i]==0) count[i]=listener[i].i;
					if(count[i]==1) button[i].setText("O");
					else if(count[i]==2) button[i].setText("X");
					input+=count[i];
				}
				
				//String temp ="1"; 
				//强行接收
				//while(temp.equals("1")){
					
				
				//try {
					try {
						client = server.accept();
					} catch (IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					} 
					//text.append("已重新连接"+"\r\n");
					
					//try {
					//	sleep(2000);
					//} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						//e.printStackTrace();
					//}
					
					//client_cout.println("1");//确认接收状态
					//text.append("已发送重连确认信息"+"\r\n");
					
					//temp ="0";
					/*
					temp = client_cin.readLine();
					text.append("已收到客户端端确认信息，信息为："+temp+"\r\n");
					*/
				//} catch (IOException e1) {
					// TODO Auto-generated catch block
				//	e1.printStackTrace();
				//}
				
				client_cout.println(input);
				//text.append("服务端已发送信息，信息："+input+"\r\n");
				
				client_cout.flush();
				try{
				save = client_cin.readLine();
				//text.append("服务端已接收信息，信息："+save+"\r\n");
				}catch(IOException e)
				{
					System.out.println("server的save读取出错");
				}
				interrupt_judge =0;//落子判断归零
			}
			else
			{
				if(jud.judge()==2) 
				{
					text.append("你已获胜！");
					input = "你输了！";
					client_cout.println("8");
					for(int i =0;i<9;i++)
						button[i].setEnabled(false);
					break;
				}
				else{
					text.append("你输了！");
					input = "你已获胜！";
					client_cout.println("9");
					for(int i =0;i<9;i++)
						button[i].setEnabled(false);
					break;
				}
			}
			}	
			if(input.equals("平局")||input.equals("你已获胜！")||input.equals("你输了！"))
			{
				client_cout.print(input);
			}
			//程序执行完之后,关闭所有东西
			try{
			client_cin.close();
			client_cout.close();
			server_cin.close(); 
			client.close();
			server.close();
			}catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}
	
	
	//输入输出流
	BufferedReader client_cin;//读取客户端传来的数据
	PrintWriter client_cout;//输出客户端传来的数据
	BufferedReader server_cin;//读取键盘数据
	
	//操作方法
	public server() throws IOException//建立服务器
	{
		this.startplaying = new chess();
	}	
		//这里进行startplaying的初始化使程序卡死在accept();
		
	public void set_server_client(Socket client)
	{
	try{
			server = new ServerSocket(12349);
			text.append("端口申请成功"+"\r\n");
			
		}catch(Exception e)                                   //异常信息输出，没啥好看的
		{
			System.out.println("Error:"+e);
			System.out.println("服务器建立失败");
			text.append("服务器建立失败"+"\r\n");
			System.exit(-1);
			
		}
	try
	{
		client = server.accept(); 		//新建的客户端口，指向向服务器发送信号的客户端口
		System.out.println("服务器开始运行");
		text.append("服务器开始运行"+"\r\n");
		
	}catch(Exception e)
	{
		System.out.println("请求接受失败");
		text.append("请求接受失败"+"\r\n");
		System.exit(-1);
	
	}
		this.client = client;
	}
	
	public void setframe()//创建界面
	{
		JFrame ui = new JFrame();
		ui.setTitle("井字棋对战(服务端)");
		//关闭方式（其实我也不知道为什么是这样的）
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
		
		
		//（x位置，y位置，长，高），根据像素确定位置，坐标原点左上角
		ui.setBounds(400,400,550,400);
		ui.setVisible(true);
		
		
	}
	public void play() throws IOException//开始下棋
	{
		Socket client = null;
		
	}
	public void set_stream() throws IOException
	{
		client_cin = new BufferedReader(new InputStreamReader(client.getInputStream()));//用于接收客户端信息
		client_cout = new PrintWriter(client.getOutputStream());//用于输出客户端信息
		server_cin = new BufferedReader(new InputStreamReader(System.in));//用于接收键盘输入信息
	}
	
	
	public static void main(String[] args) throws IOException
	{
		server game_server = new server();//创建一个服务器
		game_server.setframe();//创建好界面
		game_server.set_server_client(game_server.client);//配置好服务器
		game_server.set_stream();//配置好输入输出流
		game_server.startplaying.run();//跑线程
		
	}
	}

