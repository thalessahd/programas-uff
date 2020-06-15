<?php
	include("../Modelo/Todo.php");
	
	class Modelo{
		public function cadastrar(String $nome, String $email, String $senha){
		    //Chave criada com a data atual e salva no BD.
		    $chave_autenticar = md5(date("Y-m-d").$nome);
			include 'conexao.php';
			include 'cadastro.php';
			return $cadastro;
		}
		public function autenticar_conta(String $chave){
		    include 'conexao.php';
		    include 'verifica_autenticar_conta.php'; 
		    return $verifica_autenticar;
		}
		public function logar(String $login, String $senha){
			include 'conexao.php';
			include 'login.php';
			include 'verificacaoLogin.php';
			return $logado;
		}
		public function logout($token){
			include 'logout.php';
			return $logout;
		}
		public function inserir($task){
			include 'conexao.php';
			include 'insere.php';
			return $insere;
		}
		public function deletar($id2del,$data,$rec){
			include 'conexao.php';
			include 'deletar.php';
			return $deletar;
		}
	}
?>
