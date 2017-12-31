#!/bin/bash

COLUME_ITEM="color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes"
#replace the ',' in \" \"
#sed -e 's/\("[^,]*\)[,]\([^"]*"\)/\1_\2/g' $FILE_PATH
#get $FILE_PATH from input
if [ $# -ne 1 ];then
    echo "run.sh <path of the binary file>"
    exit 1
fi

IFS=”,”
BINARYFILE=$1
num_ok=0
num_wrong=0


echo "dataset1, director_name"
colume_item="director_name"
#echo "cat $DATAFILE | $BINARYFILE -c $colume_item"
cat ./dataset1.csv | $BINARYFILE -c $colume_item > ./grade_temp.csv
#echo "run binary ok"
cat ./grade_temp.csv | ./grade -c $colume_item
#echo "run grade ok"
return_code=$(echo $?)
if [ $return_code -eq 1 ];then
    let num_wrong++
else
  let num_ok++
fi

echo "dataset1, budget"
colume_item="budget"
#echo "cat $DATAFILE | $BINARYFILE -c $colume_item"
cat ./dataset1.csv | $BINARYFILE -c $colume_item > ./grade_temp.csv
#echo "run binary ok"
cat ./grade_temp.csv | ./grade -c $colume_item
#echo "run grade ok"
return_code=$(echo $?)
if [ $return_code -eq 1 ];then
    let num_wrong++
else
  let num_ok++
fi


echo "dataset2, movie_title"
colume_item="movie_title"
#echo "cat $DATAFILE | $BINARYFILE -c $colume_item"
cat ./dataset2.csv | $BINARYFILE -c $colume_item > ./grade_temp.csv
#echo "run binary ok"
cat ./grade_temp.csv | ./grade -c $colume_item
#echo "run grade ok"
return_code=$(echo $?)
if [ $return_code -eq 1 ];then
    let num_wrong++
else
  let num_ok++
fi

echo "dataset2, gross"
colume_item="gross"
#echo "cat $DATAFILE | $BINARYFILE -c $colume_item"
cat ./dataset2.csv | $BINARYFILE -c $colume_item > ./grade_temp.csv
#echo "run binary ok"
cat ./grade_temp.csv | ./grade -c $colume_item
#echo "run grade ok"
return_code=$(echo $?)
if [ $return_code -eq 1 ];then
    let num_wrong++
else
  let num_ok++
fi

echo "dataset3, movie_title"
colume_item="movie_title"
#echo "cat $DATAFILE | $BINARYFILE -c $colume_item"
cat ./dataset3.csv | $BINARYFILE -c $colume_item > ./grade_temp.csv
#echo "run binary ok"
cat ./grade_temp.csv | ./grade -c $colume_item
#echo "run grade ok"
return_code=$(echo $?)
if [ $return_code -eq 1 ];then
    let num_wrong++
else
  let num_ok++
fi

echo "dataset3, movie_facebook_likes"
colume_item="movie_facebook_likes"
#echo "cat $DATAFILE | $BINARYFILE -c $colume_item"
cat ./dataset3.csv | $BINARYFILE -c $colume_item > ./grade_temp.csv
#echo "run binary ok"
cat ./grade_temp.csv | ./grade -c $colume_item
#echo "run grade ok"
return_code=$(echo $?)
if [ $return_code -eq 1 ];then
    let num_wrong++
else
  let num_ok++
fi


echo "dataset4, actor_1_name"
colume_item="actor_1_name"
#echo "cat $DATAFILE | $BINARYFILE -c $colume_item"
cat ./dataset4.csv | $BINARYFILE -c $colume_item > ./grade_temp.csv
#echo "run binary ok"
cat ./grade_temp.csv | ./grade -c $colume_item
#echo "run grade ok"
return_code=$(echo $?)
if [ $return_code -eq 1 ];then
    let num_wrong++
else
  let num_ok++
fi


echo "dataset4, duration"
colume_item="duration"
#echo "cat $DATAFILE | $BINARYFILE -c $colume_item"
cat ./dataset4.csv | $BINARYFILE -c $colume_item > ./grade_temp.csv
#echo "run binary ok"
cat ./grade_temp.csv | ./grade -c $colume_item
#echo "run grade ok"
return_code=$(echo $?)
if [ $return_code -eq 1 ];then
    let num_wrong++
else
  let num_ok++
fi

#this number is not accurate
#echo "num_ok(${num_ok}), num_false(${num_wrong})"
