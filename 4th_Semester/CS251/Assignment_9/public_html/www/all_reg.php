<html>
<head>
  <title>All Registrations</title>
</head>
<body>

<?php

$db = new SQLite3('bank_details.db');

function ask_admin()
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
  echo "<table style=\"width:30%\">
    <tr>
      <th>Name    </sh>
      <th>Address </th>
      <th>Email   </th>
      <th>Mobile  </th>
      <th>Bank-A/C</th>
    </tr>";
  $results = $db->query('select * from records');
  while ($row = $results->fetchArray())
    echo "<tr>
      <td>$row[0]</td>
      <td>$row[1]</td>
      <td>$row[2]</td>
      <td>$row[3]</td>
      <td>$row[4]</td>
    </tr>";
  echo "</table><br>";

  /*echo "<h2>Bank Balances:</h2>";
  echo "<table style=\"width:30%\">
    <tr>
      <th>Bank-A/C</th>
      <th>Password</th>
      <th>Balance</th>
    </tr>";
  $results = $db->query('select * from balance');
  while ($row = $results->fetchArray())
    echo "<tr>
      <td>$row[0]</td>
      <td>$row[1]</td>
      <td>$row[2]</td>
    </tr>";
  echo "</table><br>";*/
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
  if ($login_id == "admin" && $password == "lol")
    show($db);
  else
  {
    echo "<script type=\"text/javascript\">
      alert('Incorrect Account/Password');
    </script>";
    ask_admin();
  }
}
else
  ask_admin();

?>

<a href="index.php">Another Registration</a>

</body>
</html>
