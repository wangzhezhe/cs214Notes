#!/bin/sh
# executed by " /bin/bash p1_grade_h.sh ./sorter "

gcc -o grade_sorting ./grading.c
gcc -o gradenoheader_sorting ./gradingnoheader.c
gcc -o grade_pid ./grade_pid.c
gcc -o checking_answer ./checking_answer.c

for i in {1..6}; do
	testFolder="test$i"
	cp sorter $testFolder
	cp grade_sorting $testFolder
	cp gradenoheader_sorting $testFolder
	cp grade_pid $testFolder
done

mkdir full_path
mkdir relative_path
cp checking_answer extra1
cp sorter extra1


COLUMN_ITEM="color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes"
if [ $# -ne 1 ];then
    echo "p1_grade_h.sh <path of the binary file>"
    exit 1
fi

BINARYFILE=$1
# PLEASE MODIFY THE TWO VALUES BASED ON YOUR COMPUTER
SMALL_BOUND_PARAL_TIME=16
LARGE_BOUND_PARAL_TIME=48

echo -e "\n############################## TEST 1 #####################################"

cd test1
num_ok=0
num_wrong=0
# test1: sorting by movie_title in current directory
echo -e "\n*** test1: sorting by movie_title in current directory ***"
column_item="movie_title"
# write stdout to pid_output1.txt
START=`date +%s%N`;
strace -f -F -o ./straceout1.txt $BINARYFILE -c $column_item > pid_output1.txt
END=`date +%s%N`;
time=$((END-START))
time=`expr $time / 1000000`

# test for correct output of files in the current directory
echo -e "\n# test for correct output of files in the current directory: 10 pts #"
for i in a b c d; do
testFile="./dataset1_$i-sorted-movie_title.csv"
if [ -f "$testFile" ]; then 
cat $testFile | ./grade_sorting -c $column_item
return_code=$(echo $?)
if [ $return_code -eq 1 ];then
    let num_wrong++
else
  let num_ok++
fi
else
	echo "Not found 'dataset1_$i-sorted-movie_title.csv'"
    let num_wrong++
fi
done
echo "num_ok(${num_ok}), num_false(${num_wrong})"
echo "2.5 pts for each sorting OK"
echo -e "---------------------------------------------------------------------------"

# test for proper pid output & correct number of processes
echo -e "\n# test for proper pid output: 10 pts #"
echo "# test for correct number of processes: 10 pts #"
./grade_pid -v ./pid_output1.txt ./straceout1.txt
echo -e "---------------------------------------------------------------------------"

# test for parallel execution
echo -e "\n# test for parallel execution: 10 pts #"
echo "# execution time is: $time ms #"
if [ $time -lt $SMALL_BOUND_PARAL_TIME ];then
	echo "[OK], parallel execution test passed: 10 pts"
elif [ $time -gt $LARGE_BOUND_PARAL_TIME ]; then
	echo "[FAIL], child processes are processed in serial: 0 pt"
else
	echo "[POSSIBLE], please manually check the tracing file straceout1.txt, to see if child processes are processed in serial"
fi
echo -e "---------------------------------------------------------------------------"

cd ..
cd full_path
FULLPATH=$(pwd)
cd ..
echo "############################## TEST 2 #####################################"
cd test2
CRNTPATH=$(pwd)
RELAPATH=../relative_path

echo -e "\n*** test2: output sorted files to full-path or relative-path directory ***"
column_item="director_name"

echo -e "\n# check for handling full_path #"
strace -f -F -o ./straceout2.txt $BINARYFILE -c $column_item -d $CRNTPATH -o $FULLPATH > pid_output2.txt
./grade_pid -s ./pid_output2.txt ./straceout2.txt
return_code=$(echo $?)
if [ $return_code -eq 1 ];then
    echo "0 pt"
else
	echo "5 pts"
fi
echo -e "---------------------------------------------------------------------------"

echo -e "\n# check for handling relative_path #"
strace -f -F -o ./straceout2.txt $BINARYFILE -c $column_item -d ./ -o $RELAPATH > pid_output2.txt
./grade_pid -s ./pid_output2.txt ./straceout2.txt
return_code=$(echo $?)
if [ $return_code -eq 1 ];then
    echo "0 pt"
else
	echo "5 pts"
fi
echo -e "---------------------------------------------------------------------------"

echo -e "\n# test for correct outputing to assigned directory#"

# full_path
echo -e "\n# full_path: expected finding 4 sorted csv files #"
cd ..
cd full_path

num_ok=0
num_wrong=0
for i in a b c d; do
testFile="./dataset2_$i-sorted-director_name.csv"
if [ -f "$testFile" ]; then 
	echo "Found 'dataset2_$i-sorted-director_name.csv'"
	let num_ok++
else
	echo "Not found 'dataset2_$i-sorted-director_name.csv'"
    let num_wrong++
fi
done

echo "num_ok(${num_ok}), num_false(${num_wrong})"
if [ $num_ok -eq 4 ]; then 
	echo "[SUCCESS] 2.5 pts for successfully outputing to full_path"
else
	echo "[FAIL] 0 pt for failing in outputing to full_path"
fi
echo -e "---------------------------------------------------------------------------"


# relative_path
echo -e "\n# relative_path: expected finding 4 sorted csv files #"
cd ..
cd relative_path

num_ok=0
num_wrong=0
for i in a b c d; do
testFile="./dataset2_$i-sorted-director_name.csv"
if [ -f "$testFile" ]; then 
	echo "Found 'dataset2_$i-sorted-director_name.csv'"
	let num_ok++
else
	echo "Not found 'dataset2_$i-sorted-director_name.csv'"
    let num_wrong++
fi
done

echo "num_ok(${num_ok}), num_false(${num_wrong})"
if [ $num_ok -eq 4 ]; then 
	echo "[SUCCESS] 2.5 pts for successfully outputing to relative_path"
else
	echo "[FAIL] 0 pt for failing in outputing to relative_path"
fi
echo -e "---------------------------------------------------------------------------"

cd ..
echo "############################## TEST 3 #####################################"
cd test3

echo -e "\n*** test3: 3 csvs in the current directory, 2 sub directories, each with 2 csvs ***"
echo "should produce 10 processes in total, including initial process"
column_item="movie_title"

echo -e "\n# check for proper pid output & correct number processes #"
strace -f -F -o ./straceout3.txt $BINARYFILE -c $column_item > pid_output3.txt
./grade_pid -s ./pid_output3.txt ./straceout3.txt
return_code=$(echo $?)
if [ $return_code -eq 0 ];then
    echo "get 10 pts: 5 pts for proper pid output, 5 pts for correct number processes"
else
	echo "if [OK] for proper pid output, get 5 pts"
	echo "if [OK] for correct number processes, get 5 pts"
	echo "otherwise, 0 pt"
fi
echo -e "---------------------------------------------------------------------------"

num_ok=0
num_wrong=0

echo -e "\n# test for correct outputing to assigned directories #"

# current directory
for i in a b c; do
testFile="./dataset3_$i-sorted-movie_title.csv"
if [ -f "$testFile" ]; then 
	echo "Found 'dataset3_$i-sorted-movie_title.csv' in folder 'test3'"
	let num_ok++
else
	echo "Not found 'dataset3_$i-sorted-movie_title.csv in folder 'test3'"
    let num_wrong++
fi
done

# sub1 folder
cd sub1
for i in a b; do
testFile="./dataset1_$i-sorted-movie_title.csv"
if [ -f "$testFile" ]; then 
	echo "Found 'dataset1_$i-sorted-movie_title.csv' in folder 'sub1'"
	let num_ok++
else
	echo "Not found 'dataset1_$i-sorted-movie_title.csv in folder 'sub1'"
    let num_wrong++
fi
done


cd ..
# sub2 folder
cd sub2
for i in a b; do
testFile="./dataset2_$i-sorted-movie_title.csv"
if [ -f "$testFile" ]; then 
	echo "Found 'dataset2_$i-sorted-movie_title.csv' in folder 'sub2'"
	let num_ok++
else
	echo "Not found 'dataset2_$i-sorted-movie_title.csv in folder 'sub2'"
    let num_wrong++
fi
done

echo "num_ok(${num_ok}), num_false(${num_wrong})"
if [ $num_ok -eq 7 ]; then 
	echo "[SUCCESS] 5 pts for successfully outputing to right directories"
else
	echo "[FAIL] 0 pt for failing in outputing to right directories"
fi
echo -e "---------------------------------------------------------------------------"

cd ..
cd ..
echo "############################## TEST 4 #####################################"
cd test4

echo -e "\n*** test4: 0 csvs in current directory, 3 sub directories, 1 with 1 csv, 1 with 2 csvs, 1 with 3 csvs ***"
echo "should produce 10 processes in total, including initial process"
column_item="movie_title"

echo -e "\n# check for proper pid output & correct number processes #"
strace -f -F -o ./straceout4.txt $BINARYFILE -c $column_item > pid_output4.txt
./grade_pid -s ./pid_output4.txt ./straceout4.txt
return_code=$(echo $?)
if [ $return_code -eq 0 ];then
    echo "get 10 pts: 5 pts for proper pid output, 5 pts for correct number processes"
else
	echo "if [OK] for proper pid output, get 5 pts"
	echo "if [OK] for correct number processes, get 5 pts"
	echo "otherwise, 0 pt"
fi
echo -e "---------------------------------------------------------------------------"

num_ok=0
num_wrong=0

echo -e "\n# test for correct outputing to assigned directories #"


# sub1 folder
cd sub1
for i in a; do
testFile="./dataset1_$i-sorted-movie_title.csv"
if [ -f "$testFile" ]; then 
	echo "Found 'dataset1_$i-sorted-movie_title.csv' in folder 'sub1'"
	let num_ok++
else
	echo "Not found 'dataset1_$i-sorted-movie_title.csv in folder 'sub1'"
    let num_wrong++
fi
done


cd ..
# sub2 folder
cd sub2
for i in a b; do
testFile="./dataset2_$i-sorted-movie_title.csv"
if [ -f "$testFile" ]; then 
	echo "Found 'dataset2_$i-sorted-movie_title.csv' in folder 'sub2'"
	let num_ok++
else
	echo "Not found 'dataset2_$i-sorted-movie_title.csv in folder 'sub2'"
    let num_wrong++
fi
done


cd ..
# sub3 folder
cd sub3
for i in a b c; do
testFile="./dataset3_$i-sorted-movie_title.csv"
if [ -f "$testFile" ]; then 
	echo "Found 'dataset3_$i-sorted-movie_title.csv' in folder 'sub3'"
	let num_ok++
else
	echo "Not found 'dataset3_$i-sorted-movie_title.csv in folder 'sub3'"
    let num_wrong++
fi
done

echo "num_ok(${num_ok}), num_false(${num_wrong})"
if [ $num_ok -eq 6 ]; then 
	echo "[SUCCESS] 5 pts for successfully outputing to right directories"
else
	echo "[FAIL] 0 pt for failing in outputing to right directories"
fi
echo -e "---------------------------------------------------------------------------"

cd ..
cd ..
echo "############################## TEST 5 #####################################"
cd test5

echo -e "\n*** test5: check handling directories with random (non csv files) ***"
strace -f -F -o ./straceout5.txt $BINARYFILE -c $column_item > pid_output5.txt
cat pid_output5.txt
./grade_pid -s ./pid_output5.txt ./straceout5.txt

return_code=$(echo $?)
if [ $return_code -eq 0 ];then
    echo "get 5 pts: for successfully handling directories with random"
else
	echo "get 0 pt: for failing in handling directories with random"
fi
echo -e "---------------------------------------------------------------------------"


cd ..
echo "############################## TEST 6 #####################################"
cd test6

echo -e "\n*** test6: check handling directory that does not exist gracefully  ***"
$BINARYFILE -c $column_item -d ./sub1 -o ./

echo -e "\nPlease check [MANUALLY], if the program gracefully deal with directory that does not exist"
echo "if gracefully: get 5 pts"
echo "otherwise: get 0 pt"
echo -e "---------------------------------------------------------------------------"



echo "############################## OTHERS #####################################"
echo -e "\n*** others: check documentation and segfaults ***\n"

echo "Please check the documentation: 5 pts"
echo "For any segfaults please -10 pts"
echo -e "---------------------------------------------------------------------------"



cd ..
echo "############################## EXRTA 1 #####################################"
cd extra1
echo -e "\n*** extra credit 1: sorting by several fields, 10 pts in total ***"
echo -e "If the student implements or includes the work for extra 1\n"

echo -e "# test for 2 fields [actor_1_name] & [movie_title]: 5 extra pts #"
$BINARYFILE -c actor_1_name,movie_title 
echo -e "\n"
# testFile="./extra1-sorted-actor_1_name-movie_title.csv"
testFile="./extra1-sorted-actor_1_name,movie_title.csv"
answerFile="./extra1_2_fields.txt"
./checking_answer 2 actor_1_name movie_title $testFile $answerFile
return_code=$(echo $?)
if [ $return_code -eq 0 ];then
    echo "get 5 pts: for successfully handling sorting by two fields"
else
	echo "get 0 pt: for failing in handling sorting by two fields"
fi

echo -e "\n---------------------------------------------------------------------------\n"

echo -e "# test for 3 fields [actor_1_name] & [movie_facebook_likes] & [movie_title]: 5 extra pts #"
$BINARYFILE -c actor_1_name,movie_facebook_likes,movie_title
echo -e "\n"
# testFile="./extra1-sorted-actor_1_name-movie_facebook_likes-movie_title.csv"
testFile="./extra1-sorted-actor_1_name,movie_facebook_likes,movie_title.csv"
answerFile="./extra1_3_fields.txt"
./checking_answer 3 actor_1_name movie_facebook_likes movie_title $testFile $answerFile
return_code=$(echo $?)
if [ $return_code -eq 0 ];then
    echo "get 5 pts: for successfully handling sorting by three fields"
else
	echo "get 0 pt: for failing in handling sorting by three fields"
fi

echo -e "---------------------------------------------------------------------------"


echo "############################## EXRTA 2 #####################################"
echo -e "\n*** extra credit 2: output the hierarchy of forked process, 10 pts in total ***"

echo -e "\nIf the student includes the work for extra 2\n"
echo "Please check [MANUALLY], by comparing output file named similar to 'extracredit2.txt' with tracing file 'straceout.txt'"
echo "suggested: document 2 + output file 6 + visualization 2 = 10 pts"

echo -e "\n**************************************************************************"