for i in $@
do
echo $i >> quo3temp
done
sort quo3temp
rm quo3temp
