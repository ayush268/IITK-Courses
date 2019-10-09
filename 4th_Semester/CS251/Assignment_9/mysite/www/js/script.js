function updatelength(field, output) {
    curr_length = document.getElementById(field).value.length;
    field_mlen = document.getElementById(field).maxLength;
    document.getElementById(output).innerHTML = curr_length+'/'+field_mlen;
    return 1;
}

function check_v_mail(field) {
    if(/^[A-Za-z]*@\w+([\.-]?\w+)*(\.com)$/.test(document.getElementById(field).value))
    {
        return (true)
    }

    return (false)
}

function valid_length(field) {
    length_df = document.getElementById(field).value.length;
    if (length_df >= 1 && length_df <= document.getElementById(field).maxLength) {
        update_css_class(field, 2);
        ret_len = 1;
    } else {
        update_css_class(field, 1);
        ret_len = 0;
    }
    return ret_len;
}

function valid_bank_length(field) {
    var val = document.getElementById(field).value;
    if (/^\d{5}$/.test(val)) {
    // value is ok, use it
        return true
    } else {
        return false
    }
}
function valid_mobile_length(field) {
    var val = document.getElementById(field).value;
    if (/^[1-9]\d{9}$/.test(val)) {
    // value is ok, use it
        return true
    } else {
        return false
    }
}
function update_css_class(field, class_index) {
    if (class_index == 1) {
        class_s = 'wrong';
    } else if (class_index == 2) {
        class_s = 'correct';
    }
    document.getElementById(field).className = class_s;
    return 1;
}

function validate_all(output) {
    t1 = valid_length('name');
    t2 = valid_length('password');
    t3 = valid_length('address');
    t4 = check_v_mail('email');
    t5 = valid_bank_length('bank');
    t6 = valid_mobile_length('mobile');

    errorlist = '';
    if (! t1) {
        errorlist += 'name is too short/long<br />';
    }
    if (! t2) {
        errorlist += 'password is too short/long<br />';
    }
    if (! t3) {
        errorlist += 'address are not the same<br />';
    }
    if (! t4) {
        errorlist += 'email is wrong<br />';
    }
    if (! t5) {
        errorlist += 'invalid bank details<br />';
    }
    if (! t6) {
        errorlist += 'invalid mobile details<br />';
    }
    if (errorlist) {
        document.getElementById(output).innerHTML = errorlist;
        return false;
    }
    return true;
}
