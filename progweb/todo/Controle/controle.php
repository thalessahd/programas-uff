<?php
	include_once '../Modelo/Modelo.php';
	include_once '../Modelo/Todo.php';
	include_once '../View/View.php';

	class Controle{
		private $model;
		private $view;
		
		public function executar(String $op){
			$model = new Modelo();
			$view = new View(); 
			switch($op){
				case "login":
					$login = $_POST['login'];
					$senha = $_POST['senha'];
					switch($model->logar($login,$senha)){
					    case 1:
					        include('../View/inicial.php');
					    break;
					    case 2:
                            $view->mensagemErro("442 - Acesso negado");
					    break;
					    case 0:
					        $view->mensagemAviso("Usuário ou senha inválidos");
					        include('../View/formlogin.php');
					    break;  
					}
				break;
				case "logout":
					if(isset($_GET['token'])){
						$token = $_GET['token'];
					}
					if($model->logout($token))
						include('../View/formlogin.php');
					else
						$view->mensagemErro("457 - Erro ao deslogar");
				break;
				case "cadastro":
					$nome = $_POST['nome'];
					$email = $_POST['email'];
					$senha = $_POST['password'];
					switch($model->cadastrar($nome,$email,$senha)){
					    case 1:
						    include("../View/viewCadastroSucesso.php");
						break;
					    case 2:
					        $view->mensagemAviso("Campos em branco ou inválidos");
						    include("../View/formlogin.php");
						break;
						case 3:
						    $view->mensagemAviso("Esse nome de usuário já está sendo usado");
						    include("../View/formlogin.php");
						break;
					}
				break;
				case "autenticar":
				    if(isset($_GET['chave'])){
					    $chave = $_GET['chave'];
					}
				    if($model->autenticar_conta($chave)){
				        $view->mensagemAviso("Conta verificada com sucesso!");
				        include("../View/formlogin.php");
				    }
				    else{
				        $view->mensagemErro("012 - Chave expirada");
				    }
				break;
				case "add":
					$tarefa = $_POST['tarefa'];
					$date = $_POST['date'];
					$recorrencia = $_POST['recorrencia'];
					$task = new Todo();
					$task->setNome($tarefa);
					$task->setData($date);
					$task->setRecorrencia($recorrencia);
					if($model->inserir($task))
					    include("../View/inicial.php");
				    else{
				        $view->mensagemErro("442 - Acesso negado");
				    }
				break;
				case "select":
					include("../Modelo/select.php");
					$arrayTask = $view->processarData($arrayTask);
					$view->exibirTarefas($arrayTask);
				break;
				case "deletar":
					if(isset($_GET['del'])){
						$del = $_GET['del'];
					}
					if(isset($_GET['data'])){
						$data = $_GET['data'];
					}
					if(isset($_GET['reco'])){
						$rec = $_GET['reco'];
					}
					$data_formatada = date_create_from_format('d/m/Y',$data);
					$data_formatada = date_format($data_formatada,'Y-m-d');
					if($model->deletar($del,$data_formatada,$rec))
					    include("../View/inicial.php");
					else
					    $view->mensagemErro("442 - Acesso negado");
				break;
			}
		}
	}
?>