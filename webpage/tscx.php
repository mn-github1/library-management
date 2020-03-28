<?php
/*
功能：图书查询界面
*/ 
include 'mysql.inc.php';
include 'config.inc.php';
//连接数据库
$link=connect();

if (!session_id()) session_start();

if (isset($_POST['submit'])) {//判断是否有提交
	if ($_POST['keyword']) {//判断是否有数据
		@$data = escape($link,$_POST[keyword]); //将数据进行转化
		@$query="select * from book where book like '%{$data}%' ";
		$result=execute($link, $query); //在数据库中进行查询
		$arr_book = execute_array($result);//将所得数据放入数组中
		$num = count($arr_book);//判断有多少个结果
	}
}



?>
<link rel="stylesheet" href="style/jsxz.css" type="text/css">
<link rel="stylesheet" href="style/css.css" type="text/css">
<link rel="stylesheet" href="style/perce.css" type="text/css">

<div class = "head_index">
	<form method = "post" class="auto">
		<div class = "lcxz">
			<a href="index.php">首页</a> &gt;<a href="tscx.php">图书查询</a> 
		</div>
		
		<div class = "write_o">
			<a href = "perc.php"><?php echo $_COOKIE['stu']['name'];?></a>
			<a href = "login.php">[注销]</a>
		</div>	
		<div class = "clear"> </div>
		<div >
			<input class = "seek_text" type = "text" name = "keyword" placeholder="请输入书名" />
		</div>
		<div >
			<input class = "seek_bt" type = "submit" name = "submit" value = "搜索" />
		</div>
		<div class = "clear"> </div>
		<div class = "book_list">
			<div class = "clear"> </div>
			<table class="mt" >		
			<thead>			
				<tr>			
				<td>书名</td>			
				<td>编号</td>
				<td>位置</td>	
				<td>状态</td>
				</tr>		
			</thead>		
			<tbody>
			<?php 
			for ($i = 0; $i < @$num; ++$i) {
				?>
			<tr>			
				<td> <?php echo $arr_book[$i]['book']; ?></td>	
				<td> <?php echo $arr_book[$i]['number']; ?></td>	
				<td> <?php echo $arr_book[$i]['place']; ?></td>
				<td> <?php if ($arr_book[$i]['state'] == '1') {
								echo "借出";
							}else{
								echo "在馆";
							}?>
				</td>
			</tr>				
			<?php
			}
			?>
					
			</tbody>	
		</table>
		</div>
	</form>
</div>
