// JavaScript Document

var map = new BMap.Map("content");          // 创建地图实例
var point = new BMap.Point(113.411973, 23.05489);  // 创建点坐标
map.centerAndZoom(point, 18);               //以该点为中心，缩放等级为18
map.enableScrollWheelZoom(true);            //利用鼠标滚轮控制缩放
map.addControl(new BMap.NavigationControl());//缩放平移控件
map.addControl(new BMap.ScaleControl());    //比例尺
map.addControl(new BMap.OverviewMapControl());//缩略图