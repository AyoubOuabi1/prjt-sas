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
    int  dateDeVente[3];
};
struct ProductSales{
	char  code[20];
    char  nom[20];
    int   quantite;
    float prix;
    float prixttc;
    float prixtotal;
    int  dateDeVente[3];
};
//static and struct variable
static int lineCount=0;
static int salesCount=0;
struct Produit prd[200];
struct ProductSales pSales[200];
//funftions section
//files 
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
        scanf("%[^\n]%*c",&p[i].nom);
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
        printf("\n\nproduct  number added with successful %d \n",i+1);
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
    fprintf(fptr, "the code of the product : ");
    fputs(pSales[i].code, fptr);
    

    //nom
    fprintf(fptr, " / the name of the product : ");
    fputs(pSales[i].nom, fptr);
   

    //quantite
    fprintf(fptr, " / the quantity : %d  / ",qntVente);

    //prix ttc 
    fprintf(fptr, "the price with ttc : %.2f  / ",pSales[i].prixttc);
    // date
    fprintf(fptr, "date : %d-%d-%d\n",pSales[i].dateDeVente[0],pSales[i].dateDeVente[1],pSales[i].dateDeVente[2]);

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
    	printf("\t\t\t  ---------------------------------------------------------------------\n");
    	printf("\t\t\t  |  PRODUCT NAME |  PRODUCT PRICE  | PRODUCT PRICETTC | \n");
    	printf("\t\t\t  ---------------------------------------------------------------------\n");
        printf("\t\t\t   %s          	%.2f      		%.2f\n", prd[i].nom,prd[i].prix,calculeTtc(prd[i].prix)+prd[i].prix);
    }
}

//search functions section
int getCodeIndex(char code[20]){
    int i;
    for(i=0;i<lineCount;i++){
        if(strcmp(prd[i].code,code)==0){
            return i;
        }
        
    }
    return -1;
}
void searchProductByCode(char code[20]){
	int i=getCodeIndex(code);
	if(i>=0){
		printf("\t\t\t  ---------------------------------------------------------------------\n");
    	printf("\t\t\t  |  PRODUCT NAME |  PRODUCT PRICE  | PRODUCT PRICETTC | \n");
    	printf("\t\t\t  ---------------------------------------------------------------------\n");
        printf("\t\t\t   %s          	%.2f      	%.2f\n", prd[i].nom,prd[i].prix,calculeTtc(prd[i].prix)+prd[i].prix);
	}else {
		printf("\n\ncode not found\n\n");
	}
	backToMenu();
}
void searchByQuantite(int qnt){
    int i;
    for (i=0;i<lineCount;i++){
        if(prd[i].quantite==qnt){
            printf("\t\t\t  ---------------------------------------------------------------------\n");
    		printf("\t\t\t  |  PRODUCT NAME |  PRODUCT PRICE  | PRODUCT PRICETTC | \n");
    		printf("\t\t\t  ---------------------------------------------------------------------\n");
        	printf("\t\t\t   %s          	%.2f      	%.2f\n", prd[i].nom,prd[i].prix,calculeTtc(prd[i].prix)+prd[i].prix);
        }
    }
    backToMenu();
}
//sell new product
void sellNewProduct(){
    char code[20];
   
    time_t tim;
    time(&tim);
    struct tm *dt=localtime(&tim);
    int i,qnt;
    printf("enter the code of the product :  ");
    scanf("%s",&code);
    if(getCodeIndex(code)>=0){
        i=getCodeIndex(code);
        printf("\t\t\t  -------------------------------------------------------------------------------------\n");
    	printf("\t\t\t  |  PRODUCT NAME | PRODUCT QUANTITY |  PRODUCT PRICE  | PROD PRICETTC | \n");
    	printf("\t\t\t  -------------------------------------------------------------------------------------\n");
        printf("\t\t\t   %s                %d            %.2f      %.2f\n", prd[i].nom,prd[i].quantite,prd[i].prix,calculeTtc(prd[i].prix)+prd[i].prix);
        printf("\n\nenter the quantity of the product :  ");
        scanf("%d",&qnt);
        if(prd[i].quantite>=qnt){
            prd[i].quantite=prd[i].quantite-qnt;
            strcpy(pSales[salesCount].code,prd[i].code);
            strcpy(pSales[salesCount].nom,prd[i].nom);
            pSales[salesCount].quantite=qnt;
            pSales[salesCount].prixttc=calculeTtc(prd[i].prix)+prd[i].prix;
            pSales[salesCount].prixtotal=pSales[salesCount].prixttc*qnt;
            pSales[salesCount].dateDeVente[0]= dt->tm_mday;
            pSales[salesCount].dateDeVente[1]= dt->tm_mon + 1;
            pSales[salesCount].dateDeVente[2]=dt->tm_year + 1900;
            insertSalesIntoFile(salesCount,qnt);
            salesCount++;
            reWriteFile();
            printf("\n\nsave with successful \n\n");
            backToMenu();
        }else
            printf("\n\nout of stock\n\n");
			backToMenu();


    }else
        printf("\n\ncode not found\n\n");
        backToMenu();

}
//Sort Functions
char sortByAlpha(){
    int i,j,d;
    struct Produit c[lineCount];
    for(i=0;i<lineCount;i++){
        for(j=i+1;j<lineCount;j++){
            if(prd[i].nom[0]>prd[j].nom[0]){
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


            }else if(prd[i].nom[0]==prd[j].nom[0]){
            	if(prd[i].nom[1]>=prd[j].nom[1]){
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
    }
    printData();
	backToMenu();
}

char sortByPrice(){
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
    int i;
    for(i=0;i<lineCount;i++){
            if(prd[i].quantite<3){
                printf("\t\t\t  -------------------------------------------------------------------------------------\n");
    			printf("\t\t\t  |  PRODUCT NAME | PRODUCT QUANTITY |  PRODUCT PRICE  | PRODUCT PRICETTC | \n");
    			printf("\t\t\t  -------------------------------------------------------------------------------------\n");
        		printf("\t\t\t   %s               	%d          	%.2f      		%.2f\n", prd[i].nom,prd[i].quantite,prd[i].prix,calculeTtc(prd[i].prix)+prd[i].prix);

            }
    }
	backToMenu();
}
//remove product from the stock 
void deletePrd(){
	char code[20];
	printf("enter the code of the product :  ");
    scanf("%s",&code);
    int i,qnt,c;
    if(getCodeIndex(code)>=0){
        i=getCodeIndex(code);
        printf("/n are sure you want to delete this product to confirm press 1 to skip it press 2 :  ");
        scanf("%d",&c);
        if(c==1){
        	 while(i<lineCount){
        	 	//code
            	strcpy(prd[i].code,prd[i+1].code);
              
            	//nom
            	strcpy(prd[i].nom,prd[i+1].nom);
            	//quantite
            	prd[i].quantite=prd[i+1].quantite;
            	//prix
            	prd[i].prix=prd[i+1].prix;
            	prd[i].dateDeVente[0]=prd[i+1].dateDeVente[0];
            	prd[i].dateDeVente[1]=prd[i+1].dateDeVente[1];
            	prd[i].dateDeVente[2]=prd[i+1].dateDeVente[2];
        		i++;
        	    printf("/n deleted with successful \n\n ");
			}
			lineCount--;
        	reWriteFile(); 
        	backToMenu();
		}else {
			backToMenu();
		}
       
        


    }else
        printf("\n\nproduct code not found\n\n");
}
//update stock 
void updateStock(){
	char code[20];
	printf("\n\nenter the code of the product :  ");
    scanf("%s",&code);
    
    int i,qnt;
    if(getCodeIndex(code)>=0){
        i=getCodeIndex(code);
        printf("\n\nenter new  quantity of the product :  ");
        scanf("%d",&qnt);
        prd[i].quantite=prd[i].quantite+qnt;
        reWriteFile();
        printf("\t\t\t  --------------------------------------------------------------------------------\n");
    	printf("\t\t\t  |  PRODUCT NAME | PRODUCT QUANTITY |  PRODUCT PRICE  | PRODUCT PRICETTC | \n");
    	printf("\t\t\t  ---------------------------------------------------------------------------------\n");
        printf("\t\t\t   %s               %d          	%.2f      	%.2f\n", prd[i].nom,prd[i].quantite,prd[i].prix,calculeTtc(prd[i].prix)+prd[i].prix);
        
        backToMenu();
        


    }else
        printf("\n\nproduct code not found\n\n");

}
//statistique section;
//total price 
float totlaPrice(){
	int i;
	float totalPrice=0,rtn;
    time_t tim;
    time(&tim);
    struct tm *dt=localtime(&tim);
	for (i=0;i<salesCount;i++){
		if(pSales[i].dateDeVente[0]== dt->tm_mday && pSales[i].dateDeVente[1]== (dt->tm_mon + 1) &&  pSales[i].dateDeVente[2]==(dt->tm_year + 1900));
		{
			totalPrice+= pSales[i].prixtotal;
		}
	 
		
	}
	rtn=totalPrice;
	return rtn ;
}
//average price 
float averagePrice(){
	float totalprice=totlaPrice();
	return totalprice/salesCount;
}

//min price 
float minPrice(){
	int i,j;
	float rtn;
	time_t tim;
    time(&tim);
    struct tm *dt=localtime(&tim);
	for(i=0;i<salesCount;i++){
		if(pSales[i].dateDeVente[0]== dt->tm_mday && pSales[i].dateDeVente[1]== (dt->tm_mon + 1) &&  pSales[i].dateDeVente[2]==(dt->tm_year + 1900));
		{
			for(j=i+1;j<salesCount;j++){
				if(pSales[i].prixttc<pSales[j].prixttc){
					rtn=pSales[i].prixttc;
					return rtn;
				}
			}
		}
	}
	
}
//max price 
float maxPrice(){
	int i,j;
	float rtn;
	time_t tim;
    time(&tim);
    struct tm *dt=localtime(&tim);
	for(i=0;i<salesCount;i++){
		if(pSales[i].dateDeVente[0]== dt->tm_mday && pSales[i].dateDeVente[1]== (dt->tm_mon + 1) &&  pSales[i].dateDeVente[2]==(dt->tm_year + 1900));
		{
			for(j=i+1;j<salesCount;j++){
				if(pSales[i].prixttc>pSales[j].prixttc){
					rtn=pSales[i].prixttc;
					return rtn;
				}
			}
		}
	}
	
}
void productStatistique(){
	int stqChoise;
	printf("            choose what you want \n");
    printf("            -------------------- \n\n\n");
    printf("choose 1 to see Total amount of  sales of the day \n\n");
    printf("choose 2 to see average price of products  \n\n");
    printf("choose 3 to see max price of products  \n\n");
    printf("choose 4 to see min price of products  \n\n");
    printf("enter your choice here :  ");
    scanf("%d",&stqChoise);
    switch (stqChoise){
    	case 1:
    		printf("\nTotal amount of sales of this day is : %.2f\n",totlaPrice());
    		break;
    	case 2:
    		printf("\nAverage price of  this day is : %.2f\n",averagePrice());
    		break;	
    	case 3:
    		printf("\nmax price  of  this day is : %.2f\n", maxPrice());
    		break;		
    	case 4:
    		printf("\nmin price of  this day is : %.2f\n",minPrice());
    		break;		
	}
	backToMenu();
}




//menu function 
void menu(){
    int choice,number,addChoise,listChoise,searchChoise,prdQnt;
    char prdCode[20];
    //system("cls");
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
            printf("\n\nenter your choice here :  ");
            scanf("%d",&listChoise);
            if(listChoise==1){
                sortByAlpha();
            }else {
               sortByPrice();
            }
            break;
        case 3:
        	system("cls");
		 	sellNewProduct();
            break;  
		case 4:
		 	system("cls");
            printf("            choose what you want \n");
            printf("            -------------------- \n\n\n");
            printf("choose 1 for search by the code\n\n");
            printf("choose 2 for search by quantity \n\n");
            printf("\n\nenter your choice here :  ");
            scanf("%d",&searchChoise);
            if(searchChoise==1){
            	printf("\n\nenter the code of the product here :  ");
            	scanf("%s",&prdCode);
                searchProductByCode(prdCode);
            }else {
            	printf("\n\nenter the quantity of the product here :  ");
            	scanf("%d",&prdQnt);
                searchByQuantite(prdQnt);
            } 	  
			break;
		case 5:
			system("cls");
		 	checkQuantity();
            break;
		case 6:
			system("cls");
		 	updateStock();
            break; 	 
		case 7:
			system("cls");
		 	deletePrd();
            break; 	
		case 8:
			system("cls");
		 	productStatistique();
            break; 	
		default :
			printf("\n\n 	try with another number \n\n");	
			menu();		
    }

}
void backToMenu(){
	int back;
	printf("\n\nto back to the menu enter 1 here :  ");
    scanf("%d",&back);
    if(back==1){
    	system("cls");
    	menu();
    	
	}
}
int main() {
	getAllProduct();
    menu();
    return 0;
}
