/*!
 * http_request.js for test http request by http module
 * 
 * author: hj; 
 * created at 2021-01-25;
 */

// 引入内置http https模块
const http = require("http");
const https = require("https");

// 重命名console模块打印日志
const eclog = {"log": console.log, "warn": console.warn, "error": console.error};

/**
 * 重写https.request方法
 * 
 */
https.request = (function(_request) {
    return function(options, callBack) {
        var timeout = options["timeout"], timeoutEventId;
        var req = _request(options, function(res) {
            res.on("end", function() {
                clearTimeout(timeoutEventId);
                eclog.log("response end...");
            });
            
            res.on("close", function() {
                clearTimeout(timeoutEventId);
                eclog.log("response close...");
            });
            
            res.on("abort", function() {
                clearTimeout(timeoutEventId);
                eclog.log("abort...");
            });

            clearTimeout(timeoutEventId);
            callBack(res);
        });
        
        //超时
        req.on("timeout", function() {
            clearTimeout(timeoutEventId);
            if (req.res && req.res.abort) {
                req.res.abort();
            }
            req.abort();
        });
        
        //如果存在超时
        timeout && (timeoutEventId=setTimeout(function() {
            req.emit("timeout", {message:"have been timeout..."});
        },timeout));
        return req;
    };
})(https.request)

/**
 * 重写http.request方法
 * 
 */
http.request = (function(_request) {
    return function(options, callBack) {
        var timeout = options["timeout"], timeoutEventId;
        var req = _request(options, function(res) {
            res.on("end", function() {
                clearTimeout(timeoutEventId);
                eclog.log("response end...");
            });
            
            res.on("close", function() {
                clearTimeout(timeoutEventId);
                eclog.log("response close...");
            });
            
            res.on("abort", function() {
                clearTimeout(timeoutEventId);
                eclog.log("abort...");
            });

            clearTimeout(timeoutEventId);
            callBack(res);
        });
        
        //超时
        req.on("timeout", function() {
            clearTimeout(timeoutEventId);
            if (req.res && req.res.abort) {
                req.res.abort();
            }
            req.abort();
        });
        
        //如果存在超时
        timeout && (timeoutEventId=setTimeout(function() {
            req.emit("timeout", {message:"have been timeout..."});
        },timeout));
        return req;
    };
})(http.request)

// http https信息 
// http://dev.kdlapi.com/testproxy 123.206.71.35:80 不能使用ip地址访问
// https://dev.kdlapi.com/testproxy
const options = {
    host    : "dev.kdlapi.com",
    port    : "443",
    path    : "/testproxy",
    method  : "GET",
	timeout : 3000,
};

var req = https.request(options, function(res) {
	console.log("STATUS: " + res.statusCode);
	console.log("HEADERS: " + JSON.stringify(res.headers));
	console.log("LOCATION: " + JSON.stringify(res.headers.location));
	res.on("data", function (chunk) {
	console.log("BODY: " + chunk);
	});
});

req.on("error",function(e) {
	if (e == undefined) {
		console.log("error");
	} else {
		console.log("error got :"+e.message);
	}
}).on("timeout",function(e) {
	if (e == undefined) {
		console.log("timeout");
	} else {
		console.log("timeout got :"+e.message);
	}
});

req.end();