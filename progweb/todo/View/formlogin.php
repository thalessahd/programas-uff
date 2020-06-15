<html>
	<head>
		<title>Login Todo</title>
		<link rel="stylesheet" type="text/css" href="../CSS/css_inicial.css">
	</head>
	<body class="formlogin">
		<h1>Credenciais</h1>
		<form method="post" action="../Controle/processar.php?op=login" id="formlogin" name="formlogin" >
			<fieldset id="fie">
			<legend title="Para usuários já cadastrados">LOGIN</legend><br>	
			<label>USUÁRIO : </label>
			<input type="text" name="login" id="login" /><br><br>
			<label>SENHA :</label>
			<input type="password" name="senha" id="senha"><br><br>
			<input class="clicar" type="submit" value="LOGAR"/>
			</fieldset>
		</form>
		
		<form method="post" action="../Controle/processar.php?op=cadastro" id="formcadastro" name="formcadastro">
			<fieldset id="fie">
			<legend title="Para novos usuários">CADASTRO</legend><br>
			<label>USUÁRIO : </label>
			<input type="text" name="nome" id="nome"/><br><br>
			<label>EMAIL :</label>
			<input type="text" name="email" id="email"><br><br>
			<label>SENHA :</label>
			<input type="password" name="password" id="password"><br><br>
			<input class="clicar" type="submit" value="CADASTRAR"/>
			</fieldset>
		</form>
		<form method="post" action="../View/ajudaAPI.html">
			<input class="clicar" type="submit" value="Como usar API"/>
		</form>
	</body>
</html>