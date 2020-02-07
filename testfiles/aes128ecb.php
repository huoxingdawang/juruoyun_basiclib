<?php
//AES 128 ECB
	function msectime(){list($msec, $sec) = explode(' ', microtime());return (float)sprintf('%.0f',(floatval($msec)+floatval($sec))*1000);}		
	if(file_exists($argv[1]))
	{
		$start=msectime();		
		$fp=fopen($argv[1],"r");
		$str=fread($fp,filesize($argv[1]));
		fclose($fp);
		$fp=fopen("testfiles/aes_128_ecb_encode.ans","w");
		fwrite($fp,base64_encode(openssl_encrypt($str,"AES-128-ECB","0CoJUm6Qyw8W8jud",OPENSSL_RAW_DATA,"")));
		fclose($fp);
		echo 'PHP AES 128 ECB encode used time:'.((msectime()-$start))."ms\n";
	}
	if(file_exists("testfiles/aes_128_ecb_encode.out"))
	{
		$start=msectime();		
		$fp=fopen("testfiles/aes_128_ecb_encode.out","r");
		$str=fread($fp,filesize("testfiles/aes_128_ecb_encode.out"));
		fclose($fp);
		$fp=fopen("testfiles/aes_128_ecb_decode.ans","w");
		fwrite($fp,openssl_decrypt(base64_decode($str),"AES-128-ECB","0CoJUm6Qyw8W8jud",OPENSSL_RAW_DATA,""));
		fclose($fp);		
		echo 'PHP MD5 used time:'.((msectime()-$start)/1000)."s\n";
	}