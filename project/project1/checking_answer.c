#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUF 512
#define MAX_ROW 20
#define INPUTCOLUMN 28
#define MAX_ARG 6

const char *header[] = {"color", "director_name", "num_critic_for_reviews", "duration", "director_facebook_likes", "actor_3_facebook_likes", "actor_2_name", "actor_1_facebook_likes", "gross", "genres", "actor_1_name", "movie_title", "num_voted_users", "cast_total_facebook_likes", "actor_3_name", "facenumber_in_poster", "plot_keywords", "movie_imdb_link", "num_user_for_reviews", "language", "country", "content_rating", "budget", "title_year", "actor_2_facebook_likes", "imdb_score", "aspect_ratio", "movie_facebook_likes"};

int checkSortIndex(char str[])
{
    int i = 0;
    //printf("get sort item %s\n",str);
    //printf("%s\n",header[1]);
    //printf("%d\n",strcmp(str,header[1]));

    for (i = 0; i < INPUTCOLUMN; i++)
    {
        //printf("%s %d\n",header[i],i);
        if (strcmp(str, header[i]) == 0)
        {
            return i;
        }
    }

    return -1;
}

int main (int argc, char *argv[])
{

  if (atoi(argv[1]) <= 0)
  {
      printf("using by this way 3 arguments: ./checking_answer 3 actor_1_name movie_facebook_likes movie_title $testFile $answerFile\n");
      printf("using by this way 2 arguments: ./checking_answer 2 actor_1_name movie_title $testFile $answerFile\n");
      exit(EXIT_FAILURE);
  }
  // printf("argv[1]: good\n");

  if (argc != 4 + atoi(argv[1]))
  {
      printf("using by this way 3 arguments: ./checking_answer 3 actor_1_name movie_facebook_likes movie_title $testFile $answerFile\n");
      printf("using by this way 2 arguments: ./checking_answer 2 actor_1_name movie_title $testFile $answerFile\n");
      exit(EXIT_FAILURE);
  }
  // printf("argc: good\n");

  int indices[MAX_ARG] = {-1};
  int k;
  for (k = 0; k < atoi(argv[1]); k++)
  {
    if (checkSortIndex(argv[k+2]) >= 0)
    {
      indices[k] = checkSortIndex(argv[k+2]);
      // printf("%d\n", indices[k]);
    }
    else
    {
      printf("please check the name of your %d argument\n", k+2);
      exit(EXIT_FAILURE);
    }
  }
  // printf("fields: good\n");

  FILE *fp;
  char path[MAX_BUF];
  char *line;
  char direct_str[MAX_BUF];
  char movie_str[MAX_BUF];
  char like_num[MAX_BUF];
  int column_num = atoi(argv[1]);
  size_t len=0; 
  char directs[MAX_ROW][MAX_BUF];
  char movies[MAX_ROW][MAX_BUF];
  int likes[MAX_ROW];
  int row_num;
  
  int idx = column_num + 2;
  strcpy(path, argv[idx]);
  //printf("path: %s\n", path);

  fp = fopen(path, "r");

  if(fp!=NULL)
  {
    getline(&line, &len, fp); // including header, if no header, comment this line
    int j = 0;
    while (getline(&line, &len, fp) > 0)
    {
      // printf("%s", line);
      if (column_num == 2)
      { 
        sscanf(line, "%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%[^,],%[^,]", direct_str, movie_str);
        strcpy(directs[j], direct_str);
        // printf("directs[j]: %s\n", directs[j]);
        strcpy(movies[j], movie_str);
        // printf("movies[j]: %s\n\n", movies[j]);
        j++;
      }
      if (column_num == 3)
      { 
        sscanf(line, "%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%[^,],%[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%[^,]", direct_str, movie_str, like_num);
        strcpy(directs[j], direct_str);
        // printf("directs[j]: %s\n", directs[j]);
        strcpy(movies[j], movie_str);
        // printf("movies[j]: %s\n", movies[j]);
        likes[j] = atoi(like_num);
        // printf("likes[j]: %d\n\n", atoi(likes[j]));
        j++;
      }
    }
    row_num = j;
    // printf("row_num: %d\n", row_num);
  }
  else
  {
    fprintf(stdout, "FP is NULL\n");
  }

  fclose(fp);
 

  char right_directs[MAX_ROW][MAX_BUF];
  char right_movies[MAX_ROW][MAX_BUF];
  int right_likes[MAX_ROW];
  int right_row_num;

  idx = idx + 1;
  strcpy(path, argv[idx]);
  //printf("path: %s\n", path);

  fp = fopen(path, "r");

  if(fp!=NULL)
  {
    getline(&line, &len, fp); // including header, if no header, comment this line
    int j = 0;
    while (getline(&line, &len, fp) > 0)
    {
      // printf("%s", line);
      if (column_num == 2)
      { 
        sscanf(line, "%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%[^,],%[^,]", direct_str, movie_str);
        strcpy(right_directs[j], direct_str);
        // printf("right_directs[j]: %s\n", right_directs[j]);
        strcpy(right_movies[j], movie_str);
        // printf("right_movies[j]: %s\n\n", right_movies[j]);
        j++;
      }
      if (column_num == 3)
      { 
        sscanf(line, "%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%[^,],%[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%[^,]", direct_str, movie_str, like_num);
        strcpy(right_directs[j], direct_str);
        // printf("right_directs[j]: %s\n", right_directs[j]);
        strcpy(right_movies[j], movie_str);
        // printf("right_movies[j]: %s\n", right_movies[j]);
        right_likes[j] = atoi(like_num);
        // printf("right_likes[j]: %d\n\n", atoi(right_likes[j]));
        j++;
      }
    }
    right_row_num = j;
    // printf("right_row_num: %d", right_row_num);
  }
  else
  {
    fprintf(stdout, "FP is NULL\n");
  }

  fclose(fp);

  

  if (right_row_num != row_num)
  {
    printf("[FAIL], row number does not match\n");
    return -1;
  }
  
  int i;
  for (i = 0; i < right_row_num; i++)
  {
    if (strcmp(right_directs[i],directs[i]) != 0)
    {
      //if no header i+1
      printf("[FAIL], director_name [output: %s, real: %s] in line %d does not match\n",directs[i], right_directs[i], i+2); 
      return 1;
    }
    if (strcmp(right_movies[i],movies[i]) != 0)
    {
      //if no header i+1
      printf("[FAIL], movie_title [output: %s, real: %s] in line %d does not match\n",movies[i], right_movies[i], i+2);
      return 1;
    }
    if (right_likes[i] != likes[i]) 
    {
      //if no header i+1
      printf("[FAIL], movie_facebook_likes [output: %d, real: %d] in line %d does not match\n", likes[i], right_likes[i], i+2);
      return 1;
    }
  }

  printf("[SUCCESS] sorting results are right\n");
  return 0;
}