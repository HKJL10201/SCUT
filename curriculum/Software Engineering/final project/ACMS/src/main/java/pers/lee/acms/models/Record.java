package pers.lee.acms.models;

public class Record {
    private String ACID;
    private String Worker;
    private String Date;
    private String detail;

    public Record(String ACID,String Worker,String Date, String detail)
    {
        this.ACID=ACID;
        this.Worker=Worker;
        this.Date=Date;
        this.detail =detail;
    }

    public String getACID(){
        return this.ACID;
    }
    public String getWorker(){
        return this.Worker;
    }
    public String getDate(){
        return this.Date;
    }
    public String getDetail(){
        return this.detail;
    }
}
