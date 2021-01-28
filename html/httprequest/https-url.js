/*!
 * https-url.js for test http request by http module
 * 
 * author: hj; 
 * created at 2021-01-25;
 */

var https = require("https");  
var url="https://api.weixin.qq.com/sns/oauth2/access_token";  
https.get(url, function (res) {  
	var datas = [];  
	var size = 0;  
	res.on('data', function (data) {  
		datas.push(data);  
		size += data.length;  
	//process.stdout.write(data);  
	});  
	res.on("end", function () {  
		var buff = Buffer.concat(datas, size);  
		console.log(buff);  
	});  
}).on("error", function (err) {  
	Logger.error(err.stack)  
	callback.apply(null);  
}); 