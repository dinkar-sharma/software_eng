<?php 
	session_start();

	if(isset($_SESSION['username']))
	{
		echo "Welcome, ". $_SESSION['username'];
		echo "<p>Click here to <a href=logout.php>Logout.</a></p>";
	}
	else
	{
		echo "You are not authorized!";
	}

 ?>