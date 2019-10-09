<html>
<head>
  <title>All Registrations</title>
</head>
<body>

<?php

$db = new SQLite3('bank.db');

$db->exec('create table if not exists admin (username varchar(20), password varchar(20))');

function adminlogin()
{ ?>
  <link href="//db.onlinewebfonts.com/c/a4e256ed67403c6ad5d43937ed48a77b?family=Core+Sans+N+W01+35+Light" rel="stylesheet" type="text/css" />
<link rel="stylesheet" href="main.css" type="text/css">
<div class="body-content">
  <div class="module">
    <h1>Enter Your Credentials</h1>
    <form class="form" method="post" id="form" action="<?php  echo htmlspecialchars($_SERVER["PHP_SELF"]);?>" autocomplete="off">
      <div class="alert alert-error"></div>
      <input type="text" placeholder="Username" name="username" required />
      <input type="password" placeholder="Password" name="password" autocomplete="new-password" required />
      <input type="submit" value="Login" name="register" class="btn btn-block btn-primary" onclick="validate()"/>
    </form>
    <h1><a href="index.php" style="color:white;text-decoration:none">New User?</h1>
  </div>
</div>
<?php }

function show($db)
{
  echo "<h2>All Registrations</h2>";
  echo "<table style=\"width:70%\">
    <tr>
      <th>Name    </th>
      <th>Address </th>
      <th>Email   </th>
      <th>Mobile  </th>
      <th>Bank Acc</th>
      <th>Balance </th>
    </tr>";
  $results = $db->query('select * from users');
  while ($info = $results->fetchArray())
  {
    $money = $db->query("select * from accounts where bank_acc like '".$info[4]."'");
    $m = $money->fetchArray();
    echo "<tr>
      <td>$info[0]</td>
      <td>$info[1]</td>
      <td>$info[2]</td>
      <td>$info[3]</td>
      <td>$info[4]</td>
      <td>$m[2]</td>
    </tr>";
  }
  echo "</table><br>";
?>
  <h1><a href="index.php" style="color:black;text-decoration:none">New User?</h1>
<?php
}

include 'functions.php';

if ($_SERVER["REQUEST_METHOD"] == "POST")
{
  $username = test_input($_POST["username"]);
  $password = test_input($_POST["password"]);
  $results = $db->query("select * from admin where username like '".$username."'");
  while($res = $results->fetchArray()) 
  {
    if($username == $res[0] && $password == $res[1])
      show($db);
    else
    {
      echo "<script type=\"text/javascript\">
        alert('Incorrect Username/Password');
      </script>";
      adminlogin();
    }
  }
}
else
  adminlogin();
?>


</body>

</html>
