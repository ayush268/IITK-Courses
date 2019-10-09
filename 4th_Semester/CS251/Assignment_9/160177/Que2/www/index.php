<html>
<head>
  <title>Let's Build Stuff</title>
</head>

<body>

<?php

$name = $address = $email = $mobile = $bank_acc = $acc_pass = "";

$db = new SQLite3('bank.db');

$db->exec('create table if not exists users (name varchar(20), address varchar(100), email varchar(255), mobile integer, bank_acc integer, acc_pass varchar(20))');
$db->exec('create table if not exists accounts (bank_acc integer, acc_pass varchar(20), balance integer)');

include 'functions.php';

if ($_SERVER["REQUEST_METHOD"] == "POST")
{
  $name = test_input($_POST["name"]);
  $address = test_input($_POST["address"]);
  $email = test_input($_POST["email"]);
  $mobile = test_input($_POST["mobile"]);
  $bank_acc = test_input($_POST["bank_acc"]);
  $acc_pass = test_input($_POST["acc_pass"]);
  $ins = "insert into users values ('".$name."', '".$address."', '".$email."', '".$mobile."', '".$bank_acc."', '".$acc_pass."')";

  if( isRegSuccess($db, $email) )
  {
    if(isAccValid($db, $bank_acc, $acc_pass)) 
    {
      if(isLoaded($db, $bank_acc))
      {
        echo "<script type=\"text/javascript\">
          alert('Registration Successful');
        </script>";
        $insres = $db->query($ins);
      }
      else
      {
        echo "<script type=\"text/javascript\">
          alert('Insufficient Balance');
        </script>";
      }
    }
    else
    {
      echo "<script type=\"text/javascript\">
        alert('Invalid Account/Password');
      </script>";
    }
  }
  else
  {
    echo "<script type=\"text/javascript\">
      alert('Already Registered');
    </script>";
  }
}

?>

<link href="//db.onlinewebfonts.com/c/a4e256ed67403c6ad5d43937ed48a77b?family=Core+Sans+N+W01+35+Light" rel="stylesheet" type="text/css" />
<link rel="stylesheet" href="main.css" type="text/css">
<div class="body-content">
  <div class="module">
    <h1>Create an User Account</h1>
    <form class="form" method="post" id="form" action="<?php  echo htmlspecialchars($_SERVER["PHP_SELF"]);?>" autocomplete="off">
      <div class="alert alert-error"></div>
      <input type="text" placeholder="Name" name="name" required />
      <input type="text" placeholder="Address" name="address" required />
      <input type="email" placeholder="Email" name="email" required />
      <input type="text" placeholder="Mobile Number" name="mobile" required />
      <input type="text" placeholder="Bank Account Number" name="bank_acc" required />
      <input type="password" placeholder="Bank Account Password" name="acc_pass" autocomplete="new-password" required />
      <input type="submit" value="Register" name="register" class="btn btn-block btn-primary" onclick="validate()"/>
    </form>
    <h1><a href="admin_reg.php" style="color:white;text-decoration:none">Admin Login</h1>
  </div>
</div>

<script src="script.js"></script>

</body>

</html>
