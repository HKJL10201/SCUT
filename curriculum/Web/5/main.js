// JavaScript Document

function append()   //新添事项
{
    var txt=document.getElementById("Input").value; //获取文本输入框的文本
    var newli=document.createElement("li");         //创建新的li
    newli.innerHTML='<input type="checkbox">' + txt;    //设置li的checkbook和文字内容
    var list=document.getElementById("to-do-list");     //获得事项列表的ul对象
    list.appendChild(newli);                        //将新建的li添加到ul中
    document.getElementById("Add").blur();      //取消按钮的焦点（为了屏蔽Enter键对按钮的操作）
}

function delet()   //删除所选事项
{
    var list=document.getElementById("to-do-list"); //获得事项列表的ul对象
    var lst=list.getElementsByTagName("li");        //获得ul列表的li内容
    for(let i=lst.length-1;i>=0;i--)        //遍历列表
    {
        if(lst[i].getElementsByTagName("input")[0].checked==true)
        {   //如果复选框为true
            if(i==index)//如果当前删除对象为焦点对象（index即焦点下标）
            {
                flag=0; //flag为0表示当前没有任何焦点
            }
            list.removeChild(lst[i]);   //从ul列表中删除li事项
        }
    }
    document.getElementById("Delete").blur();   //取消按钮的焦点（屏蔽Enter）
}

function selectall()    //全选
{   //获得事项列表ul的内容（获取所有li）
    var list=document.getElementById("to-do-list").getElementsByTagName("li");
    for(let i=0;i<list.length;i++)        //遍历列表
    {   //设置列表中每一项的checkbox都为true
        list[i].getElementsByTagName("input")[0].checked=true;
    }
    document.getElementById("Selectall").blur();   //取消按钮的焦点（屏蔽Enter）
}

function deselectall()    //取消全选
{   //获得事项列表ul的内容（获取所有li）
    var list=document.getElementById("to-do-list").getElementsByTagName("li");
    for(let i=0;i<list.length;i++)        //遍历列表
    {   //设置列表中每一项的checkbox都为false
        list[i].getElementsByTagName("input")[0].checked=false;
    }
    document.getElementById("Deselectall").blur();   //取消按钮的焦点（屏蔽Enter）
}

var flag=0;     //用于表示当前是否已有事项获取焦点
var index=-1;   //当前焦点下标

document.onkeydown=function(event){
    if(event.keyCode == 13){    //键盘按下Enter键
        var list=document.getElementById("to-do-list").getElementsByTagName("li");  //获取列表元素
        if(flag==1){    //如果已有事项获取了焦点
            list[index].getElementsByTagName("input")[0].checked=!list[index].getElementsByTagName("input")[0].checked;
        }   //将其checkbox值取反
    }
    if(event.keyCode == 38){    //键盘按下Up（向上）键
        var list=document.getElementById("to-do-list").getElementsByTagName("li");  //获取列表元素
        if(flag==0){    //如果尚未存在焦点
            flag=1;
            index=list.length-1;    //设置列表最后一项为焦点
            list[index].style.backgroundColor="rgba(255,255,255,.3)";   //焦点的背景色改变
        }
        else{   //如果已有焦点，且下标为index
            list[index].style.backgroundColor="transparent";    //设置第index项背景色为透明
            index=(index+list.length-1)%list.length;            //index-1，并取模，防止越界
            list[index].style.backgroundColor="rgba(255,255,255,.3)";   //焦点的背景色改变
        }
    }
    if(event.keyCode == 40){    //键盘按下Down（向下）键
        var list=document.getElementById("to-do-list").getElementsByTagName("li");  //获取列表元素
        if(flag==0){    //如果尚未存在焦点
            flag=1;
            index=0;    //设置列表第一项为焦点
            list[index].style.backgroundColor="rgba(255,255,255,.3)";   //焦点的背景色改变
        }
        else{   //如果已有焦点，且下标为index
            list[index].style.backgroundColor="transparent";    //设置第index项背景色为透明
            index=(index+1)%list.length;                //index+1，并取模，防止越界
            list[index].style.backgroundColor="rgba(255,255,255,.3)";   //焦点的背景色改变
        }
    }
};
