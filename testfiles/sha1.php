<?php
	function msectime(){list($msec, $sec) = explode(' ', microtime());return (float)sprintf('%.0f',(floatval($msec)+floatval($sec))*1000);}		
	if(file_exists($argv[1]))
	{
		$start=msectime();		
		$fp=fopen($argv[1],"r");
		$str=fread($fp,filesize($argv[1]));
		fclose($fp);
		$fp=fopen("testfiles/sha1_encode.ans","w");
		fwrite($fp,sha1($str));
		fclose($fp);
		echo 'PHP SHA1 used time:'.((msectime()-$start))."ms\n";		
	}