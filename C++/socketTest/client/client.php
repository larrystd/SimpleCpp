<?php
$fp = fsockopen("127.0.0.1", 5000 $errno, $errstr, 30);
if (!$fp) {
    echo "111<br />\n";
} else {
    fwrite($fp, "Hello =)");
    while (!feof($fp)) {
        echo fgets($fp, 128);
    }
    fclose($fp);
} 
