<?php
//AES 128 ECB
	function msectime(){list($msec, $sec) = explode(' ', microtime());return (float)sprintf('%.0f',(floatval($msec)+floatval($sec))*1000);}		
	if(file_exists($argv[1]))
	{
		$fp=fopen($argv[1],"r");
		$str=fread($fp,filesize($argv[1]));
		fclose($fp);
		$start=msectime();		
		$str=base64_encode(openssl_encrypt($str,"AES-128-ECB","0CoJUm6Qyw8W8jud",OPENSSL_RAW_DATA,""));
		echo 'PHP AES 128 ECB encode used time:'.((msectime()-$start))."ms\n";
		$fp=fopen("tmp/aes_128_ecb_encode.ans","w");
		fwrite($fp,$str);
		fclose($fp);
	}
	if(file_exists("tmp/aes_128_ecb_encode.out"))
	{
		$fp=fopen("tmp/aes_128_ecb_encode.out","r");
		$str=fread($fp,filesize("tmp/aes_128_ecb_encode.out"));
		fclose($fp);
		$start=msectime();		
		$str=openssl_decrypt(base64_decode($str),"AES-128-ECB","0CoJUm6Qyw8W8jud",OPENSSL_RAW_DATA,"");
		echo 'PHP AES 128 ECB decode used time:'.((msectime()-$start))."ms\n";
		$fp=fopen("tmp/aes_128_ecb_decode.ans","w");
		fwrite($fp,$str);
		fclose($fp);		
	}