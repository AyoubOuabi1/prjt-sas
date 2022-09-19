#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//structs sections
struct Produit{
    char  code[20];
    char  nom[20];
    int   quantite;
    float prix;
    float prixTtc;
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

void reWriteFile(int n){
    FILE *fptr;
    int i;
    fptr = fopen("ProduitData.txt","w");
    for(i = 0; i < lineCount; ++i)
    {
    	//code
        fputs(prd[i].code, fptr);
        fprintf(fptr, "/");
        
        //nom
        fputs(prd[i].nom, fptr);
        fprintf(fptr, "/");
        
        //quantite
		fprintf(fptr, "%d /",prd[i].quantite);
		
        //prix
        fprintf(fptr, "%.2f\n",prd[i].prix);
    }
    fclose(fptr);
}
void getAllProduct(){
	char data[200][200];
   
    int i;
    FILE *file;
    file= fopen("ProduitData.txt","r");
    
    while(!feof(file)){
    	if(fgets(data[lineCount],200,file)!=NULL){
    		lineCount++;
		}
    	
    	
    	 
	}

	fclose(file);
	for(i=0;i<lineCount;i++){
		char* item =strtok(data[i],"/");
		//code 
		strcpy(prd[i].code,item);
		//nom
		item=strtok(NULL,"/");
		strcpy(prd[i].nom,item);
		//quantite
		item=strtok(NULL,"/");
		prd[i].quantite=atof(item);
		//prix
		item=strtok(NULL,"/");
		prd[i].prix= atof(item);
	}
	
}
//calcule de prix avec ttc--> prix * 15%
float calculeTtc(float prix){
	float ttc;
	ttc=prix *0.15;
	return ttc;
	
}
//print 
void printData(){
	
	int i;
	float pTtc;
    for (i=0;i<lineCount;i++){
		printf("le nom : %s  le prix : %.2f  / le prix ttc est : %.2f \n ", prd[i].nom, prd[i].prix,calculeTtc(prd[i].prix));
	}
}

//Sort Functions 
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
//sell new product 
void sellNewProduct(){
	
}
//search functions section
int searchByCode(char code[20]){
	int i,index;
	for(i=0;i<lineCount;i++){
		if(prd[i].code==code){
			return i;
		}
	}
	return 0;
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
    sortByPrice();
    return 0;
}
