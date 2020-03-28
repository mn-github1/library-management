<?php 
include '../mysql.inc.php';
include '../config.inc.php';
include '../tool.inc.php';

if (!session_id()) session_start();

$link=connect();

//$t_data = time();
//获取时间
$time = date('Y-m-d H:i');

echo "预约成功";
//更改座位的状态
$query = "update {$_SESSION['room']} set state = '1' where id = {$_SESSION['seat']}";
$result = execute($link, $query);

//在个人信息中写入预约座位信息
$data = "教室:".$_SESSION['room_name']."  "."座位号:".$_SESSION['seat'];
$data = escape($link,$data);
$query = "update user set seat = '{$data}', seat_room = '{$_SESSION['room']}', seat_num = '{$_SESSION['seat']}' where name = '{$_SESSION['name']}'";
$result = execute($link, $query);

//在个人信息中写入预约座位时间
$time = escape($link,$time);
$query = "update user set seat_time = '{$time}' where name = '{$_SESSION['name']}'";
$result = execute($link, $query);

$url = $_SESSION['room'].".php";
?>
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8" />
<?php
$html = <<<A
<meta http-equiv="refresh" content="2;URL={$url}" />
A;
echo $html;
?>
<title>正在跳转中</title>

</head>

<body>

</body>
</html>