<?php
    //Se a chave passada pelo link(que foi enviado pelo email) for igual a chave salva no BD então a conta é verificada
	$sql = "SELECT * FROM usuario WHERE autenticar='$chave';";
	$result = $conn->query($sql);
	
	if($result->num_rows > 0) {
	    $row = $result->fetch_assoc();
	    $id = $row["id_user"];
	    $sql = "UPDATE usuario SET autenticar='TRUE' WHERE id_user=$id;";
	    $result = $conn->query($sql);
	    $verifica_autenticar = true;   
	}
	else{
	    $verifica_autenticar = false;   
	}
?>
