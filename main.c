#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//structs sections
struct Produit{
    char  code[20];
    char  nom[20];
    int   quantite;
    float prix;
    float prixTtc;
    int  dateDeVente[3];
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

void reWriteFile(){
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

void insertSalesIntoFile(int i,int qntVente){
    FILE *fptr;
     fptr = fopen("SalesData.txt","a");


    //code
    fputs(prd[i].code, fptr);
    fprintf(fptr, "/");

    //nom
    fputs(prd[i].nom, fptr);
    fprintf(fptr, "/");

    //quantite
    fprintf(fptr, "%d /",qntVente);

    //prix
    fprintf(fptr, "%.2f/",prd[i].prix);
    fprintf(fptr, "%d-%d-%d\n",prd[i].dateDeVente[0],prd[i].dateDeVente[1],prd[i].dateDeVente[2]);

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
    for (i=0;i<lineCount;i++){
        printf("le nom : %s la quantite est : %d / le prix : %.2f  / le prix ttc est : %.2f \n ", prd[i].nom,prd[i].quantite, prd[i].prix,calculeTtc(prd[i].prix)+prd[i].prix);
    }
}

//search functions section
int getCodeIndex(char code[20]){
    int i;
    for(i=0;i<lineCount;i++){
        if(strcmp(prd[i].code,code)==0){
            return i;
        }else {

        }
    }
    return -1;
}
void searchProductByCode(char code[20]){
    if(getCodeIndex(code)>=0){
        int i=getCodeIndex(code);
        printf("le nom : %s / le prix : %.2f  / le prix ttc est : %.2f \n ", prd[i].nom, prd[i].prix,calculeTtc(prd[i].prix)+prd[i].prix);
    }else
        printf("saisir un autre code");

}
void searchByQuantite(int qnt){
    int i;
    for (i=0;i<lineCount;i++){
        if(prd[i].quantite==qnt){
            printf("le nom : %s  le prix : %.2f  / le prix ttc est : %.2f \n", prd[i].nom, prd[i].prix,calculeTtc(prd[i].prix)+prd[i].prix);
        }
    }
}
//sell new product
void sellNewProduct(){
    char code[20];
    time_t currentTime;
    //time(&currentTime);
    time_t tim;
    time(&tim);
    struct tm *dt=localtime(&tim);
    int i,qnt;
    printf("entrez le code de produit");
    scanf("%s",&code);
    if(getCodeIndex(code)>=0){
        i=getCodeIndex(code);
        printf("entrez la quantite");
        scanf("%d",&qnt);
        if(prd[i].quantite>=qnt){
            prd[i].quantite=prd[i].quantite-qnt;
            prd[i].dateDeVente[0]= dt->tm_mday;
            prd[i].dateDeVente[1]= dt->tm_mon + 1;
            prd[i].dateDeVente[2]=dt->tm_year + 1900;
             printf("le nom : %s la quantite est : %d / le prix : %.2f  / le prix ttc est : %.2f est la date de vente %d/%d/%d \n ", prd[i].nom,prd[i].quantite, prd[i].prix,calculeTtc(prd[i].prix)+prd[i].prix
                    ,prd[i].dateDeVente[0],prd[i].dateDeVente[1],prd[i].dateDeVente[2]);
            insertSalesIntoFile(i,qnt);
            reWriteFile();
            getAllProduct();
        }else
            printf("la quantite demand superieure la quantite en stock");



    }else
        printf("entrez un autre code");

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
char sortByQuantity(){
    getAllProduct();
    int i;
    for(i=0;i<lineCount;i++){
            if(prd[i].quantite<3){
                printf("le nom : %s la quantite est : %d / le prix : %.2f  / le prix ttc est : %.2f \n ", prd[i].nom,prd[i].quantite, prd[i].prix,calculeTtc(prd[i].prix)+prd[i].prix);

            }
    }
    printData();

}
int main() {

    sortByQuantity();
    return 0;
}
