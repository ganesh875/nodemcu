<?php
$dbhost = 'localhost';
$dbuser = 'root';
$dbpass = '11223344';
$dbname = 'test';

$mood = $_GET['mood'];
$conn = mysqli_connect($dbhost,$dbuser,$dbpass,$dbname);

if(!$conn)
{
    die("Could not connect: " . mysql_error());
}
$datenow = date('Y-m-d');
if (isset($mood)){
$sql = "INSERT INTO esptest(logdate, temp) VALUES (NOW(),'$mood')";
$result = mysqli_query($conn,$sql);
if(!$result)
{
    die("Invalid query: " . mysqli_error());
}
echo "<h1>The data has been sent!</h1>";
}
mysqli_close($conn);
?>

<html>
	<head>
		<title>ESP Test</title>
		<style>
		html, body{
			background-color: #F2F2F2;
			font-family: Arial;
			font-size: 1em;
		}
		table{
			border-spacing: 0;
			border-collapse: collapse;
			margin: 0 auto;
		}
		th{
			padding: 8px;
			background-color: #FF837A;
			border: 1px solid #FF837A;
		}
		td{
			padding: 10px;
			background-color: #FFF;
			border: 1px solid #CCC;
		}
		
		div.notes{
			font-family: arial;
			text-align: center;
		}
		
		div.current{
			font-size: 58px;
			font-family: arial black;
			text-align: center;
		}
		</style>
	</head>
	<body>
		<?php	
			// Database credentials.
			$dbhost = 'localhost';
			$dbuser = 'root';
			$dbpass = '11223344';
			$dbname = 'test';
			// Number of entires to display.
			$display = 15;
			// Create connection.
			$conn = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);
			if (!$conn) {
				die("Connection failed: " . mysqli_connect_error());
			}
			
			// Get the most recent 15 entries.
			$result = mysqli_query($conn, "SELECT logdate,temp FROM esptest ORDER BY Id DESC LIMIT " . $display . "");
			echo "<table><tr><th>Date</th><th>Temperature</th></tr>";
			while($row = mysqli_fetch_assoc($result)) {
				echo "<tr><td>";
				echo $row["logdate"];
				echo "</td><td>";
				echo $row["temp"];
				echo "</td></tr>";
				$counter++;
			}
			echo "</table>";
			
			// Print number of entries in the database. Replace YOUR_TABLE_NAME with your database table name.
			$row_cnt = mysqli_num_rows(mysqli_query($conn, "SELECT logdate FROM esptest"));
			echo "<div class='notes'>Displaying last " . $display . " entries.<br/>The database table has " . $row_cnt . " total entries.</div>";
			
			// Close connection.
			mysqli_close($conn);
		?>
	</body>
</html>