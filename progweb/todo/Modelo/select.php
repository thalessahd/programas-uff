<?php
    //Extrai as tarefas do BD a partir do id_user e salva elas em um array
	@session_start(); /*Notice: session_start(): A session had already been started 
	- ignoring in C:\xampp\htdocs\thalessa\select.php on line 2*/
	
	include "conexao.php";
	$id_user = $_SESSION['id_user'];
	$sql = "SELECT * FROM todo WHERE id_user=$id_user ORDER BY data";
	$result = $conn->query($sql);
	
	//Vetor das tarefas
	$arrayTask = array();
	
	if($result->num_rows > 0) {
		// output data of each row
		while($row = $result->fetch_assoc()) {
			$task = new Todo();
			$task->setId($row["id"]);
			$task->setNome($row["nome"]);
			$task->setId_user($row["id_user"]);
			$task->setData($row["data"]);
			$task->setRecorrencia($row["recorrencia"]);
			array_push($arrayTask,$task); 
		}
	}
?>