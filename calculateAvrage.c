#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

void readFromFile(char fileName[], char message[]){
   FILE *fp = fopen(fileName, "r"); 
  int ch = getc(fp); 
  int lines = 0;
  double sum = 0.0;
  double el;
  while (ch != EOF)  
  { 
    fscanf(fp, "%lf", &el);
    sum = sum + el;
    lines = lines + 1;
    ch = getc(fp); 
  } 
  // printf("%f \n", sum);
  // printf("%d \n", lines);
  double result = sum / lines;
  printf("%f \n", result);
  fclose(fp); 
  FILE *ff = fopen("averages.txt", "a+"); 
  fprintf(ff, "%s %f \n",message,result);
  fclose(ff);
}

int main (int argc, char *argv[])
{


  char fileName1[50] = "result/Secventialinvertcolor.txt";
  char fileName2[50] = "result/Secventialblurcolor.txt";
  char fileName3[50] = "result/Secventialrotate90.txt";
  char fileName4[50] = "result/Secventialrotate180.txt";
  char fileName5[50] = "result/Secventialrotate270.txt";


  char fileName6[50] = "result/Parallelinvertcolor.txt";
  char fileName7[50] = "result/Parallelblurcolor.txt";
  char fileName8[50] = "result/Parallelrotate90.txt";
  char fileName9[50] = "result/Parallelrotate180.txt";
  char fileName10[50] = "result/Parallelrotate270.txt";
 
  // readFromFile(fileName1,"secv invertColor: ");
  // readFromFile(fileName2, "secv blurColor: ");
  // readFromFile(fileName3,"secv rotate90: ");
  // readFromFile(fileName4,"secv rotate180: ");
  // readFromFile(fileName5,"secv rotate270: ");
  readFromFile(fileName6,"par invertColor: ");
  readFromFile(fileName7,"par blurColor: ");
  readFromFile(fileName8,"par rotate90: ");
  readFromFile(fileName9,"par rotate180: ");
  readFromFile(fileName10,"par rotate270: ");
    FILE *ff = fopen("averages.txt", "a+"); 
  fprintf(ff, "\n");
  fclose(ff);
}

