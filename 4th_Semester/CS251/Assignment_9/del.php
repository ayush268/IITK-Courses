<?php
$db = new SQLite3('database.db');

$name = "hh";
$address = "hh";
$email  = "hh";
$mobile = "6666666";
$bank = "6666666";
$password = "6666666";
 $qstr = "INSERT INTO users VALUES ('$name', '$address', '$email', '$mobile', '$bank', '$password')";
$in = $db->query($qstr);
?>
