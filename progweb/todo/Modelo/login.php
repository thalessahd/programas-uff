<?php 
	// session_start inicia a sessão
	session_start();
	include 'conexao.php'; // conectar com o bando de dados.

	//criptografia
	$senha = md5($senha);
	
	$sql = "SELECT * FROM usuario WHERE NOME = '$login' AND SENHA= '$senha'";
	$result = $conn->query($sql);
    
	if ($result->num_rows > 0) { //sucesso no login
		$_SESSION['login'] = $login;
		$_SESSION['senha'] = $senha;
		
		while($row = $result->fetch_assoc()){
			$_SESSION['id_user'] = $row["id_user"];
			$_SESSION['autenticar'] = $row["autenticar"];
		}
		$login = true;
	} else { //falha no login
		unset ($_SESSION['login']);
		unset ($_SESSION['senha']);
		$login = false;
	}
?>