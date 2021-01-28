/*!
 * test-js.js for test http request by http module
 * 测试js nodejs代码 
 *
 * author: hj; 
 * created at 2021-01-26;
 */
 
 // 重命名console模块打印日志
const eclog = {"log": console.log, "warn": console.warn, "error": console.error};

var url = "http://192.168.5.69:443/index.html";
eclog.log("url [ %s ].", url);

//去掉头部http://或者https://
var index = url.indexOf("://");
var ishttp = false;
if (index != -1) {
	var header = url.slice(0, index);
	url = url.slice(index+3);
	if (header == "http") {
		ishttp = true;
	}
}
eclog.log("drop header's url[ %s ], header [ %s ] is http [ %s ].", url, header, ishttp);


/**
 * 判断是否是https开头
 * 
 * @param {in} url 输入的中心管理地址
 */
function isHttpsAddr(url) {
	return url.startsWith("https://");
}

/**
 * 判断是否是http开头
 * 
 * @param {in} url 输入的中心管理地址
 */
function isHttpAddr(url) {
	return url.startsWith("http://");
}

url = "https://192.168.5.69:443/index.html";
if (isHttpAddr(url)) {
	url = url.slice(7);
	eclog.log("drop [http://] header, url: %j.", url);
}

// 传入时 host 与 port 在一个字符串中,需要解析
var arr = url.split("/");
var host = arr[0];
// http请求默认端口是80
var httpport = "80";
// https请求默认端口是443
var httpsport = "443";

var index = arr[0].indexOf(":");
if (index !== -1) {
	host = arr[0].slice(0, index);
	httpport = arr[0].slice(index+1);
	httpsport = httpport;
}
index = url.indexOf(arr[0]);
var moudlepath = url.slice(index+arr[0].length)
eclog.log("host: %j, httpport: %j, httpsport: %j, moudlepath: %j.", host, httpport, httpsport, moudlepath);

// 修改传参函数值不会有异步问题，全局变量会有异步问题?
var value = 123;
eclog.log("value = %s.", value);

function sleep(callback, time) {
  if (typeof callback == "function") {
    setTimeout(callback, time);
  }
}
function output() {
  console.log(1);
}

var result = (function(_value) {
	eclog.log("_value = %s.", _value);
	sleep(output, 2000);
	_value = 321;
	value = 321;
	eclog.log("_value = %s.", _value);
	return _value;
})(value)

eclog.log("result = %s.", result);
eclog.log("value = %s.", value);

// 难道是需要回调函数才能有异步问题?





