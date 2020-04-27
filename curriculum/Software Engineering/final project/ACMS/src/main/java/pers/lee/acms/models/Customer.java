package pers.lee.acms.models;

public class Customer extends User {
    public Customer(String username,String password) {
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