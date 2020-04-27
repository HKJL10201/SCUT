// JavaScript Document

/* 通用操作 */

function error(s){
    let e = document.getElementById("error");
    e.innerHTML=s;
    e.style.color="red";
}

function derror(){
    let errs=document.getElementsByClassName("error");
    for(let i=errs.length-1;i>=0;i--){
        errs[i].style.color="transparent";
    }
    //document.getElementById("error").style.color="transparent";
}

function error_a(s){
    let e = document.getElementById("error_a");
    e.innerHTML=s;
    e.style.color="red";
}

function clearList(list){
    let lst=list.getElementsByTagName("li");        //获得列表的li内容
    for(let i=lst.length-1;i>=0;i--)        //遍历列表
    {
        list.removeChild(lst[i]);
    }
}

function addHeader(list){
    let newli=document.createElement("li");
    newli.className="list-header";
    newli.innerHTML=divilise(HEADER);
    list.appendChild(newli);
}

function noResult(list){
    let newli=document.createElement("li");
    newli.className="no_result";
    newli.innerHTML="No record.";
    list.appendChild(newli);
}

function showList(list,data){
    derror();
    let len=data.length;
    if(len>0){
        addHeader(list);
        for(i=0;i<len;i++){
            let txt=divilise(data[i]);
            let newli=document.createElement("li");         //创建新的li
            newli.innerHTML=txt;    //设置li的checkbook和文字内容
            list.appendChild(newli);
        }
    }
    else{
        noResult(list);
    }
}

function divilise(data){
    return '<div class="list_acid">'+data.acid+'</div>\
    <div class="list_date">'+data.date+'</div>\
    <div class="list_detail">'+data.detail+'</div>\
    <div class="list_worker">'+data.worker+'</div>';
}

function showList_withCheck(list,data){
    derror();
    let len=data.length;
    if(len>0){
        addHeader(list);
        for(i=0;i<len;i++){
            let txt=divilise(data[i]);
            let newli=document.createElement("li");         //创建新的li
            newli.innerHTML='<input type="checkbox">' + txt;    //设置li的checkbook和文字内容
            list.appendChild(newli);
        }
    }
    else{
        noResult(list);
    }
}
