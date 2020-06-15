<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		<title>Todo</title>
		<!--Include do CSS-->
		<link rel="stylesheet" type="text/css" href="../CSS/css_inicial.css">
		<!--Include da biblioteca Jquery-->
		<script src="../jquery.js"></script>
		<!--Metodo ajax-->
		<script>
			$(document).ready(function() {
				setInterval(function(){
				$('#exibe').load('../Controle/processar.php?op=select')
				}, 2000);
			})
		</script>
	</head>
	<body class="inicial">
		<pre style="float:left"> Versão 1.0</pre>
		<h1><?php echo $_SESSION['login'];?> Todo
			<!--Botao de Logout-->
			<div class="btlogout" style="float:right; padding-top: 10px;
            padding-bottom: 10px;">
				<?php 
					echo '<a href="../Controle/processar.php?op=logout&&
					token='.md5(session_id()).'">
					<button type="button" class="clicar">
						Sair
					</button>
					</a>';
				?>
			</div>
		</h1>
		<form method="post" action="../Controle/processar.php?op=add">
			Tarefa: <input type="text" name="tarefa" id="tarefa"> 
			<input type="date" name ="date" id="date">
			<input class="clicar" type="submit">
			</br>
			Recorrência:
			<input type="radio" name="recorrencia" value=0 id="recorrencia" checked="checked"> Não
			<input type="radio" name="recorrencia" value=1 id="recorrencia"> Diário
			<input type="radio" name="recorrencia" value=2 id="recorrencia"> Semanal
			<input type="radio" name="recorrencia" value=3 id="recorrencia"> Mensal
		</form>

		<!--Bloco que sera repetido assincronamente pelo ajax-->
		<div id="exibe">
		    <?php 
		        $controle = new Controle();
		        $controle->executar("select"); 
            ?>
		</div>
	</body>
</html>