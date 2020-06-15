<?php
	date_default_timezone_set('America/Sao_Paulo');
	class Todo{
		private $id;
		private $nome;
		private $id_user;
		private $data;
		private $recorrencia;
		
		/*function __construct($id,$nome,$id_user,$data,$reco) {
			$this->setId($id);
			$this->setNome($nome);
			$this->setId_user($id_user);
			$this->setData($data);
			$this->setRecorrencia($reco);
		}*/
		
		public function getId(){
			return $this->id;
		}
		public function setId($id){
			$this->id = $id;
		}
		public function getNome(){
			return $this->nome;
		}
		public function setNome($nome){
			$this->nome = $nome;
		}
		public function getId_user(){
			return $this->id_user;
		}
		public function setId_user($id_user){
			$this->id_user = $id_user;
		}
		public function getData(){
			return $this->data;
		}
		public function setData($data){
			if($data==null)
				$data = date("Y-m-d");
			$this->data = $data;
		}
		public function getRecorrencia(){
			return $this->recorrencia;
		}
		public function setRecorrencia($reco){
			$this->recorrencia = $reco;
		}
		public function printar(){
			echo "id: ".$this->getId()."</br>";
			echo "nome: ".$this->getNome()."</br>";
			echo "id_user: ".$this->getId_user()."</br>";
			echo "data: ".$this->getData()."</br>";
			echo "recorrencia: ".$this->getRecorrencia()."</br>";
		}
	}
?>