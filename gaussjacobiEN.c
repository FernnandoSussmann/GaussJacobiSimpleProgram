#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
#define PAUSE 1
#else
#define PAUSE 0
#endif

void setValues(float *, float *, float *, float *, float *);
void printAll(float *, float *, float *, float *, float, float, float);
void printAllResolution(float *, float *, float *, float *, float, float, float);
float gaussJacob(float *, float *, float *, float *, float *, float *, float *);
float higherNumber(float *);
float module(float);

int main(){

   int i;
   float a[3], b[3], c[3], result[3], x1 = 0, x2 = 0, x3 = 0, epsilon, dr;

   setValues(a,b,c,result, &epsilon);
   printAll(a,b,c,result,x1,x2,x3);

   x1 = result[0] / a[0];
   x2 = result[1] / b[1];
   x3 = result[2] / c[2];

   do {
     printAllResolution(a,b,c,result,x1,x2,x3);

	 dr = gaussJacob(a,b,c,result,&x1,&x2,&x3);
   }while (dr > epsilon);

   printAllResolution(a,b,c,result,x1,x2,x3);

   if(PAUSE==1)
     system("pause");
   else
     system("read -p \"Press enter to exit\" exiting");

  return(0);
}

void setValues(float *a, float *b, float *c, float *result, float *epsilon){
   int i;

   printf("Insert epsilon value:\n");
   scanf("%f", epsilon);

   for(i = 0; i < 3; i++){
      printf("Insert a value (signal on) of function %d:\n", i + 1);
      scanf("%f", a + i);

      printf("Insert b value (signal on) of function %d:\n", i + 1);
      scanf("%f", b + i);

      printf("Insert c value (signal on) of function %d:\n", i + 1);
      scanf("%f", c + i);

      printf("Insert function %d value:\n", i + 1);
      scanf("%f", result + i);
  }
}

void printAll(float *a, float *b, float *c, float *result, float x1, float x2, float x3){
   int i;

   if (x1 == 0 && x2 == 0 && x3 ==0)
       for(i = 0; i < 3; i++){
         printf("\n%.2fx1 + ", *(a + i));

         printf("%.2fx2 + ", *(b + i));

         printf("%.2fx3 = ", *(c + i));

         printf("%.2f", *(result + i));
      }
    else{
	   for(i = 0; i < 3; i++){
         printf("\n%.2f(%.2f) + ", *(a + i), x1);

         printf("%.2f(%.2f) + ", *(b + i), x2);

         printf("%.2f(%.2f) = ", *(c + i), x3);

         printf("%.2f", *(result + i));
      }
     }

   printf("\n\n");
}

void printAllResolution(float *a, float *b, float *c, float *result, float x1, float x2, float x3){
   int i;

   printf("x1 = 1/%.2f(%.2f - %.2f(%.2f) - %.2f(%.2f))\n", *a, *result, *b, x2, *c, x3);
   printf("x2 = 1/%.2f(%.2f - %.2f(%.2f) - %.2f(%.2f))\n", *(b + 1), *(result + 1), *(a + 1), x1, *(c + 1), x3);
   printf("x3 = 1/%.2f(%.2f - %.2f(%.2f) - %.2f(%.2f))\n", *(c + 2), *(result + 2), *(a + 2), x1, *(b + 2), x2);

   printf("\n\n");
}


float gaussJacob(float *a, float *b, float *c, float *result, float *x1, float *x2, float *x3){
   int i;
   float xNew[3], higherDiference, higherNew, xDiference[3], dr;

   xNew[0] = (1/ *a) * (*result - *b * *x2 - *c * *x3);
   xNew[1] = (1/ *(b+1)) * (*(result+1) - *(a+1) * *x1 - *(c+1) * *x3);
   xNew[2] = (1/ *(c+2)) * (*(result+2) - *(a+2) * *x1 - *(b+2) * *x2);

   for (i = 0; i < 3; i++)
     printf("x%d = %.2f \n",i + 1, xNew[i]);

   xDiference[0] = xNew[0] - *x1;
   xDiference[1] = xNew[1] - *x2;
   xDiference[2] = xNew[2] - *x3;


   for (i = 0; i < 3; i++)
     printf("\nDiference of x%d = %.2f \n",i + 1, module(xDiference[i]));

   higherDiference = higherNumber(xDiference);
   higherNew = higherNumber(xNew);

   dr = higherDiference/higherNew;

   *x1 = *(xNew);
   *x2 = *(xNew + 1);
   *x3 = *(xNew + 2);

   printf("\ndr = %f \n\n", dr);

   return dr;
}

float higherNumber(float *comparison){
   if (module(*comparison) > module(*(comparison + 1)) && module(*comparison) > module(*(comparison + 2))){
      return module(*comparison);
   }
   else {
       if (module(*(comparison + 1)) > module(*(comparison + 2))){
	  return module(*(comparison + 1));
	}
       else{
	  return module(*(comparison + 2));
	}
   }
}

float module(float module){
   if (module < 0){
      return module * -1;
   }
   else {
      return module;
   }
}
