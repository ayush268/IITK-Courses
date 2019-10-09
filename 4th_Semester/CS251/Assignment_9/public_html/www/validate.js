function validate_js()
{
  var flag = true;
  var form = document.getElementById("form");
  if (! /^[a-zA-z ]{1,20}$/.test(form.elements[0].value))
  {
    flag = false;
    alert("Error in name");
  }
  if (! /^.{1,100}$/.test(form.elements[1].value))
  {
    flag = false;
    alert("Error in address");
  }
  if (! /^[a-zA-z\.]+@[a-zA-z0-9]+\.com$/.test(form.elements[2].value))
  {
    flag = false;
    alert("Error in email");
  }
  if (! /^[0-9]{10}$/.test(form.elements[3].value))
  {
    flag = false;
    alert("Error in mobile number");
  }
  if (! /^[0-9]{5}$/.test(form.elements[4].value))
  {
    flag = false;
    alert("Error in account number");
  }
  if (! /^[a-zA-z0-9]{1,20}$/.test(form.elements[5].value))
  {
    flag = false;
    alert("Error in account password");
  }

  if (flag)
    form.submit();
}
