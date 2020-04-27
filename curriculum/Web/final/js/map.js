// JavaScript Document

var map = new BMap.Map("map-block"); // 创建地图实例
var point = new BMap.Point(114.05173, 22.53731); // 创建点坐标
map.centerAndZoom(point, 12); //以该点为中心，缩放等级为15
//map.enableScrollWheelZoom(true);            //利用鼠标滚轮控制缩放
map.addControl(new BMap.NavigationControl()); //缩放平移控件
map.addControl(new BMap.ScaleControl()); //比例尺
map.addControl(new BMap.OverviewMapControl()); //缩略图
map.addControl(new BMap.MapTypeControl()); //地图类型
map.setCurrentCity("深圳"); // 仅当设置城市信息时，MapTypeControl的切换功能才能可用


/*
//var map = new AMap.Map('map-block');
var map = new AMap.Map('map-block', {
    zoom:11,//级别
    center: [114.05173, 22.53731],//中心点坐标
});*/
/*
function initialize() {
    var map =new BMap.Map('map-block');
    map.centerAndZoom(new BMap.Point(114.05173, 22.53731), 12);
    map.addControl(new BMap.NavigationControl());//缩放平移控件
    map.addControl(new BMap.ScaleControl());    //比例尺
    map.addControl(new BMap.OverviewMapControl());//缩略图
    map.addControl(new BMap.MapTypeControl());      //地图类型
    map.setCurrentCity("深圳"); // 仅当设置城市信息时，MapTypeControl的切换功能才能可用

}
function loadScript() {
var script = document.createElement("script");
script.src ="http://api.map.baidu.com/api?v=2.0&ak=dvR6EBG5Z7yzEeAiGcwArzXet3XbqDUj&callback=initialize";
document.body.appendChild(script);
}
    
window.onload = loadScript;*/
/*
window.onLoad  = function(){
    var layer = new AMap.TileLayer({
    zooms:[3,20],    //可见级别
    visible:true,    //是否可见
    opacity:1,       //透明度
    zIndex:0         //叠加层级
});
    var map = new AMap.Map('map-block');
    map.add(layer);
}
var url = 'https://webapi.amap.com/maps?v=1.4.15&key=492be57f6b2cbf2242e927e73b07b1b4&callback=onLoad';
var jsapi = document.createElement('script');
jsapi.charset = 'utf-8';
jsapi.src = url;
document.head.appendChild(jsapi);*/