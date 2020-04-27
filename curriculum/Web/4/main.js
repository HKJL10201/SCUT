// JavaScript Document

//Employee类定义
var Employee=function(name,wage){
    this.name=name;
    this.wage=wage;
    this.show=function()
    {
        return "name: "+this.name+"\nwage: "+this.wage;
    };
};

//Manager类定义
var Manager=function(inferiors){
    this.inferiors=inferiors;
    this.getInferiors=function()
    {
        var names="";
        for(var i in inferiors)
        {
            names+=inferiors[i].name+"\n";
        }
        return names;
    };
};

//Secretary类定义
var Secretary=function(superior){
    this.superior=superior;
    this.getSuperior=function()
    {
        return this.superior;
    };
};



var Em1=new Employee("Arthur",3000);
var Em2=new Employee("Bob",4000);
var Em3=new Employee("Charles",5000);
var Em4=new Employee("Dylan",6000);

var ems=[Em1,Em2,Em3,Em4];

// 继承功能函数
function extend(parent, child)
{ 
    for (var i in parent) 
    { child[i] = parent[i]; } 
}

//实例化Manager
var Em0=new Employee("Jack",10000);
var Mag=new Manager(ems);
// 通过复制的继承
extend(Em0, Mag);

//原型的继承
Secretary.prototype=new Employee("Elsa",5000);

//实例化Secretary
var Sec=new Secretary(Mag);
Sec.name="Elsa";
Sec.wage=5000;

function f1()
{
    alert(Mag.show());
}
function f2()
{
    alert(Sec.show());
}
function f3()
{
    alert(Em1.show());
}
function f4()
{
    alert(Em2.show());
}
function f5()
{
    alert(Em3.show());
}
function f6()
{
    alert(Em4.show());
}

function g1()
{
    alert("Inferiors:\n"+Mag.getInferiors());
}
function g2()
{
    alert("Superior:\n"+Sec.getSuperior().name);
}