echo "Enter the string";
read s;
len=${#s};
is_palin=1;
for (( i = 0; i < len / 2; i++ ))
do
if [[ "${s:$i:1}" != "${s:$((len-i-1)):1}" ]]
then
is_palin=0;
break
fi
done
if [[ $is_palin -eq 1 ]];
then
echo "the string is palindrome";
else
echo "the string is not palindrome";
fi