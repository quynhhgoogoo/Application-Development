<?php
$log_file = 'sound_log.txt';	//log file name
$data = $_POST['data'];
date_default_timezone_set("UTC");
$str = gmdate("M d Y H:i:s", time()).', '.$data."\n";	//two fields in one record, the timestamp and post data
//echo : "This is from server
//now we open the file
if(file_exists($log_file))
{
	$fp = fopen($log_file, "a");	//the file is opened as well as append mode
	fwrite($fp, $str);	//write current data value (post data with timestamp)
	fclose($fp);
}
else	//the file does not exist so open a new one
{
	$fp = fopen($log_file, "w");
	fwrite($fp, $str);
	fclose($fp);
}
echo "Data is stored\n";	//echo something back to the raspberry pi
?>