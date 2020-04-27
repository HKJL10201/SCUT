package pers.lee.acms.controllers;

import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;
import pers.lee.acms.models.User;
import pers.lee.acms.services.UserHelper;

@Api(tags = "内部用户（管理员和工人）操作接口")
@RestController
@RequestMapping("/acms")
public class UserController {

    @ApiOperation(value = "登录",notes = "账户登录")
    @ApiImplicitParam(name = "user",value = "用户",required = true,paramType = "body",dataType = "User")
    @RequestMapping(value = "/login",method = RequestMethod.POST)
    public User login(@RequestBody User user) {     //登录
        return UserHelper.verify(user);
    }
}
