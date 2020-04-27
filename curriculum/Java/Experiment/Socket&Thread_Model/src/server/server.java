package server;
import javax.swing.*;
import java.io.*;
import java.net.*;
import java.awt.*;
import java.awt.event.*;

public class server extends JFrame{
	
	//�������
	JButton[] button = new JButton[9];
	JButton start =new JButton();
	JButton quit=new JButton();
	JTextArea text = new JTextArea();
	
	//�������
	ServerSocket server = null;//������
	int[] count = new int[9];//ͳ�ƾ�����״̬
	chess startplaying;
	Socket client = null;//�ͻ���
	
	
	buttonlistener[] listener = new buttonlistener[9];
	quitlistener qtlistener = new quitlistener();
	startlistener stlistener = new startlistener();
	
	static int interrupt_judge = 0;//�ж��Ƿ�����
	boolean ready=false;//�ж�����Ƿ� ׼����
	

	//�ڲ���
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
		public int i = 0;//Ĭ��δ����
		public void actionPerformed(ActionEvent e)
		{
			i = 2;
			
			for(int j = 0;j<9;j++)
			{
				button[j].setEnabled(false);//��������
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
			System.out.println("�رշ�����ʧ�ܣ����֪����ʲôԭ��");
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
	class chess extends Thread//Ū���߳�ר�Ź�����
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
			text.append("�ȴ��������......"+"\r\n");
			String save = null;//����ͻ��˴�������������Ϣ
			String input = null;//�����Լ���������Ϣ���������͸��ͻ���
			
			//client_cin.readline()���մӿͻ��˴�������Ϣ
			//client_cout.print(input)���͸��ͻ�����Ϣ
			try {
				client = server.accept();
				text.append("��������ӡ�"+"\r\n");
				
				text.append("�����ĵȴ���Ϸ��ʼ......"+"\r\n");
				
				text.append("��Ϸ��ʼ���ɶԷ������ӡ�"+"\r\n");
				save = client_cin.readLine();//��ȡ�ͻ��˵���Ϣ
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			
			
			
			//text.append("�ж���û������"+"\r\n");
			
			
			for(int countnum = 0;save != null && !save.trim().equals("quit") && countnum<5;countnum++)
			{
				text.append("�ֵ�������"+"\r\n");
			//�ѿͻ�����Ϣ���뵽������
			for(int i = 0;i<9;i++)
			{
				count[i] = Integer.parseInt(save.substring(i, i+1)) ;//�ַ����е��ַ����ת��Ϊ���֣����count����
				button[i].setEnabled(false);//�رհ�ť
				
			if(count[i]==1) 
				{
				button[i].setText("O");
			
				}
			else if(count[i]==2) 
				{
				button[i].setText("X");
				}
			
			}
			
			//�ж��Ƿ��Ѿ�����ʤ��
			//û����ʤ��judge==0
			if(jud.judge()==0) 
			{
				if(countnum==5){
					text.append("ƽ��");
					client_cout.println("7");
					input = "ƽ��";
					break;
				}
				//����������Ϣ�������Բ����İ�ť
				for(int i =0;i<9;i++)
				{
					if(count[i]==0)
						button[i].setEnabled(true);
				}
				while(interrupt_judge == 0)
				{
					//text.append("�ж���û�н����ж�ѭ��"+"\r\n");
					try {
						sleep(500);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					if(interrupt_judge ==1) {
						text.append("��������"+"\r\n");
						break;
				}
				}
			}
			else{
				if(jud.judge()==2) 
					{
					text.append("���ѻ�ʤ��");
					input = "�����ˣ�";
					break;
					}
				else{
					text.append("�����ˣ�");
					input = "���ѻ�ʤ��";
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
				//ǿ�н���
				//while(temp.equals("1")){
					
				
				//try {
					try {
						client = server.accept();
					} catch (IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					} 
					//text.append("����������"+"\r\n");
					
					//try {
					//	sleep(2000);
					//} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						//e.printStackTrace();
					//}
					
					//client_cout.println("1");//ȷ�Ͻ���״̬
					//text.append("�ѷ�������ȷ����Ϣ"+"\r\n");
					
					//temp ="0";
					/*
					temp = client_cin.readLine();
					text.append("���յ��ͻ��˶�ȷ����Ϣ����ϢΪ��"+temp+"\r\n");
					*/
				//} catch (IOException e1) {
					// TODO Auto-generated catch block
				//	e1.printStackTrace();
				//}
				
				client_cout.println(input);
				//text.append("������ѷ�����Ϣ����Ϣ��"+input+"\r\n");
				
				client_cout.flush();
				try{
				save = client_cin.readLine();
				//text.append("������ѽ�����Ϣ����Ϣ��"+save+"\r\n");
				}catch(IOException e)
				{
					System.out.println("server��save��ȡ����");
				}
				interrupt_judge =0;//�����жϹ���
			}
			else
			{
				if(jud.judge()==2) 
				{
					text.append("���ѻ�ʤ��");
					input = "�����ˣ�";
					client_cout.println("8");
					for(int i =0;i<9;i++)
						button[i].setEnabled(false);
					break;
				}
				else{
					text.append("�����ˣ�");
					input = "���ѻ�ʤ��";
					client_cout.println("9");
					for(int i =0;i<9;i++)
						button[i].setEnabled(false);
					break;
				}
			}
			}	
			if(input.equals("ƽ��")||input.equals("���ѻ�ʤ��")||input.equals("�����ˣ�"))
			{
				client_cout.print(input);
			}
			//����ִ����֮��,�ر����ж���
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
	
	
	//���������
	BufferedReader client_cin;//��ȡ�ͻ��˴���������
	PrintWriter client_cout;//����ͻ��˴���������
	BufferedReader server_cin;//��ȡ��������
	
	//��������
	public server() throws IOException//����������
	{
		this.startplaying = new chess();
	}	
		//�������startplaying�ĳ�ʼ��ʹ��������accept();
		
	public void set_server_client(Socket client)
	{
	try{
			server = new ServerSocket(12349);
			text.append("�˿�����ɹ�"+"\r\n");
			
		}catch(Exception e)                                   //�쳣��Ϣ�����ûɶ�ÿ���
		{
			System.out.println("Error:"+e);
			System.out.println("����������ʧ��");
			text.append("����������ʧ��"+"\r\n");
			System.exit(-1);
			
		}
	try
	{
		client = server.accept(); 		//�½��Ŀͻ��˿ڣ�ָ��������������źŵĿͻ��˿�
		System.out.println("��������ʼ����");
		text.append("��������ʼ����"+"\r\n");
		
	}catch(Exception e)
	{
		System.out.println("�������ʧ��");
		text.append("�������ʧ��"+"\r\n");
		System.exit(-1);
	
	}
		this.client = client;
	}
	
	public void setframe()//��������
	{
		JFrame ui = new JFrame();
		ui.setTitle("�������ս(�����)");
		//�رշ�ʽ����ʵ��Ҳ��֪��Ϊʲô�������ģ�
		ui.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		JPanel centerpanel = new JPanel();
		ui.getContentPane().add(centerpanel, BorderLayout.CENTER);//����Ĭ�ϲ���
		quit.addActionListener(qtlistener);
		start.addActionListener(stlistener);
		
		//����BOX����
		Box[] box_vert = new Box[3];
		Box box = Box.createHorizontalBox();
		for(int i =0;i<3;i++ )
		{
			box_vert[i] = Box.createVerticalBox();
			for(int j =0;j<3;j++ )
			{
				button[j+3*i] = new JButton(" ");
				listener[j+3*i] = new buttonlistener();
				
				//������ע�ᵽ��ť��
				button[j+3*i].addActionListener(listener[j+3*i]);
				
				//panel.add(button[j]);
				
				//��Ӱ�ť
				box_vert[i].add(button[j+3*i]);
				//���ô�ֱ���
				box_vert[i].add(Box.createVerticalStrut(20));
				
			}
			box.add(box_vert[i]);
			box.add(Box.createHorizontalStrut(20));
		}
		centerpanel.add(box);
		
		JPanel southpanel = new JPanel();
		ui.getContentPane().add(southpanel,BorderLayout.SOUTH);
		
		JPanel toppanel = new JPanel();
		JLabel label = new JLabel("�������ս");
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
		
		
		
		start = new JButton("��ʼ��Ϸ");
		quit = new JButton("�˳���Ϸ");
		Box box_south = Box.createHorizontalBox();
		box_south.add(start);
		box_south.add(Box.createHorizontalStrut(10));
		box_south.add(quit);
		
		southpanel.add(box_south);
		
		
		//��xλ�ã�yλ�ã������ߣ�����������ȷ��λ�ã�����ԭ�����Ͻ�
		ui.setBounds(400,400,550,400);
		ui.setVisible(true);
		
		
	}
	public void play() throws IOException//��ʼ����
	{
		Socket client = null;
		
	}
	public void set_stream() throws IOException
	{
		client_cin = new BufferedReader(new InputStreamReader(client.getInputStream()));//���ڽ��տͻ�����Ϣ
		client_cout = new PrintWriter(client.getOutputStream());//��������ͻ�����Ϣ
		server_cin = new BufferedReader(new InputStreamReader(System.in));//���ڽ��ռ���������Ϣ
	}
	
	
	public static void main(String[] args) throws IOException
	{
		server game_server = new server();//����һ��������
		game_server.setframe();//�����ý���
		game_server.set_server_client(game_server.client);//���ú÷�����
		game_server.set_stream();//���ú����������
		game_server.startplaying.run();//���߳�
		
	}
	}

