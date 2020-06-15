<?php
	// Verificação se o usuário está logado
	if($login){
	    if($_SESSION['autenticar']=="TRUE"){
		    $logado = 1; //tudo certo
	    }
	    else{
            unset($_SESSION['login']);
	    	unset($_SESSION['senha']);
	        $logado=2; //não está autenticado
	    }
	}
	else{
		unset($_SESSION['login']);
		unset($_SESSION['senha']);
		unset($_SESSION['id_user']);
		unset($_SESSION['autenticar']);
		$logado=0; //login ou senha errados
	}
?>