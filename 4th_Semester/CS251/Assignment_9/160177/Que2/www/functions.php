<?php

function test_input($data) {
  $data = trim($data);
  $data = stripslashes($data);
  $data = htmlspecialchars($data);
  return $data;
}

function isRegSuccess($db, $email) {
  $results = $db->query("select * from users where email like '".$email."'");
  if ($results->fetchArray())
    return false;
  else
    return true;
}

function isAccValid($db, $bank_acc, $acc_pass) {
  $results = $db->query("select  * from accounts where bank_acc like '".$bank_acc."'");
  $info = $results->fetchArray();
  if($info[1] != $acc_pass)
    return false;
  else
    return true;
}

function isLoaded($db, $bank_acc) {
  $results = $db->query("select * from accounts where bank_acc like '".$bank_acc."'");
  $info = $results->fetchArray();
  if($info[2] < 1000)
    return false;
  else
  {
    $db->query("update accounts set balance = ".($info[2] - 1000)." where bank_acc = ".$bank_acc);
    return true;
  }
}

?>
