package pers.lee.acms.controllers;

import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;
import pers.lee.acms.models.Record;
import pers.lee.acms.services.RecordDbServices;

import java.util.List;

@Api(tags = "一般客户操作接口")
@RestController
@RequestMapping("/acms")
public class CustomerController {

    @ApiOperation(value = "查找检修记录", notes = "通过空调编号查找记录")
    @ApiImplicitParam(name = "acid",value = "空调编号",required = true,paramType = "query",dataType = "String")
    @RequestMapping(value = "/findbyid/{acid}",method = RequestMethod.POST)
    public List<Record> findById(@PathVariable("acid") String acid){     //通过空调ID查找记录
        return RecordDbServices.findRecordByAcid(acid);
    }
}
