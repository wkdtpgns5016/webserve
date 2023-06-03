echo "test[Simple/Syntax]"
read test_directory
if [ $test_directory != "Simple" -a $test_directory != "Syntax" ];then
	echo "only simple or syntax, please..."
	exit
fi

echo "*****************************************"
echo "$test_directory"
echo "*****************************************\n"

for directory in ./$test_directory/*
do
echo "*****************************************"
echo "$directory"
echo "*****************************************\n"
read
for file in $directory/*
do
	echo "-----------------test--------------------"
	echo "$file"
	cat $file
	echo "\n----------------result-------------------"
	../webserv "$file" &
	./pkill.sh > /dev/null 2>&1
	echo "-----------------------------------------\n"
	echo "\n\n"
done
done
