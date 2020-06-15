<?php
	class Todo{
 
    // database connection and table name
    private $conn;
    private $table_name = "todo";
 
    // object properties
 	private $id;
	private $nome;
	private $id_user;
	private $data;
	private $recorrencia;
	
	// atributo auxiliar
	public $nome_usuario;
 
    // constructor with $db as database connection
    public function __construct($db){
        $this->conn = $db;
    }
	// read tarefas
	function read(){
 
		// select all query
		$query = "SELECT
					*
				FROM
					" . $this->table_name . " ";
	 
		// prepare query statement
		$stmt = $this->conn->prepare($query);
	 
		// execute query
		$stmt->execute();
	 
		return $stmt;
	}
	// read tarefas por usuario específico
	function buscarUser(){
		// query to read single record
		$query = "SELECT
					todo.id, todo.nome, todo.id_user, todo.data, todo.recorrencia
				FROM
					" . $this->table_name . " 
				JOIN usuario on todo.id_user = usuario.id_user
				WHERE
					usuario.nome = ?";
	 
		// prepare query statement
		$stmt = $this->conn->prepare($query);
	 
		// bind nome_usuario of usuario
		$stmt->bindParam(1, $this->nome_usuario);
	 
		// execute query
		$stmt->execute();
	 
		return $stmt;
	}
	
	//Função auxiliar
	function getRecorrencia($num){
		switch($num){
			case 0:
				return "Not";
			case 1:
				return "Daily";
			case 2:
				return "Weekly";
			case 3:
				return "Monthly";
		}
	}
}