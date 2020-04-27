package pers.lee.acms.models;

public class Administrator extends User {
    public Administrator(String username,String password) {
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
