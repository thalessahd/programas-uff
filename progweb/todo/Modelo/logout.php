<?php
    //Encerra a sessão de um usuário
	session_start();
	$token2 = md5(session_id());
	if($token === $token2) {
		// limpe tudo que for necessário na saída.
		session_destroy();
		$logout = true;
	} else {
		$logout = false;
	}
	return $logout;
?>