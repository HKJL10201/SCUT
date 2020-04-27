// JavaScript Document

/* 界面定义 */

var LOGIN='<div class="bt_space">\
<label>Username</label><label class="error" id="error1">_</label>\
</div>\
<input class="unpw" id="username" type="text" autocomplete="off"/>\
<label>Password</label>\
<input class="unpw" id="password" type="password" onkeyup="if(event.keyCode==13)Login();" autocomplete="off" />\
<button class="onebtn" id="login_confirm" onclick="Login()">Sign in</button>\
<div class="bt_space">\
<button class="one_of_btns" id="register_confirm" onclick="signUp()">Sign up</button>\
<button class="one_of_btns" id="cancel_btn" onclick="signHid()">Cancel</button>\
</div>';

var REGISTER='<div class="bt_space">\
<label>Username</label><label class="error" id="error1">_</label>\
</div>\
<input class="unpw" id="username" type="text" autocomplete="off"/>\
<label>Password</label>\
<input class="unpw" id="password" type="password" autocomplete="off"/>\
<label>Repeat password</label>\
<input class="unpw" id="password2" type="password" onkeyup="if(event.keyCode==13)Register();" autocomplete="off"/>\
<button class="onebtn" id="register_confirm" onclick="Register()">Sign up</button>\
<button class="onebtn" id="cancel_btn" onclick="signBak()">Cancel</button>';

var UPDATE='<label>Original password</label>\
<input class="unpw" id="ori-pw" type="password" autocomplete="off"/>\
<label>New password</label>\
<input class="unpw" id="new-pw" type="password" autocomplete="off"/>\
<label>Repeat new password</label>\
<input class="unpw" id="new-pw2" type="password" onkeyup="if(event.keyCode==13)Update();" autocomplete="off"/>\
<label class="error" id="error1">_</label>\
<button class="onebtn" id="login_confirm" onclick="Update()">Confirm</button>\
<button class="onebtn" id="cancel_btn" onclick="signHid()">Cancel</button>';

var CUSFORM='<div class="col-wrapper">\
<div class="linyx" id="home-search">\
<input id="acid" type="text" placeholder="Input air-conditioner ID" onkeyup="if(event.keyCode==13)findById();" autocomplete="off"/>\
<button id="find_id" onclick="findById()">Search</button>\
</div>\
<label class="error" id="error">_</label>\
</div>\
<ul id="resList"></ul>';

var WORKERFORM='<div id="add_form">\
    <div class="virtic">\
        <label>Add a new record:</label>\
        <div class="col-wrapper">\
            <div class="linyx" id="add_bar">\
                <input id="ACID" type="text" placeholder="Air conditioner ID" autocomplete="off"/>\
                <input id="detail" placeholder="detail" autocomplete="off"/>\
                <button id="add_new" onclick="addRec()">Submit</button>\
            </div>\
            <label class="error" id="error_a">_</label>\
        </div>\
    </div>\
</div>\
<div class="bt_space">\
    <button id="find_wk" onclick="showMyRec()">Show my records</button>\
    <div class="col-wrapper">\
        <div class="linyx">\
            <input type="text" id="edit_txt" placeholder="Click to edit" autocomplete="off" onclick="selEdit()" onkeyup="if(event.keyCode==13)subEdit();"/>\
            <button id="edit_btn" onclick="subEdit()" disabled="disabled">Submit</button>\
        </div>\
        <label class="error" id="error">_</label>\
    </div>\
</div>\
<ul id="resList"></ul>';

var ADMINFORM='\
<div class="bt_space">\
    <button id="del_rec" onclick="delRec()">Delete chosen</button>\
    <div class="linyx">\
        <input type="date" id="selDate" placeholder="Date" onkeyup="if(event.keyCode==13)findByDt();"/>\
        <button id="find_dt" onclick="findByDt()">Search by date</button>\
    </div>\
    <div class="linyx">\
        <input id="worker" type="text" placeholder="Input worker name" onkeyup="if(event.keyCode==13)findByWk();"/>\
        <button id="find_wk" onclick="findByWk()">Search by worker</button>\
    </div>\
    <div class="col-wrapper">\
        <div class="linyx">\
            <input type="text" id="edit_txt" placeholder="Click to edit" autocomplete="off" onclick="selEdit()" onkeyup="if(event.keyCode==13)subEdit();"/>\
            <button id="edit_btn" onclick="subEdit()" disabled="disabled">Submit</button>\
        </div>\
        <label class="error" id="error">_</label>\
    </div>\
</div>\
<ul id="resList"></ul>';