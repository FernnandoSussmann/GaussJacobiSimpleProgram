#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
#define PAUSE 1
#else
#define PAUSE 0
#endif

void atribuiValores(float *, float *, float *, float *, float *);
void printaPorraToda(float *, float *, float *, float *, float, float, float);
void printaPorraTodaResolucao(float *, float *, float *, float *, float, float, float);
float gaussJacob(float *, float *, float *, float *, float *, float *, float *);
float maiorNumero(float *);
float modulo(float);

int main(){

   int i;
   float a[3], b[3], c[3], resultado[3], x1 = 0, x2 = 0, x3 = 0, epsilon, dr;

   atribuiValores(a,b,c,resultado, &epsilon);

   printf("\n %f \n", epsilon);

   printaPorraToda(a,b,c,resultado,x1,x2,x3);	

   x1 = resultado[0] / a[0];
   x2 = resultado[1] / b[1];
   x3 = resultado[2] / c[2];

   do {
	printaPorraTodaResolucao(a,b,c,resultado,x1,x2,x3);

	dr = gaussJacob(a,b,c,resultado,&x1,&x2,&x3);
   }while (dr > epsilon);
   

   if(PAUSE==1)
     system("pause");
   else
     system("read -p \"Pressione enter para sair\" saindo");
  return(0); 
}

void atribuiValores(float *a, float *b, float *c, float *resultado, float *epsilon){
   int i;

   printf("Digite o valor de epsilon (mais conhecida como letra romana que seu professor coloca como limite):\n");
   scanf("%f", epsilon);

   for(i = 0; i < 3; i++){
      printf("Digite o valor de a da funcao (com sinal) %d:\n", i + 1);
      scanf("%f", a + i);

      printf("Digite o valor de b da funcao (com sinal) %d:\n", i + 1);
      scanf("%f", b + i);

      printf("Digite o valor de c da funcao (com sinal) %d:\n", i + 1);
      scanf("%f", c + i);

      printf("Digite o valor do resultado da funcao %d:\n", i + 1);
      scanf("%f", resultado + i);
  }	
}

void printaPorraToda(float *a, float *b, float *c, float *resultado, float x1, float x2, float x3){
   int i;
    if (x1 == 0 && x2 == 0 && x3 ==0)
       for(i = 0; i < 3; i++){
         printf("\n%.2fx1 + ", *(a + i));

         printf("%.2fx2 + ", *(b + i));

         printf("%.2fx3 = ", *(c + i));

         printf("%.2f", *(resultado + i));
      }	
    else{
	for(i = 0; i < 3; i++){
         printf("\n%.2f(%.2f) + ", *(a + i), x1);

         printf("%.2f(%.2f) + ", *(b + i), x2);

         printf("%.2f(%.2f) = ", *(c + i), x3);

         printf("%.2f", *(resultado + i));
      }	
     }


   printf("\n\n");
}

void printaPorraTodaResolucao(float *a, float *b, float *c, float *resultado, float x1, float x2, float x3){
   int i;

   printf("x1 = 1/%.2f(%.2f - %.2f(%.2f) - %.2f(%.2f))\n", *a, *resultado, *b, x2, *c, x3);
   printf("x2 = 1/%.2f(%.2f - %.2f(%.2f) - %.2f(%.2f))\n", *(b + 1), *(resultado + 1), *(a + 1), x1, *(c + 1), x3);
   printf("x3 = 1/%.2f(%.2f - %.2f(%.2f) - %.2f(%.2f))\n", *(c + 2), *(resultado + 2), *(a + 2), x1, *(b + 2), x2);   

   printf("\n\n");
}


float gaussJacob(float *a, float *b, float *c, float *resultado, float *x1, float *x2, float *x3){
   int i;
   float xNovo[3], maiorDiferenca, maiorNovo, xDiferenca[3], dr;

   xNovo[0] = (1/ *a) * (*resultado - *b * *x2 - *c * *x3);
   xNovo[1] = (1/ *(b+1)) * (*(resultado+1) - *(a+1) * *x1 - *(c+1) * *x3);
   xNovo[2] = (1/ *(c+2)) * (*(resultado+2) - *(a+2) * *x1 - *(b+2) * *x2);

   for (i = 0; i < 3; i++)
     printf("x%d = %.2f \n",i + 1, xNovo[i]);

   xDiferenca[0] = xNovo[0] - *x1;
   xDiferenca[1] = xNovo[1] - *x2;
   xDiferenca[2] = xNovo[2] - *x3;


   for (i = 0; i < 3; i++)
     printf("\n diferenca de x%d = %.2f \n",i + 1, modulo(xDiferenca[i]));

   maiorDiferenca = maiorNumero(xDiferenca);
   maiorNovo = maiorNumero(xNovo);

   dr = maiorDiferenca/maiorNovo;

   x1 = xNovo;
   x2 = xNovo + 1;
   x3 = xNovo + 2;
 
   return 0;

   printf("\n\n");
}

float maiorNumero(float *comparacao){
   if (modulo(*comparacao) > modulo(*(comparacao + 1)) && modulo(*comparacao) > modulo(*(comparacao + 2))){
      return modulo(*comparacao);
   }
   else {
       if (modulo(*(comparacao + 1)) > modulo(*(comparacao + 2))){
	  return modulo(*(comparacao + 1));
	}
       else{
	  return modulo(*(comparacao + 2));
	}
   }
}

float modulo(float modulo){
   if (modulo < 0){
      return modulo * -1;
   }
   else {
      return modulo;
   }
}
