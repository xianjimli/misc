export lname=$1
export uname=$2

cp img_filter_dummy.h img_filter_$lname.h
cp img_filter_dummy.c img_filter_$lname.c
cat img_filter_$lname.h|sed -e "s/rotate/$lname/g" -e "s/ROTATE/$uname/g" >temp.h; mv temp.h img_filter_$lname.h
cat img_filter_$lname.c|sed -e "s/rotate/$lname/g" -e "s/ROTATE/$uname/g" >temp.c; mv temp.c img_filter_$lname.c

