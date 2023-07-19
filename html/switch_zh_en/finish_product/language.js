/*
  语言转换函数
  参考来源网络
  2023-07-19 by hj
*/
function toLang(lang) {
    var baseUrl = window.location.pathname;
    //alert(baseUrl);
    //alert(document.body.className);
    var isEn = baseUrl.slice(-7, -5);
    //alert(isEn);
    if (lang === "en_US" && isEn !== "en") {
        window.location.href = baseUrl.slice(0, -5) + '-en.html';
        document.body.className = "en_US";
    } else if (lang === "zh_CN" && isEn === "en") {
        window.location.href = baseUrl.slice(0, -8) + '.html';
        document.body.className = "zh_CN";
    }
    //window.location.reload();
}