<html>
<head>
  <title>All Registrations</title>
</head>
<body>

<?php

$db = new SQLite3('database.db');

function adminpass()
{ ?>
  <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
    Admin Login ID: <input type="text" name="admin_id">
    <br><br>
    Admin Password: <input type="password" name="admin_pass">
    <br><br>
    <input type="submit" name="submit" value="Submit">
  </form>
<?php }

function show($db)
{
  echo "<h2>All Registrations:</h2>";
  echo "<table style=\"width:70%\">
    <tr>
      <th>Name    </sh>
      <th>Address </th>
      <th>Email   </th>
      <th>Mobile  </th>
      <th>Bank-A/C</th>
      <th>Balance</th>
    </tr>";
  $results = $db->query('select * from users');
  while ($row = $results->fetchArray()){
  $res = $db->query("select * from accounts where bank like '".$row[4]."'");
  $r = $res->fetchArray();
    echo "<tr>
      <td>$row[0]</td>
      <td>$row[1]</td>
      <td>$row[2]</td>
      <td>$row[3]</td>
      <td>$row[4]</td>
      <td>$r[1]</td>
    </tr>";
  echo "</table><br>";


  }
}

function trim_input($data)
{
  $data = trim($data);
  $data = stripslashes($data);
  $data = htmlspecialchars($data);
  return $data;
}

if ($_SERVER["REQUEST_METHOD"] == "POST")
{
  $login_id = trim_input($_POST["admin_id"]);
  $password = trim_input($_POST["admin_pass"]);
  $res = $db->query("SELECT * FROM admins WHERE admin like '".$login_id."'");
  while($r = $res->fetchArray()) {
      if($login_id == $r[0] && $password == $r[1]){
          show($db);
          }
        else
        {
            echo "<script type=\"text/javascript\">
            alert('Incorrect Account/Password');
            </script>";
            adminpass();
        }
  }

}
else
  adminpass();

?>

<a href="index.php">Another Registration</a>

</body>
</html>
