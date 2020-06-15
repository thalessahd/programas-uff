<?php 
    session_start();
	$data_atual = date("Y-m-d"); //Pegar data atual
		
	//Se $rec=0 OU
	//Se data_atual for menor que a data da tarefa só deleta a tarefa
	if($rec==0 || $data_atual<$data){
		//sql to delete a record
		$sql = "DELETE FROM todo WHERE id= $id2del";
		if ($conn->query($sql) == TRUE) {
			//echo "Deletado com sucesso";
			$deletar = true;
		} else {
			echo "Error deleting record: " . $conn->error;
			$deletar = false;
		}
	}
	//Se $rec!=0 e data atual maior que a data da tarefa realiza update na data da tarefa
	else if($rec!=0 && $data_atual>=$data){
		switch($rec){
			case 1: //Diario
				$data =  date('Y-m-d', strtotime('+1 days', strtotime($data)));	
			break;
			case 2: //Semanal
				$data =  date('Y-m-d', strtotime('+7 days', strtotime($data)));	
			break;
			case 3: //Mensal
				$data =  date('Y-m-d', strtotime('+1 month', strtotime($data)));	
			break;
		}
		$sql = "UPDATE todo SET data = '$data' WHERE id =". $id2del;
		if ($conn->query($sql) == TRUE) {
			//echo "Alterado com sucesso";
			$deletar = true;
		} else {
			echo "Error update record:  " . $conn->error;
			$deletar = false;
		}
	}
?>