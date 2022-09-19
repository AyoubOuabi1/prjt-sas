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
	//printf("%d \n ",lineCount);
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
//print 
void printData(){
	//getAllProduct();
	int i;
    for (i=0;i<lineCount;i++){
		printf("le code : %s / le nom : %s / la quantite est : %d / le prix : %.2f \n ",prd[i].code,prd[i].nom,prd[i].quantite,prd[i].prix);
	}
}
//calcule de prix avec ttc--> prix * 15%
float calculeTtc(float prix){
	float ttc;
	ttc=prix *0.15;
	return ttc;
	
}
//comapre two char 
char sortByAlpha(){
	getAllProduct();
	int i,j,d;
	struct Produit c[lineCount];
	for(i=0;i<lineCount;i++){
		for(j=i+1;j<lineCount;j++){
			if(prd[i].code[0]>=prd[j].code[0]){
				//code
				
				strcpy(c[i].code,prd[i].code);
				strcpy(prd[i].code,prd[j].code);
				strcpy(prd[j].code,c[i].code);
				//nom
				strcpy(c[i].nom,prd[i].nom);
				strcpy(prd[i].nom,prd[j].nom);
				strcpy(prd[j].nom,c[i].nom);
				//quantite 
				c[i].quantite=prd[i].quantite;
				prd[i].quantite=prd[j].quantite;
				prd[j].quantite=c[i].quantite;
				//prix 
				c[i].prix=prd[i].prix;
				prd[i].prix=prd[j].prix;
				prd[j].prix=c[i].prix;
				
				
			}
		}
	}
	printData();

}

char sortByPrice(){
	getAllProduct();
	int i,j,d;
	struct Produit c[lineCount];
	for(i=0;i<lineCount;i++){
		for(j=i+1;j<lineCount;j++){
			if(prd[i].prix<=prd[j].prix){
				//code
				
				strcpy(c[i].code,prd[i].code);
				strcpy(prd[i].code,prd[j].code);
				strcpy(prd[j].code,c[i].code);
				//nom
				strcpy(c[i].nom,prd[i].nom);
				strcpy(prd[i].nom,prd[j].nom);
				strcpy(prd[j].nom,c[i].nom);
				//quantite 
				c[i].quantite=prd[i].quantite;
				prd[i].quantite=prd[j].quantite;
				prd[j].quantite=c[i].quantite;
				//prix 
				c[i].prix=prd[i].prix;
				prd[i].prix=prd[j].prix;
				prd[j].prix=c[i].prix;
				
				
			}
		}
	}
	printData();

}
int main() {
    //float prx=14.98;
    //printf("%.2f",calculeTtc(prx));
    //char f[10][20]={"ayoub","taza","mohamed","fes","mjid","jalil","aicha","huawei","dell","youness"};
    //char e[10][20];
    //e=compare(f);
    sortByPrice();
    return 0;
}
