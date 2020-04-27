package pers.lee.acms.services;

import pers.lee.acms.models.User;

import java.util.ArrayList;
import java.util.List;

public class UserHelper {
    public static User findUser(String username){
        List<User> userList = new ArrayList<>();
        userList = UserDbServices.findUser(username);
        if (userList.size() == 0)
            return new User("","");
        else {
            return userList.get(0);
        }
    }

    public static String existUser(String username){
        User user=findUser(username);
        return user.getUsername();
    }

    public static User verify(User user){
        User u=findUser(user.getUsername());
        if(!u.getUsername().equals("")&&u.getPassword().equals(user.getPassword())){
            return u;
        }
        else return new User("","");
    }
}
