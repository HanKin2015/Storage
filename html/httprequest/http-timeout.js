// 引入内置http模块
const http = require("http");  
const https = require("https"); 

// 要访问的目标页面
const targeturl = "https://121.12.76.25:443/por/login_psw.csp";
//http://127.0.0.1:8000/index.html


// https信息
const options = {
    host    : "121.12.76.25",
    port    : "443",
    path    : "/por/login_psw.csp",
    method  : "GET",
};

// http信息
const option = {
    host    : "127.0.0.1",
    port    : "8000",
    path    : "/index.html",
    method  : "GET",
};

http.request(option,  (res) => {
        console.log("got response: " + res.statusCode);
		console.log("%s", res);
		// 输出返回内容(使用了gzip压缩)
        if (res.headers['content-encoding'] && res.headers['content-encoding'].indexOf('gzip') != -1) {
            let zlib = require('zlib');
            let unzip = zlib.createGunzip();
            res.pipe(unzip).pipe(process.stdout);
        } else {
            // 输出返回内容(未使用gzip压缩)
            res.pipe(process.stdout);
        }
		console.error("location: %s.", res.headers.location);
    })
    .on("error", (err) => {
        console.log("There are some error, %s.", err.message);
    })
    .end()
;