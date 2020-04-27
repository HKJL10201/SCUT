package pers.lee.acms.models;

public class Message {
    private String mess;
    public Message(String message){
        this.mess=message;
    }
    public String getMess(){return mess;}

    public Message() {
    }

    public void setMess(String mess) {
        this.mess = mess;
    }

    @Override
    public String toString() {
        return "Message{" +
                "mess='" + mess + '\'' +
                '}';
    }
}
