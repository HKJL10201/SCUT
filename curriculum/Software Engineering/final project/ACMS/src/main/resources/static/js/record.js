// JavaScript Document

/* 针对记录的增删改查等操作 */

var HOST='http://localhost:8328';

let HEADER={acid:"Air-conditioner ID",date:"Date",detail:"Detail",worker:"Worker"};
let start_index=1;

//增加记录
function addRec(){
    let acid=document.getElementById("ACID").value;
    let worker=USER;
    let detail=document.getElementById("detail").value;
    //今天的时间
    let day2 = new Date();
    day2.setTime(day2.getTime());
    let date = day2.getFullYear()+"-" + (day2.getMonth()+1) + "-" + day2.getDate();

    if(worker==""){
        error_a("Please sign in your account.");
        return;
    }
    else if(acid==""){
        error_a("Please input air-conditioner ID.");
        return;
    }
    if(detail=="")detail="normal";
    //json
    let data=JSON.stringify({
        ACID: acid,
        Worker: worker,
        Date: date,
        detail: detail
    });
    fetch(HOST+'/acms/addrec', {
        method: 'POST',
        body: data,
        mode: 'cors',
        headers: {
            'Content-Type' : 'application/json',
            'Content-Length': data.length.toString(),
        },
        cache:"default"
    }).then(res=>{
        res.json().then(data=>{
            //console.log(data);
            if(data.mess==""){
                error_a('The record of today has been existed.');
            }
            else{
                //error(data.mess);
                showMyRec();
                document.getElementById("ACID").value="";
                document.getElementById("detail").value="";
            }
        })
    }).catch(e=>{
        console.log(e);
    });
}

//通过空调ID查找
function findById(){
    let list=document.getElementById("resList");
    let acid = document.getElementById("acid").value;
    if(acid==""){
        if(USER==""){error("Please input the ID.");}
        return;
    }
    clearList(list);
     //json
    let data=JSON.stringify({
        mess: acid
    });
    fetch(HOST+'/acms/findbyid/'+acid, {
        method: 'POST',
        body: null,
        mode: 'cors',
        headers: {
            'Content-Type' : 'application/json',
            'Content-Length': data.length.toString(),
        },
        cache:"default"
    }).then(res=>{
        res.json().then(data=>{
            //console.log(data);
            if(USER==""){
                showList(list,data);
            }
            else{
                showList_withCheck(list,data);
            }
        })
    }).catch(e=>{
        console.log(e);
    });
}

//通过工人名查找
function findByWk(){
    let list=document.getElementById("resList");
    let worker = document.getElementById("worker").value;
    if(worker==""){
        error("Please input worker name.");
        return;
    }
    clearList(list);
     //json
    let data=JSON.stringify({
        mess: worker
    });
    fetch(HOST+'/acms/findbyworker/'+worker, {
        method: 'POST',
        body: null,
        mode: 'cors',
        headers: {
            'Content-Type' : 'application/json',
            'Content-Length': data.length.toString(),
        },
        cache:"default"
    }).then(res=>{
        res.json().then(data=>{
            //console.log(data);
            showList_withCheck(list,data);
        })
    }).catch(e=>{
        console.log(e);
    });
}

//显示当前用户的所有记录
function showMyRec(){
    let list=document.getElementById("resList");
    clearList(list);
    let worker = USER;
    if(worker==""){
        error('No worker found.');
        return;
    }
     //json
    let data=JSON.stringify({
        mess: worker
    });
    fetch(HOST+'/acms/findbyworker/'+worker, {
        method: 'POST',
        body: null,
        mode: 'cors',
        headers: {
            'Content-Type' : 'application/json',
            'Content-Length': data.length.toString(),
        },
        cache:"default"
    }).then(res=>{
        res.json().then(data=>{
            //console.log(data);
            showList_withCheck(list,data);
        })
    }).catch(e=>{
        console.log(e);
    });
}

//通过日期查找记录
function findByDt(){
    let list=document.getElementById("resList");
    let date = document.getElementById("selDate").value;
    if(date==null) {
        error("Please select the date");
        return;
    }
    else{
        clearList(list);
        //json
        let data=JSON.stringify({
            mess: date
        });
        fetch(HOST+'/acms/admin/findbydate/'+date, {
            method: 'POST',
            body: null,
            mode: 'cors',
            headers: {
                'Content-Type' : 'application/json',
                'Content-Length': data.length.toString(),
        },
        cache:"default"
        }).then(res=>{
            res.json().then(data=>{
                //console.log(data);
                showList_withCheck(list,data);
            })
        }).catch(e=>{
            console.log(e);
        });
    }
}

//显示今天的所有记录
function showTodayRec(){
    let list=document.getElementById("resList");
    //今天的时间
    let day2 = new Date();
    day2.setTime(day2.getTime());
    let date = day2.getFullYear()+"-" + (day2.getMonth()+1) + "-" + day2.getDate();
    clearList(list);
    //json
    let data=JSON.stringify({
        mess: date
    });
    fetch(HOST+'/acms/admin/findbydate/'+date, {
        method: 'POST',
        body: null,
        mode: 'cors',
        headers: {
            'Content-Type' : 'application/json',
            'Content-Length': data.length.toString(),
    },
    cache:"default"
    }).then(res=>{
        res.json().then(data=>{
            //console.log(data);
            showList_withCheck(list,data);
        })
    }).catch(e=>{
        console.log(e);
    });
}

//删除记录
function delRec(){
    let list=document.getElementById("resList"); //获得事项列表的ol对象
    let lst=list.getElementsByTagName("li");        //获得ol列表的li内容
    if(lst.length==0){ 
        error("No record is chosen.");
        return; 
    }
    let chosen=0;
    for(let i=lst.length-1;i>=start_index;i--)        //遍历列表
    {
        if(lst[i].getElementsByTagName("input")[0].checked==true)
        {   //如果复选框为true
            chosen++;
            let acid=lst[i].getElementsByTagName("div")[0].innerHTML;
            let date=lst[i].getElementsByTagName("div")[1].innerHTML;
            let detail=lst[i].getElementsByTagName("div")[2].innerHTML;
            let worker=lst[i].getElementsByTagName("div")[3].innerHTML;
            //console.log(acid+'\t'+date+'\t'+detail+'\t'+worker)
            //json
            let data=JSON.stringify({
                ACID: acid,
                Worker: worker,
                Date: date,
                detail: detail
            });
            fetch(HOST+'/acms/admin/delrec', {
                method: 'POST',
                body: data,
                mode: 'cors',
                headers: {
                    'Content-Type' : 'application/json',
                    'Content-Length': data.length.toString(),
                },
                cache:"default"
            }).then(res=>{
                res.json().then(data=>{
                    //console.log(data);
                    if(data.mess==""){
                        error('第'+toString(i+1)+'条记录删除失败');
                    }
                    else{
                        //console.log(data.mess);
                        list.removeChild(lst[i]);   //从ul列表中删除li事项
                    }
                })
            }).catch(e=>{
                console.log(e);
            });
        }
    }
    if(chosen==0){
        error("No record is chosen.");
    }
}

let edit_selected=-1;

function deSel(){
    document.getElementById("edit_btn").disabled="disabled";
    document.getElementById("edit_txt").value="";
    edit_selected=-1;
}

//选择一条记录进行修改
function selEdit(){
    let list=document.getElementById("resList"); //获得事项列表的ol对象
    let lst=list.getElementsByTagName("li");        //获得ol列表的li内容
    if(lst.length==0){
        error("Please select one record");
        deSel();
        return;
    }
    let num=0;
    let tar=0;
    for(let i=lst.length-1;i>=start_index;i--)        //遍历列表
    {
        if(lst[i].getElementsByTagName("input")[0].checked==true)
        {   //如果复选框为true
            tar=i;
            num++;
        }
    }
    if(num==0){
        error("Please select one record.");
        deSel();
    }
    else if(num>1){
        error("You can only selece ONE record.");
        deSel();
    }
    else if(USER!=ADMIN&&USER!=lst[tar].getElementsByTagName("div")[3].innerHTML){
        error("You can only edit your record.");
        deSel();
    }
    else{
        derror();
        document.getElementById("edit_txt").value = lst[tar].getElementsByTagName("div")[2].innerHTML;
        edit_selected=tar;
        document.getElementById("edit_btn").removeAttribute("disabled");
    }
}

//提交修改
function subEdit(){
    let list=document.getElementById("resList"); //获得事项列表的ol对象
    let lst=list.getElementsByTagName("li");        //获得ol列表的li内容
    if(lst.length==0||edit_selected==-1){ 
        error('Fail to edit.');
        return; 
    }
    let acid=lst[edit_selected].getElementsByTagName("div")[0].innerHTML;
    let date=lst[edit_selected].getElementsByTagName("div")[1].innerHTML;
    let detail=document.getElementById("edit_txt").value;
    let worker=lst[edit_selected].getElementsByTagName("div")[3].innerHTML;
    if(detail==""){
        error('Edit content is null.');
        return;
    }
    let data=JSON.stringify({
        ACID: acid,
        Worker: worker,
        Date: date,
        detail: detail
    });
    fetch(HOST+'/acms/modrec', {
        method: 'POST',
        body: data,
        mode: 'cors',
        headers: {
            'Content-Type' : 'application/json',
            'Content-Length': data.length.toString(),
        },
        cache:"default"
    }).then(res=>{
        res.json().then(data=>{
            //console.log(data);
            if(data.mess==""){
                error('Fail to edit');
            }
            else{
                derror();
                alert("Edit successfully");
                if(USER!=ADMIN){showMyRec();}
                deSel();
            }
        })
    }).catch(e=>{
        console.log(e);
    });
}