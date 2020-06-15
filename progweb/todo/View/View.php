<?php
	class View{
		public function exibirTarefas(array $arrayTask){
			include 'viewTarefas.php';
		}
		public function processarData(array $arrayTask){
			foreach($arrayTask as $t) {
				if($t->getData()=="0000-00-00")
					$data = date("d/m/Y");
				else
					$data = date('d/m/Y', strtotime($t->getData()));
				$t->setData($data);
			}
			return $arrayTask;
		}
		public function mensagemErro(String $erro){
		    include 'viewErros.php';
		}
		public function mensagemAviso(String $aviso){
		    include 'viewAvisos.php';
		}
	}
?>