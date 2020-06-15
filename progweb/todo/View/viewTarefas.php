<?php	
	//Imprimir tarefas + botao de deletar
	$i=0;
	if(!empty($arrayTask)){
		echo '<div class="tarefa">';
		foreach($arrayTask as $t) {
			$i++;
			echo "<p>";
			echo "<li>";
			if($t->getRecorrencia()!=0){
				switch($t->getRecorrencia()){
					case 1:
						echo "[Diário] ";
					break;
					case 2:
						echo "[Semanal] ";
					break;
					case 3:
						echo "[Mensal] ";
					break;
				}
			}
			if($t->getData()!=null)
				echo $t->getData();
			echo " ".$t->getNome();
			?> 
			<a class="del"href="../Controle/processar.php?op=deletar&&del=
				<?php echo $t->getId(); ?>
				&&data=<?php echo $t->getData();?>
				&&reco=<?php echo $t->getRecorrencia(); ?>"
				>
				X
			</a>
			<?php
			echo"</li>";
			echo "</p>";
			if($i< sizeof($arrayTask))
				echo "<hr>";
		}
		echo "</div>";
	}
	else{
		echo "Nenhuma tarefa registrada";
	}
?>