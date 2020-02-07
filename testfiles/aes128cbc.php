<?php
//AES 128 CBC
	function msectime(){list($msec, $sec) = explode(' ', microtime());return (float)sprintf('%.0f',(floatval($msec)+floatval($sec))*1000);}		
	if(file_exists($argv[1]))
	{
		$start=msectime();
		$fp=fopen($argv[1],"r");
		$str=fread($fp,filesize($argv[1]));
		fclose($fp);
		$fp=fopen("testfiles/aes_128_cbc_encode.ans","w");
		fwrite($fp,base64_encode(openssl_encrypt($str,"AES-128-CBC","0CoJUm6Qyw8W8jud",OPENSSL_RAW_DATA,"0CoJUm6Qyw8W8jud")));
		fclose($fp);
		echo 'PHP AES 128 CBC encode used time:'.((msectime()-$start))."ms\n";
	}	
	if(file_exists("testfiles/aes_128_cbc_encode.out"))
	{
		$start=msectime();
		$fp=fopen("testfiles/aes_128_cbc_encode.out","r");
		$str=fread($fp,filesize("testfiles/aes_128_cbc_encode.out"));
		fclose($fp);
		$fp=fopen("testfiles/aes_128_cbc_decode.ans","w");
		fwrite($fp,openssl_decrypt(base64_decode($str),"AES-128-CBC","0CoJUm6Qyw8W8jud",OPENSSL_RAW_DATA,"0CoJUm6Qyw8W8jud"));
		fclose($fp);		
		echo 'PHP AES 128 CBC decode used time:'.((msectime()-$start))."ms\n";
	}	
