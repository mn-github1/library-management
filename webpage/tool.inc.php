<?php 
//间接跳转函数
function skip($url,$pic,$message){
$html=<<<A
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8" />
<meta http-equiv="refresh" content="3;URL={$url}" />
<title>正在跳转中</title>
<link rel="stylesheet" type="text/css" href="style/remind.css" />
</head>
<body>
<div class="notice"><span class="pic {$pic}"></span> {$message} <a href="{$url}">3秒后自动跳转中!</a></div>
</body>
</html>
A;
echo $html;
exit();
}
//直接跳转函数
function tourl($url) {
	header('Location:'.$url);
}
//确认预约函数
function confirm($url){
$html=<<<A
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8" />
<title>正在跳转中</title>

</head>
<script> 
if(confirm( '确认预约')) 
	location.href='yycg.php';
else 
	location.href="$url"; 
</script>
<body>

</body>
</html>
A;
echo $html;
exit();
}
//取消预约函数
function cancel($url){
$html=<<<A
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8" />
<title>正在跳转中</title>

</head>
<script> 
if(confirm( '取消预约')) 
	location.href='room/qxcg.php';
else 
	location.href="$url"; 
</script>
<body>

</body>
</html>
A;
echo $html;
exit();
}

?>