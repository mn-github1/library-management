<?php
include 'mysql.inc.php';
include 'tool.inc.php';
include 'config.inc.php';

//判断开启session，存储暂时数据
if (!session_id()) session_start();

//连接数据库
$link=connect();
?>

<!DOCTYPE html>
<html> 
<head>
<meta charset = "utf-8" />
<title> 登陆 </title>
<link rel="stylesheet" href="style/css.css" type="text/css">

</head>
<body >
<div class = "head">
	<form method = "post" class="auto">
		<div class="box">
			<div class = "nav_list0">
				登 录
			</div>			
			<div class="box-one active">
				<input type = "text" name = "username" placeholder="请输入账号"/> 
			</div>
			<div class="box-one">
			   <input type = "password" name = "password" placeholder="请输入密码">
			</div>
			<div class="box-one">
			   <input type = "text" name = "vcode" placeholder="请输入验证码">
			</div>
			<div class = "code">
				<img id="vdimgck" src="show_code.php" alt="看不清？点击更换" 
				 style="cursor:pointer" onclick="this.src=this.src+'?'" />			
			</div>
			<div class="box-btn">
				<input type = "submit" name = "submit" value = "登陆" />
			</div>
	<div class = "text">
	<?php 			
		if (isset($_POST['submit'])) {
			if ($_SESSION['vcode'] != $_POST['vcode']) { //判断验证码是否正确
				echo "验证码错误";
			}else {
				escape($link,$_POST);  //数据转义
				$query="select * from user where name='{$_POST['username']}' and password='{$_POST['password']}'";
				$result=execute($link, $query); //查找数据库中是否有这个用户，并和密码相匹配，有的话拿到数据
				if(mysqli_num_rows($result)==1){//如果拿到数据，说明用户名和密码正确
					//设置数据暂存时间，并存储数据
					setcookie('stu[name]',$_POST['username'],time()+5*3600);
					setcookie('stu[pw]',sha1(md5($_POST['pw'])),time()+5*3600);
					/*设置这个登录的会员对于的last_time这个字段为now()*/
					//skip('index.php','ok','登录成功！');
					$_SESSION['name']=$_POST['username'];
					tourl('index.php');//登陆成功，跳转到主界面
					//echo '登陆成功！';
				}else{
					//skip('login.php', 'error', '用户名或密码填写错误！');
					echo '用户名或密码填写错误';
				//	echo $_SESSION['vcode'];
					//echo $src;
				}
			}				
		}
	?>	
	</div>
		</div>
</div>	

</body>
</html>
