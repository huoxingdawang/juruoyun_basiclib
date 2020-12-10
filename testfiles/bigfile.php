<?php
	$fp=fopen("tmp/bigfile.tmp","w");
	$s="juruoyunjuruoyunjuruoyunjuruoyun";
	for($i=0;$i<20;$i++)$s.=$s;
	for($i=0;$i<2;$i++)$s.=$s;
	fwrite($fp,$s);
	fclose($fp);