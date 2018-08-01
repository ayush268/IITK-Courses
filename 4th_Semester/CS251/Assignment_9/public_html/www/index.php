<html>
<head>
  <title>Let's Build Stuff</title>
</head>
<body>

<?php

// define variables and set to empty values
$name = $address = $email = $mobile = $bank_acc = $bank_pass = "";
$db = new SQLite3('bank_details.db');
$db->query("create table records(name varchar(20), addresss varchar(100), email varchar(30), mobile integer, bank_acc integer, bank_pass varchar(20))");
$db->query("create table balance(bank_acc integer, bank_pass varchar(20), money integer)");

include 'registration.php';

function trim_input($data)
{
  $data = trim($data);
  $data = stripslashes($data);
  $data = htmlspecialchars($data);
  return $data;
}

if ($_SERVER["REQUEST_METHOD"] == "POST")
{
  $entry = array();
  $entry[0] = trim_input($_POST["name"]);
  $entry[1] = trim_input($_POST["address"]);
  $entry[2] = trim_input($_POST["email"]);
  $entry[3] = trim_input($_POST["mobile"]);
  $entry[4] = trim_input($_POST["bank_acc"]);
  $entry[5] = trim_input($_POST["bank_pass"]);
  $qstr = "insert into records values ('".$entry[0]."', '".$entry[1]."', '".$entry[2]."', '".$entry[3]."', '".$entry[4]."', '".$entry[5]."')";

  if (check_reg($db, $entry[2]))
    if (correct_pass($db, $entry))
      if (check_balance($db, $entry[4]))
      {
        echo "<script type=\"text/javascript\">
          alert('Registration Successful');
        </script>";
        $insres = $db->query($qstr);
      }
      else
        echo "<script type=\"text/javascript\">
          alert('Insufficient Balance');
        </script>";
    else
      echo "<script type=\"text/javascript\">
        alert('Invalid Account/Password');
      </script>";
  else
    echo "<script type=\"text/javascript\">
      alert('Already Registered');
    </script>";
}

?>

<h2>Let's Build Stuff</h2>
<form method="post" id="form" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
  Name: <input type="text" name="name">
  <br><br>
  Address: <textarea name="address" rows="3" cols="40"></textarea>
  <br><br>
  E-mail: <input type="text" name="email">
  <br><br>
  Mobile: <input type="text" name="mobile">
  <br><br>
  Bank Account Number: <input type="text" name="bank_acc">
  <br><br>
  Bank Account Password: <input type="password" name="bank_pass">
  <br><br>
  <input type="button" name="submit_button" value="Submit" onclick="validate_js()">
</form>

<script src="validate.js"></script>

<a href="all_reg.php">See All Registrations</a>

</body>
</html>
