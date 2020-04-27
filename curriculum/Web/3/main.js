//快速排序按钮
function clickSort() 
{
    //vec是用来存放用户输入数据的数组（用户输入以空格隔开）
    var s=document.getElementById("Input").value;
    var vec = new Array();
    vec = s.split(" ");

    //检查用户是否输入了非数字类型的数据
    var flag=0;
    for(let i=0; i<vec.length;i++)
    {
        if(isNaN(vec[i]))
        {
            flag=1;
            break;
        }
    }
    //如果用户输入的都是纯数字，就将vec中的所有字符串转化为数字
    //否则以字典序给字符串排序
    if(flag==0)
    {
        for(let i=0; i < vec.length;i++)
        {
            vec[i]=parseFloat(vec[i]);
        }
    }

    //对vec进行快速排序
    Qsort(vec,0,vec.length-1);

    //输出结果
    var res=document.getElementById("Output");
    res.value = vec;
}

//快速排序
function Qsort(a,i,j)
{
    if(j<=i)return;
    if((i+j)%2==0)
        var pivot=(i+j)/2;
    else
        var pivot=(i+j-1)/2;

    swap(a,pivot,j);

    var k=partition(a,i,j,a[j]);
    swap(a,k,j);
    Qsort(a,i,k-1);
    Qsort(a,k+1,j);
}

function partition(a,l,r,pivot)
{
    do
    {
        while(a[l]<pivot)
            l++;
        while((r>l)&&a[r]>=pivot)
            r--;
        swap(a,l,r);
    }while(l<r);
    return l;
}

function swap(a,i,j)
{
    var tmp=a[i];
    a[i]=a[j];
    a[j]=tmp;
}

//列表反序
function reverse()
{
    //用ulst储存电影列表
    var ulst=document.getElementById("MovieList").getElementsByTagName("li");
    var list=new Array();//list储存了每一个电影名（字符串）
    for(let i=0;i<ulst.length;i++)
    {
        list.push(ulst[i].innerHTML);
    }
    list.reverse();//反序函数

    //输出到对话框
    var str="";
    for(let i=0;i<list.length;i++)
    {
        str+=list[i];
        if(i!=list.length-1)
            str+="\n";
    }
    alert(str);
}

//电影名轮流变色
var i=0;//全局变量
function changeColor()
{
    //获取电影列表
    var ulst=document.getElementById("MovieList").getElementsByTagName("li");
    var len=ulst.length;    //获取列表长度
    ulst[(i+len-1)%len].style.color="white";    //上一个电影名变回白色
    ulst[i].style.color="red";  //当前第i个电影名变为红色
    i=(i+1)%len;    //i自增，并对表长取模
    setTimeout("changeColor()",3000);   //递归调用，延时3秒
}