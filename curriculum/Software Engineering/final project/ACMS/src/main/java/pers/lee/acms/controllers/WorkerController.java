package pers.lee.acms.controllers;

import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiImplicitParams;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;
import pers.lee.acms.models.Message;
import pers.lee.acms.models.Record;
import pers.lee.acms.models.User;
import pers.lee.acms.services.RecordDbServices;
import pers.lee.acms.services.RecordHelper;
import pers.lee.acms.services.UserHelper;
import pers.lee.acms.services.UserDbServices;

import java.util.List;

@Api(tags = "检修工人操作接口")
@RestController
@RequestMapping("/acms")
public class WorkerController {

    @ApiOperation(value = "注册",notes = "创建新账户")
    @ApiImplicitParam(name = "user",value = "用户",required = true,paramType = "body",dataType = "User")
    @RequestMapping(value = "/register",method = RequestMethod.POST)
    public Message register(@RequestBody User user) {       //注册
        String check= UserHelper.existUser(user.getUsername());
        if(!check.equals(""))       //如果已存在该用户
            return new Message("");
        else {
            UserDbServices.addUser(user.getUsername(), user.getPassword());
            return new Message(user.getUsername());     //注册成功返回用户名
        }
    }

    @ApiOperation(value = "修改密码", notes = "修改某个用户的密码")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "newPassword",value = "新密码",required = true,paramType = "query",dataType = "String"),
            @ApiImplicitParam(name = "user",value = "用户（含用户名和原密码）",required = true,paramType = "body",dataType = "User")
    })
    @RequestMapping(value = "/moduser/{pw}",method = RequestMethod.POST)
    public Message modUser(@PathVariable("pw") String newPassword, @RequestBody User user)      //改密码
    {
        User u= UserHelper.verify(user);     //验证旧密码是否正确
        if(u.getUsername().equals(""))      //如果输入的用户名和旧密码不匹配
            return new Message("");
        else {
            UserDbServices.modifyUser(user.getUsername(),newPassword);
            return new Message("done");
        }
    }

    @ApiOperation(value = "查找检修记录", notes = "通过工人用户名查找记录")
    @ApiImplicitParam(name = "worker",value = "工人用户名",required = true,paramType = "query",dataType = "String")
    @RequestMapping(value = "/findbyworker/{worker}",method = RequestMethod.POST)
    public List<Record> findByWorker(@PathVariable("worker") String worker){      //通过用户名查找记录
        return RecordDbServices.findRecordByWorker(worker);
    }

    @ApiOperation(value = "增加检修记录",notes = "增加新的记录")
    @ApiImplicitParam(name = "record",value = "新记录的内容",required = true,paramType = "body",dataType = "Record")
    @RequestMapping(value = "/addrec",method = RequestMethod.POST)
    public Message addRec(@RequestBody Record record){      //新增记录
        if(!RecordHelper.existRec(record).getMess().equals(""))   //如果已存在该记录
            return new Message("");                         //不能新增同一人同一天同一台空调的记录，只能修改
        else {
            RecordDbServices.addRec(record.getACID(),record.getWorker(),record.getDate(),record.getDetail());
            return new Message("done");
        }
    }

    @ApiOperation(value = "修改检修记录",notes = "修改选中的记录")
    @ApiImplicitParam(name = "record",value = "编辑后的记录",required = true,paramType = "body",dataType = "Record")
    @RequestMapping(value = "/modrec",method = RequestMethod.POST)      //修改特定记录
    public Message modRec(@RequestBody Record record){
        if(RecordHelper.existRec(record).getMess().equals(""))    //如果不存在该记录
            return new Message("");
        else {
            RecordDbServices.modifyRec(record.getACID(),record.getWorker(),record.getDate(),record.getDetail());
            return new Message("done");
        }
    }
}