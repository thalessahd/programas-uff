<?php
	class Database{
 
    // specify your own database credentials
	private $servername = "localhost";
	private $username = "id9495374_myadmin";
	private $password = "myadmin";
	private $dbname = "id9495374_meutodo";
    public $conn;
 
    // get the database connection
    public function getConnection(){
 
        $this->conn = null;
 
        try{
            $this->conn = new PDO("mysql:host=" . $this->servername . 
			";dbname=" . $this->dbname, $this->username, $this->password);
            $this->conn->exec("set names utf8");
        }catch(PDOException $exception){
            echo "Connection error: " . $exception->getMessage();
        }
 
        return $this->conn;
    }
}
?>