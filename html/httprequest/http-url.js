const http = require("http");  // 引入内置http模块
const url  = require("url");


// 要访问的目标页面
const targetUrl = "http://dev.kdlapi.com/testproxy";
const urlParsed   = url.parse(targetUrl);

// 代理ip,由快代理提供
const proxyIp = "47.115.36.94";  // 代理服务器ip
const proxyPort = "16816"; // 代理服务器host

// http代理验证信息
const options = {
    host    : proxyIp,
    port    : proxyPort,
    path    : targetUrl,
    method  : "GET",
    headers : {
        "Host"                : urlParsed.hostname,
    }
};

http.request(options,  (res) => {
        console.log("got response: " + res.statusCode);
        // 输出返回内容(使用了gzip压缩)
        if (res.headers['content-encoding'] && res.headers['content-encoding'].indexOf('gzip') != -1) {
            let zlib = require('zlib');
            let unzip = zlib.createGunzip();
            res.pipe(unzip).pipe(process.stdout);
        } else {
            // 输出返回内容(未使用gzip压缩)
            res.pipe(process.stdout);
        }
    })
    .on("error", (err) => {
        console.log(err);
    })
    .end()
;