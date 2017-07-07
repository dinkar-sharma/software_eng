<?php 
	$authenticated = FALSE;
	session_start();
	$usernameSubmit = $_POST['username'];
	$passwordSubmit = $_POST['password'];

	$contents = file_get_contents('C:\xampp\htdocs\Software-Midterm\members.json');
	$memberArray = json_decode($contents, true);

	if(!empty($memberArray))
	{
		foreach ($memberArray as $member) {
			if ($usernameSubmit == $member['username'] && $passwordSubmit == $member['password']) 
			{
				$authenticated = TRUE;
			}
		}
	}

	if ($authenticated == TRUE) {
		$_SESSION['username'] = $usernameSubmit;
		echo "<p>Congratulations, you are now logged into the site.</p>";
		echo "<p>You will now be redirected into the site.</p>";
		header('Refresh: 1; url=members.php');
	}
	else
	{
		echo "Wrong username or password.";
		echo "<p>Go to <a href=request_access.html>Request Access</a> page.</p>";
	}

 ?>