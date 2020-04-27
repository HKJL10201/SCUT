// JavaScript Document

/* 针对用户验证的操作 */

var USER="";

//登录
function Login()
{
    let username=document.getElementById("username").value;
    let password=document.getElementById("password").value;
    if(username==""||password==""){
        //alert("用户名和密码不能为空");
        error1('Username or password is null.');
        return;
    }
    let data = JSON.stringify({
        username: document.getElementById("username").value,
        password: document.getElementById("password").value
    });
    fetch(HOST+'/acms/login', {
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
            if(data.username==""){
                //alert('Username or password is wrong');
                error1('Incorrect username or password.');
            }
            else{
                USER=data.username;
                loginSucc(USER);
            }
        })
    }).catch(e=>{
        console.log(e);
    });
}

//注册
function Register()
{
    let username=document.getElementById("username").value;
    let password=document.getElementById("password").value;
    let password2=document.getElementById("password2").value;
    if(username==""||password==""){
        //alert("用户名和密码不能为空");
        error1('Username or password is null.');
        return;
    }
    else if(username[0]<'A'||username[0]>'Z'&&username[0]<'a'||username[0]>'z'){
        //alert("用户名应以字母开头");
        error1('Username must start with letters.');
        return;
    }
    if(password!=password2){
        //alert("两次输入不一致");
        error1('Incorrectly repeat password.');
        return;
    }
    else{
        let data = JSON.stringify({
            username: username,
            password: password
        });
        fetch(HOST+'/acms/register', {
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
                    //alert(username+' have been existed');
                    error1('Error: '+username+' have been existed.');
                }
                else{
                    alert("Register successfully, "+username);
                    USER=username;
                    loginSucc(USER);
                }
            })
        }).catch(e=>{
            console.log(e);
        });
    }
}

//修改密码
function Update(){      //修改密码
    let username=USER;      //用户名：当前登录用户USER
    if(USER==""){           //如果没有登录
        error1("Please sign in your account.");
    }
    let origin=document.getElementById("ori-pw").value;
    let new1=document.getElementById("new-pw").value;
    let new2=document.getElementById("new-pw2").value;
    if(origin==""||new1==""){
        //alert("密码不能为空");
        error1('Origin or new password is null.');
        return;
    }
    else if(new1!=new2){
        //alert("两次输入不一致");
        error1('Incorrectly repeat password.');
        return;
    }
    else if(origin==new1){
        error1('New and old passwords cannot be the same.');
        return;
    }
    else{
        let data = JSON.stringify({
            username: username,
            password: origin
        });
        fetch(HOST+'/acms/moduser/'+new1, {
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
                    //alert(username+' have been existed');
                    error1('Incorrect origin password.');
                }
                else{
                    alert("Password updated.");
                    signHid();
                }
            })
        }).catch(e=>{
            console.log(e);
        });
    }
}

//报错
function error1(s){
    let e = document.getElementById("error1");
    e.innerHTML=s;
    e.style.color="red";
}