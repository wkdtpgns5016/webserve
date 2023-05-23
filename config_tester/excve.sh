for file in ./SimpleTest/*/*
do
	echo "*****************test********************"
	echo "$file"
	cat $file
	echo "****************result*******************"
	../webserv "$file" &
	./pkill.sh > /dev/null 2>&1
	echo "*****************************************\n"
	echo "\n\n"
done
