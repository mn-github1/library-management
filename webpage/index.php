<?php 
/*
功能：首页显示界面
*/
include 'mysql.inc.php';
include 'config.inc.php';

//判断开启session，存储暂时数据
if (!session_id()) session_start();

//连接数据库
$link=connect();

?>
<link rel="stylesheet" href="style/css.css" type="text/css">
<link rel="stylesheet" href="style/jsxz.css" type="text/css">

<div class = "head_index">

	<div class = "home_p">
		<a href="index.php">首页</a> 
	</div>
	
	<div class = "write_o">
		<a href = "perc.php"><?php echo @$_COOKIE['stu']['name'];?></a>
		<a href="login.php">[注销]</a> </div>	
	<div class = "clear"> </div>
	<div>	
		<div >
			<a class = "zwyy" href="lcxz.php"> 座位预约</a>
		</div>
		<div class = "clear"> </div>
		<div >
			<a class = "tscx" href="tscx.php">图书查询</a>	
		</div>
	</div>
</div>
