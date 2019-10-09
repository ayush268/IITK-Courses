<!-- Original code taken from https://www.w3schools.com/php/php_form_validation.asp
Modified with additions for SQLite
-->

<html>
<head>
</head>
<body>  

<?php

// define variables and set to empty values
$name = $email = $gender = $comment = $website = "";
$db = new SQLite3('mysqlitedb.db');

if ($_SERVER["REQUEST_METHOD"] == "POST") {
  $name = test_input($_POST["name"]);
  $email = test_input($_POST["email"]);
  $website = test_input($_POST["website"]);
  $comment = test_input($_POST["comment"]);
  $gender = test_input($_POST["gender"]);
  $qstr = "insert into records values ('$name', '$email', '$website', '$gender')";
  $insres = $db->query($qstr);
}

function test_input($data) {
  $data = trim($data);
  $data = stripslashes($data);
  $data = htmlspecialchars($data);
  return $data;
}
?>

<h2>PHP SQLite</h2>
<form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">  
  Name: <input type="text" name="name">
  <br><br>
  E-mail: <input type="text" name="email">
  <br><br>
  Website: <input type="text" name="website">
  <br><br>
  Comment: <textarea name="comment" rows="5" cols="40"></textarea>
  <br><br>
  Gender:
  <input type="radio" name="gender" value="female">Female
  <input type="radio" name="gender" value="male">Male
  <br><br>
  <input type="submit" name="submit" value="Submit">  
</form>

<?php
echo "<h2>Records:</h2>";

$results = $db->query('SELECT * FROM records');
while ($row = $results->fetchArray()) {
	    echo "<br> $row[0] $row[1] $row[2] $row[3]";
}
/*echo $name;
echo "<br>";
echo $email;
echo "<br>";
echo $website;
echo "<br>";
echo $comment;
echo "<br>";
echo $gender;*/
?>

</body>
</html>
