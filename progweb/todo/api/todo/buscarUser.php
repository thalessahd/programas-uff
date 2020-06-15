<?php
	// required headers
	header("Access-Control-Allow-Origin: *");
	header("Content-Type: application/json; charset=UTF-8");
	 
	// include database and object files
	include_once '../config/database.php';
	include_once '../objects/todo.php';
	 
	// instantiate database and todo object
	$database = new Database();
	$db = $database->getConnection();
	 
	// initialize object
	$todo = new Todo($db);

	// set NOME_USUARIO property of record to read
	$todo->nome_usuario = isset($_GET['usuario']) ? $_GET['usuario'] : die();
	
	$usuario = $_GET['usuario'];
	 
	// query todo
	$stmt = $todo->buscarUser();
	$num = $stmt->rowCount();
	 
	// check if more than 0 record found
	if($num>0){
	 
		// todo array
		$todo_arr=array();
		$todo_arr[$usuario]=array();
	 
		// retrieve our table contents
		while ($row = $stmt->fetch(PDO::FETCH_ASSOC)){
			// extract row
			extract($row);
	 
			$todo_item=array(
				"id" => $id,
				"tarefa" => $nome,
				"id_user" => $id_user,
				"data" => $data,
				"recorrencia" => $todo->getRecorrencia($recorrencia)
			);
	
			array_push($todo_arr[$usuario], $todo_item);
			
		}
	 
		// set response code - 200 OK
		http_response_code(200);
	 
		// show todo data in json format
		echo json_encode($todo_arr, JSON_PRETTY_PRINT);
	} 
	else{
	 
		// set response code - 404 Not found
		http_response_code(404);
	 
		// tell the user no todo found
		echo json_encode(
			array("message" => "Usuario does not exist.")
		);
	}
?>