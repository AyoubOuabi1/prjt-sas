#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//structs sections
struct Produit{
    char  code[20];
    char  nom[20];
    int   quantite;
    float prix;
};
//static variable 
static int lineCount=0;
struct Produit prd[200];
//funftions section
void insertIntoFile(int n){
    FILE *fptr;
    int i;
    struct Produit p[n];
    fptr = fopen("ProduitData.txt","a");
    for(i = 0; i < n; ++i)
    {
        fflush(stdin);
        //code
        printf("saisir le code : ");
        scanf("%s",&p[i].code);
        fputs(p[i].code, fptr);
        fprintf(fptr, "/");
        //nom
        printf("saisir le nom: ");
        scanf("%s",&p[i].nom);
        fputs(p[i].nom, fptr);
        fprintf(fptr, "/");
        //quantite
        printf("saisir la quantite: ");
        scanf("%d",&p[i].quantite);
		fprintf(fptr, "%d /",p[i].quantite);
        //prix
        printf("saisir le prix: ");
        scanf("%f",&p[i].prix);
        fprintf(fptr, "%.2f\n",p[i].prix);
    }
    fclose(fptr);
}
void getAllProduct(){
	char data[200][200];
   
    int i;
    FILE *file;
    file= fopen("ProduitData.txt","r");
    //fgets(data,200,file);
    while(!feof(file)){
    	if(fgets(data[lineCount],200,file)!=NULL){
    		lineCount++;
		}
    	//printf("line : %s", data);
    	
    	 
	}
	//printf("line : %s", data[2]);
	fclose(file);
	printf("%d \n ",lineCount);
	//struct  Produit prd[lineCount],*p;
	for(i=0;i<lineCount;i++){
		char* item =strtok(data[i],"/");
		strcpy(prd[i].code,item);
		//printf("%s\n ",item);
		item=strtok(NULL,"/");
		strcpy(prd[i].nom,item);
		//printf("%s\n ",item);
		item=strtok(NULL,"/");
		prd[i].quantite=atof(item);
		//printf("%s\n ",item);
		item=strtok(NULL,"/");
		prd[i].prix= atof(item);
		//printf("%s\n ",item);
	}
	//p=prd;
	//return prd;
}
int main() {
    int i;
    struct  Produit pr[lineCount];
    getAllProduct();
    for (i=0;i<lineCount;i++){
		printf("le code : %s / le nom : %s / la quantite est : %d / le prix : %.2f \n ",prd[i].code,prd[i].nom,prd[i].quantite,prd[i].prix);
	}
    return 0;
}
