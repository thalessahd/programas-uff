<?php
    //Salva o usuário no BD e envia o email de confirmação
	if($nome!=null && $email!=null && $senha!=null){
		//criptografia
		$senha = md5($senha);
		
		$sql = "INSERT INTO usuario (nome,email,senha,autenticar)
		VALUES ('$nome','$email','$senha','$chave_autenticar')";

		if ($conn->query($sql) === TRUE) {
			$cadastro = 1; //tudo certo
			include 'confirmacaoEmailCadastro.php';
		} else {
			//echo "Error: " . $sql . "<br>" . $conn->error;
			$cadastro = 3; //erro no bd
		}
	}
	else{
		$cadastro = 2; //campos inválidos ou em branco
	}
?>