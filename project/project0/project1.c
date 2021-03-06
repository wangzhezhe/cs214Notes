#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define STRLEN 3000
#define ARRAYLEN 30
#define INPUTCOLUME 28
#define LINENUM 10000

typedef struct
{
    char *token[ARRAYLEN];
    
} Row;

const char *header[] = {"color","director_name","num_critic_for_reviews","duration","director_facebook_likes","actor_3_facebook_likes","actor_2_name","actor_1_facebook_likes","gross","genres","actor_1_name","movie_title","num_voted_users","cast_total_facebook_likes","actor_3_name","facenumber_in_poster","plot_keywords","movie_imdb_link","num_user_for_reviews","language","country","content_rating","budget","title_year","actor_2_facebook_likes","imdb_score","aspect_ratio","movie_facebook_likes"};
static int sortIndex;


int cmpfunc(Row* a, Row* b){

    
    int elemTypea=checkType(a->token[sortIndex]);
    int elemTypeb=checkType(b->token[sortIndex]);

    //if (elemTypea!=elemTypeb){
    //    printf("sorting element is in different type (%s,%s)\n",a->token[sortIndex],b->token[sortIndex]);
    //    exit(EXIT_FAILURE);
    //}

    //empty value return -1

    //integer return2

    //float return1

    //string return0

    if(elemTypea==-1 && elemTypeb!=-1){
        elemTypea=elemTypeb;
    }
    
    if(elemTypeb==-1 && elemTypea!=-1){
        elemTypeb=elemTypea;
    }
    if(elemTypeb==-1 && elemTypea==-1){
        elemTypea=0;
        elemTypeb=0;
    }

    if(elemTypea==0){
        if (strcmp(a->token[sortIndex],b->token[sortIndex])<0){
            return -1;
        }else{
            return 1;
        }
    }else if(elemTypea==2){
        int Inta=atof(a->token[sortIndex]);
        int Intb=atof(b->token[sortIndex]);
        if(Inta<Intb){
            return -1;
        }else{
            return 1;
        }
    }else{
        float fa=atof(a->token[sortIndex]);
        float fb=atof(b->token[sortIndex]);
        if(fa<fb){
            return -1;
        }else{
            return 1;
        }
    }
}

int containComma(char *str){
    int len =strlen(str);
    int i=0;
    for(i=0;i<len;i++){
        if(str[i]==','){
            return 1;
        }
    }
    return 0;
}

//assume all the input is valid 
int checkType(char str[])
{

    int len = strlen(str);
    char *strtemp = str;
    int i = 0;

    while (*strtemp == '\0')
    {
        return -1;
    }

    while (*strtemp == ' ')
    {
        strtemp++;
    }

    //special input: 50 Cent...

    if (*strtemp >= '0' && *strtemp <= '9')
    {

        char *strfilter = strtemp;

        while (*strfilter != '\0')
        {
            if ((*strfilter) < '0' || (*strfilter) > '9')
            {
                if ((*strfilter) == '.' || (*strfilter) == ' ')
                {
                    strfilter++;
                    continue;
                }
                else
                {
                    return 0;
                }
            }
            strfilter++;
        }

        while (*strtemp != '\0')
        {
            if (*strtemp == '.')
            {
                return 1;
            }
            strtemp++;
        }
        return 2;
    }

    return 0;

    //empty value return -1

    //integer retur2

    //float return1

    //string return0
}

void split(char *returnstr[], char *inputstr, char seprator)
{
    if(inputstr==NULL){
        printf("return str is NULL\n");
        exit(EXIT_FAILURE);
    }

   //printf("inpit (%s)\n",inputstr);
    int len = strlen(inputstr);
    //int len=INPUTCOLUME;
    int lindex = 0;
    int rindex = 0;
    int flag = 0;
    int num = 0;
    char *temp = inputstr;
    for (rindex = 0; rindex <= len; rindex++,temp++)
    {

        if (rindex == len)
        {
            returnstr[num] = (char*)malloc(rindex - lindex + 2);
            if (returnstr[num]==NULL){
                printf("malloc fail\n");
                exit(EXIT_FAILURE);
            }
            memcpy(returnstr[num], inputstr + lindex, rindex - lindex);
            //the last value is '\n' for this case
            char *last = returnstr[num] + rindex - lindex - 1;
            if (*last == '\n')
            {
                if(*(last-1)=='"'){
                    *(returnstr[num] + rindex - lindex - 2) = '\0';
                    
                }else{
                    *(returnstr[num] + rindex - lindex - 1) = '\0';
                }
                
            }
            else
            {
                *(returnstr[num] + rindex - lindex)  = '\0';
            }

            //printf("token:(%s)\n", returnstr[num]);
            num++;
            break;
        }
        if(*temp == '"' && flag==0){
            lindex = rindex + 1;
            flag=1;
            continue;
        }
        if(*temp == ','&& *(temp-1)=='"' && flag==1){
            returnstr[num] = (char*)malloc(rindex - lindex + 2);
            if (returnstr[num]==NULL){
                printf("malloc fail\n");
                exit(EXIT_FAILURE);
            }
            memcpy(returnstr[num], inputstr + lindex, rindex - lindex-1);
            *(returnstr[num] + rindex - lindex ) = '\0';
            flag=0;
            lindex = rindex+1;
            num++;
            continue;
        }
        
        if (*temp == ',' && flag==0)
        {
            //printf("debug\n");
            returnstr[num] = (char* )malloc(rindex - lindex + 2);
            if (returnstr[num]==NULL){
                printf("malloc fail\n");
                exit(EXIT_FAILURE);
            }
            memcpy(returnstr[num], inputstr + lindex, rindex - lindex);
            *(returnstr[num] + rindex - lindex + 1) = '\0';
            //printf("token:(%s)\n", returnstr[num]);
            lindex = rindex + 1;
            num++;
        }
        
    }
}

int checkSortIndex(char str[]){
    int i=0;
    //printf("get sort item %s\n",str);
    //printf("%s\n",header[1]);
    //printf("%d\n",strcmp(str,header[1]));



    for(i=0;i<INPUTCOLUME;i++){
        //printf("%s %d\n",header[i],i);
        if(strcmp(str,header[i])==0){
            return i;
        }
    }
    
    return -1;
}

void main(int argc,char*argv[])
{
    //printf("argc num (%d)\n",argc);
    if(argc!=3){
        printf("using by this way: ./sorter -c  movie_title\n");
        exit(EXIT_FAILURE);
    }
    //printf("%s\n",argv[1]);
    if(strcmp(argv[1],"-c")!=0){
        printf("using by this way: ./sorter -c  movie_title\n");
        exit(EXIT_FAILURE);
    }

    //get sort index

    sortIndex=checkSortIndex(argv[2]);
    if (sortIndex==-1){
        printf("using valid index\n");
        exit(EXIT_FAILURE);
    }

    //printf("get sortIndex: sort index (%d,%s)",sortIndex,argv[2]);
    

    char input[STRLEN];
    int index = 0;
    char *line[ARRAYLEN];
    Row row[LINENUM];
    char *token;
    //FILE *file;
    //file = fopen("movie_metadata_dname.csv", "at+");


    //get first line and process the input argument
    if(fgets(input, STRLEN, stdin) != NULL){
        //printf("header (%s)\n",input);
        printf("%s",input);
    }


    int lineNum=0;
    while (fgets(input, STRLEN, stdin) != NULL)
    {
        int i=0;
        for(i=0;i<ARRAYLEN;i++){
            line[i]=NULL;
        }
        //printf("debug, linenum (%d)\n", lineNum);

        split(line,input, ',');

        for(i=0;i<INPUTCOLUME;i++){
            row[lineNum].token[i]=line[i];
            //printf("index (%d), value(%s), sizeof row (%ld)\n",i,row[lineNum].token[i],sizeof(row));
         }
         lineNum++;
    }
    //fclose(file);
    qsort(row,lineNum,sizeof(Row),cmpfunc);
    
    
    //output to file 
    
    //FILE * outputFile=fopen("ouput","w++");
    int i=0;
    int j=0;
    


    //attention add quatation mark back!!!
    for(i=0;i<lineNum;i++){
        // no quotation for the first item
         sprintf(input,"%s",row[i].token[0]);
         for(j=1;j<INPUTCOLUME;j++){
           if(containComma(row[i].token[j])==1){
            sprintf(input,"%s,\"%s\"",input,row[i].token[j]);
           }else{
            sprintf(input,"%s,%s",input,row[i].token[j]);
           }
          
           //printf("%s\n",row[i].token[j]);
         }
        sprintf(input,"%s\n",input);
        //outputFile=fopen("testoutput","rw");
        //fprintf(outputFile,"%s",input);
        printf("%s",input);
    }

    //fclose(outputFile);
    
}
