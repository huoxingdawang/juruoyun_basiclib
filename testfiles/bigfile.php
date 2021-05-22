<?php
	$fp=fopen("tmp/bigfile.tmp","w");
	$s="juruoyunjuruoyunjuruoyunjuruoyun";
	for($i=0;$i<25;$i++)$s.=$s;
	fwrite($fp,$s);
	fclose($fp);
