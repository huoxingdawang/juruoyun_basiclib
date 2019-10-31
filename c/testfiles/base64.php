<?php
	function msectime(){list($msec, $sec) = explode(' ', microtime());return (float)sprintf('%.0f',(floatval($msec)+floatval($sec))*1000);}		
	if(file_exists($argv[1]))
	{
		$start=msectime();		
		$fp=fopen($argv[1],"r");
		$str=fread($fp,filesize($argv[1]));
		fclose($fp);
		$fp=fopen("testfiles/base64_encode.ans","w");
		fwrite($fp,base64_encode($str));
		fclose($fp);
		echo 'BASE64 encode used time:'.((msectime()-$start)/1000)."s\n";		
	}
	if(file_exists("testfiles/base64_encode.out"))
	{
		$start=msectime();		
		$fp=fopen("testfiles/base64_encode.out","r");
		$str=fread($fp,filesize("testfiles/base64_encode.out"));
		fclose($fp);
		$fp=fopen("testfiles/base64_decode.ans","w");
		fwrite($fp,base64_decode($str));
		fclose($fp);		
		echo 'BASE64 decode used time:'.((msectime()-$start)/1000)."s\n";		
	}