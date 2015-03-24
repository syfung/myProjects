for file in ?? 
do
	echo $file
	cd $file
	ls
	rm -vi *'~' test
	cd ..
done
