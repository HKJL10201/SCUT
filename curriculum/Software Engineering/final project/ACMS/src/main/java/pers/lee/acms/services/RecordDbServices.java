package pers.lee.acms.services;

import pers.lee.acms.models.Record;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class RecordDbServices {

    public static List<Record> findRecordByAcid(String acid){
        String sql = "select * from record where ACID = ? order by  Date desc";
        Connection conn = null;
        PreparedStatement pstmt=null;
        ResultSet rs=null;
        //创建一个集合对象用来存放查询到的数据
        List<Record> recList = new ArrayList<>() ;
        try {
            conn = DbUtil.getConnection();
            pstmt = (PreparedStatement) conn.prepareStatement(sql);
            pstmt.setString(1, acid); //给占位符赋值
            rs = (ResultSet) pstmt.executeQuery();
            while (rs.next()) {
                String Acid = rs.getString("ACID");
                String Wker = rs.getString("Worker");
                String Date = rs.getString("Date");
                String Dtil = rs.getString("detail");
                //每个记录对应一个对象
                Record record=new Record(Acid,Wker,Date,Dtil);
                //将对象放到集合中
                recList.add(record);
            }
        }catch (SQLException e) {
            // TODO: handle exception
            e.printStackTrace();
        }finally{
            DbUtil.close(pstmt);
            DbUtil.close(conn);		//必须关闭
        }
        return recList;
    }

    public static List<Record> findRecordByWorker(String worker){
        String sql = "select * from record where Worker = ? order by  Date desc";
        Connection conn = null;
        PreparedStatement pstmt=null;
        ResultSet rs=null;
        //创建一个集合对象用来存放查询到的数据
        List<Record> recList = new ArrayList<>() ;
        try {
            conn = DbUtil.getConnection();
            pstmt = (PreparedStatement) conn.prepareStatement(sql);
            pstmt.setString(1, worker); //给占位符赋值
            rs = (ResultSet) pstmt.executeQuery();
            while (rs.next()) {
                String Acid = rs.getString("ACID");
                String Wker = rs.getString("Worker");
                String Date = rs.getString("Date");
                String Dtil = rs.getString("detail");
                //每个记录对应一个对象
                Record record=new Record(Acid,Wker,Date,Dtil);
                //将对象放到集合中
                recList.add(record);
            }
        }catch (SQLException e) {
            // TODO: handle exception
            e.printStackTrace();
        }finally{
            DbUtil.close(pstmt);
            DbUtil.close(conn);		//必须关闭
        }
        return recList;
    }

    public static List<Record> findRecordByDate(String date){
        String sql = "select * from record where Date = ?";
        Connection conn = null;
        PreparedStatement pstmt=null;
        ResultSet rs=null;
        //创建一个集合对象用来存放查询到的数据
        List<Record> recList = new ArrayList<>() ;
        try {
            conn = DbUtil.getConnection();
            pstmt = (PreparedStatement) conn.prepareStatement(sql);
            pstmt.setString(1, date); //给占位符赋值
            rs = (ResultSet) pstmt.executeQuery();
            while (rs.next()) {
                String Acid = rs.getString("ACID");
                String Wker = rs.getString("Worker");
                String Date = rs.getString("Date");
                String Dtil = rs.getString("detail");
                //每个记录对应一个对象
                Record record=new Record(Acid,Wker,Date,Dtil);
                //将对象放到集合中
                recList.add(record);
            }
        }catch (SQLException e) {
            // TODO: handle exception
            e.printStackTrace();
        }finally{
            DbUtil.close(pstmt);
            DbUtil.close(conn);		//必须关闭
        }
        return recList;
    }

    /**
     * 添加记录
     * @param acid 空调编号
     * @param worker 工人用户名
     * @param date 创建日期
     * @param detail 详细信息
     */
    public static void addRec(String acid,String worker,String date,String detail){
        String sql = "insert into record(ACID,Worker,Date,detail) values(?,?,?,?)";
        //该语句为每个 IN 参数保留一个问号("?")作为占位符
        Connection conn = null;				//和数据库取得连接
        PreparedStatement pstmt = null;		//创建statement
        try{
            conn = DbUtil.getConnection();
            pstmt = (PreparedStatement) conn.prepareStatement(sql);
            pstmt.setString(1, acid); //给占位符赋值
            pstmt.setString(2, worker); //给占位符赋值
            pstmt.setString(3, date); //给占位符赋值
            pstmt.setString(4, detail); //给占位符赋值
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
     * 删除记录
     * @param acid 空调编号
     * @param worker 工人用户名
     * @param date 创建日期
     */
    public static void delRec(String acid,String worker,String date){
        String sql = "delete from record where ACID=? and Worker=? and Date=?";
        Connection conn = null;
        PreparedStatement pstmt = null;
        try {
            conn = DbUtil.getConnection();
            pstmt = (PreparedStatement) conn.prepareStatement(sql);
            pstmt.setString(1, acid);
            pstmt.setString(2, worker); //给占位符赋值
            pstmt.setString(3, date); //给占位符赋值
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
     * 修改记录
     * @param acid 空调编号
     * @param worker 工人用户名
     * @param date 创建日期
     * @param detail 详细信息
     */
    public static void modifyRec(String acid,String worker,String date,String detail){
        String sql = "update record set detail =? where ACID=? and Worker=? and Date=?";
        Connection conn = null;
        PreparedStatement pstmt = null;
        try {
            conn = DbUtil.getConnection();
            pstmt = (PreparedStatement) conn.prepareStatement(sql);
            pstmt.setString(1, detail);  //利用Preparedstatement的set方法给占位符赋值
            pstmt.setString(2, acid); //给占位符赋值
            pstmt.setString(3, worker); //给占位符赋值
            pstmt.setString(4, date); //给占位符赋值
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
     * 查找特定记录
     * @param acid 空调编号
     * @param worker 工人用户名
     * @param date 创建日期
     */
    public static List<Record> findOneRecord(String acid,String worker,String date){
        String sql = "select * from record where ACID=? and Worker=? and Date=?";
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs=null;
        //创建一个集合对象用来存放查询到的数据
        List<Record> recList=new ArrayList<>();
        try {
            conn = DbUtil.getConnection();
            pstmt = (PreparedStatement) conn.prepareStatement(sql);
            pstmt.setString(1, acid); //给占位符赋值
            pstmt.setString(2, worker); //给占位符赋值
            pstmt.setString(3, date); //给占位符赋值
            rs=(ResultSet)pstmt.executeQuery();
            while(rs.next()) {
                String Acid = rs.getString("ACID");
                String Wker = rs.getString("Worker");
                String Date = rs.getString("Date");
                String Dtil = rs.getString("detail");
                //每个记录对应一个对象
                Record record = new Record(Acid, Wker, Date, Dtil);
                //将对象放到集合中
                recList.add(record);
            }
        } catch (SQLException e) {
            // TODO: handle exception
            e.printStackTrace();
        }finally{
            DbUtil.close(pstmt);
            DbUtil.close(conn);		//必须关闭
        }
        return recList;
    }
}
