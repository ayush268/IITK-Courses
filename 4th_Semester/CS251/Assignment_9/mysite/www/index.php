<?php
session_start();
// set error reporting level
if (version_compare(phpversion(), '5.3.0', '>=') == 1)
  error_reporting(E_ALL & ~E_NOTICE & ~E_DEPRECATED);
else
  error_reporting(E_ALL & ~E_NOTICE);


if (isset($_POST['submit'])) {


$db = new SQLite3('database.db');
    $sname = escape($_POST['name']);
    $saddress = escape($_POST['address']);
    $semail = escape($_POST['email']);
    $spassword = escape($_POST['password']);
    $sbank = escape($_POST['bank']);
    $smobile = escape($_POST['mobile']);

    $sErrors = '';
    if (strlen($sname) >= 1 and strlen($sname) <= 20) {
    if (strlen($saddress) >= 1 and strlen($saddress) <= 100) {
        if (strlen($spassword) >= 1 and strlen($spassword) <= 20) {
            if (strlen($semail) >= 1 and strlen($semail) <= 55) {

                        //Check1
                 $result = $db->query("SELECT * FROM users WHERE email like '".$semail."'");

                        if ($result->fetchArray()) {

                           $sErrors =  "Already Registered";
                            $aParams = array(
                                '{errors}' => $sErrors,
                                '{login}' => $sname,
                                '{pass}' => $spassword,
                                '{email}' => $semail,
                                '{bank}' => $sbank,
                                '{mobile}' => $smobile,
                            );
                            echo strtr(file_get_contents('templates/step2.html'), $aParams);
                            exit;
                        } else {

                            $results = $db->query("SELECT * FROM accounts WHERE bank like '".$sbank."'");
                            $row = $results->fetchArray();
                                if((int)$row[1] < 1000){
                                    $sErrors = "Insufficient Balance";
                                    $aParams = array(
                                        '{errors}' => $sErrors,
                                        '{login}' => $sname,
                                        '{pass}' => $spassword,
                                        '{email}' => $semail,
                                        '{bank}' => $sbank,
                                        '{mobile}' => $smobile,
                                    );
                                    echo strtr(file_get_contents('templates/step2.html'), $aParams);
                                    exit;
                                }
                                if($row[2] != $spassword) {
                                    $sErrors = "Invalid Account/Password";
                                    $aParams = array(
                                        '{errors}' => $sErrors,
                                        '{login}' => $sname,
                                        '{pass}' => $spassword,
                                        '{email}' => $semail,
                                        '{bank}' => $sbank,
                                        '{mobile}' => $smobile,
                                    );
                                    echo strtr(file_get_contents('templates/step2.html'), $aParams);
                                    exit;
                                }

                            $qstr = "INSERT INTO users (name, address, email, mobile, bank, password) VALUES ('$sname', '$saddress', '$semail', '$smobile', '$sbank', '$spassword')";
                                echo $sname;
                                echo "<br>";
                            $in = $db->query("INSERT INTO users (name, address, email, mobile, bank, password) VALUES ('$sname', '$saddress', '$semail', '$smobile', '$sbank', '$spassword');COMMIT"
);
                            $res = $db->query("SELECT * FROM accounts WHERE bank like '".$sbank."'");
                            $r1 = $res->fetchArray();

                            $db->query("UPDATE accounts SET balance = ".($r1[1]-1000)." WHERE bank = ".$sbank."");
                             echo strtr(file_get_contents('templates/step3.html'), array());
                            exit;
                        }
                    } 
                    
             else {
                $sErrors = 'Address email is too long';
            }
        } else {
            $sErrors = 'Password is too long' . $spassword;
        }
     
    } else {
        $sErrors = 'Address is too long';
      }
    } else {
        $sErrors = 'Login is too long';
    }

    // display step 2
    $aParams = array(
        '{errors}' => $sErrors,
        '{login}' => $sname,
        '{pass}' => $spassword,
        '{email}' => $semail,
        '{bank}' => $sbank,
        '{mobile}' => $smobile,
    );
    echo strtr(file_get_contents('templates/step2.html'), $aParams);
    exit;
}


// draw registration page
echo strtr(file_get_contents('templates/main_page.html'), array());

// extra useful function to make POST variables more safe
function escape($s) {
    //return mysql_real_escape_string(strip_tags($s)); // uncomment in when you will use connection with database
    return strip_tags($s);
}
?>
