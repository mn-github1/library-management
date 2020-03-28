<?php 
/*
功能：楼层选择界面
*/
include 'mysql.inc.php';
include 'config.inc.php';

$link=connect();

?>
<link rel="stylesheet" href="style/css.css" type="text/css">


<div class = "head_index">

	<div class = "lcxz">
		<a href="index.php">首页</a> &gt;<a href="lcxz.php">楼层选择</a> 
	</div>
	
	<div class = "write_o">
		<a href = "perc.php"><?php echo $_COOKIE['stu']['name'];?></a>
		<a href = "login.php">[注销]</a>
	</div>	
	<div class = "clear"> </div>
	<div class = "lcxz_jpg">
		<div >
			<a class = "lcxz_five" href = "lcxz_five.php">五楼</a>	
		</div>
		<div class = "clear"> </div>
		<div  >
			<a class = "lcxz_four" href = "lcxz_four.php">四楼</a>	
		</div>
		<div class = "clear"> </div>
		<div>
			<a  class = "lcxz_three" href = "lcxz_three.php">三楼</a>	
		</div>
		<div class = "clear"> </div>
		<div >
			<a class = "lcxz_two" href = "lcxz_two.php">二楼</a>	
		</div>
	</div>
	
</div>
