<?php 

include '../mysql.inc.php';
include '../config.inc.php';
include '../tool.inc.php';

//连接数据库
$link=connect();
if (!session_id()) session_start();

//获得该教室的座位和插座的信息
$query="select * from sheke1";
$result=execute($link, $query);
$arr = execute_array($result);

//获得用户的信息
$query="select seat from user where name = '{$_SESSION['name']}' ";
$result=execute($link, $query);
$arr_user = execute_array($result);

if(isset($_POST['submit'])){
	$_SESSION['seat']=$_POST['submit'];//座位的位置
	$_SESSION['room']="sheke1";		//教室的数据库表名
	$_SESSION['room_name'] = "社会科学(1)";//教室的名字
	if ($arr[$_POST['submit']-1]['state'] != '1') { //座位从1开始排列，数组从0开始排列:$_POST['submit']-1
		if ($arr_user[0]['seat'] == NULL) { 	//判断是否已经预约了座位
			confirm("sheke1.php");
		}
	}
}

?>
<link rel="stylesheet" href="../style/css.css" type="text/css">
<link rel="stylesheet" href="../style/jsxz.css" type="text/css">


<div class = "head_index">

	<div class = "zwxz">
		<a href="../index.php">首页</a> &gt;<a href="../lcxz.php">楼层选择</a> &gt;
		<a href="../lcxz_two.php">二楼</a> &gt; <a href="sheke1.php">社会科学(1)</a>
	</div>
	
	<div class = "write_o">
		<a href = "../perc.php"><?php echo $_COOKIE['stu']['name'];?></a>
		<a href = "../login.php">[注销]</a>
	</div>	
	<div class = "clear"> </div>
	<form method = "post" class="auto">
	
	<div class = "sk1_1">
		<?php if ($arr[32]['state'] == '1') { ?>
				<so class = "socket">插座</so>	
		<?php }else { ?>
				<so class = "socket_bad">插座</so>	
		<?php } ?>
	</div>
	<div class = "clear"> </div>
	<!--由于数组下标从0开始，座位标号从1开始，所以下面的判断为所有的下标减一-->
	<div class = "zw_start">
		<div >
			<?php if ($arr[0]['state'] == '0') { ?>
				<input class = "zw" type = "submit" name = "submit" value = "1" />
			<?php }else { ?>
				<input class = "zw_y" type = "submit" name = "submit" value = "1" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[7]['state'] == '0') { ?>
				<input class = "zw" type = "submit" name = "submit" value = "8" />
			<?php }else { ?>
				<input class = "zw_y" type = "submit" name = "submit" value = "8" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[8]['state'] == '0') { ?>
				<input class = "zw_p" type = "submit" name = "submit" value = "9" />
			<?php }else { ?>
				<input class = "zw_p_y" type = "submit" name = "submit" value = "9" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[15]['state'] == '0') { ?>
				<input class = "zw" type = "submit" name = "submit" value = "16" />
			<?php }else { ?>
				<input class = "zw_y" type = "submit" name = "submit" value = "16" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[16]['state'] == '0') { ?>
				<input class = "zw_p" type = "submit" name = "submit" value = "17" />
			<?php }else { ?>
				<input class = "zw_p_y" type = "submit" name = "submit" value = "17" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[23]['state'] == '0') { ?>
				<input class = "zw" type = "submit" name = "submit" value = "24" />
			<?php }else { ?>
				<input class = "zw_y" type = "submit" name = "submit" value = "24" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[24]['state'] == '0') { ?>
				<input class = "zw_p" type = "submit" name = "submit" value = "25" />
			<?php }else { ?>
				<input class = "zw_p_y" type = "submit" name = "submit" value = "25" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[31]['state'] == '0') { ?>
				<input class = "zw" type = "submit" name = "submit" value = "32" />
			<?php }else { ?>
				<input class = "zw_y" type = "submit" name = "submit" value = "32" />
			<?php } ?>
		</div>
		<div class = "clear"> </div>
		<div >
			<?php if ($arr[1]['state'] == '0') { ?>
				<input class = "zw_p" type = "submit" name = "submit" value = "2" />
			<?php }else { ?>
				<input class = "zw_y" type = "submit" name = "submit" value = "2" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[6]['state'] == '0') { ?>
				<input class = "zw" type = "submit" name = "submit" value = "7" />
			<?php }else { ?>
				<input class = "zw_y" type = "submit" name = "submit" value = "7" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[9]['state'] == '0') { ?>
				<input class = "zw_p" type = "submit" name = "submit" value = "10" />
			<?php }else { ?>
				<input class = "zw_p_y" type = "submit" name = "submit" value = "10" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[14]['state'] == '0') { ?>
				<input class = "zw" type = "submit" name = "submit" value = "15" />
			<?php }else { ?>
				<input class = "zw_y" type = "submit" name = "submit" value = "15" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[17]['state'] == '0') { ?>
				<input class = "zw_p" type = "submit" name = "submit" value = "18" />
			<?php }else { ?>
				<input class = "zw_p_y" type = "submit" name = "submit" value = "18" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[22]['state'] == '0') { ?>
				<input class = "zw" type = "submit" name = "submit" value = "23" />
			<?php }else { ?>
				<input class = "zw_y" type = "submit" name = "submit" value = "23" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[25]['state'] == '0') { ?>
				<input class = "zw_p" type = "submit" name = "submit" value = "26" />
			<?php }else { ?>
				<input class = "zw_p_y" type = "submit" name = "submit" value = "26" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[30]['state'] == '0') { ?>
				<input class = "zw" type = "submit" name = "submit" value = "31" />
			<?php }else { ?>
				<input class = "zw_y" type = "submit" name = "submit" value = "31" />
			<?php } ?>
		</div>
		<div class = "clear"> </div>
		<div >
			<?php if ($arr[2]['state'] == '0') { ?>
				<input class = "zw" type = "submit" name = "submit" value = "3" />
			<?php }else { ?>
				<input class = "zw_y" type = "submit" name = "submit" value = "3" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[5]['state'] == '0') { ?>
				<input class = "zw" type = "submit" name = "submit" value = "6" />
			<?php }else { ?>
				<input class = "zw_y" type = "submit" name = "submit" value = "6" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[10]['state'] == '0') { ?>
				<input class = "zw_p" type = "submit" name = "submit" value = "11" />
			<?php }else { ?>
				<input class = "zw_p_y" type = "submit" name = "submit" value = "11" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[13]['state'] == '0') { ?>
				<input class = "zw" type = "submit" name = "submit" value = "14" />
			<?php }else { ?>
				<input class = "zw_y" type = "submit" name = "submit" value = "14" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[18]['state'] == '0') { ?>
				<input class = "zw_p" type = "submit" name = "submit" value = "19" />
			<?php }else { ?>
				<input class = "zw_p_y" type = "submit" name = "submit" value = "19" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[21]['state'] == '0') { ?>
				<input class = "zw" type = "submit" name = "submit" value = "22" />
			<?php }else { ?>
				<input class = "zw_y" type = "submit" name = "submit" value = "22" />
			<?php } ?>
		</div>	
		<div >
			<?php if ($arr[26]['state'] == '0') { ?>
				<input class = "zw_p" type = "submit" name = "submit" value = "27" />
			<?php }else { ?>
				<input class = "zw_p_y" type = "submit" name = "submit" value = "27" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[29]['state'] == '0') { ?>
				<input class = "zw" type = "submit" name = "submit" value = "30" />
			<?php }else { ?>
				<input class = "zw_y" type = "submit" name = "submit" value = "30" />
			<?php } ?>
		</div>
		<div class = "clear"> </div>
		<div >
			<?php if ($arr[3]['state'] == '0') { ?>
				<input class = "zw" type = "submit" name = "submit" value = "4" />
			<?php }else { ?>
				<input class = "zw_y" type = "submit" name = "submit" value = "4" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[4]['state'] == '0') { ?>
				<input class = "zw" type = "submit" name = "submit" value = "5" />
			<?php }else { ?>
				<input class = "zw_y" type = "submit" name = "submit" value = "5" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[11]['state'] == '0') { ?>
				<input class = "zw_p" type = "submit" name = "submit" value = "12" />
			<?php }else { ?>
				<input class = "zw_p_y" type = "submit" name = "submit" value = "12" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[12]['state'] == '0') { ?>
				<input class = "zw" type = "submit" name = "submit" value = "13" />
			<?php }else { ?>
				<input class = "zw_y" type = "submit" name = "submit" value = "13" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[19]['state'] == '0') { ?>
				<input class = "zw_p" type = "submit" name = "submit" value = "20" />
			<?php }else { ?>
				<input class = "zw_p_y" type = "submit" name = "submit" value = "20" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[20]['state'] == '0') { ?>
				<input class = "zw" type = "submit" name = "submit" value = "21" />
			<?php }else { ?>
				<input class = "zw_y" type = "submit" name = "submit" value = "21" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[27]['state'] == '0') { ?>
				<input class = "zw_p" type = "submit" name = "submit" value = "28" />
			<?php }else { ?>
				<input class = "zw_p_y" type = "submit" name = "submit" value = "28" />
			<?php } ?>
		</div>
		<div >
			<?php if ($arr[28]['state'] == '0') { ?>
				<input class = "zw" type = "submit" name = "submit" value = "29" />
			<?php }else { ?>
				<input class = "zw_y" type = "submit" name = "submit" value = "29" />
			<?php } ?>
		</div>
		<div class = "clear"> </div>
	</div>
	<div class = "sk1_2">
			<?php if ($arr[33]['state'] == '1') { ?>
				<so class = "socket">插座</so>	
			<?php }else { ?>
				<so class = "socket_bad">插座</so>	
			<?php } ?>
	</div>
	</form>
</div>
