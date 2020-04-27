package pers.lee.acms.models;

public class Worker extends User {
    public Worker(String username,String password) {
        super(username,password);
    }
    @Override
    public String getUsername() {
        return super.getUsername();
    }
    @Override
    public String getPassword() {
        return super.getPassword();
    }
}