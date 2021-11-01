#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

void password();
void heading();
void adm();
void usr();
void addBook();
void viewBook();
void srBook();
void delBook();
void updateBook();
void issueBook();
void rtBook();
void Exit();

struct Book_info{
    int id;
    char name[20];
    char author[30];
    int quantity;
    char publisher[20];
};

struct Book_info a;

FILE *file, *file2;

int d=1;
int main()
{
    password();
}

void adm()
{
    system("cls");
    int n;
    printf("\n\n \t\t*************** Main Menu ***************");

    printf("\n \t\t 1. Add Book\n");
    printf("\t\t 2. View Book\n");
    printf("\t\t 3. Search Book\n");
    printf("\t\t 4. Delete Book\n");
    printf("\t\t 5. Update Book Records\n");
    printf("\t\t 6. Exit\n\n");

    printf("\t\t*************************\n");
    printf("\t\tEnter your choice : ");
    scanf("%d",&n);
    if(n==1)
    {
        addBook();
    }
    else if(n==2)
    {
        viewBook();
    }
    else if(n==3)
    {
        srBook();
    }
    else if(n==4)
    {
        delBook();
    }
    else if(n==5)
    {
        updateBook();
    }
    else if(n==6)
    {
        Exit();
    }
    else
    {
        printf("\n\n \t\t Your choice is wrong!! \n \t\t Try again.....");
        fflush(stdin);
        getchar();
        adm();
    }
}

void usr()
{
    system("cls");
    int n;
    printf("\n\n \t\t*************** Main Menu ***************");

    printf("\n \t\t 1. Issue Book\n");
    printf("\t\t 2. View Book\n");
    printf("\t\t 3. Search Book\n");
    printf("\t\t 4. Returning of Book\n");
    printf("\t\t 5. Exit\n\n");

    printf("\t\t*************************\n");
    printf("\t\tEnter your choice : ");
    scanf("%d",&n);
    if(n==1)
    {
        issueBook();
    }
    else if(n==2)
    {
        viewBook();
    }
    else if(n==3)
    {
        srBook();
    }
    else if(n==4)
    {
        rtBook();
    }
    else if(n==5)
    {
        Exit();
    }
    else
    {
        printf("\n\n \t\t Your choice is wrong!! \n \t\t Try again.....");
        fflush(stdin);
        getchar();
        usr();
    }
}

void addBook()
{
    system("cls");

    int b,count=0;

    printf("\n\n \t\t *************** Add Book ***************");
    file = fopen("Books.dat","ab+");
    printf("\n\n\t\t Enter ID : ");
    fflush(stdin);
    scanf("%d",&b);
    rewind(file);
    while(fread(&a,sizeof(a),1,file)==1)
    {
        if(b==a.id)
        {
            printf("\n\n \t\t This book is already in library.....");
            count=1;
        }
    }
    if(count==1)
    {
        fflush(stdin);
        getchar();
        adm();
    }
    a.id = b;
    printf("\n \t\t Enter Name : ");
    fflush(stdin);
    scanf("%s",a.name);
    printf("\t\t Enter Author : ");
    fflush(stdin);
    scanf("%s",a.author);
    printf("\t\t Enter quantity : ");
    fflush(stdin);
    scanf("%d",&a.quantity);
    printf("\t\t\t Enter Publisher : ");
    fflush(stdin);
    scanf("%s",a.publisher);

    fseek(file,0,SEEK_END);
    fwrite(&a,sizeof(a),1,file);
    fclose(file);

    printf("\n\n\t\t Add Book Successfully!!!");

    fflush(stdin);
    getchar();
    adm();
}

void viewBook()
{
    system("cls");

    printf("\n\n\t\t *************** View Book List ***************\n\n");
    printf("\tID\tName\tAuthor\tQuantity\tPublisher\n\n");
    file = fopen("books.dat","rb");
    while(fread(&a,sizeof(a),1,file)==1)
    {
        printf("\t%d",a.id);
        printf("\t%s",a.name);
        printf("\t%s",a.author);
        printf("\t%d",a.quantity);
        printf("\t%s\n",a.publisher);
    }
    printf("\n\n\t\tPress any key...");
    fflush(stdin);
    getchar();
    adm();
    usr();
}

void srBook()
{
    system("cls");

    int i, count=0;
    printf("\n\n\t\t ************ Search Book ************\n");
    printf("\n\t\t searching.........\n\n");
    file = fopen("books.dat","rb");
    printf("\n\t\t Enter ID : ");
    scanf("%d",&i);
    while(fread(&a,sizeof(a),1,file)==1)
    {
        if(i == a.id)
        {
            printf("\n\n\t\t Book is found!!!\n");
            printf("\t\t ID : %d",a.id);
            printf("\n\t\t Name : %s",a.name);
            printf("\n\t\t Author : %s",a.author);
            printf("\n\t\t Quantity : %d",a.quantity);
            printf("\n\t\t Publisher : %s\n",a.publisher);
            count = 1;
        }
    }
    if(count==0)
    {
        printf("\n\n Book is not found:(!!");
    }
    printf("\n\n\t\t press any key.......");
    fflush(stdin);
    getchar();
    adm();
    usr();
}

void delBook()
{
    system("cls");

    int b1, count=0;
    printf("\n\n\t\t *************** Delete Book ***************");
    printf("\n\n\t\t Enter ID for delete book");
    scanf("%d",&b1);

    file = fopen("books.dat","rb+");
    rewind(file);
    while(fread(&a,sizeof(a),1,file)==1)
    {
        if(b1==a.id)
        {
            printf("\n\t\t Book is available");
            printf("\n\t\t Book Name is : %s",a.name);
            count = 1;
        }
    }
    if(count == 0)
    {
        printf("\n\t\t Book is not available");
    }
    else
    {
        file2 = fopen("text.dat","wb+");
        rewind(file);
        while(fread(&a,sizeof(a),1,file) == 1)
        {
            if(b1 != a.id)
            {
                fseek(file2,ftell(file2)-sizeof(a),0);
                fwrite(&a,sizeof(a),1,file2);
            }
        }
        fclose(file);
        fclose(file2);
        remove("books.dat");
        rename("text.dat","books.dat");
        file = fopen("books.dat","rb");
        fclose(file);
    }
    printf("\n\n\t\t press any key");
    fflush(stdin);
    getchar();
    adm();
}

void updateBook()
{
    system("cls");
    int b, count=0;
    printf("\n\n\t\t ************ Update Book ************\n\n");
    file = fopen("books.dat","rb+");
    printf("\n\t\t Enter ID : ");
    scanf("%d",&b);

    while(fread(&a,sizeof(a),1,file)==1)
    {
        if(b==a.id)
        {
            printf("\n\t\t Book is available!!\n");
            printf("\n\n ID : %d",a.id);
            printf("\n\t\t Updated quantity of books : ");
            scanf("%d",&a.quantity);

            fseek(file,ftell(file)-sizeof(a),0);
            fwrite(&a,sizeof(a),1,file);
            fclose(file);
            count = 1;
        }
    }
    if(count == 0)
    {
        printf("\n\n\t\t Book is not found!!");
    }
    printf("\n\n\t\t press any key....");
    fflush(stdin);
    getchar();
    adm();
}

void issueBook()
{
    system("cls");
    int b2;
    printf("\n\n\t\t ************ Issue Book ************");
    printf("\n\n\t\tEnter Book ID : ");
    scanf("%d",&b2);

    file = fopen("books.dat","rb+");
    rewind(file);
    while(fread(&a,sizeof(a),1,file)==1)
    {
        if(b2==a.id)
        {
            printf("\n\t\t Book is available");
            printf("\n\t\t Book Name is : %s",a.name);
            printf("\n\t\t Yayyyyy.......");
        }
        else
        {
            printf("\n\t\t Sorry.....Book is not available:(");
        }
    }
    fclose(file);
    fflush(stdin);
    getchar();
    usr();
}

void rtBook()
{
    system("cls");
    int b3;
    printf("\n\n\t\t ************ Return Book ************");
    printf("\n\n\t\tEnter Book ID : ");
    scanf("%d",&b3);

    file = fopen("books.dat","rb+");
    rewind(file);
    while(fread(&a,sizeof(a),1,file)==1)
    {
        if(b3==a.id)
        {
            printf("\n\t\t Thank you for returning %s on time.....",a.name);
        }
    }
    fclose(file);
    fflush(stdin);
    getchar();
    usr();
}

void Exit()
{
    system("cls");
    printf("\n\n\t\t Thank you for spending time......");
    fflush(stdin);
    getchar();
    exit(0);
}

void heading()
{
    system("cls");
    printf("\n\n \t\t************** Library Management System **************\n");
    fflush(stdin);
    getchar();
}

void password()
{
   heading();
   char username[20];
   char pwd[10];
   system("cls");
   printf("Please Enter Your Username : ");
   scanf("%s",&username);
   printf("\nPlease Enter Your Password : ");
   scanf("%s",&pwd);
   if(strcmp(pwd,"admin")==0)
   {
      printf("\n Welcome....Login Successful");
      adm();
   }
   else if(strcmp(pwd,"user")==0)
   {
       printf("\n Welcome!!!");
       usr();
   }
   else
   {
       if(d==3)
       {
           exit(0);
       }

       printf("\n\n \t\tYour password is incorrect %d to 3\n",d);
       printf("\n\n \t\t Try again....");
       d++;

       fflush(stdin);
       getchar();

       password();
   }
   fflush(stdin);
   getchar();
}
