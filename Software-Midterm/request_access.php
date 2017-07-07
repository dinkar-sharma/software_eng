<?php 
	$usernameSubmit = $_POST['username'] ?? '';
	$passwordSubmit = $_POST['password'];
	$exists = false;

	$contents = file_get_contents('C:\xampp\htdocs\Software-Midterm\members.json');

	$memberArray= json_decode($contents, true);

	// foreach ($memberArray as $key => $member) {
	// 	if(isset($member[$key]) && $member[$key] == $usernameSubmit)
	// 		$exists = true;
	// }

	// if($exists == false)
	// {
		$memberArray[] = array('username' => $usernameSubmit, 'password' => $passwordSubmit);

		if(!empty($memberArray))
		{
			$memberArrayJson = json_encode($memberArray, true);
			file_put_contents('C:\xampp\htdocs\Software-Midterm\members.json', $memberArrayJson);
			echo "<p>Successfully signed up! Redirecting you to login page.</p>";
			header('Refresh: 1; url=login.html');
		}
	// }
	else
	{
		echo "Member already exists!";
	}
 ?>