<?php
$value = $_POST['value'];	//take the value of "value" field
$from = $_POST['from'];		//take the value of "from" field
$ip = $_SERVER['REMOTE_ADDR'];	//take the cilent's ip address
echo "Your value = ".$value." from=".$from.". And your IP address is ".$ip."\n";
//echo is the message sent back to cilent, in many IoT based communication
$today=date("Y-m-d H:i:s");	//current time
$file = "curltest.log";	//the log file name
if(file_exists($file))
{
	$fp = fopen($file, "a");	//open the file in appending mode
}
else
{
	$fp = fopen($file, "w");	//open the file in writing mode
}
//prepare a line of record to write to a file, in CSV format
$record = $today . "," . $from . "," . $ip . "," . $value . "\n";
fwrite($fp, $record);	//write to file
fclose($fp);	//close the open file
?>