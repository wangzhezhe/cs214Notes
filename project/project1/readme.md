<!-- @ By SG -->

# Documentation for Project 1 Grading Scripts

## Running Steps:

1. Compile sorter.c by either of the following:
   		gcc -o sorter sorter.c 
   		gcc -o sorter sorter.c mergesort.c
   or other methods given by the student such as "make"
   notice that the executable file sholud be named "sorter"

2. Copy 7 folders {test1, test2, test3, test4, test5, test6, extra1} to the project folder

3. Copy 4 c files {grade_pid.c, grading.c, gradingnoheader.c, checking_answer.c} to the project folder

4. Copy 2 grading shell scripts {p1_grade_h.sh, p1_grade_nh.sh} to the project folder

5. Run "/bin/bash p1_grade_h.sh ./sorter" in linux shell

6. Read the grade results
 
   a. Check the documentation: 5 pts


   b. *Test 1*: sorting by movie_title in current directory, produce 5 processes in total

      * First check if the 4 output files are in the current directory and if the
        sorting result is correct. 2.5 pts for each sorting OK, in total 10 pts

      * Then check correct number of processes, 10 pts for this. And proper pid output,
        in total 10 pts: 2 pts for correct initial process id, 4 * 2 pts for correct children pids.

      * Finally check for parallel execution. The checking is based on time. So different computers have
        different speed. Please modify the two values (unit: ms) below in line 30-32 of "p1_grade_h.sh"

          # PLEASE MODIFY THE TWO VALUES BASED ON YOUR COMPUTER
          SMALL_BOUND_PARAL_TIME=16
          LARGE_BOUND_PARAL_TIME=48

        10 pts for [OK], 0 pts for [FAIL], if [POSSIBLE], please check the straceout.txt file to see if 
        child processes are running in parallel
        A serial example is in: http://www.jeyki.com/straceout_serial.txt
        A parallel example is: http://www.jeyki.com/straceout_parallel.txt


   c. *Test 2*: output sorted files to full-path or relative-path directory, produce 5 processes in total

      * First check if the program can handle full path, 5 pts

      * Then check if the program can handle relative path, 5 pts

      * Then check if the program can correctly output to assigned directory, 2.5 pts for successfully 
        outputing to full_path, and 2.5 pts for successfully outputing to relative_path


   d. *Test 3*: 3 csvs in the current directory, 2 sub directories, each with 2 csvs, produce 10 processes 
      in total

      * Check for proper pid output, 5 pts

      * Check for correct number processes, 5 pts

      * Check for successfully outputing to right directories, 5 pts


   e. *Test 4*: 0 csvs in current directory, 3 sub directories, 1 with 1 csv, 1 with 2 csvs, 1 with 3 csvs, 
      produce 10 processes in total

      * Check for proper pid output, 5 pts

      * Check for correct number processes, 5 pts

      * Check for successfully outputing to right directories, 5 pts


   f. *Test 5*: check handling directories with random (non csv files)

      * Get 5 pts for successfully handling directories with random


   g. *Test 6*: check handling directory that does not exist gracefully

      * The output is printed in shell, please check [MANUALLY], if the program gracefully deal with 
        directory that does not exist, get 5 pts. Otherwise: get 0 pt


   h. For any segfaults please -10 pts


   i. Extra credits:

   *Extra credit 1*: sorting by several fields, 10 pts in total

      * Check this section [if the student implements or includes the work for extra 1] 

      * Test for 2 fields [actor_1_name] & [movie_title], get 5 extra pts for successfully handling sorting 
        by two fields. Otherwise, get 0 pt

      * Test for 3 fields [actor_1_name] & [movie_facebook_likes] & [movie_title], get 5 extra pts 
        for successfully handling sorting by three fields. Otherwise, get 0 pt


   *Extra credit 2*: check handling directory that does not exist gracefully

      * Check this section [if the student implements or includes the work for extra 2] 

      * Please check [MANUALLY], by comparing output file named similar to 'extracredit2.txt' with tracing 
        file 'straceout.txt'. Suggested credits distribution: document 2 pts + output file 6 pts + visualization 
        2 pts = 10 pts




ps: If the student's output does not include fields header, you can
grade by "/bin/bash p1_grade_nh.sh ./sorter". At the same time, please follow
the comment to slightly modify the grade_pid.c in line 88, line 138, line 187, 
line 193, and line 199. Should deduct some points for no header!

  
pps: The grading script is for the standard output. If the script is failed,
please run the following scripts, and check [manually]:

#Preparing:

for i in {1..6}; do
  testFolder="test$i"
  cp sorter $testFolder
done

cp sorter extra1
mkdir full_path
mkdir relative_path



#Test1: 
cd test1

## running the sorter, output tracing file, stdout, and time
START=`date +%s%N`;
strace -f -F -o ./straceout1.txt ./sorter -c movie_title
END=`date +%s%N`;
time=$((END-START))
time=`expr $time / 1000000`
echo $time


cd ..
cd full_path
FULLPATH=$(pwd)
cd ..
#Test2:
cd test2
CRNTPATH=$(pwd)
RELAPATH=../relative_path


## check for handling full_path
strace -f -F -o ./straceout2.txt ./sorter -c director_name -d $CRNTPATH -o $FULLPATH

## check for handling relative_path
strace -f -F -o ./straceout2.txt ./sorter -c director_name -d ./ -o $RELAPATH


cd ..
#Test3:
cd test3

strace -f -F -o ./straceout3.txt ./sorter -c movie_title


cd ..
#Test4:
cd test4

strace -f -F -o ./straceout4.txt ./sorter -c movie_title


cd ..
#Test5:
cd test5

strace -f -F -o ./straceout5.txt ./sorter -c movie_title


cd ..
#Test6:
cd test6

./sorter -c movie_title -d ./sub1 -o ./


cd ..
#Extra credit 1:
cd extra1

./sorter -c actor_1_name,movie_title
# then compare the output file with "extra1_2_fields.txt"

./sorter -c actor_1_name,movie_facebook_likes,movie_title
# then compare the output file with "extra1_3_fields.txt"



#Extra credit 2:
# check by graders
# document 2 + output file 6 + visualization 2 = 10

<!-- @ By SG -->