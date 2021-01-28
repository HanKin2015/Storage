/**
 * linehandler_test.js for vdi 5.4.5R1; 
 * author: hj; 
 * created at 2021-01-20;
 */

// 导入eclog模块
var eclog = {"log": console.log, "warn": console.warn, "error": console.error};

// =========== 分割线:上面的不需要拷贝 ===========

const http = require("http");
const url = require("url");
// 全局变量
var isCancel = false;

/**
 * 判断是否是https开头
 * 
 * @param {in} url 多线路页面url
 */
function isHttpsAddr(url) {
    var ret = url.indexOf("https://");
    if (ret == 0) {
        return true;
    }
    return false;
}

/**
 * 判断是否是http开头
 * 
 * @param {in} url 多线路页面url
 */
function isHttpAddr(url) {
    var ret = url.indexOf("http://");
    if (ret == 0) {
        return true;
    }
    return false;
} 

/**
 * 通过请求url页面，获取线路信息总入口。此方法会调用网络连接， 不要在主线程下执行，否则android3.0以上会报错。
 *
 * @param {in} url 多线路页面url
 */
function handle(url) {
    eclog.log('======== line handler ========');

    // 每次进来都要重装下
    isCancel = false;
    // 如果用户输入的是https开头的就不用去选路了
    if (isHttpsAddr(url)) {
        // 回调成功接口
        //successListener(getHttpsAddr(url));
        eclog.log("url[%s] is [https://] header.", url);
        return;
    }

    handleSelf(url, function(vdc_url){
        // 请求该地址判断是否可达
        console.log(vdc_url);
    });
}

/**
 * 通过请求url页面，获取线路信息
 *
 * @param {in} url 多线路页面url
 * @param {out} cb 线路信息回调函数
 */
function handleSelf(url, callback) {
    if (url == null || url == "") {
        eclog.warn("input url is empty.");

        // 回调失败接口,url为空
        //errorListener(General.LINE_ERROR_CODE_URL_EMPTY);
        return;
    }
    var tmpUrl = url;
    var content = "";

    // 不是http://或https://开头要加上http://
    if (!isHttpAddr(url) && !isHttpsAddr(url)) {
        tmpUrl = "http://" + url;
        eclog.log("add [http://] header, url: %s, tmpUrl: %s.", url, tmpUrl);
    }

    if (isCancel) {
        eclog.log("isCancel: true.");
        return;
    }

    while (true) {
        try {
            var options = 
            {
                host : "10.70.253.163",
                port : "80",
                path : "/webagent/normal1.php",
                method : 'GET',
            }
            http.request(options, function(res) {
                callback(res.headers.location);
            }).end();
            eclog.log("requestStringWithURL: %s.", tmpUrl);
        } catch (ee) {
            eclog.log("request URL Exception: %s.", ee);
        }

        if (content != null && content.length > 0) {
            eclog.log("get content[%s].", content);
            break;
        }

        // 获取不到时，如果是http请求，就尝试https请求
        if (isHttpsAddr(tmpUrl)) {
            break;
        }

        //eclog.log("http connection refused, try to connect https.");

        //StringBuilder sb = new StringBuilder(tmpUrl);
        // 把http转成https，在第四为插入s
        //tmpUrl = tmpUrl.slice(0, 4) + "s" + tmpUrl.slice(4);
        //eclog.log("[http://] header convert to [https://] header, tmpUrl: %s.", tmpUrl);
        
        break;
    }

    // 开始选路
    //handleWithPageContent(content);
    eclog.log("next step");
}














