////////////////////////////////////////////////////Running Steps//////////////////////////////////////////////////////////////////

1. Compile sorter.c by either of the following:

   gcc -lpthread -o sorter sorter.c 
   gcc -lpthread -o sorter sorter.c mergesort.c
   
   or other methods given by the student such as "make"
   Note that the executable file sholud be named "sorter"

2. Copy 7 folders {test1, test2, test3, test4, test5, test6, collections_for_output_files} to the project folder

3. Copy 2 c files {check_sorting.c, check_thread.c} to the project folder

4. Copy 1 grading shell script {PA2_grader.sh} to the project folder

5. Copy the blank file 'grading_record.txt' to the project folder to record grading information.

6. Run "/bin/bash PA2_grader.sh" in linux shell

7. Read the results:
   For each test, the script prints a message asking for input. Please read the information in terminal from executable sorter:
        "Initial PID: XXXXX
         TIDS of all child threads: AAA,BBB,CCC,DDD,EEE,FFF (... etc.)
         Total number of threads: ZZZZZ"
   and provide the total number of threads (ZZZZZ) for that test.
   
8. At the end, record the accumulated elapsed time shown in the terminal (the script runs sorter on test (4.1) for 10 times and records the total time automatically). 
   I  will do the stats and provide the 10% and 30% cutting point. 


Important Note:
    The initial directory is counted. E.g., if input_dir="./test1/test1.1", a thread needs to be launched to handle the initial directory "./test1/test1.1"
    
    However, some students might have a different way to count the total number of threads. For example, they might only count the threads that actually sort the files.
    In this case, you may flexibly reset the following values in the shell script PA2_grader.sh for each test to handle these special cases.
    
    ############# reset value ############
    real_threads_number=10   # reset value to handle special case
    real_movies_num=140      # reset value to handle special case
    ######################################


///////////////////////////////////////////////////Dataset Description////////////////////////////////////////////////////////////////
The number of threads for each test:
  test1.1:          10  threads
  test1.2:          8   threads
  test2.1:          32  threads
  test2.2:          24  threads
  test3.1:          17  threads
  test4.1:          272 threads
  test5.1:          10  threads
  test5.2:          10  threads
  test6.1:          10  threads


The number of csv files within each test folder:
  test1.1:          7  csv files
  test1.2:          5  csv files
  test2.1:          16 csv files
  test2.2:          8  csv files
  test3.1:          16 csv files
  test4.1:          16*16=256 csv files
  test5.1:          7 csv files
  test5.2:          7 csv files
  test6.1:          7 csv files (there are 2 additional invalid .o files)
  

The number of movies in each csv file:
  dataset1_a.csv:   20
  dataset1_b.csv:   20
  dataset1_c.csv:   20
  dataset1_d.csv:   20

  dataset2_a.csv:   20
  dataset2_b.csv:   20
  dataset2_c.csv:   20
  dataset2_d.csv:   20

  dataset3_a.csv:   20
  dataset3_b.csv:   20
  dataset3_c.csv:   20

  dataset4_a.csv:   20
  dataset4_b.csv:   20
  dataset4_c.csv:   20
  dataset4_d.csv:   20
  dataset4_e.csv:   20


/////////////////////////////////////////////////////////////Rubric Description/////////////////////////////////////////////////////////////////////////
[0] documentation 10pts
(0.1) General desciption 5pts
      Document the design, assumptions, difficulties encountered and testing procedure.
(0.2) Time analysis 5pts
      If the documentation does not contain elapsed time comparison between multiprocessing sorter in PA1 and multithreading sorter in PA2, 
      give 0 pts for time analysis

[1] Basic test 
(1.1) 15pts: with -c, -d, -o, involving a few sub-directories, each contains a few files
(1.2) 15pts: with -c, -d, -o, involving a few sub-directories, but some of them contains no file

[2] Test for directory structure
(2.1) 10pts: with -c, -d, -o, involving long sub-directory chain, each contains only one file
(2.2) 10pts: with -c, -d, -o, involving long sub-directory chain, some contain only one file, others contain no file

[3] Test for file amount
(3.1) 10pts: with -c, -d, -o, involving only one directory (one layer), which contains lots of files

[4] combination test for directory structure and file amount, with timing
(4.1) 15pts: with -c, -d, -o, combine long sub-directory and lots of files, while timing the accumulated elapsed time by executing sorter on test (4.1) for 10 times

[5] test for input argument
(5.1) 5pts: basic test (1.1) without -o (the default behavior of your code should be to store the sorted file in the current directory)
(5.2) 5pts: basic test (1.1) with a reversing argument order: -o, -d, -c

[6] test for format check
(6.1) 5pts: basic test (1.1) with non-csv files (should ignore them and still work)

[7] extra points for timing
Top 10: 30pts
Top 30: 10pts
no significant difference: 5pts
     
After all TAs have recorded the time in test (4.1), TAs can send all elapsed-time to me, then I sort the time and give them the 10% and 30% cutting point. 
