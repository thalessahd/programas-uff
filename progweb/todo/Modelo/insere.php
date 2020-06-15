<?php
	session_start();
	if(isset($_SESSION['id_user'])){
    	$id_user = $_SESSION['id_user'];
    	$insere = true;
    	
    	$task->setId_user($id_user);	
    	$tarefa = $task->getNome();
    	$id_user = $task->getId_user();
    	$date = $task->getData();
    	$recorrencia = $task->getRecorrencia();
    	
    	if($tarefa!=null){
    		$sql = "INSERT INTO todo (nome,id_user,data,recorrencia)
    		VALUES ('$tarefa',$id_user,'$date',$recorrencia)";
    
    		if ($conn->query($sql) === TRUE) {
    			//echo "New record created successfully<br>";
    			$insere = true;
    		} else {
    			echo "Error: $sql <br> $conn->error";
    		}
    	}
	}
	else{
	    $insere = false;   
	}
?>