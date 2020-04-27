package pers.lee.acms.services;

import java.sql.*;

public class DbUtil {
    /**
     * 取得数据库的连接
     * @return 一个数据库的连接
     */
    public static Connection getConnection(){
        Connection conn = null;
        try {
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/rjgc3328","rjgc","rjgc123");
        }catch (SQLException e) {
            e.printStackTrace();
        }
        return conn;
    }

    /**
     * 封装三个关闭方法
     * @param pstmt
     */
    public static void close(PreparedStatement pstmt){
        if(pstmt != null){						//避免出现空指针异常
            try{
                pstmt.close();
            }catch(SQLException e){
                e.printStackTrace();
            }
        }
    }

    public static void close(Connection conn){
        if(conn != null){
            try {
                conn.close();
            } catch (SQLException e) {
                // TODO: handle exception
                e.printStackTrace();
            }
        }
    }

    public static void close(ResultSet rs){
        if (rs != null) {
            try {
                rs.close();
            } catch (SQLException e) {
                // TODO: handle exception
                e.printStackTrace();
            }
        }
    }

}
