package Server;

import javax.swing.*;
import java.io.*;
import java.net.*;
import java.awt.*;
import java.awt.event.*;

public class server extends JFrame{
	
	//功能组件
	private boolean isBlackPlay=false;//是否是黑棋先手  
    boolean gameover=false;  
    private int blackChess=0,whiteChess=0;  
    //private int[][] data=new int[4][4];  
    
    ServerSocket server = null;//服务器
    Socket client = null;//客户端
    int[] count = new int[16];//统计棋状态
    static int interrupt_judge=0;//落子判断
    
    Othello startplaying;

    int flag=0;
    
	//界面组件
	private JPanel p1=new JPanel();  
    private JButton renewB=new JButton("重新开始");
    private JButton exitB=new JButton("退出");  
      
    private JPanel p2=new JPanel();  
    private JButton button[][]=new JButton[4][4];  
    
    private JTextArea text = new JTextArea();
    private JScrollPane textscroll = new JScrollPane();
    private JPanel eastpanel = new JPanel();
	
	
	public void setframe()//创建界面
	{
		Container c=this.getContentPane();  

    	
		text.setRows(20);
		text.setColumns(20);
		
		
		textscroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
		textscroll.setViewportView(text);
		
        
		eastpanel.add(text); 
		eastpanel.add(textscroll);
        c.add(eastpanel,BorderLayout.EAST);
        
        c.add(p1, BorderLayout.NORTH);  
        p1.add(renewB);
        p1.add(exitB);  
          
        c.add(p2, BorderLayout.CENTER);  
        p2.setLayout(new GridLayout(4, 4));  
          
        for(int i=0;i<4;i++){  
            for(int j=0;j<4;j++){  
                button[i][j]=new JButton("");  
            }  
        }  
        for(int i=0;i<4;i++){  
            for(int j=0;j<4;j++){  
                p2.add(button[i][j]);  
                button[i][j].setBackground(Color.GRAY);  
                button[i][j].addActionListener(new Handler(i, j));  
            }  
        }  
          
        button[1][1].setBackground(Color.WHITE);  
        button[1][2].setBackground(Color.BLACK);  
        button[2][1].setBackground(Color.BLACK);  
        button[2][2].setBackground(Color.WHITE);  
          
        renewB.addActionListener(new renewHandler());
        exitB.addActionListener(new exitHandler());  
	}
	
    class renewHandler implements ActionListener{  
    	  
        @Override  
        public void actionPerformed(ActionEvent e) {  
            // TODO Auto-generated method stub  
            for(int i=0;i<4;i++){  
                for(int j=0;j<4;j++){  
                    button[i][j].setBackground(Color.GRAY);  
                }  
            }  
            button[1][1].setBackground(Color.WHITE);  
            button[1][2].setBackground(Color.BLACK);  
            button[2][1].setBackground(Color.BLACK);  
            button[2][2].setBackground(Color.WHITE);  
              
            isBlackPlay=true;  
            blackChess=0;  
            whiteChess=0;  
            gameover=false; 
        }  
          
    }  
    
 
    class exitHandler implements ActionListener{  
  
        @Override  
        public void actionPerformed(ActionEvent e) {  
            // TODO Auto-generated method stub  
            System.exit(0);  
        }  
          
    }  
      
    class Handler implements ActionListener{  
          
        int row=-1,col=-1;  
          
        public Handler(int x,int y){  
            row=x;  
            col=y;  
        }  
          
        private boolean isValidPosition(int x,int y){  
            if(button[x][y].getBackground()!=Color.GRAY)  
                return false;  
            if(isBlackPlay==true){//黑方下  
                for(int i=0;i<4;i++){//垂直方向判断  
                    if(button[i][y].getBackground()==Color.BLACK){  
                        if((i-x)>=2){  
                            int count=0;  
                            for(int k=x;k<i;k++){  
                                if(button[k][y].getBackground()==Color.white){  
                                    count++;  
                                }  
                            }  
                            if(count==(i-x-1)){//如果两个黑子之间夹得都是白子  
                                return true;  
                            }  
                        }  
                        if((x-i)>=2){  
                            int count=0;  
                            for(int k=x;k>i;k--){  
                                if(button[k][y].getBackground()==Color.WHITE){  
                                    count++;  
                                }  
                            }  
                            if(count==(x-i-1))  
                                return true;  
                        }  
                    }  
                }  
                //水平方向判断  
                for(int j=0;j<4;j++){  
                    if(button[x][j].getBackground()==Color.BLACK){  
                        if((j-y)>=2){  
                            int count=0;  
                            for(int k=y;k<j;k++){  
                                if(button[x][k].getBackground()==Color.WHITE)  
                                    count++;  
                            }  
                            if(count==(j-y-1))  
                                return true;  
                        }  
                        if((y-j)>=2){  
                            int count=0;  
                            for(int k=y;k>j;k--){  
                                if(button[x][k].getBackground()==Color.white)  
                                    count++;  
                            }  
                            if(count==(y-j-1))  
                                return true;  
                        }  
                    }  
                }  
                //斜线方向上判断  
                for(int i=0;i<4;i++){  
                     for(int j=0;j<4;j++){  
                         if(button[i][j].getBackground()==Color.BLACK){  
                             if((x-i)==(y-j)&&(x-i)>=2){  
                                 int yy=y;  
                                 int count=0;  
                                 for(int k=x;k>i;k--){  
                                     if(button[k][yy].getBackground()==Color.WHITE)  
                                         count++;  
                                     yy--;  
                                 }  
                                 if(count==(x-i-1))  
                                     return true;  
                             }  
                             if((x-i)==(j-y)&&(x-i)>=2){  
                                 int yy=y;  
                                 int count=0;  
                                 for(int k=x;k>i;k--){  
                                     if(button[k][yy].getBackground()==Color.WHITE){  
                                         count++;  
                                     }  
                                     yy++;  
                                 }  
                                 if(count==(x-i-1))  
                                     return true;  
                             }  
                             if((i-x)==(y-j)&&(i-x)>=2){  
                                 int yy=y;  
                                 int count=0;  
                                 for(int k=x;k<i;k++){  
                                     if(button[k][yy].getBackground()==Color.WHITE)  
                                         count++;  
                                     yy--;  
                                 }  
                                 if(count==(i-x-1))  
                                     return true;  
                             }  
                             if((i-x)==(j-y)&&(i-x)>=2){  
                                 int yy=y;  
                                 int count=0;  
                                 for(int k=x;k<i;k++){  
                                     if(button[k][yy].getBackground()==Color.WHITE)  
                                         count++;  
                                     yy++;  
                                 }  
                                 if(count==(i-x-1))  
                                     return true;  
                             }  
                         }  
                     }  
                }  
                return false;  
            }  
            else{  
                for (int i = 0; i < 4; i++)  
                {  
                    if (button[i][y].getBackground() == Color.WHITE)  
                    {  
                        if ((i - x) >= 2)  
                        {  
                            int count = 0;  
                            for (int k = x; k < i; k++)  
                            {  
                                if (button[k][y].getBackground() == Color.BLACK)  
                                    count++;  
                            }  
                            if (count == (i - x - 1))  
                                return true;  
                        }  
                        if ((x - i) >= 2)  
                        {  
                            int count = 0;  
                            for (int k = x; k > i; k--)  
                            {  
                                if (button[k][y].getBackground() == Color.BLACK)  
                                    count++;  
                            }  
                            if (count == (x - i - 1))  
                                return true;  
                        }  
                    }  
                }  
  
                for (int j = 0; j < 4; j++)  
                {  
                    if (button[x][j].getBackground() == Color.WHITE)  
                    {  
                        if ((j - y) >= 2)  
                        {  
                            int count = 0;  
                            for (int k = y; k < j; k++)  
                            {  
                                if (button[x][k].getBackground() == Color.BLACK)  
                                    count++;  
                            }  
                            if (count == (j - y - 1))  
                                return true;  
                        }  
  
                        if ((y - j) >= 2)  
                        {  
                            int count = 0;  
                            for (int k = y; k > j; k--)  
                            {  
                                if (button[x][k].getBackground() == Color.BLACK)  
                                    count++;  
                            }  
                            if (count == (y - j - 1))  
                                return true;  
                        }  
  
                    }  
                }  
  
                for (int i = 0; i < 4; i++)  
                {  
                    for (int j = 0; j < 4; j++)  
                    {  
                        if (button[i][j].getBackground() == Color.WHITE)  
                        {  
                            if ((x - i) == (y - j) && (x - i) >= 2)  
                            {  
                                int yy = y;  
                                int count = 0;  
                                for (int k = x; k > i; k--)  
                                {  
                                    if (button[k][yy].getBackground() == Color.BLACK)  
                                    {  
                                        count++;  
                                    }  
                                    yy--;  
  
                                }  
                                if (count == (x - i - 1))  
                                    return true;  
                            }  
  
                            if ((x - i) == (j - y) && (x - i) >= 2)  
                            {  
                                int yy = y;  
                                int count = 0;  
                                for (int k = x; k > i; k--)  
                                {  
                                    if (button[k][yy].getBackground() == Color.BLACK)  
                                    {  
                                        count++;  
                                    }  
                                    yy++;  
  
                                }  
                                if (count == (x - i - 1))  
                                    return true;  
                            }  
  
                            if ((i - x) == (y - j) && (i - x) >= 2)  
                            {  
                                int yy = y;  
                                int count = 0;  
                                for (int k = x; k < i; k++)  
                                {  
                                    if (button[k][yy].getBackground() == Color.BLACK)  
                                    {  
                                        count++;  
                                    }  
                                    yy--;  
                                }  
                                if (count == (i - x - 1))  
                                    return true;  
                            }  
  
                            if ((i - x) == (j - y) && (i - x) >= 2)  
                            {  
                                int yy = y;  
                                int count = 0;  
                                for (int k = x; k < i; k++)  
                                {  
                                    if (button[k][yy].getBackground() == Color.BLACK)  
                                    {  
                                        count++;  
                                    }  
                                    yy++;  
                                }  
                                if (count == (i - x - 1))  
                                    return true;  
                            }  
  
                        }  
                    }  
                }  
  
                return false;  
            }  
        }  
          
          
        private void refresh(int x, int y)  
        {  
            if (isBlackPlay == true)// 若是黑方下  
            {  
                for (int i = 0; i < 4; i++)  
                {  
                    if (button[i][y].getBackground() == Color.BLACK)  
                    {  
                        if ((i - x) >= 2)  
                        {  
                            int count = 0;  
                            for (int k = x; k < i; k++)  
                            {  
                                if (button[k][y].getBackground() == Color.WHITE)  
                                    count++;  
                            }  
  
                            if (count == (i - x - 1))  
                            {  
                                for (int k = x; k < i; k++)  
                                    button[k][y].setBackground(Color.BLACK);  
                            }  
  
                        }  
  
                        if ((x - i) >= 2)  
                        {  
                            int count = 0;// /////////////////////////  
                            for (int k = x; k > i; k--)  
                            {  
                                if (button[k][y].getBackground() == Color.WHITE)  
                                    count++;  
                            }  
  
                            if (count == (x - i - 1))  
                            {  
                                for (int k = x; k > i; k--)  
                                    button[k][y].setBackground(Color.BLACK);  
                            }  
                        }  
                    }  
                }  
  
                for (int j = 0; j < 4; j++)  
                {  
                    if (button[x][j].getBackground() == Color.BLACK)  
                    {  
                        if ((j - y) >= 2)  
                        {  
                            int count = 0;  
                            for (int k = y; k < j; k++)  
                            {  
                                if (button[x][k].getBackground() == Color.WHITE)  
                                    count++;  
                            }  
  
                            if (count == (j - y - 1))  
                            {  
                                for (int k = y; k < j; k++)  
                                    button[x][k].setBackground(Color.BLACK);  
                            }  
                        }  
  
                        if ((y - j) >= 2)  
                        {  
                            int count = 0;  
                            for (int k = y; k > j; k--)  
                            {  
                                if (button[x][k].getBackground() == Color.WHITE)  
                                    count++;  
                            }  
                            if (count == (y - j - 1))  
                            {  
                                for (int k = y; k > j; k--)  
                                    button[x][k].setBackground(Color.BLACK);  
                            }  
                        }  
                    }  
                }  
  
                for (int i = 0; i < 4; i++)  
                {  
                    for (int j = 0; j < 4; j++)  
                    {  
                        if (button[i][j].getBackground() == Color.BLACK)  
                        {  
                            if ((x - i) == (y - j) && (x - i) >= 2)  
                            {  
                                int yy = y;  
                                int count = 0;  
                                for (int k = x; k > i; k--)  
                                {  
                                    if (button[k][yy].getBackground() == Color.WHITE)  
                                    {  
                                        count++;  
                                    }  
                                    yy--;  
  
                                }  
                                if (count == (x - i - 1))  
                                {  
                                    yy = y;  
                                    for (int k = x; k > i; k--)  
                                    {  
                                        button[k][yy].setBackground(Color.BLACK);  
                                        yy--;  
                                    }  
                                }  
                            }  
  
                            if ((x - i) == (j - y) && (x - i) >= 2)  
                            {  
                                int yy = y;  
                                int count = 0;  
                                for (int k = x; k > i; k--)  
                                {  
                                    if (button[k][yy].getBackground() == Color.WHITE)  
                                    {  
                                        count++;  
                                    }  
                                    yy++;  
  
                                }  
                                if (count == (x - i - 1))  
                                {  
                                    yy = y;  
                                    for (int k = x; k > i; k--)  
                                    {  
                                        button[k][yy].setBackground(Color.BLACK);  
                                        yy++;  
                                    }  
                                }  
                            }  
  
                            if ((i - x) == (y - j) && (i - x) >= 2)  
                            {  
                                int yy = y;  
                                int count = 0;  
                                for (int k = x; k < i; k++)  
                                {  
                                    if (button[k][yy].getBackground() == Color.WHITE)  
                                    {  
                                        count++;  
                                    }  
                                    yy--;  
  
                                }  
                                if (count == (i - x - 1))  
                                {  
                                    yy = y;  
                                    for (int k = x; k < i; k++)  
                                    {  
                                        button[k][yy].setBackground(Color.BLACK);  
                                        yy--;  
                                    }  
                                }  
                            }  
  
                            if ((i - x) == (j - y) && (i - x) >= 2)  
                            {  
                                int yy = y;  
                                int count = 0;  
                                for (int k = x; k < i; k++)  
                                {  
                                    if (button[k][yy].getBackground() == Color.WHITE)  
                                    {  
                                        count++;  
                                    }  
                                    yy++;  
  
                                }  
                                if (count == (i - x - 1))  
                                {  
                                    yy = y;  
                                    for (int k = x; k < i; k++)  
                                    {  
                                        button[k][yy].setBackground(Color.BLACK);  
                                        yy++;  
                                    }  
                                }  
                            }  
  
                        }  
                    }  
                }  
  
            }  
            else  
            // 若是白方下  
            {  
                for (int i = 0; i < 4; i++)  
                {  
                    if (button[i][y].getBackground() == Color.WHITE)  
                    {  
                        if ((i - x) >= 2)  
                        {  
                            int count = 0;  
                            for (int k = x; k < i; k++)  
                            {  
                                if (button[k][y].getBackground() == Color.BLACK)  
                                    count++;  
                            }  
  
                            if (count == (i - x - 1))  
                            {  
                                for (int k = x; k < i; k++)  
                                    button[k][y].setBackground(Color.WHITE);  
                            }  
  
                        }  
                        if ((x - i) >= 2)  
                        {  
                            int count = 0;  
                            for (int k = x; k > i; k--)  
                            {  
                                if (button[k][y].getBackground() == Color.BLACK)  
                                    count++;  
                            }  
  
                            if (count == (x - i - 1))  
                            {  
                                for (int k = x; k > i; k--)  
                                    button[k][y].setBackground(Color.WHITE);  
                            }  
                        }  
                    }  
                }  
  
                for (int j = 0; j < 4; j++)  
                {  
                    if (button[x][j].getBackground() == Color.WHITE)  
                    {  
                        if ((j - y) >= 2)  
                        {  
                            int count = 0;  
                            for (int k = y; k < j; k++)  
                            {  
                                if (button[x][k].getBackground() == Color.BLACK)  
                                    count++;  
                            }  
  
                            if (count == (j - y - 1))  
                            {  
                                for (int k = y; k < j; k++)  
                                    button[x][k].setBackground(Color.WHITE);  
                            }  
                        }  
                        if ((y - j) >= 2)  
                        {  
                            int count = 0;  
                            for (int k = y; k > j; k--)  
                            {  
                                if (button[x][k].getBackground() == Color.BLACK)  
                                    count++;  
                            }  
                            if (count == (y - j - 1))  
                            {  
                                for (int k = y; k > j; k--)  
                                    button[x][k].setBackground(Color.WHITE);  
                            }  
                        }  
                    }  
                }  
  
                for (int i = 0; i < 4; i++)  
                {  
                    for (int j = 0; j < 4; j++)  
                    {  
                        if (button[i][j].getBackground() == Color.WHITE)  
                        {  
                            if ((x - i) == (y - j) && (x - i) >= 2)  
                            {  
                                int yy = y;  
                                int count = 0;  
                                for (int k = x; k > i; k--)  
                                {  
                                    if (button[k][yy].getBackground() == Color.BLACK)  
                                    {  
                                        count++;  
                                    }  
                                    yy--;  
                                }  
                                if (count == (x - i - 1))  
                                {  
                                    yy = y;  
                                    for (int k = x; k > i; k--)  
                                    {  
                                        button[k][yy].setBackground(Color.WHITE);  
                                        yy--;  
                                    }  
                                }  
                            }  
  
                            if ((x - i) == (j - y) && (x - i) >= 2)  
                            {  
                                int yy = y;  
                                int count = 0;  
                                for (int k = x; k > i; k--)  
                                {  
                                    if (button[k][yy].getBackground() == Color.BLACK)  
                                    {  
                                        count++;  
                                    }  
                                    yy++;  
  
                                }  
                                if (count == (x - i - 1))  
                                {  
                                    yy = y;  
                                    for (int k = x; k > i; k--)  
                                    {  
                                        button[k][yy].setBackground(Color.WHITE);  
                                        yy++;  
                                    }  
                                }  
                            }  
                            if ((i - x) == (y - j) && (i - x) >= 2)  
                            {  
                                int yy = y;  
                                int count = 0;  
                                for (int k = x; k < i; k++)  
                                {  
                                    if (button[k][yy].getBackground() == Color.BLACK)  
                                    {  
                                        count++;  
                                    }  
                                    yy--;  
  
                                }  
                                if (count == (i - x - 1))  
                                {  
                                    yy = y;  
                                    for (int k = x; k < i; k++)  
                                    {  
                                        button[k][yy].setBackground(Color.WHITE);  
                                        yy--;  
                                    }  
                                }  
                            }  
                            if ((i - x) == (j - y) && (i - x) >= 2)  
                            {  
                                int yy = y;  
                                int count = 0;  
                                for (int k = x; k < i; k++)  
                                {  
                                    if (button[k][yy].getBackground() == Color.BLACK)  
                                    {  
                                        count++;  
                                    }  
                                    yy++;  
  
                                }  
                                if (count == (i - x - 1))  
                                {  
                                    yy = y;  
                                    for (int k = x; k < i; k++)  
                                    {  
                                        button[k][yy].setBackground(Color.WHITE);  
                                        yy++;  
  
                                    }  
                                }  
                            }  
  
                        }  
                    }  
                }  
  
            }  
  
        }  
          
        /** 
         * @return 
         * 判断是否还有位置可下 
         */  
        private boolean hasValidPosition(){  
            for(int i=0;i<4;i++){  
                for(int j=0;j<4;j++){  
                    if(isValidPosition(i, j))  
                        return true;  
                }  
            }  
            return false;  
        }  
          
        public void changePlayer(){  
            if(isBlackPlay==true) 
            { 
                isBlackPlay=false; 
                interrupt_judge=0;
            }
            else 
            {
            	isBlackPlay=true;  
            	interrupt_judge=1;
            }
        }  
          
        private void whoWin(){  
            for(int i=0;i<4;i++){  
                for(int j=0;j<4;j++){  
                    if(button[i][j].getBackground()==Color.BLACK)  
                        blackChess++;  
                    if(button[i][j].getBackground()==Color.WHITE)  
                        whiteChess++;  
                }  
            }  
            if(blackChess>whiteChess)  
            	text.append("恭喜黑方获胜！\n");  
            else if(blackChess<whiteChess)  
            	text.append("恭喜白方获胜！\n");  
            else   
            	text.append("平局了！\n");  
        }  
          
        @Override  
        public void actionPerformed(ActionEvent e) {  
            // TODO Auto-generated method stub  
        	if(flag==0)
        		return;
        	else {
            if(gameover==true){  
            	text.append("棋局已经结束 请重新开始\n");  
                return;  
            }else{  
                if(!isValidPosition(row, col))
                {  
                	//text.append("非法位置 请重新放置\n");  
                    return;  
                }
                else
                {  
                    refresh(row, col);  
                    changePlayer();  
                    if(!hasValidPosition())
                    {  
                        changePlayer();  
                        {  
                            if(!hasValidPosition())
                            {  
                                gameover=true;  
                                whoWin();  
                            }
                            else
                            {  
                            	text.append("对方已无处可下 己方继续\n");  
                                return;  
                            }  
                        }  
                    }  
                    else   
                        return;  
                }  
            }  
        	}  
        } 
    }  
  
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
	
	//输入输出流
		BufferedReader client_cin;//读取客户端传来的数据
		PrintWriter client_cout;//输出客户端传来的数据
		BufferedReader server_cin;//读取键盘数据
	
	public void set_stream() throws IOException
	{
		client_cin = new BufferedReader(new InputStreamReader(client.getInputStream()));//用于接收客户端信息
		client_cout = new PrintWriter(client.getOutputStream());//用于输出客户端信息
		server_cin = new BufferedReader(new InputStreamReader(System.in));//用于接收键盘输入信息
	}
	
	public void setCount()
	{
		for(int i=0;i<4;i++){  
            for(int j=0;j<4;j++){  
                if(button[i][j].getBackground()==Color.BLACK)  
                    count[i*4+j]=1;  
                if(button[i][j].getBackground()==Color.WHITE)  
                	count[i*4+j]=2; 
            }  
        } 
	}
	
	public void CountSetColour()
	{
		for(int i=0;i<4;i++){  
            for(int j=0;j<4;j++){  
                if(count[i*4+j]==1)  
                	button[i][j].setBackground(Color.BLACK);  
                if(count[i*4+j]==2)  
                	button[i][j].setBackground(Color.WHITE); 
            }  
        } 
	}
	
	public server() throws IOException//建立服务器
	{
		this.startplaying = new Othello();
	}	
	
	
	class Othello extends Thread//弄个线程专门管下棋
	{
		public Othello() throws IOException
		{
			//start();
		}

		public void run()
		{
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
				//text.append("服务端已接收信息，信息："+save+"\r\n");
				
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			
			for(int countnum = 0;save != null && countnum<20;countnum++)
			{
				text.append("轮到你落子"+"\r\n");
				
				for(int i = 0;i<16;i++)
				{
					count[i] = Integer.parseInt(save.substring(i, i+1)) ;//字符串中的字符逐个转换为数字，填进count里面
				}
				CountSetColour();//恢复棋盘
				
				
				//if(gameover==false)
				{
					while(interrupt_judge == 0)
					{
						flag=1;
						//text.append("判断有没有进入判断循环"+"\r\n");
						try {
							sleep(500);
						} catch (InterruptedException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
						if(interrupt_judge ==1) {
							text.append("你已落子"+"\r\n");
							flag=0;
							break;
						}
					}
					
					setCount();
					input = "";
					for(int i=0;i<16;i++)
					{
						input+=count[i];
					}
				}
				
				try {
					client = server.accept();
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				
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
				isBlackPlay=false;
				
				
				
				
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
	
	public static void main(String[] args) throws IOException
	{
		server game_server = new server();//创建一个服务器
		game_server.setframe();//创建好界面
		game_server.setTitle("黑白棋对战(服务器)");
		game_server.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);  
		game_server.setBounds(400,300,570,400);  
		game_server.setVisible(true);  
		
		game_server.set_server_client(game_server.client);//配置好服务器
		game_server.set_stream();//配置好输入输出流
		game_server.startplaying.run();//跑线程
		
	}
}
