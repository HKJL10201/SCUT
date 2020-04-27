package client;
import javax.swing.*;
import java.io.*;
import java.net.*;
import java.awt.*;
import java.awt.event.*;

public class client {

	//�������
	JButton[] button = new JButton[9];
	JButton start=new JButton();
	JButton quit=new JButton();
	JTextArea text = new JTextArea();
	
	//�������
	Socket server = null;//������
	int[] count = new int[9];//ͳ�ƾ�����״̬
	chess startplaying;
	
	
	
	buttonlistener[] listener = new buttonlistener[9];
	quitlistener qtlistener = new quitlistener();
	startlistener stlistener = new startlistener();
	
	static int interrupt_judge=0;//�����ж�
	boolean ready = false;//�ж�����Ƿ� ׼����
	
	
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
		public int i = 0;//Ĭ��δ����
		public void actionPerformed(ActionEvent e)
		{
			i = 1;
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
			start.setEnabled(false);
		}
	}
	
	class chess extends Thread//Ū���߳�ר�Ź�����
	{
		
		
		count_chess jud = new count_chess();
		public chess() throws IOException
		{
			//text.append("���ٽ���chess()�˰ɣ�143");
			
			
			//start();
		}
		public void run()
		{
			for(int i =0;i<9;i++)
				button[i].setEnabled(false);
			
			text.append("���뷿�䡣"+"\r\n");
			
			
			try {
				server = new Socket("127.0.0.1",12349);
			} catch (UnknownHostException e3) {
				// TODO Auto-generated catch block
				e3.printStackTrace();
			} catch (IOException e3) {
				// TODO Auto-generated catch block
				e3.printStackTrace();
			}
			
			
			
			text.append("�����ĵȴ���Ϸ��ʼ......"+"\r\n");
			
			
			String ready_signal = null;
			
		
			
			
			text.append("��Ϸ��ʼ���������ӡ�"+"\r\n");
			
			
			String save = "000000000";//����ͻ��˴�������������Ϣ
			String input = "000000000";//�����Լ���������Ϣ���������͸��ͻ���
			
			//client_cin.readline()���մӿͻ��˴�������Ϣ
			//client_cout.print(input)���͸��ͻ�����Ϣ
			/*
			try{
			save = server_cin.readLine();//��ȡ�ͻ��˵���Ϣ
			}
			catch(IOException e)
			{
				System.out.println("client��save��ȡ����");
			}
			*/
			while(save != null && !save.trim().equals("quit"))
			{
			//�ѿͻ�����Ϣ���뵽������
			for(int i = 0;i<9;i++)
			{
				count[i] = Integer.parseInt(save.substring(i, i+1)) ;//�ַ����е��ַ����ת��Ϊ���֣����count����
				if(count[i]==0)
					button[i].setEnabled(true);
				if(count[i]==1) button[i].setText("O");
				else if(count[i]==2) button[i].setText("X");
			}
			input = "";
			//if(interrupt_judge == 0) text.append("���������ж�ѭ��"+"\r\n");
			while(interrupt_judge==0)
			{
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
			//text.append("�ͻ����ѷ�����Ϣ����Ϣ��"+input+"\r\n");
			server_cout.flush();
			
			//String temp = "0";
			
			//ǿ�з�������
			//while(temp.equals("0")){
				//text.append("�ͻ����ѽ��������ж�ѭ��"+"\r\n");
				
				
				//try {
				//	sleep(3000);
				//} catch (InterruptedException e) {
					// TODO Auto-generated catch block
				//	e.printStackTrace();
				//}
				
				
				
			try {
				
				server = new Socket("127.0.0.1",12349);
				//text.append("�ͻ��������½�������"+"\r\n");
				
				//temp = server_cin.readLine();
				
				//text.append("���յ������ȷ����Ϣ����ϢΪ��"+temp+"\r\n");
				/*
				server_cout.println(temp);
				text.append("�������˷���ȷ����Ϣ"+"\r\n");
				
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
			//text.append("�ͻ����ѽ��յ���Ϣ����ϢΪ��"+save+"\r\n");
			
			}catch(IOException e)
			{
				System.out.println("client��save��ȡ����");
			}
			interrupt_judge = 0;
			/*
			if(save.equals("ƽ��")||save.equals("���ѻ�ʤ��")||save.equals("�����ˣ�"))
			{
				text.append(save);
				for(int i =0;i<9;i++)
					button[i].setEnabled(false);
				break;
				
			}*/
			text.append("�ж�");
			if(save.substring(0,1)=="7")
			{
				text.append("ƽ��");
				for(int i =0;i<9;i++)
					button[i].setEnabled(false);
				break;
			}
			else if(save.substring(0,1)=="9")
			{
				text.append("���ѻ�ʤ��");
				for(int i =0;i<9;i++)
					button[i].setEnabled(false);
				break;
			}
			else if(save.substring(0,1)=="8")
			{
				text.append("�����ˣ�");
				for(int i =0;i<9;i++)
					button[i].setEnabled(false);
				break;
			}
		}
			
			
			
			
			//����ִ����֮��,�ر����ж���
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
	
	
	
	
	//���������
	BufferedReader server_cin;//��ȡ����˴���������
	PrintWriter server_cout;//�������˴���������
	BufferedReader client_cin;//��ȡ��������
	
	//��������
	public void setframe()//��������
	{
		JFrame ui = new JFrame();
		ui.setTitle("�������ս(�ͻ���)");
		//�رշ�ʽ
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
		
		
		
		//��xλ�ã�yλ�ã�����������������ȷ��λ�ã�����ԭ�����Ͻ�
		ui.setBounds(400,400,550,400);
		ui.setVisible(true);
		
	}
	public client() throws IOException
	{
		//text.append("client()��297"+"\r\n");
		this.startplaying = new chess();
	}
	public void	set_stream() throws IOException
	{
		server_cin = new BufferedReader(new InputStreamReader(server.getInputStream()));//���ڽ��շ������Ϣ
		server_cout = new PrintWriter(server.getOutputStream());//��������������Ϣ
		client_cin = new BufferedReader(new InputStreamReader(System.in));//���ڽ��ռ���������Ϣ
	}
	public void set_server()
	{
		try
		{
			server = new Socket("127.0.0.1",12349);
			//text.append("������ָ��ɹ���145"+"\r\n");
			
		}catch(Exception e)
		{
			System.out.println("�������ʧ��");
			//text.append("������ָ��ʧ�ܣ�150"+"\r\n");
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
