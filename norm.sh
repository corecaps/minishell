for f in src/* 
do 
	echo "==========================================";
	echo "|  " $f "  |";
	echo "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";
	norminette $f | grep -v src | wc | awk '{printf "\n%d norm error\n",$1}';
	echo "==========================================";
	norminette $f | grep -v src;
done