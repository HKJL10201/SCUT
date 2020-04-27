// JavaScript Document

function append()   //新添留言
{
    var txt=document.getElementById("Input").value; //获取文本输入框的文本
    var name=document.getElementById("Input-name").value; //获取文本输入框的文本
    if (txt.length==0||name.length==0)
    {
        alert("名字或留言不能为空！");
        return;
    }
    var date=new Date();
    var ht=date.getHours();
    var mt=date.getMinutes();
    if(ht<10)
    {
        ht='0'+ht;
    }
    if(mt<10)
    {
        mt='0'+mt;
    }
    date=date.toLocaleDateString()+' '+ht+':'+mt;
    var newli=document.createElement("li");         //创建新的li
    newli.innerHTML='<input type="checkbox"><div class="li-txt"><p>' + txt+'</p></div><div class="name-time"><p>'+name+'</p><p>'+date+'</p></div>';    //设置li的checkbook和文字内容
    var list=document.getElementById("to-do-list");     //获得留言列表的ul对象
    list.appendChild(newli);                        //将新建的li添加到ul中
    document.getElementById("Add").blur();      //取消按钮的焦点（为了屏蔽Enter键对按钮的操作）
}

function delet()   //删除所选留言
{
    var list=document.getElementById("to-do-list"); //获得留言列表的ul对象
    var lst=list.getElementsByTagName("li");        //获得ul列表的li内容
    for(let i=lst.length-1;i>=0;i--)        //遍历列表
    {
        if(lst[i].getElementsByTagName("input")[0].checked==true)
        {   //如果复选框为true
            list.removeChild(lst[i]);   //从ul列表中删除li留言
        }
    }
    document.getElementById("Delete").blur();   //取消按钮的焦点（屏蔽Enter）
}

function selectall()    //全选
{   //获得留言列表ul的内容（获取所有li）
    var list=document.getElementById("to-do-list").getElementsByTagName("li");
    for(let i=0;i<list.length;i++)        //遍历列表
    {   //设置列表中每一项的checkbox都为true
        list[i].getElementsByTagName("input")[0].checked=true;
    }
    document.getElementById("Selectall").blur();   //取消按钮的焦点（屏蔽Enter）
}

function deselectall()    //取消全选
{   //获得留言列表ul的内容（获取所有li）
    var list=document.getElementById("to-do-list").getElementsByTagName("li");
    for(let i=0;i<list.length;i++)        //遍历列表
    {   //设置列表中每一项的checkbox都为false
        list[i].getElementsByTagName("input")[0].checked=false;
    }
    document.getElementById("Deselectall").blur();   //取消按钮的焦点（屏蔽Enter）
}

$(function(){
    //当滚动条的位置处于距顶部800像素以下时，跳转链接出现，否则消失
    $(function () {
        $(window).scroll(function(){
            if ($(window).scrollTop()>200){
                $("#Top-button").fadeIn(300);
            }
            else
            {
                $("#Top-button").fadeOut(300);
            }
        });

        //当点击跳转链接后，回到页面顶部位置
        $("#Top-button").click(function(){
            //$('body,html').animate({scrollTop:0},1000);
    if ($('html').scrollTop()) {
            $('html').animate({ scrollTop: 0 }, 500);
            return false;
        }
        $('body').animate({ scrollTop: 0 }, 500);
             return false;            
       });       
 });    
});

window.onload=function(){
    $("#Top-button").fadeOut(0);
};