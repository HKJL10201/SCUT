package pers.lee.acms.services;

import pers.lee.acms.models.User;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class UserDbServices {

    public static List<User> findUser(String username) {
        String sql = "select * from users where Username = ?";
        Connection conn=null;
        PreparedStatement pstmt=null;
        ResultSet rs=null;
        //创建一个集合对象用来存放查询到的数据
        List<User> userList = new ArrayList<>() ;
        try {
            conn = DbUtil.getConnection();
            pstmt = (PreparedStatement) conn.prepareStatement(sql);
            pstmt.setString(1, username); //给占位符赋值
            rs = (ResultSet) pstmt.executeQuery();
            while (rs.next()) {
                String Uname = rs.getString("Username");
                String Pword = rs.getString("Password");
                //每个记录对应一个对象
                User user=new User(Uname,Pword);
                //将对象放到集合中
                userList.add(user);
            }
        }catch (SQLException e) {
            // TODO: handle exception
            e.printStackTrace();
        }finally{
            DbUtil.close(pstmt);
            DbUtil.close(conn);		//必须关闭
        }
        return userList;
    }

    /**
     * 添加用户
     * @param username 用户名
     * @param password 密码
     */
    public static void addUser(String username,String password){
        String sql = "insert into users(Username,Password) values(?,?)";
        //该语句为每个 IN 参数保留一个问号("?")作为占位符
        Connection conn = null;				//和数据库取得连接
        PreparedStatement pstmt = null;		//创建statement
        try{
            conn = DbUtil.getConnection();
            pstmt = (PreparedStatement) conn.prepareStatement(sql);
            pstmt.setString(1, username); //给占位符赋值
            pstmt.setString(2, password); //给占位符赋值
            pstmt.executeUpdate();			//执行
        }catch(SQLException e){
            e.printStackTrace();
        }
        finally{
            DbUtil.close(pstmt);
            DbUtil.close(conn);		//必须关闭
        }
    }

    /**
     * 删除用户
     * @param username
     */
    public static void delUser(String username){
        String sql = "delete from users where Username = ?";
        Connection conn = null;
        PreparedStatement pstmt = null;
        try {
            conn = DbUtil.getConnection();
            pstmt = (PreparedStatement) conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            // TODO: handle exception
            e.printStackTrace();
        }finally{
            DbUtil.close(pstmt);
            DbUtil.close(conn);		//必须关闭
        }
    }

    /**
     * 修改用户
     * @param username
     * @param password
     */
    public static void modifyUser(String username,String password){
        String sql = "update users set Password =? where Username=?";
        Connection conn = null;
        PreparedStatement pstmt = null;
        try {
            conn = DbUtil.getConnection();
            pstmt = (PreparedStatement) conn.prepareStatement(sql);
            pstmt.setString(1, password);  //利用Preparedstatement的set方法给占位符赋值
            pstmt.setString(2, username);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            // TODO: handle exception
            e.printStackTrace();
        }finally{
            DbUtil.close(pstmt);
            DbUtil.close(conn);		//必须关闭
        }
    }

}
