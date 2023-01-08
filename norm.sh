for f in src/* 
do 
	echo $f;
	echo "=========================================";
	norminette $f | grep -v src | wc | awk '{printf "\n\n%d norm error\n\n",$1}';
	norminette $f;
	echo "==========================================";
done
