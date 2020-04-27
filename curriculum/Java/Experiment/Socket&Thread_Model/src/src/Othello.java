package src;
import java.awt.*;  
import java.awt.event.ActionEvent;  
import java.awt.event.ActionListener;
import java.util.*;  
import javax.swing.*;  
  
  
/** 
 * @author Lenovo 
 * 构造方法  实现界面 为按钮添加事件监听器 
 */  
public class Othello extends JFrame{  
      
    private boolean isBlackPlay=true;//是否是黑棋先手  
    boolean gameover=false;  
    private int blackChess=0,whiteChess=0;  
    private int[][] data=new int[4][4];  
      
    private JPanel p1=new JPanel();  
    private JButton renewB=new JButton("重新开始");
    private JButton exitB=new JButton("退出");  
      
    private JPanel p2=new JPanel();  
    private JButton button[][]=new JButton[4][4];  
    
      
    public Othello(){  
        Container c=this.getContentPane();  
        
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
      
    /** 
     * @author Lenovo 
     * 实现重新开始按钮功能 初始化界面参数 
     */  
    class renewHandler implements ActionListener
{  
  
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
                isBlackPlay=false;  
            else isBlackPlay=true;  
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
                JOptionPane.showMessageDialog(null, "恭喜黑方获胜！");  
            else if(blackChess<whiteChess)  
                JOptionPane.showMessageDialog(null, "恭喜白方获胜！");  
            else   
                JOptionPane.showMessageDialog(null, "平局了！");  
        }  
          
        @Override  
        public void actionPerformed(ActionEvent e) {  
            // TODO Auto-generated method stub  
            if(gameover==true){  
                JOptionPane.showMessageDialog(null, "棋局已经结束 请重新开始");  
                return;  
            }else{  
                if(!isValidPosition(row, col)){  
                    //JOptionPane.showMessageDialog(null, "非法位置 请重新放置");  
                    return;  
                }else{  
                    refresh(row, col);  
                    changePlayer();  
                    if(!hasValidPosition()){  
                        changePlayer();  
                        {  
                            if(!hasValidPosition()){  
                                gameover=true;  
                                whoWin();  
                            }else{  
                                JOptionPane.showMessageDialog(null, "对方已无处可下 己方继续");  
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
      
      
    public static void main(String[] args){  
        Othello othello=new Othello();  
        othello.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);  
        othello.setSize(350,400);  
        othello.setVisible(true);  
    }  
      
}  