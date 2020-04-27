package pers.lee.acms.services;

import pers.lee.acms.models.Message;
import pers.lee.acms.models.Record;

import java.util.ArrayList;
import java.util.List;

public class RecordHelper {
    public static Message existRec(Record record){
        List<Record> recordList= new ArrayList<>();
        recordList = RecordDbServices.findOneRecord(record.getACID(),record.getWorker(),record.getDate());
        if(recordList.size()==0)
            return new Message("");
        else return new Message("true");
    }
}
