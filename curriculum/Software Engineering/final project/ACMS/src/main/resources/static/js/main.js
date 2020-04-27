// JavaScript Document

/*界面生成函数*/

var ADMIN="Administrator";

function signIn(){      //点击登录后产生界面
    let frame=document.getElementById("body");      //父元素为body
    let login=document.createElement("div");        //创造子元素div
    login.className="Interface";                    //子元素类：Interface
    login.id="interface";                           //子元素id：interface
    login.innerHTML='<div class="interface_bg" onclick="signHid()"></div>\
    <div id="login_form" class="form">'+LOGIN+'</div>';
    frame.appendChild(login);                       //子元素添加到父元素
}

function signUp(){      //点击注册后更换界面
    let frame=document.getElementById("interface");     //父元素为interface
    let form=document.getElementById("login_form");     //子元素为登录框
    frame.removeChild(form);                            //删除子元素
    let register=document.createElement("div");         //创造新的子元素div
    register.className="form";                          //子元素类：form
    register.id="register_form";                        //子元素id：register_form
    register.innerHTML=REGISTER;
    frame.appendChild(register);                        //子元素添加到父元素
}

function signBak(){     //点击取消返回登陆界面
    let frame=document.getElementById("interface");     //父元素为interface
    let form=document.getElementById("register_form");  //子元素为注册框
    frame.removeChild(form);                            //删除子元素
    let login=document.createElement("div");            //创造新的子元素div
    login.className="form";                             //子元素类：form
    login.id="login_form";                              //子元素id：login_form
    login.innerHTML=LOGIN;
    frame.appendChild(login);                           //子元素添加到父元素
}

function signHid(){         //关闭登录/注册窗口
    let frame=document.getElementById("body");          //父元素：body
    let forms=frame.getElementsByClassName("Interface"); //子元素：Interface类div
    for(let i=forms.length-1;i>=0;i--)                   //删除所有Interface（一般只有一个）
    {
        frame.removeChild(forms[i]);
    }
}

function loginSucc(username){           //登陆成功产生用户界面
    if(username==""){
        alert("Fail to Login");
        return;
    }
    let status=document.getElementById("status");   //父元素：status
    let btn=document.getElementById("signIn");      //删除登录按钮
    status.removeChild(btn);
    let d=document.createElement("div");
    d.className="dropdown";
    d.id="dropdown_status";
    d.innerHTML='<div class="linyx">\
    <label id="status-user">'+username+'</label>\
    <label id="dropdown-arrow">∨</label>\
    </div>\
    <div class="dropdown-content">\
    <a onclick="modPassword()">Update password</a>\
    <a id="signOut" onclick = "signOut()">Sign out</a>\
    </div>';
    status.appendChild(d);

    let hs=document.getElementById("header-search");
    let bar=document.createElement("div");
    bar.className="linyx";
    bar.id="search_bar";
    bar.innerHTML='<input id="acid" type="text" placeholder="Search by ID" \
    onkeyup="if(event.keyCode==13)findById();" autocomplete="off"/>';
    hs.appendChild(bar);
    if(username==ADMIN){
        loginAdmin();
    }
    else{
        loginWorker();
    }
    signHid();                                      //关闭登录/注册窗口
}

function signOut(){         //退出登录返回首页
    USER="";
    let status=document.getElementById("status");
    let d=document.getElementById("dropdown_status");
    status.removeChild(d);
    let b=document.createElement("button");
    b.id="signIn";
    b.onclick = signIn;
    let t = document.createTextNode("Sign in");
    b.appendChild(t);
    status.appendChild(b);

    let hs=document.getElementById("header-search");
    let bar=document.getElementById("search_bar");
    hs.removeChild(bar);
    loginCustomer();
}

function modPassword(){     //产生修改密码界面
    let frame=document.getElementById("body");      //父元素为body
    let update=document.createElement("div");        //创造子元素div
    update.className="Interface";                    //子元素类：Interface
    update.id="interface";                           //子元素id：interface
    update.innerHTML='<div class="interface_bg" onclick="signHid()"></div>\
    <div id="update_form" class="form">'+UPDATE+'</div>';
    frame.appendChild(update);                       //子元素添加到父元素
}

function clearFuncForm(){       //清除界面
    let frame=document.getElementById("content-interface");
    let forms=document.getElementsByClassName("function-form");
    for(let i=forms.length-1;i>=0;i--)                   //删除所有function-form（一般只有一个）
    {
        frame.removeChild(forms[i]);
    }
}

function loginWorker(){     //产生工人界面
    clearFuncForm();
    let frame=document.getElementById("content-interface");
    let div_wk=document.createElement("div");            //创造新的子元素div
    div_wk.className="function-form";
    div_wk.id="div-for-wkr";
    div_wk.innerHTML=WORKERFORM;
    frame.appendChild(div_wk);
    showMyRec();
}

function loginCustomer(){       //产生一般用户界面，即首页
    clearFuncForm();
    let frame=document.getElementById("content-interface");
    let div_cs=document.createElement("div");            //创造新的子元素div
    div_cs.className="function-form";
    div_cs.id="div-for-cus";
    div_cs.innerHTML=CUSFORM;
    frame.appendChild(div_cs);
}

function loginAdmin(){      //产生管理员界面
    clearFuncForm();
    let frame=document.getElementById("content-interface");
    let div_cs=document.createElement("div");            //创造新的子元素div
    div_cs.className="function-form";
    div_cs.id="div-for-adm";
    div_cs.innerHTML=ADMINFORM;
    frame.appendChild(div_cs);
    showTodayRec();
}
