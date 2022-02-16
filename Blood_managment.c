#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

void newdata();
void display();
void deletedata();
void modifydata();
void finddata();
void finddonor();


struct blood
{

    char name[20];
    char bgroup[10];
    char id[15];
    char dept[20];
    char phone[15];
    char date[12];
    struct blood *next;
    int count;
}*head=NULL,*current,*newnode;





void Registration()
{
    char ch;
    do
    {
        fflush(stdin);
        puts("\nWelcome To Registration");
        puts("-- -----------------------------");
        puts("1 - New Registration");
        puts("2 - Update date");
        puts("R - Return to main menu\n");
        puts("-- -----------------------------");
        printf("\tYour choice:");
        ch = getchar();
        ch = toupper(ch);
        switch(ch)
        {
        case '1':
            puts("New Registration");
            newdata();
            break;
        case '2':
            puts("Update date");
            modifydata();
            break;
        case 'R':
            puts("Return to main menu\n");
        default:
            break;
        }
    }
    while(ch!= 'R');

}

void Users()
{
    puts("Find a donor");
    finddonor();

}

void Administration ()
{
    char ch;
    do
    {
        fflush(stdin);
        puts("\nWelcome To Administration");
        puts("-- -----------------------------");
        puts("1 - Display all donor List");
        puts("2 - Delete data");
        puts("3 - Find information");
        puts("R - Return to main menu\n");
        puts("-- -----------------------------");
        printf("\tYour choice:");
        ch = getchar();
        ch = toupper(ch);
        switch(ch)
        {
        case '1':
            puts("Display all donor List");
            display();
            break;
        case '2':
            puts("Delete data");
            deletedata();
            break;
        case '3':
            puts("3 - Find information");
            finddata();
            break;
        case 'R':
            puts("Return to main menu\n");
        default:
            break;
        }
    }
    while(ch!= 'R');
}

int main()
{

    char ch;
    char u[15] = {"admin"};
    char p[15] = {"12345"};
    char pass[15];
    char uname[15];

    system("color f1");
    FILE *bloodcloud;
    char *filename = "bloodcloud.txt";
    bloodcloud = fopen(filename,"r");

    if(bloodcloud)
    {
        head = (struct blood *)malloc(sizeof(struct blood));
        current = head;
        while(1)
        {
            newnode = (struct blood *)malloc(sizeof(struct blood));
            fread(current,sizeof(struct blood),1,bloodcloud);
            if(current->next == NULL)
                break;
            current->next = newnode;
            current = newnode;
        }
        fclose(bloodcloud);

    }
    do
    {

        fflush(stdin);
        puts("\nWelcome To The blood cloud");
        puts("-- -----------------------------");
        puts("1 - Registration");
        puts("2 - Users");
        puts("3 - Administration");
        puts("S - Save and quit\n");
        puts("-- -----------------------------");

        printf("\tYour choice:");
        ch = getchar();
        ch = toupper(ch);
        switch(ch)
        {
        case '1':
            Registration();
            break;
        case '2':

            puts("Find a donor");
            finddonor();


            break;
        case '3':
            puts("\n\n\nWelcome To Administration\n\n");
            fflush(stdin);
            printf("Enter User ID       :");
            fflush(stdin);
            gets(uname);
            fflush(stdin);
            printf("Enter password      :");
            fflush(stdin);
            gets(pass);
            fflush(stdin);
            if((strcmp(uname,u)==0)&&(strcmp(pass,p)==0))
                Administration ();
            else
                puts("Invalid Username & password");
            break;
        case 'S':
            puts("Save and quit\n");
        default:
            break;
        }
    }
    while(ch!= 'S');
    current = head;

    if(current == NULL)
        return(0);

    bloodcloud = fopen(filename,"w");

    if(bloodcloud == NULL)
    {
        printf("Error writing to %s\n",filename);
        return(1);
    }

    while(current != NULL)
    {
        fwrite(current,sizeof(struct blood),1,bloodcloud);
        current = current->next;
    }
    fclose(bloodcloud);
    return(0);

}
void newdata()
{
    newnode = (struct blood *)malloc(sizeof(struct blood));

    if(head==NULL)
        head = current = newnode;
    else
    {
        current = head;
        while(current->next != NULL)
            current = current->next;

        current->next = newnode;
        current = newnode;
    }
    fflush(stdin);
    printf("%-37s: ","Enter member name");
    gets(current->name);
    printf("%-37s: ","Enter Blood Group");
    gets(current->bgroup);
    printf("%-37s: ","Enter ID");
    gets(current->id);
    printf("%-37s: ","Enter Department");
    gets(current->dept);
    printf("%-37s: ","Enter Phone Number");
    gets(current->phone);
    printf("%-37s: ","Enter Date of donation (dd\\mm\\yyyy)");
    gets(current->date);
    printf("\nMember added!");
    current->next = NULL;
}

void display()
{
    if(head==NULL)
        puts("There are no data to display!");

    else
    {
        printf("%-20s %-15s %-15s %-20s %-15s %-15s\n","Name","Blood_group","ID","Department","Phone_Number","Last Date of Donation (dd\\mm\\yyyy)");
        puts("-------------------  --------------  --------------  -------------------  -------------   ----------------------------------");
        current=head;

        do
        {

            printf("%-20s %-15s %-15s %-20s %-15s %-15s\n",current->name,current->bgroup,current->id,current->dept,current->phone,current->date);

        }

        while((current=current->next) != NULL);
    }
}

void finddata()
{
    char id[20];

    if(head==NULL)
    {
        puts("There are no data to find!");
        return ;
    }

    printf("Enter the ID: ");
    fflush(stdin);
    gets(id);
    current = head;
    while(current != NULL)
    {
        if( strcmp(current->id, id) == 0 )
        {
            printf("%-20s %-15s %-15s %-20s %-15s %-15s\n","Name","Blood_group","ID","Department","Phone_Number","Date(dd\\mm\\yyyy)");
            puts("-------------------  --------------  --------------  -------------------  -------------   ----------------");
            printf("%-20s %-15s %-15s %-20s %-15s %-15s\n",current->name,current->bgroup,current->id,current->dept,current->phone,current->date);
            return 0;
        }
        else
        {
            current = current->next;
        }
    }
    printf("Data %s was not found!\n",id);
    return ;
}

void deletedata()
{
    char id[20];
    int pos=0,i;
    printf("Enter the deleting ID: ");
    fflush(stdin);
    gets(id);
    current = head;
    while(current != NULL)
    {
        pos++;
        if( strcmp(current->id, id) == 0 )
        {
            break;

        }
        else
        {
            current = current->next;
        }
    }


    {
        struct blood*c,*temp1,*temp2 ;
        c=head;
        for(i=1; i<=pos-1; i++)
        {
            c=c->next;
        }
        if(c==head)
        {
            head=c->next;
        }

        else if(c->next==NULL)
        {
            c=head;
            for(i=0; i<pos-2; i++)
            {
                c=c->next;
            }
            c->next=NULL;
        }
        else
        {
            temp2=c->next;
            c=head;
            for(i=0; i<pos-2; i++)
            {
                c=c->next;
            }
            temp1=c;
            temp1->next=temp2;
        }
    }

}

void modifydata()
{
    char id[20];

    if(head==NULL)
    {
        puts("There are no data to update!");
        return ;
    }

    printf("Enter the ID: ");
    fflush(stdin);
    gets(id);
    current = head;
    while(current != NULL)
    {
        if( strcmp(current->id, id) == 0 )
        {
            printf("%-37s: ","Update The Date of donation (dd\\mm\\yyyy)");
            gets(current->date);
            return 0;
        }
        else
        {
            current = current->next;
        }
    }
    printf("Data %s was not found!\n",id);
    return ;
}
void finddonor()
{
    char bgroup[20];
    printf("Enter the Blood Group: ");
    fflush(stdin);
    gets(bgroup);
    printf("%-20s %-15s %-15s %-20s %-15s %-15s\n","Name","Blood_group","ID","Department","Phone_Number","Date(dd\\mm\\yyyy)");
    puts("-------------------  --------------  --------------  -------------------  -------------   ----------------");
    current=head;

    while(current != NULL)
    {
        if( strcmp(current->bgroup, bgroup) == 0 )
        {
            printf("%-20s %-15s %-15s %-20s %-15s %-15s\n",current->name,current->bgroup,current->id,current->dept,current->phone,current->date);
            current = current->next;
        }
        else
        {
            current = current->next;
        }
    }
}