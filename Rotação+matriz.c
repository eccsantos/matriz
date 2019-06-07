#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <malloc.h>

float *matriz;
 int n=0;    //numero de linhas
 
void *rotate(void *value){//funcao para rotacionar a matriz de modo threadable
 int n = n;
printf("%d\n\n",n);
    for (int i=0; i<n/2; i++){//percorrer metade da matriz 
        for (int j=i; j<n+i+1; j++){//percorre a matriz do meio pra frente
            float temp[i*j+n];
            temp[i*j+n]= matriz[i*j+n];
            //algoritmo para rotacionar matriz 90º sentido horario
            matriz[i*j+n] = matriz[i*j+n];
            matriz[i*j+n] = matriz[i*j+n]; 
            matriz[i*j+n] = matriz[i*j+n]; 
            matriz[i*j+n]= *temp;
        } 
    }
    return NULL; 
} 

int main(int argc, char *argv[]){
    
    char str[] = "teste";  //declarando a string para o caminho do arquivo de entrada
    int m=0;    //numero de colunas
   
    int t=0;    //numero de threads
    FILE *arqIn, *arqOut;   //arquivos de entrada e saida
	char strFile[n*m];      //buffer para ler o arquivo
    pthread_t threads[t];   //cria um vetor de threads
    
    if (argc!=4){ //verificando a quantidade de argumentos
        fprintf(stderr,"Numero de parametros invalidos\n");
        fprintf(stderr,"Uso:\n\t %s #linhas #colunas\n",argv[0]);
        exit(1);
    }    
    
    n = (int) atoi(argv[1]); //recebendo argumento do compilador
    m = (int) atoi(argv[2]);
    t = (int) atoi(argv[3]);
    
	
    matriz = (float* ) malloc(n * m * sizeof(float)); //alocando espaço
	arqIn = fopen(str, "rb"); //abre o arquivo de entrada
    arqOut = fopen("ppso.rot","w"); //abre o arquivo de saida
    
    int i;
    int j;
    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            if(!fscanf(arqIn, "%f", &matriz[i*j+n]))
                break;
        printf("%f ",matriz[i*j+n]); //Use lf format specifier, \n is for new line
        } 
        printf("\n");
    }

    for(int i=0; i<t; i++){
        pthread_create(&threads[i], NULL, rotate, &n); //cria t threads e passa o metodo rotate para elas
    }
    
    for(int i=0; i <t; i++) {
        pthread_join(threads[i], NULL); //une os resultados
    }

    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            fprintf(arqOut, "%.2f ", matriz[i*j+n]);
        }
        fprintf(arqOut, "\n");
    }
    
    fclose(arqOut);
    fclose(arqIn);
    free(matriz);
  return 0;
}