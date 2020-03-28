<?php 
include_once 'config.inc.php';
include_once 'mysql.inc.php';
include_once 'tool.inc.php';

//连接数据库
$link=connect();
$member_id=is_login($link);
//清楚cookie中的数据
setcookie('sfk[name]','',time()-3600);
setcookie('sfk[pw]','',time()-3600);
//放回到登陆界面
tourl('login.php');
?>