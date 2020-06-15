<?php
    //Envia o email de confirmação
    ini_set('display_errors', 1);
    
    error_reporting(E_ALL);
    
    $from = "thalessahd@hotmail.com";
    
    $to = $email; //talvez precise verificar se o email é válido/existe
    
    $subject = "Bem vindo(a) ao Todo by Thalessa";
    
    $message = "Seja muito bem vindo(a), $nome! 
    Para concluir seu cadastro e poder desfrutar do Todo by Thalessa acesse o link: 
    https://todothalessa.000webhostapp.com/Controle/processar.php?op=autenticar&&chave=$chave_autenticar";

    $headers = "De:". $from;
    
    mail($to, $subject, $message, $headers);
    
    //echo "A mensagem de e-mail foi enviada.";
?>