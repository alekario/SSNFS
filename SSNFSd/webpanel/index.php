<?php
if (check_auth_cookie($_COOKIE['SSNFS_auth']) == FALSE) {
    header("Set-Cookie: SSNFS_auth=; Secure; expires=Thu, 01 Jan 1970 00:00:00 GMT");
    header("Location: /login.php");
    http_response_code(303);
    exit();
}
?>
