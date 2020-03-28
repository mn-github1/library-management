<?php 
include '../mysql.inc.php';
include '../config.inc.php';
include '../tool.inc.php';

if (!session_id()) session_start();

$link=connect();

echo "取消成功";
//更改座位的状态
$query = "update {$_SESSION['room']} set state = '0' where id = '{$_SESSION['seat']}' ";
$result = execute($link, $query);

//在个人信息中取消预约座位信息
$query = "update user set seat = default, seat_room = default, seat_num = default where name = '{$_SESSION['name']}'";
$result = execute($link, $query);

//在个人信息中取消预约座位时间
$query = "update user set seat_time = default where name = '{$_SESSION['name']}'";
$result = execute($link, $query);

?>
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8" />
<meta http-equiv="refresh" content="2;URL='../perc.php'" />
<title>正在跳转中</title>

</head>

<body>

</body>
</html>