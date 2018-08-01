<?php

function check_reg($db, $email)
{
  $response = $db->query("select * from records where email like '".$email."'");
  if ($response->fetchArray())
    return false;
  else
    return true;
}

function check_balance($db, $acc_no)
{
  $response = $db->query("select * from balance where bank_acc like '".$acc_no."'");
  $row = $response->fetchArray();
  if ($row[2] > 1000)
  {
    $db->query("update balance set money = ".($row[2] - 1000)." where bank_acc = ".$acc_no);
    return true;
  }
  else
    return false;
}

function correct_pass($db, $entry)
{
  $response = $db->query("select * from balance where bank_acc like '".$entry[4]."'");
  $row = $response->fetchArray();
  if ($row[1] != $entry[5])
    return false;
  else
    return true;
}

?>
