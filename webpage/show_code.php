<?php 
/*
功能：调用验证码生成函数，显示验证码
*/
session_start();
include_once 'ver_code.php';
$_SESSION['vcode']=vercode();
?>