<?php
	$servername = "localhost";
	$username = "id9495374_myadmin";
	$password = "myadmin";
	$dbname = "id9495374_meutodo";

	// Create connection
	$conn = new mysqli($servername, $username, $password, $dbname);
	// Check connection
	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	}
	//else
		//echo "Connected successfully<br>"; 
?>