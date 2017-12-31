This is the scripts for grading sorting project for class 214

project1.c is the sample code for sorting (without using merge sort for the convenience)

grading.c is the grading scripts to make sure the output file sorted by specific item.

rungrade.sh is used for run the grade file by different sorting item, the first element is the path of the dataset file the second one is path of binaryfile from students

dataset1.csv: 10 records, no special cases (no null fields, no trailing/leading space, no double quotes/special characters, no commas in titles)

dataset2.csv: 20 records, include capital letters, leading spaces, trailing spaces, commas in titles, null fields

dataset3.csv: Original movie_metadata.csv

dataset2.csv: Original movie_metadata.csv, duplicate appx 2000 records for a total of ~7000 records

```
gcc -o grade ./grading.c
gcc -o gradenoheader ./gradingnoheader.c
gcc -o project ./project1.c
```

if output of sorting project include header

```
./rungrade_h.sh ./<binary file>
```
if not include header

```
./rungrade_nh.sh ./<binary file>
```


