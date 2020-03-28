<?php 
/*
功能：二楼的教室的显示界面
*/
include 'mysql.inc.php';
include 'config.inc.php';
//连接数据库
$link=connect();

?>
<link rel="stylesheet" href="style/css.css" type="text/css">
<link rel="stylesheet" href="style/jsxz.css" type="text/css">


<div class = "head_index">

	<div class = "jsxz">
		<a href="index.php">首页</a> &gt;<a href="lcxz.php">楼层选择</a> &gt;<a href="lcxz_two.php">二楼</a> 
	</div>
	
	<div class = "write_o">
		<a href = "perc.php"><?php echo $_COOKIE['stu']['name'];?></a>
		<a href = "login.php">[注销]</a> </div>	
	<div class = "clear"> </div>
	<div >
		<div>
			<a class = "two_sheke1" href = "room/sheke1.php">社会科学(1)</a>
		</div>
		<div >
			<a class = "two_sheke2" href = "room/sheke2.php">社会科学(2)</a>
		</div>
		<div class = "clear"> </div>
		<div>
			<a class = "two_sheke3" href = "room/sheke3.php">社会科学(3)</a>
		</div>
		<div>
			<a class = "two_sheke4" href = "room/sheke4.php">社会科学(4)</a>
		</div>
	</div>
	
</div>
