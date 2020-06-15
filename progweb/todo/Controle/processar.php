<?php
	include_once 'controle.php';
	$controle = new Controle();
	
	if( isset($_GET['op']) ){
		$op = $_GET['op'];
	}
	$controle->executar($op);
?>
