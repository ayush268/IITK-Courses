function validate()
{
  var flag = true;
  var form = document.getElementById("form");
  if (! /^[a-zA-z ]{1,20}$/.test(form.elements[0].value))
  {
    flag = false;
    alert("Please check the Name field");
  }
  if (! /^.{1,100}$/.test(form.elements[1].value))
  {
    flag = false;
    alert("Please check the Address field");
  }
  if (! /^[a-zA-z]+@[a-zA-z0-9]+\.com$/.test(form.elements[2].value))
  {
    flag = false;
    alert("Please check the email field");
  }
  if (! /^[1-9][0-9]{9}$/.test(form.elements[3].value))
  {
    flag = false;
    alert("Please check the mobile number");
  }
  if (! /^[0-9]{5}$/.test(form.elements[4].value))
  {
    flag = false;
    alert("Please check the account number");
  }
  if (! /^[a-zA-z0-9]{1,20}$/.test(form.elements[5].value))
  {
    flag = false;
    alert("Please check the account password");
  }

  if (flag)
    form.submit();
}
