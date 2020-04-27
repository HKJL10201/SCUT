package Client;

import javax.swing.*;
import java.io.*;
import java.net.*;
import java.awt.*;
import java.awt.event.*;

public class client extends JFrame{
	
	//功能组件
	private boolean isBlackPlay=true;//是否是黑棋先手  
    boolean gameover=false;  
    private int blackChess=0,whiteChess=0;  
    //private int[][] data=new int[4][4];  
    
    Socket server = null;//服务器
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
    			interrupt_judge=1;
            }
            else
            {
            	isBlackPlay=true; 
    			interrupt_judge=0;
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

  //输入输出流
  	BufferedReader server_cin;//读取服务端传来的数据
  	PrintWriter server_cout;//输出服务端传来的数据
  	BufferedReader client_cin;//读取键盘数据
    
	public void	set_stream() throws IOException
	{
		server_cin = new BufferedReader(new InputStreamReader(server.getInputStream()));//用于接收服务端信息
		server_cout = new PrintWriter(server.getOutputStream());//用于输出服务端信息
		client_cin = new BufferedReader(new InputStreamReader(System.in));//用于接收键盘输入信息
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
	
	public client() throws IOException
	{
		//text.append("client()，297"+"\r\n");
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
			
			//String ready_signal = null;
			
			text.append("游戏开始。你先落子。"+"\r\n");
			
			
			String save = "0000000000000000";//储存服务器传过来的数组信息
			String input = "0000000000000000";//储存自己的数组信息，用来发送给服务器
			
			while(save != null)
			{
				//把服务器信息输入到数组中
				for(int i = 0;i<16;i++)
				{
					count[i] = Integer.parseInt(save.substring(i, i+1)) ;//字符串中的字符逐个转换为数字，填进count里面
				}
				CountSetColour();//恢复棋盘
				
				
				
				while(interrupt_judge==0)
				{
					flag=1;
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
				
				try {
					
					server = new Socket("127.0.0.1",12349);
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
					isBlackPlay=true;
					
				
					
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
	
    public static void main(String[] args) throws IOException
    {
    	client game_client = new client();
    	game_client.setframe();
    	game_client.setTitle("黑白棋对战(客户端)");
    	game_client.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);  
    	game_client.setBounds(970,300,570,400);  
    	game_client.setVisible(true);  
		
    	game_client.set_server();
    	game_client.set_stream();
    	game_client.startplaying.run();
    }
}
