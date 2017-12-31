#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUF 3000
#define INT_SIZE_BUF 8
#define CHILD_ARRAY_BUF 16

typedef struct
{
    int init_pid;
    int child_pid[CHILD_ARRAY_BUF];
    int pid_num;
    int total_proc_num;
} pid_info;

int containComma(char *str)
{
    int len = strlen(str);
    int num = 0;
    int i;
    for (i = 0; i < len; i++)
    {
        if (str[i] == ',')
        {
            num++;
        }
    }
    return num;
}

int ifEndByComma(char *str)
{
    int len = strlen(str);
    int i;
    if (str[len-2] == ',')
    {
          return 1;
    }
    return 0;
}

int ifEndBySpacing(char *str)
{
    int len = strlen(str);
    int i;
    if (str[len-2] == ' ')
    {
          return 1;
    }
    return 0;
}

void bubble_sort(int arr[], int len) {
  int i, j, temp;
  for (i = 0; i < len - 1; i++)
    for (j = 0; j < len - 1 - i; j++)
      if (arr[j] > arr[j + 1]) {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
}

int main (int argc, char *argv[])
{
  if (argc != 4)
  {
      printf("using by this way for verbose : ./grade_pid -v ./pid_output.txt ./straceout.txt\n");
      printf("using by this way for short   : ./grade_pid -s ./pid_output.txt ./straceout.txt\n");
      exit(EXIT_FAILURE);
  }

  if (strcmp(argv[1], "-v") != 0 && strcmp(argv[1], "-s") != 0)
  {
      printf("using by this way for verbose : ./grade_pid -v ./pid_output.txt ./straceout.txt\n");
      printf("using by this way for short   : ./grade_pid -s ./pid_output.txt ./straceout.txt\n");
      exit(EXIT_FAILURE);
  }
  
  FILE *fp;

  char path[MAX_BUF];
  char *line;
  char *child_line;
  int init_pid_str;
  int pid_num_str;
  int comma_num;
  char format[MAX_BUF];
  int cpid[CHILD_ARRAY_BUF];
  int child_pid[CHILD_ARRAY_BUF];
  int init_pid;
  int total_proc_num;
  size_t len=0; 
  
  // get info from student's pid output
  strcpy(path, argv[2]);
  //printf("path: %s\n", path);

  fp = fopen(path, "r");

  if(fp!=NULL)
  {
    getline(&line, &len, fp);
    sscanf(line, "%*[^:]: %d", &init_pid_str);
    init_pid = init_pid_str;
    if (strcmp(argv[1], "-v") == 0)
    {
      printf("output_init_pid: %d\n", init_pid);
    }

    getline(&child_line, &len, fp);

    getline(&line, &len, fp);
    sscanf(line, "%*[^:]: %d", &pid_num_str);
    int pid_num = pid_num_str;
    if (strcmp(argv[1], "-v") == 0)
    {
      printf("output_pid_num: %d\n", pid_num);
    }
    
    comma_num=containComma(child_line);
    
    strcpy(format,"%*[^:]: ");
    if (ifEndByComma(child_line))
    {
      total_proc_num = comma_num + 1;
      if (strcmp(argv[1], "-v") == 0)
      {
        printf("output_total_proc_num: %d\n", total_proc_num);
      }
      int i;
      for (i = 0; i < comma_num; i++)
      {
        strcat(format, "%d,");
      }
      
      switch (comma_num)
      {
        case 1:  sscanf(child_line, format, &cpid[0]); break;
        case 2:  sscanf(child_line, format, &cpid[0], &cpid[1]); break;
        case 3:  sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2]); break;
        case 4:  sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3]); break;
        case 5:  sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4]); break;
        case 6:  sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5]); break;
        case 7:  sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5], &cpid[6]); break;
        case 8:  sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5], &cpid[6], &cpid[7]); break;
        case 9:  sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5], &cpid[6], &cpid[7], &cpid[8]); break;
        case 10: sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5], &cpid[6], &cpid[7], &cpid[8], &cpid[9]); break;
        case 11: sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5], &cpid[6], &cpid[7], &cpid[8], &cpid[9], &cpid[10]); break;
        case 12: sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5], &cpid[6], &cpid[7], &cpid[8], &cpid[9], &cpid[10], &cpid[11]); break;
        case 13: sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5], &cpid[6], &cpid[7], &cpid[8], &cpid[9], &cpid[10], &cpid[11], &cpid[12]); break;
        case 14: sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5], &cpid[6], &cpid[7], &cpid[8], &cpid[9], &cpid[10], &cpid[11], &cpid[12], &cpid[13]); break;
        case 15: sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5], &cpid[6], &cpid[7], &cpid[8], &cpid[9], &cpid[10], &cpid[11], &cpid[12], &cpid[13], &cpid[14]); break;
        case 16: sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5], &cpid[6], &cpid[7], &cpid[8], &cpid[9], &cpid[10], &cpid[11], &cpid[12], &cpid[13], &cpid[14], &cpid[15]); break;
        default: printf("error\n");
      }
      bubble_sort(cpid, comma_num);
      printf("output_child_pid: ");
      for (i = 0; i < comma_num; i++)
      {
        child_pid[i] = cpid[i];
        printf("%d,", child_pid[i]);
      }
      printf("\n");  
    }
    else
    {
      if (ifEndBySpacing(child_line))
      {
        total_proc_num = comma_num + 1;
        if (strcmp(argv[1], "-v") == 0)
        {
          printf("output_total_proc_num: %d\n", total_proc_num);
        }
        printf("output_child_pid: ");
      }
      else
      {
        total_proc_num = comma_num + 2; 
        if (strcmp(argv[1], "-v") == 0)
        {
          printf("output_total_proc_num: %d\n", total_proc_num);
        }
        int i;
        for (i = 0; i < comma_num; i++)
        {
          strcat(format, "%d,");
        }
        strcat(format, "%d");

        switch (comma_num)
        {
          case 0:  sscanf(child_line, format, &cpid[0]); break;
          case 1:  sscanf(child_line, format, &cpid[0], &cpid[1]); break;
          case 2:  sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2]); break;
          case 3:  sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3]); break;
          case 4:  sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4]); break;
          case 5:  sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5]); break;
          case 6:  sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5], &cpid[6]); break;
          case 7:  sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5], &cpid[6], &cpid[7]); break;
          case 8:  sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5], &cpid[6], &cpid[7], &cpid[8]); break;
          case 9:  sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5], &cpid[6], &cpid[7], &cpid[8], &cpid[9]); break;
          case 10: sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5], &cpid[6], &cpid[7], &cpid[8], &cpid[9], &cpid[10]); break;
          case 11: sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5], &cpid[6], &cpid[7], &cpid[8], &cpid[9], &cpid[10], &cpid[11]); break;
          case 12: sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5], &cpid[6], &cpid[7], &cpid[8], &cpid[9], &cpid[10], &cpid[11], &cpid[12]); break;
          case 13: sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5], &cpid[6], &cpid[7], &cpid[8], &cpid[9], &cpid[10], &cpid[11], &cpid[12], &cpid[13]); break;
          case 14: sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5], &cpid[6], &cpid[7], &cpid[8], &cpid[9], &cpid[10], &cpid[11], &cpid[12], &cpid[13], &cpid[14]); break;
          case 15: sscanf(child_line, format, &cpid[0], &cpid[1], &cpid[2], &cpid[3], &cpid[4], &cpid[5], &cpid[6], &cpid[7], &cpid[8], &cpid[9], &cpid[10], &cpid[11], &cpid[12], &cpid[13], &cpid[14], &cpid[15]); break;
          default: printf("error\n");
        }
        bubble_sort(cpid, comma_num+1);
        printf("output_child_pid: ");
        for (i = 0; i < comma_num; i++)
        {
          child_pid[i] = cpid[i];
          printf("%d,", child_pid[i]);
        }
        child_pid[comma_num] = cpid[comma_num];
        printf("%d", child_pid[comma_num]);
        printf("\n");  
      }
    } 
  }
  else
  {
    fprintf(stdout, "FP is NULL\n");
  }

  fclose(fp);

  // get info from student's pid tracing file
  strcpy(path, argv[3]);
  //printf("path: %s\n", path);
  
  char buf[INT_SIZE_BUF];
  int real_total_proc_num;
  int real_init_pid;
  int new_pid;
  int real_cpid[CHILD_ARRAY_BUF] = {0};
  int cp_num = 0;
  int j;

  fp = fopen(path, "r");

  if(fp!=NULL)
  {
    getline(&line, &len, fp);
    sscanf(line, "%[^ ]", buf);
    real_init_pid = atoi(buf);
    if (strcmp(argv[1], "-v") == 0)
    {
      printf("real_init_pid: %d\n", real_init_pid);
    }
    
    while (getline(&line, &len, fp) > 0)
    {
      int neq_num = 0;
      sscanf(line, "%[^ ]", buf);
      new_pid = atoi(buf);
      for (j = 0; j < CHILD_ARRAY_BUF; j++)
      {
        if (new_pid != real_cpid[j] && real_cpid[j] != 0)
        {
          neq_num++;
        }
      }
      if (neq_num == cp_num && new_pid != real_init_pid)
      {
        real_cpid[cp_num] = new_pid;
        cp_num++;
      }
    }
    
    bubble_sort(real_cpid, cp_num);
    printf("real_child_pid: ");
    for (j = 0; j < cp_num; j++)
    {
      printf("%d,", real_cpid[j]);
    }
    printf("\n");


    real_total_proc_num = cp_num + 1;
    if (strcmp(argv[1], "-v") == 0)
    {
      printf("real_total_proc_num: %d\n", real_total_proc_num);
    }
  }
  else
  {
    fprintf(stdout, "FP is NULL\n");
  }

  fclose(fp);


  if (strcmp(argv[1], "-v") == 0)
  {
    if (total_proc_num == real_total_proc_num)
    {
      printf("[OK], processes number is correct: 10 pts\n");
    }
    else
    {
      printf("[FAIL], processes number is wrong: 0 pt\n");
    }

    if (real_init_pid == init_pid)
    {
      printf("[OK], initial process id is correct: 2 pts\n");
    }
    else
    {
      printf("[FAIL], initial process id is wrong: 0 pt\n");
    }

    int k;
    int right_num = 0;

    for (k = 0; k < real_total_proc_num - 1; k++)
    {
      if (child_pid[k] == real_cpid[k])
      {
        right_num++;
      }
    }
    if (right_num > 0)
    {
      printf("[OK], %d of %d child process ids are correct: %d pts\n", right_num, real_total_proc_num-1, 2*right_num);
    }
    else
    {
      printf("[FAIL], all child process ids are incorrect: 0 pt\n");
    }
  }
  
  if (strcmp(argv[1], "-s") == 0)
  {
    int flag = 1;
    if (total_proc_num == real_total_proc_num)
    {
      printf("[OK], processes number is correct\n");
    }
    else
    {
      printf("[FAIL], processes number is wrong\n");
      flag = 0;
    }

    if (real_init_pid == init_pid)
    {
      printf("[OK], initial process id is correct\n");
    }
    else
    {
      printf("[FAIL], initial process id is wrong\n");
      flag = 0;
    }

    int k;
    int right_num = 0;

    for (k = 0; k < real_total_proc_num - 1; k++)
    {
      if (child_pid[k] == real_cpid[k])
      {
        right_num++;
      }
    }
    
    if (right_num == real_total_proc_num - 1)
    {
      printf("[OK], all child process ids are correct\n");
    }
    else
    {
      printf("[FAIL], child process ids are incorrect\n");
      flag = 0;
    }

    if (flag == 1)
    {
      printf("[SUCCESS]\n");
    }
    else
    {
      printf("[FAIL]\n");
      return 1;
    }
  }

  return 0;
}