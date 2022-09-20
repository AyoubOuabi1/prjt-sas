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
	system("cls");
    FILE *fptr;
    int i;
    struct Produit p[n];
    fptr = fopen("ProduitData.txt","a");
    for(i = 0; i < n; ++i)
    {
        fflush(stdin);
         printf("\nproduct  number %d \n",i+1);
        //code
        printf("\nenter the code of the product :  ");
        scanf("%s",&p[i].code);
        fputs(p[i].code, fptr);
        fprintf(fptr, "/");
        //nom
        printf("\nenter the name of the product : ");
        scanf("%s",&p[i].nom);
        fputs(p[i].nom, fptr);
        fprintf(fptr, "/");
        //quantite
        printf("\nenter the quantity of the product :");
        scanf("%d",&p[i].quantite);
        fprintf(fptr, "%d /",p[i].quantite);
        //prix
        printf("\nenter the price of the product : ");
        scanf("%f",&p[i].prix);
        fprintf(fptr, "%.2f \n",p[i].prix);
    }
    fclose(fptr);
    backToMenu();
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
    	printf("\t\t\t  -----------------------------------------------------\n");
    	printf("\t\t\t  |  PROD NAME |  PROD PRICE  | PROD PRICETTC | \n");
    	printf("\t\t\t  -----------------------------------------------------\n");
        printf("\t\t\t   %s          %.2f      %.2f\n", prd[i].nom,prd[i].prix,calculeTtc(prd[i].prix)+prd[i].prix);
    }
}

//search functions section
int getCodeIndex(char code[20]){
    int i;
    //getAllProduct();
    for(i=0;i<lineCount;i++){
        if(strcmp(prd[i].code,code)==0){
            return i;
        }
    }
    //return -1;
}
void searchProductByCode(char code[20]){
	int i;
	for(i=0;i<lineCount;i++){
        if(strcmp(prd[i].code,code)==0){
           printf("\t\t\t  -----------------------------------------------------\n");
    		printf("\t\t\t  |  PROD NAME |  PROD PRICE  | PROD PRICETTC | \n");
    		printf("\t\t\t  -----------------------------------------------------\n");
        	printf("\t\t\t   %s          %.2f      %.2f\n", prd[i].nom,prd[i].prix,calculeTtc(prd[i].prix)+prd[i].prix);
        }
    }
//    if(i>=0){
//        printf("\t\t\t  -----------------------------------------------------\n");
//    	printf("\t\t\t  |  PROD NAME |  PROD PRICE  | PROD PRICETTC | \n");
//    	printf("\t\t\t  -----------------------------------------------------\n");
//        printf("\t\t\t   %s          %.2f      %.2f\n", prd[i].nom,prd[i].prix,calculeTtc(prd[i].prix)+prd[i].prix);
//        
//    }else
//        printf("saisir un autre code\n\n");
	backToMenu();
}
void searchByQuantite(int qnt){
	//getAllProduct();
    int i;
    for (i=0;i<lineCount;i++){
        if(prd[i].quantite==qnt){
            printf("\t\t\t  -----------------------------------------------------\n");
    		printf("\t\t\t  |  PROD NAME |  PROD PRICE  | PROD PRICETTC | \n");
    		printf("\t\t\t  -----------------------------------------------------\n");
        	printf("\t\t\t   %s          %.2f      %.2f\n", prd[i].nom,prd[i].prix,calculeTtc(prd[i].prix)+prd[i].prix);
        }
    }
    backToMenu();
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
    printf("enter the code of the product");
    scanf("%s",&code);
    if(getCodeIndex(code)>=0){
        i=getCodeIndex(code);
        printf("enter the quantity of the product");
        scanf("%d",&qnt);
        if(prd[i].quantite>=qnt){
            prd[i].quantite=prd[i].quantite-qnt;
            prd[i].dateDeVente[0]= dt->tm_mday;
            prd[i].dateDeVente[1]= dt->tm_mon + 1;
            prd[i].dateDeVente[2]=dt->tm_year + 1900;
            insertSalesIntoFile(i,qnt);
            reWriteFile();
            getAllProduct();
            backToMenu();
        }else
            printf("la quantite demande superieure la quantite en stock");



    }else
        printf("invalid");

}
//Sort Functions
char sortByAlpha(){
    //getAllProduct();
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
	backToMenu();
}

char sortByPrice(){
    //getAllProduct();
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
	backToMenu();
}
char checkQuantity(){
    //getAllProduct();
    int i;
    for(i=0;i<lineCount;i++){
            if(prd[i].quantite<3){
                printf("\t\t\t  -----------------------------------------------------\n");
    			printf("\t\t\t  |  PROD NAME | PROD QUANTITY |  PROD PRICE  | PROD PRICETTC | \n");
    			printf("\t\t\t  -----------------------------------------------------\n");
        		printf("\t\t\t   %s               %d          %.2f      %.2f\n", prd[i].nom,prd[i].quantite,prd[i].prix,calculeTtc(prd[i].prix)+prd[i].prix);

            }
    }
	backToMenu();
}
//menu function 
void menu(){
    int choice,number,addChoise,listChoise,searchChoise,prdQnt;
    char prdCode[20];
    system("cls");
    printf("		//////////////////////////////////////////////////////////\n");
    printf("		//             Pharmacy System Managment                // \n");
    printf("		//////////////////////////////////////////////////////////\n \n \n \n");
    printf("               		  choose one of the following options\n");
    printf("                          -----------------------------------\n \n");
    printf("        choose 1 for add product or many products\n");
    printf("        choose 2 for List All the Products\n");
    printf("        choose 3 for save sales \n");
    printf("        choose 4 search for the product\n");
    printf("        choose 5 for state of the stock\n");
    printf("        choose 6 for update the product in the stock\n");
    printf("        choose 7 for delete the product from the stock\n");
    printf("        choose 8 see the statistique of the sales\n\n");
    printf("enter your choice here :  ");
    scanf("%d",&choice);
    switch (choice) {
        case 1:
            system("cls");
            printf("            choose what you want \n");
            printf("            -------------------- \n\n\n");
            printf("choose 1 for add one product\n\n");
            printf("choose 2 for add many products\n\n");
            printf("enter your choice here :  ");
            scanf("%d",&addChoise);
            if(addChoise==1){
                insertIntoFile(1);
            }else {
                printf("enter how many product you want to add : ");
                scanf("%d",&number);
                insertIntoFile(number);
            }
            break;
         case 2:
		 	system("cls");
            printf("            choose what you want \n");
            printf("            -------------------- \n\n\n");
            printf("choose 1 for sort by Alphabetical order\n\n");
            printf("choose 2 for sort by price \n\n");
            printf("enter your choice here :  ");
            scanf("%d",&listChoise);
            if(listChoise==1){
                sortByAlpha();
            }else {
               sortByPrice();
            }
            break;
        case 3:
		 	sellNewProduct();
            break;  
		case 4:
		 	system("cls");
            printf("            choose what you want \n");
            printf("            -------------------- \n\n\n");
            printf("choose 1 for search by the code\n\n");
            printf("choose 2 for search by quantity \n\n");
            printf("enter your choice here :  ");
            scanf("%d",&prdCode);
            if(searchChoise==1){
            	printf("enter the code of the product here :  ");
            	scanf("%d",&prdCode);
                searchProductByCode(prdCode);
            }else {
            	printf("enter the quantity of the product here :  ");
            	scanf("%d",&prdQnt);
                searchByQuantite(prdQnt);
            } 	  
			break;
		case 5:
		 	checkQuantity();
            break; 	
    }

}
void backToMenu(){
	int back;
	printf("to back to the menu enter 1 here :  ");
    scanf("%d",&back);
    if(back==1){
    	menu();
	}
}
int main() {
	getAllProduct();
    menu();
    return 0;
}
