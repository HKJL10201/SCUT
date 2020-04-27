package pers.lee.acms.controllers;

import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
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

@Api(tags = "管理员操作接口")
@RestController
@RequestMapping("/acms/admin")
public class AdministratorController {

    @ApiOperation(value = "查找检修记录", notes = "通过日期查找记录")
    @ApiImplicitParam(name = "date",value = "日期",required = true,paramType = "query",dataType = "String")
    @RequestMapping(value = "/findbydate/{date}",method = RequestMethod.POST)
    public List<Record> findByDate(@PathVariable("date") String date){       //通过日期查找记录
        return RecordDbServices.findRecordByDate(date);
    }

    @ApiOperation(value = "删除检修记录",notes = "删除选中的记录")
    @ApiImplicitParam(name = "record",value = "记录",required = true,paramType = "body",dataType = "Record")
    @RequestMapping(value = "/delrec",method = RequestMethod.POST)
    public Message delRec(@RequestBody Record record){      //删除特定记录
        if(RecordHelper.existRec(record).getMess().equals(""))    //如果不存在该记录
            return new Message("");
        else {
            RecordDbServices.delRec(record.getACID(),record.getWorker(),record.getDate());
            return new Message("done");
        }
    }

    @ApiOperation(value = "删除用户",notes = "永久注销某个用户的账号")
    @ApiImplicitParam(name = "user",value = "用户",required = true,paramType = "body",dataType = "User")
    @RequestMapping(value = "/deluser",method = RequestMethod.POST)
    public Message delUser(@RequestBody User user) {        //删除某用户
        User u= UserHelper.verify(user);
        if(u.getUsername().equals("")){     //如果输入用户名或密码错误
            return new Message("");
        }
        else {
            UserDbServices.delUser(user.getUsername());
            return new Message("done");
        }
    }
}