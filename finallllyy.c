
/* START OF PROGRAM */

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
/*----------------------------------------------------------------------------*/
/* Functions Declaration*/
void clearInput(void);
void addNewcontact(void);
void listAll(void);
void deletecontact(void);
void modifycontact(void);
void zero(void);
int findcontact(void);
int prompt(void);
int findnum (int);
/*----------------------------------------------------------------------------*/
/* Structure Declaration*/
typedef struct contact {
    int number;        /*unique account number*/
    char name[20];     /*contains name*/
    char phone[15];    /*contains phone number*/
    char email[20];           /*contains email address*/
    struct contact *next;   /*next is used to navigate through structures.*/
    int count;              /*count is used to input comments into array*/
    char payment[8];
    } Contact;
Contact *firstc,*currentc,*newc;    /*pointers*/
/* firstc is used to point to first record in list
currentc points to current record in list
newc contains address of new structure/node
*/
int cnum = 0; /*gives unique account numbers*/
/*----------------------------------------------------------------------------*/
/* Main Function */
int main()
{
    FILE *datafile;
    char *filename = "contactdatabase.dat";   /*declare file name*/
    char ch;
    firstc = NULL;
    datafile = fopen(filename,"r");     /* open file for reading*/

    if(datafile)
    {
	    firstc = (struct contact *)malloc(sizeof(struct contact));
	    currentc = firstc;       /*make first record current*/
	    while(1)     /*endless while loop. a NULL pointer in final node ends loop*/
     	    {
		    newc = (struct contact *)malloc(sizeof(struct contact));
		    fread(currentc,sizeof(struct contact),1,datafile);
		    if(currentc->next == NULL)   /* NULL indicates end of node list*/
			    break;
		    currentc->next = newc;       /* pointer referencing next node*/
            currentc->count=0;           /* initiates count for comments*/
		    currentc = newc;             /* make current record new*/
	    }
	    fclose(datafile);
	    cnum = currentc->number;

    }
    int d,e;
    do
    {
	fflush(stdin);
        puts("\nWelcome To The Contact Database");/* print menu messages*/
        puts("-- -----------------------------");
        puts("1 - Add a new contact");
	puts("2 - Delete contact");
	puts("3 - List all contacts");
	puts("4 - Modify contact");
	puts("5 - Find a contact by name");
	puts("6 - Zero Balance");
	puts("-- -----------------------------");
        puts("Q - Save and quit\n");
        printf("\tEnter your choice:");
        ch = getchar();
	    ch = toupper(ch);
        switch(ch)
        {
            case '1':
                puts("Add a new contact\n");
	        fflush(stdin);
                addNewcontact();
                break;
	    case '2':
        printf("\nEnter Password: ");
                scanf("%d",&d);
                do{
                if(d==911){
                    puts("Delete a contact\n");
		            deletecontact();
		            break;
		            }
		            else
                         printf("/n Enter the password again ");
                        scanf("%d",&d);
                }while(d!=911);
                    break;
	    case '3':
		puts("List all contacts\n");
		listAll();
		break;
	    case '4':
	         printf("\nEnter Password: ");
                scanf("%d",&e);
                do{
                if(e==912){
                    puts("Modify a contact\n");
		            modifycontact();
		            break;
		            }
		            else
                        printf("/n Enter the password again ");
                        scanf("%d",&e);
                }while(e!=912);
		break;
	    case '5':
		puts("Find a contact by name\n");
		findcontact();
		break;
		case '6':
        puts("Zero Balance");
        zero();
        break;
            case 'Q':
                puts("Save and quit\n");
                default:
                break;
        }
    }
    while(ch != 'Q');
/*
 * Save the records to disk
 */
    currentc = firstc;

    if(currentc == NULL)
	    return(0);		/*no data to write*/

    datafile = fopen(filename,"w");

    if(datafile == NULL)
    {
	    printf("Error writing to %s\n",filename);
	    return(1);
    }
    				/* Write each record to file*/
    while(currentc != NULL)
    {
	    fwrite(currentc,sizeof(struct contact),1,datafile);
	    currentc = currentc->next;
    }
    fclose(datafile);
    return(0);
}
/*----------------------------------------------------------------------------*/

/* Functions Definition */

void addNewcontact(void)    /* add new contact function*/
{
    newc = (struct contact *)malloc(sizeof(struct contact));
    if(firstc==NULL)
        firstc = currentc = newc;
    else
    {
        currentc = firstc;      /* make the first record the current one*/

        while(currentc->next != NULL)currentc = currentc->next;
        currentc->next = newc;  /* pointer to next node */
        currentc = newc;
    }
/* update the structure */
    cnum++;
    printf("%27s: %5i\n","contact number",cnum);
    currentc->number = cnum;    /*cnum is used to give unique account numbers*/

    printf("%27s: ","Enter contact name");
    gets(currentc->name);
    printf("%27s: ","Enter contact Phone number");
    gets(currentc->phone);
    printf("%27s: ","Enter contact Payment");
    gets(currentc->payment);
    printf("%27s: ","Enter contact email");
    gets(currentc->email);
    printf("contact added!");
    currentc->count=0;
    currentc->next = NULL;
}
/*----------------------------------------------------------------------------*/
void listAll(void)      /* list all contacts function*/
{
    if(firstc==NULL)
        puts("There are no contacts to display!");

    else
    {
	    printf("%6s %-20s %-15s %-15s %-15s\n","Acct#","Name","Phone","Payment","Email");
        puts("------ -------------------- ------------- -------------- --------------");
        currentc=firstc;

        do
        {

                printf("%6d: %-20s %-15s %-15s %-20s\n",\
                currentc->number,\
                currentc->name,\
                currentc->phone,\
                currentc->payment,\
                currentc->email);
                /*prints values of number, name, phone and email*/
        }

        while((currentc=currentc->next) != NULL);
    }
}
/*----------------------file------------------------------------------------------*/
void zero(void)      /* zero payment function*/
{
    if(firstc==NULL)
        puts("There are no contacts to display!");

    else
    {
	    printf("%6s %-20s %-15s %-15s %-15s\n","Acct#","Name","Phone","Payment","Email");
        puts("------ -------------------- ------------- -------------- --------------");
        currentc=firstc;

        do
        {
                if(strcmp(currentc->payment,"0")==0){
                printf("%6d: %-20s %-15s %-15s %-20s\n",\
                currentc->number,\
                currentc->name,\
                currentc->phone,\
                currentc->payment,\
                currentc->email);
                /*prints values of number, name, phone and email*/
                }
        }
        while((currentc=currentc->next) != NULL);
    }
}

/*----------------------------------------------------------------------------*/
void deletecontact(void)     /*delete contact function */
{
    int record;
    struct contact *previousa;
    if(firstc==NULL)
    {
    puts("There are no contacts to delete!");
	return;
    }

    listAll();		/* show all records*/
    printf("Enter contact account number to delete: ");
    scanf("%d",&record);
    currentc = firstc;

    while(currentc != NULL)
    {
        if(currentc->number == record)
	{
	    if(currentc == firstc)	/*if record to be deleted is the first record*/
		firstc=currentc->next;
	    else
		previousa->next = currentc->next;
                                         /*to delete is not the first*/
        free(currentc);
	    printf("contact %d deleted!\n",record);
	    return;
	}

	else
	{
        previousa = currentc;
	    currentc = currentc->next;
	}
    }
    printf("contact %d not found!\n",record);
 }
/*----------------------------------------------------------------------------*/
void modifycontact(void)   /*modify contact function*/
{
    int record, result;
    if(firstc==NULL)
    {
        puts("There are no contacts to modify!");
	return;
    }

    listAll();		/* show all records */
    printf("Enter contact account number to modify or change: ");
    scanf("%d",&record);  /*scan user input to record*/
    result = findnum(record);

    if( result >0 ){
	    printf("Contact %d:\n",currentc->number);
	    printf("Name: %s\n",currentc->name);
	    if(prompt())
		    gets(currentc->name);
	    printf("Phone: %s\n",currentc->phone);
	    if(prompt())
		    gets(currentc->phone);
	    printf("Email: %s\n",currentc->email);
	    if(prompt())
		    gets(currentc->email);
	    return;
	}
    printf("contact %d was not found!\n",record);
}
/*----------------------------------------------------------------------------*/
int findnum (int recordnum)
{
    int record;
    record = recordnum;
    currentc = firstc;
    while(currentc != NULL)
    {

        if(currentc->number == record)
	     {
           return 1;
         }

	else
	{
	    currentc = currentc->next;
	}
    }
    return -1;
}
/*----------------------------------------------------------------------------*/
int findcontact(void) /* find contact function*/
{
     char buff[20];

     if(firstc==NULL)
	{
        puts("There are no contacts to find!");
	    return 1;
    }

    printf("Enter contact name: ");
    fflush(stdin);/*clears any text from the input stream*/
    gets(buff);

    currentc = firstc;
    while(currentc != NULL)
    {
        if( strcmp(currentc->name, buff) == 0 )
	    {
			printf("%6s %-20s %-15s %-15s\n","Acct#","Name","Phone","Email");
			/*prints table titles*/
            printf("%6d: %-20s %-15s %-20s\n",\
            currentc->number,\
            currentc->name,\
            currentc->phone,\
            currentc->payment,\
            currentc->email);


			return 0;
	    }
		else
		{
			currentc = currentc->next;
		}
    }
    printf("contact %s was not found!\n",buff);
          return 1;
}
/*----------------------------------------------------------------------------*/
int prompt(void)
{
	char ch;
    fflush(stdin);
	printf("Update? (Y to update any other key to not)");
	ch = getchar();
	ch = toupper(ch);
	fflush(stdin);
	if(ch == 'Y')
	{
		printf("Enter new value: ");
		return(1);
	}
	else
		return(0);
}
/*----------------------------------------------------------------------------*/
/* END OF PROGRAM */

