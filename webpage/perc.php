<?php 

include 'mysql.inc.php';
include 'config.inc.php';
include 'tool.inc.php';

//连接数据库
$link=connect();
if (!session_id()) session_start();

//获得用户的信息
$query="select * from user where name = '{$_SESSION['name']}' ";
$result=execute($link, $query);
$arr_user = execute_array($result);

if (isset($_POST['cancel'])) {
	if ($arr_user[0]['seat'] != NULL) {
		$_SESSION['seat']=$arr_user[0]['seat_num'];//座位的位置
		$_SESSION['room']=$arr_user[0]['seat_room'];//教室的数据库表名
		cancel("perc.php");
	}
}

?>

<link rel="stylesheet" href="style/css.css" type="text/css">
<link rel="stylesheet" href="style/jsxz.css" type="text/css">
<link rel="stylesheet" href="style/perce.css" type="text/css">

<div class = "head_index">

	<div class = "zwxz">
		<a href="index.php">首页</a> &gt;<a href="perc.php">个人中心</a> 
	</div>
	
	<div class = "write_o">
		<a href = "perc.php"><?php echo @$_COOKIE['stu']['name'];?></a>
		<a href = "login.php">[注销]</a>
	</div>	
	<div class = "clear"> </div>
	<form method = "post" class="auto">
	<div class = "text_per">
		<b >姓名:
		<?php 
			echo $arr_user[0]['name'];
		?>
		</b>
	</div>
	<div class = "clear"> </div>
	<div class = "text_a">
		<b>座位预约:
		<?php 
			if ($arr_user[0]['seat'] != NULL) {
				echo $arr_user[0]['seat'];
			} 
		?>
		</b>
	</div >
	<div>
		<a> <input class = "sub_cancel" type = "submit" name = "cancel" value = "取消预约" /> </a>
	</div>
	<div class = "clear"> </div>
	<div class = "text_a">
		<b>预约时间:
		<?php 
			if ($arr_user[0]['seat_time'] != NULL) {
				echo $arr_user[0]['seat_time'];
			} 
		?>
		</b>
	</div >
	<div class = "clear"> </div>
	<div class = "text_a">
		<b>图书借阅:</b>
		<div class = "clear"> </div>
		<table class="mt">		
			<thead>			
				<tr>			
				<td>书名</td>			
				<td>借阅时间</td>			
				</tr>		
			</thead>		
			<tbody>		
			<tr>			
				<td>
				<?php if ($arr_user[0]['book1'] != NULL) {
					echo $arr_user[0]['book1'];
				} 
				?>
				</td>		
				<td>
				<?php if ($arr_user[0]['book_time1'] != NULL) {
					echo $arr_user[0]['book_time1'];
				} 
				?>
				</td>				
			</tr>		
			<tr>			
				<td>
				<?php if ($arr_user[0]['book2'] != NULL) {
					echo $arr_user[0]['book2'];
				} 
				?>
				</td>		
				<td>
				<?php if ($arr_user[0]['book_time2'] != NULL) {
					echo $arr_user[0]['book_time2'];
				} 
				?>
				</td>		
			</tr>		
			<tr>			
				<td>
				<?php if ($arr_user[0]['book3'] != NULL) {
					echo $arr_user[0]['book3'];
				} 
				?>
				</td>		
				<td>
				<?php if ($arr_user[0]['book_time3'] != NULL) {
					echo $arr_user[0]['book_time3'];
				} 
				?>
				</td>	
			</tr>		
			<tr>			
				<td>
				<?php if ($arr_user[0]['book4'] != NULL) {
					echo $arr_user[0]['book4'];
				} 
				?>
				</td>		
				<td>
				<?php if ($arr_user[0]['book_time4'] != NULL) {
					echo $arr_user[0]['book_time4'];
				} 
				?>
				</td>	
			</tr>	
			<tr>		
				<td>
				<?php if ($arr_user[0]['book5'] != NULL) {
					echo $arr_user[0]['book5'];
				}
				?>
				</td>		
				<td>
				<?php if ($arr_user[0]['book_time5'] != NULL) {
					echo $arr_user[0]['book_time5'];
				} 
				?>
				</td>
			</tr>	
			</tbody>	
		</table>

	</div>
	
	
	
	</form>
</div>
	
	
	
	
	
	