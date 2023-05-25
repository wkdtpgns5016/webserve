
echo "****************SIMPLE*******************"
echo "*****************TEST********************"
echo "*****************************************\n"
for file in ./SimpleTest/*
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

echo "****************SYNTAX*******************"
echo "*****************TEST********************"
echo "*****************************************\n"

echo "****************Brace********************"

for file in ./SyntaxTest/Brace/*
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

echo "***************SemiColon*****************"

for file in ./SyntaxTest/Semicolon/*
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
