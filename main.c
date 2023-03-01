#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

void gotoxy(int,int);
void delay(float);
void introp();
void intro(int, char[],int, int);
void password_menu();
char *get_pass();
void signup();
void login();
void mainmenu();
void add_books();
void delete_book();
void edit_book();
void view_books();
char *get_date();
char *get_date_after(int);
void issue_book_menu();
void issue_book();
void search_issued_book();
void remove_issued_book();
void view_issued_book();
void due_date();
void search_book();
void class_details();
void available();
void total_books();
void update_password();

char ch;
struct library
{
    char book_name[50];
    int book_no;
    char author_name[50];
    char genres[50];
    char password[50];
    char student_name[50];
    char section[50];
    char date[15];
    char due_date[15];
    int student_class;
    int n;
}l;
int main()
{
    mainmenu();
}
void gotoxy(int x,int y)
{
    COORD pos={0,0};
    pos.X=x;
    pos.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void delay(float seconds)
{
    float mseconds=1000*seconds;
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
void introp()
{
    intro(36,"Welcome to Library management system",35,10);
    intro(7,"Made by",46,12);
    intro(11,"Rishi Dhama",43,14);
    intro(10,"B.Tech CSE",43,16);
}
void intro(int a, char g[], int b, int c)
{
    gotoxy(b,c);
    for(int i=0;i<a;i++)
    {
        delay(0.1);
        printf("%c",g[i]);
    }
}
void password_menu()
{
    int ch;
    system("cls");
    gotoxy(43,2);
    printf("Password Menu");
    gotoxy(39,4);
    printf("1. Login");
    gotoxy(39,6);
    printf("2. Signup");
    gotoxy(39,8);
    printf("3. Exit");
    gotoxy(39,10);
    printf("Enter your choice: ");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1:
            login();
            break;
        case 2:
            signup();
            break;
        case 3:
            exit(0);
        default:
            printf("Wrong choice");
    }
}
char *get_pass()
{
    static char pass[20],temp_pass[20];
    int i=0;
    while(1)
    {
        temp_pass[i]=getch();
        if(temp_pass[i]==13)
           break;
        else if(temp_pass[i]==8)
        {

            if(i!=0)
            {
                printf("\b \b");
                i--;
            }
            else
            {
                printf("\a");
            }
        }
        else
        {
             printf("*");
             pass[i]=temp_pass[i];
             i++;
        }
    }
    pass[i]='\0';
    return pass;
}
void signup()
{
    system("cls");
    FILE *c_pass,*pass;
    char *new_pass,*re_new_pass;
    int count=0;
    c_pass=fopen("pass.txt","r");
    system("cls");
    gotoxy(45,2);
    printf("SIGNUP");
    gotoxy(38,5);
    while(fscanf(c_pass,"%s",l.password)!=EOF)
    {
        count++;
    }
    if(count==0)
	{
	       pass=fopen("pass.txt","w");
          B:
            system("cls");
            gotoxy(45,2);
            printf("SIGNUP");
            gotoxy(38,5);
	        printf("Enter password: ");
            new_pass=get_pass();
            gotoxy(38,6);
            printf("Re-Enter password: ");
            re_new_pass=get_pass();
            if(strcmp(new_pass,re_new_pass)==0)
            {
                strcpy(l.password,new_pass);
            }
            else
            {
                gotoxy(38,8);
                printf("Password Mismatched");
                getch();
                goto B;
            }
            fprintf(pass,"%s",l.password);
            fclose(pass);
            fclose(c_pass);
            password_menu();
    }
    else
    {
        printf("You have already signed up");
        gotoxy(34,7);
        printf("Enter any key to go to password menu: ");
        fclose(c_pass);
        getch();
        password_menu();
    }
}
void login()
{
    system("cls");
    char user_name[20],password[50],*pass;
    int k=1,c=6,count=0;
    FILE *login;
    FILE *c_pass;
    login=fopen("pass.txt","r");
    gotoxy(47,2);
    printf("LOGIN");
    fflush(stdin);
    if(login==NULL)
    {
        gotoxy(43,4);
        printf("No Record found");
        gotoxy(38,6);
        printf("Press any key to go to password menu");
        fclose(login);
        getch();
        password_menu();
    }
    else
    {
        c_pass=fopen("pass.txt","r");
        while(fscanf(c_pass,"%s",l.password)!=EOF)
        {
              count++;
        }
        fclose(c_pass);
    }
    if(count==0)
    {
        gotoxy(43,4);
        printf("You have not signed up");
        gotoxy(38,6);
        printf("Press any key to go to password menu");
        fclose(login);
        getch();
        password_menu();
    }
    {
    system("cls");
    gotoxy(44,2);
    printf("LOGIN DETAILS:-");
    A:
    gotoxy(40,c);
    printf("Enter user Name: ");
    gotoxy(40,(c+2));
    printf("Password: ");
    gotoxy(57,c);
    gets(user_name);
    gotoxy(50,(c+2));
    pass=get_pass();
    gotoxy(40,c+4);
    while(fscanf(login,"%s",l.password)!=EOF)
    {
          strcpy(password,l.password);
    }
          if((strcmp(user_name,"rishi dhama")==0) && strcmp(pass,password)==0)
          {
              printf("Access Granted");
              fclose(login);
              gotoxy(40,c+6);
              printf("press any key to continue: ");
              getch();
              fclose(login);
              mainmenu();
           }
          else
          {
              printf("Access Denied");
              k++;
              if(k<4)
              {
                 c=c+6;
                 goto A;
              }
              else
              {
                 gotoxy(40,c+4);
                 printf("press any key to continue: ");
                 fclose(login);
                 exit(0);
              }
           }
    }
}
void mainmenu()
{
    int ch;
    system("cls");
    gotoxy(43,2);
    printf("MAIN MENU");
    gotoxy(39,4);
    printf("1. Add new Book");
    gotoxy(39,6);
    printf("2. Delete Book");
    gotoxy(39,8);
    printf("3. Edit Book Details");
    gotoxy(39,10);
    printf("4. view all Books");
    gotoxy(39,12);
    printf("5. Issue Menu");
    gotoxy(39,14);
    printf("6. Due date gone");
    gotoxy(39,16);
    printf("7. Search Book");
    gotoxy(39,18);
    printf("8. Class Details");
    gotoxy(39,20);
    printf("9. Book available or not");
    gotoxy(39,22);
    printf("10. Total Books in library");
    gotoxy(39,24);
    printf("11. Update password");
    gotoxy(39,26);
    printf("0. Exit");
    gotoxy(39,28);
    printf("Enter your choice: ");
    scanf("%d",&ch);
    switch(ch)
    {
        case 0:
            exit(0);
        case 1:
            add_books();
            break;
        case 2:
            delete_book();
            break;
        case 3:
            edit_book();
            break;
        case 4:
            view_books();
            break;
        case 5:
            issue_book_menu();
            break;
        case 6:
            due_date();
            break;
        case 7:
            search_book();
            break;
        case 8:
            class_details();
            break;
        case 9:
            available();
            break;
        case 10:
            total_books();
            break;
        case 11:
            update_password();
            break;
        default:
            {
                gotoxy(39,30);
                printf("Wrong choice");
                gotoxy(39,32);
                printf("Press any key to try again: ");
                getch();
                mainmenu();
            }
    }
}
void add_books()
{
    system("cls");
    gotoxy(44,2);
    printf("ADD BOOKS");
    FILE *lfile;
    lfile=fopen("Books.txt","a");
    fflush(stdin);
    gotoxy(39,6);
    printf("Enter Book name: ");
    gets(l.book_name);
    fflush(stdin);
    gotoxy(39,8);
    printf("Enter Book number: ");
    scanf("%d",&l.book_no);
    fflush(stdin);
    gotoxy(39,10);
    printf("Enter Author name: ");
    gets(l.author_name);
    fflush(stdin);
    gotoxy(39,12);
    printf("Enter Genres: ");
    gets(l.genres);
    fflush(stdin);
    fprintf(lfile,"%s %d %s %s\n",l.book_name,l.book_no,l.author_name,l.genres);
    fclose(lfile);
    gotoxy(39,14);
    printf("Do you want to enter more books[y/n]: ");
    scanf("%c",&ch);
    if(ch=='y'||ch=='Y')
        add_books();
    else
    mainmenu();
}
void delete_book()
{
    system("cls");
    int del,found=0;
    FILE *tfile;
    FILE *lfile;
    gotoxy(43,2);
    printf("DELETE BOOK");
    gotoxy(35,4);
    printf("Enter Book number to delete book:");
    scanf("%d",&del);
    lfile=fopen("Books.txt","r");
    tfile=fopen("temp.txt","w+");
    if(lfile==NULL)
	{
	    gotoxy(35,6);
		printf("No Record in File!");
		gotoxy(35,8);
		printf("Enter any key to go to main menu: ");
		getch();
		fclose(lfile);
		fclose(tfile);
		mainmenu();
	}
	else
	{
    while(fscanf(lfile,"%s %d %s %s",l.book_name,&l.book_no,l.author_name,l.genres)!=EOF)
    {
          if(l.book_no!=del)
          {
             fprintf(tfile,"%s %d %s %s\n",l.book_name,l.book_no,l.author_name,l.genres);
          }
          else
          {
             found=1;
          }
    }
    gotoxy(35,6);
    if(found==1)
    {
        printf("Record deleted successfully!!!");
    }
    else
    {
        printf("Record not found");
    }
    fclose(lfile);
    fclose(tfile);
    remove("Books.txt");
    rename("temp.txt","Books.txt");
    fflush(stdin);
    gotoxy(35,8);
    printf("Do you want to delete more books[y/n]: ");
    scanf("%c",&ch);
    if(ch=='y'||ch=='Y')
        delete_book();
    else
    mainmenu();
	}
}
void edit_book()
{
    int edit;
    FILE *lfile;
    FILE *tfile;
    char new_book_name[50];
    int new_book_no;
    char new_author_name[50];
    char new_genres[50];
    system("cls");
    gotoxy(43,2);
    printf("EDIT BOOK INFO");
    gotoxy(30,4);
    printf("Enter book number of book who's detail is to be edited:");
    scanf("%d",&edit);
    lfile=fopen("Books.txt","rb+");
    if(lfile==NULL)
	{
	    gotoxy(30,6);
		printf("\nNo Record in File!");
		fclose(lfile);
		mainmenu();
	}
    tfile=fopen("temp.txt","a+");
    while(fscanf(lfile,"%s %d %s %s",l.book_name,&l.book_no,l.author_name,l.genres)!=EOF)
    {
        if(l.book_no==edit)
        {
            gotoxy(30,6);
            printf("Enter New Book Number(Press '0', if No Change): ");
            fflush(stdin);
            scanf("%d",&new_book_no);
            if(new_book_no!=0)
            {
                l.book_no=new_book_no;
            }
            fflush(stdin);
            gotoxy(30,8);
            printf("Enter New Book Name(Press '.', if No change) : ");
            gets(new_book_name);
            if(strcmp(new_book_name,".")!=0)
            {
                strcpy(l.book_name,new_book_name);
            }
            fflush(stdin);
            gotoxy(30,10);
            printf("Enter New Author Name(Press '.', if No change) : ");
            gets(new_author_name);
            if(strcmp(new_author_name,".")!=0)
            {
                strcpy(l.author_name,new_author_name);
            }
            fflush(stdin);
            gotoxy(30,12);
            printf("Enter New Book Genre(Press '.', if No change) : ");
            gets(new_genres);
            if(strcmp(new_genres,".")!=0)
            {
                strcpy(l.genres,new_genres);
            }
            fprintf(tfile,"%s %d %s %s\n",l.book_name,l.book_no,l.author_name,l.genres);
        }
        else
        {
            fprintf(tfile,"%s %d %s %s\n",l.book_name,l.book_no,l.author_name,l.genres);
        }
    }
        fclose(lfile);
        fclose(tfile);
        remove("Books.txt");
        rename("temp.txt","Books.txt");
        fflush(stdin);
        gotoxy(30,14);
        printf("Do you want to edit more books info[y/n]: ");
        scanf("%c",&ch);
        if(ch=='y'||ch=='Y')
            edit_book();
        else
            mainmenu();
}
void view_books()
{
     int count;
     system("cls");
     FILE *lfile;
     gotoxy(43,2);
     printf("BOOKS IN LIBRARY");
     lfile=fopen("Books.txt","r");
     if(lfile==NULL)
     {
        gotoxy(43,4);
        printf("No Record found");
        gotoxy(36,6);
		printf("Enter any key to go to main menu: ");
		fclose(lfile);
		getch();
		mainmenu();
     }
    else
    {
        gotoxy(21,4);
        printf("Book Name");
        gotoxy(36,4);
        printf("Book Number");
        gotoxy(51,4);
        printf("Author Name");
        gotoxy(66,4);
        printf("Genres");
        count=8;
        while(fscanf(lfile,"%s %d %s %s",l.book_name,&l.book_no,l.author_name,l.genres)!=EOF)
        {
            gotoxy(21,count);
            printf("%s",l.book_name);
            gotoxy(36,count);
            printf("%d",l.book_no);
            gotoxy(51,count);
            printf("%s",l.author_name);
            gotoxy(66,count);
            printf("%s",l.genres);
            count=count+2;
        }
        fclose(lfile);
        getch();
        mainmenu();
    }
}
char* get_date()
{
    static char buffer[50];
    time_t current = time(NULL); /* Gets GMT time as a time_t. */
    struct tm* pLocal = localtime(&current); /* Converts to local time in broken down format. */
    strftime(buffer,sizeof(buffer),"%Y/%m/%d",pLocal);/* Formats as string into provided buffer. */
    return buffer;
}
char *get_date_after(int a)
{
    struct tm date = {0} ;
    time_t timer;
    int datee,year,month;
    static char str[20];
    char str_date[20],str_month[20],str_year[20];
    timer=time(NULL);
    date = *gmtime( &timer );
    datee=date.tm_mday+1;
    month=date.tm_mon+1;
    year=date.tm_year+1900;
    date.tm_year = date.tm_year;
    date.tm_mon = date.tm_mon;
    date.tm_mday = date.tm_mday + a;
    timer = mktime( &date );
    date = *gmtime( &timer );
    datee=date.tm_mday+1;
    month=date.tm_mon+1;
    year=date.tm_year+1900;
    itoa(datee,str_date,10);
    itoa(month,str_month,10);
    itoa(year,str_year,10);
    strcpy(str,str_year);
    if(month<=9)
       strcat(str,"/0");
    else
       strcat(str,"/");
    strcat(str,str_month);
    if(datee<=9)
       strcat(str,"/0");
    else
       strcat(str,"/");
    strcat(str,str_date);
    return str;
}
void issue_book_menu()
{
    system("cls");
    FILE *lfile;
    int ch;
    gotoxy(43,2);
    printf("ISSUE MENU");
    lfile=fopen("Books.txt","r");
    gotoxy(42,4);
    if(lfile==NULL)
     {
        printf("No Record found");
        gotoxy(36,6);
		printf("Enter any key to go to main menu: ");
        fclose(lfile);
		mainmenu();
     }
    else
    {
        fclose(lfile);
        gotoxy(39,4);
        printf("1. Issue Book");
        gotoxy(39,6);
        printf("2. Remove Issued Book");
        gotoxy(39,8);
        printf("3. Search Issued Book");
        gotoxy(39,10);
        printf("4. view all Issued Books");
        gotoxy(39,12);
        printf("Enter Your choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                issue_book();
                break;
            case 2:
                remove_issued_book();
                break;
            case 3:
                search_issued_book();
                break;
            case 4:
                view_issued_book();
                break;
            default:
                printf("Wrong choice");
        }
    }
}
void issue_book()
{
    system("cls");
    FILE *lfile;
    FILE *ifile;
    int id,found=0;
    gotoxy(43,2);
    printf("ISSUE BOOK");
    lfile=fopen("Books.txt","r");
    gotoxy(41,4);
    printf("Enter Book No.: ");
    scanf("%d",&id);
    gotoxy(41,6);
    while(fscanf(lfile,"%s %d %s %s",l.book_name,&l.book_no,l.author_name,l.genres)!=EOF)
    {
        if(l.book_no==id)
        {
            found=1;
            ifile=fopen("Issue.txt","a");
            fflush(stdin);
            printf("Enter Student name: ");
            scanf("%s",l.student_name);
            gotoxy(41,8);
            fflush(stdin);
            printf("Enter class: ");
            scanf("%d",&l.student_class);
            gotoxy(41,10);
            fflush(stdin);
            printf("Enter Section: ");
            scanf("%s",l.section);
            strcpy(l.date,get_date());
            gotoxy(41,12);
            printf("Enter no of days book is issued for: ");
            scanf("%d",&l.n);
            strcpy(l.due_date,get_date_after(l.n));
            fprintf(ifile,"%s %d %s %d %s %d %s\n",l.student_name,l.student_class,l.section,l.book_no,l.date,l.n,l.due_date);
            gotoxy(41,14);
            printf("Book is issued on:%s till :%s ",l.date,l.due_date);
            fclose(ifile);
            fclose(lfile);
            fflush(stdin);
            gotoxy(41,16);
            printf("Do you want to issue more books[y/n]: ");
            scanf("%c",&ch);
            if(ch=='y'||ch=='Y')
                issue_book();
            else
                mainmenu();
            }
    }
    if(found==0)
    {
        printf("Book Not found");
        fclose(lfile);
        fflush(stdin);
        gotoxy(41,8);
        printf("Issue another book[y/n]: ");
        scanf("%c",&ch);
        if(ch=='y'||ch=='Y')
            issue_book();
        else
            mainmenu();
    }
}
void remove_issued_book()
{
    system("cls");
    FILE *ifile;
    FILE *tfile;
    int id,found=0;
    ifile=fopen("Issue.txt","r");
    gotoxy(43,2);
    printf("REMOVE ISSUED BOOK");
    if(ifile==NULL)
    {
        gotoxy(43,4);
        printf("No Record found");
        gotoxy(43,6);
		printf("Enter any key to go to main menu: ");
		fclose(ifile);
		getch();
		mainmenu();
    }
    tfile=fopen("temp.txt","a");
    gotoxy(43,2);
    printf("REMOVE ISSUED BOOK");
    gotoxy(41,4);
    printf("Enter Book No. of the book to be removed: ");
    scanf("%d",&id);
    while(fscanf(ifile,"%s %d %s %d %s %d %s",l.student_name,&l.student_class,l.section,&l.book_no,l.date,&l.n,l.due_date)!=EOF)
    {
        if(l.book_no==id)
        {
            found=1;
        }
        else
        {
            fprintf(tfile,"%s %d %s %d %s %d %s\n",l.student_name,l.student_class,l.section,l.book_no,l.date,l.n,l.due_date);
        }
    }
    gotoxy(41,6);
    if(found==0)
    {
        printf("Book Not found");
        fclose(ifile);
        fclose(tfile);
        fflush(stdin);
        gotoxy(41,8);
        printf("Delete another book[y/n]: ");
        scanf("%c",&ch);
        if(ch=='y'||ch=='Y')
            remove_issued_book();
        else
            mainmenu();
    }
    else
        printf("Book deleted successfully");
    fclose(ifile);
    fclose(tfile);
    remove("Issue.txt");
    rename("temp.txt","Issue.txt");
    fflush(stdin);
    gotoxy(41,8);
    printf("Delete another book[y/n]: ");
    scanf("%c",&ch);
    if(ch=='y'||ch=='Y')
        remove_issued_book();
    else
        mainmenu();
}
void search_issued_book()
{
    system("cls");
    FILE *ifile;
    int id,found=0;
    gotoxy(43,2);
    printf("SEARCH ISSUED BOOK");
    ifile=fopen("Issue.txt","r");
    if(ifile==NULL)
    {
        printf("No Record found");
        gotoxy(36,6);
		printf("Enter any key to go to main menu: ");
		fclose(ifile);
		getch();
		mainmenu();
    }
    gotoxy(43,4);
    printf("Enter Book No.: ");
    scanf("%d",&id);
    while(fscanf(ifile,"%s %d %s %d %s %d %s",l.student_name,&l.student_class,l.section,&l.book_no,l.date,&l.n,l.due_date)!=EOF)
    {
        if(l.book_no==id)
        {
            gotoxy(27,6);
            found=1;
            printf("This Book is Issued to: %s of %d-%s on %s till %s",l.student_name,l.student_class,l.section,l.date,l.due_date);
        }
    }
    if(found==0)
    {
        fclose(ifile);
        gotoxy(43,6);
        printf("Book not found");
    }
    fflush(stdin);
    gotoxy(43,8);
    printf("Search another book[y/n]: ");
    scanf("%c",&ch);
    if(ch=='y'||ch=='Y')
        search_issued_book();
    else
        mainmenu();
}
void view_issued_book()
{
    system("cls");
    FILE *ifile;
    int c=6;
    gotoxy(48,2);
    printf("ALL ISSUED BOOK");
    ifile=fopen("Issue.txt","r");
    if(ifile==NULL)
    {
        printf("No Record found");
        fclose(ifile);
        gotoxy(36,6);
		printf("Enter any key to go to main menu: ");
		getch();
		mainmenu();
    }
    gotoxy(10,4);
    printf("Student name");
    gotoxy(26,4);
    printf("Student Class");
    gotoxy(43,4);
    printf("Book Number");
    gotoxy(59,4);
    printf("Issued Date");
    gotoxy(75,4);
    printf("Issued for(days)");
    gotoxy(94,4);
    printf("Return date");
    while(fscanf(ifile,"%s %d %s %d %s %d %s",l.student_name,&l.student_class,l.section,&l.book_no,l.date,&l.n,l.due_date)!=EOF)
    {
            gotoxy(10,c);
            printf("%s",l.student_name);
            gotoxy(26,c);
            printf("%d-%s",l.student_class,l.section);
            gotoxy(43,c);
            printf("%d",l.book_no);
            gotoxy(59,c);
            printf("%s",l.date);
            gotoxy(75,c);
            printf("%d",l.n);
            gotoxy(94,c);
            printf("%s",l.due_date);
            c=c+2;
    }
    fclose(ifile);
    getch();
    mainmenu();
}
void due_date()
{
    system("cls");
    FILE *ifile;
    int c=6;
    gotoxy(48,2);
    printf("DUE DATE GONE");
    ifile=fopen("Issue.txt","r");
    if(ifile==NULL)
    {
        printf("No Record found");
        fclose(ifile);
        gotoxy(36,6);
		printf("Enter any key to go to main menu: ");
		getch();
		mainmenu();
    }
    gotoxy(10,4);
    printf("Student name");
    gotoxy(26,4);
    printf("Student Class");
    gotoxy(43,4);
    printf("Book Number");
    gotoxy(59,4);
    printf("Issued Date");
    gotoxy(75,4);
    printf("Issued for(days)");
    gotoxy(94,4);
    printf("Return date");
    while(fscanf(ifile,"%s %d %s %d %s %d %s",l.student_name,&l.student_class,l.section,&l.book_no,l.date,&l.n,l.due_date)!=EOF)
    {
            if(strcmp(get_date(),l.due_date)>0)
            {
                gotoxy(10,c);
                printf("%s",l.student_name);
                gotoxy(26,c);
                printf("%d-%s",l.student_class,l.section);
                gotoxy(43,c);
                printf("%d",l.book_no);
                gotoxy(59,c);
                printf("%s",l.date);
                gotoxy(75,c);
                printf("%d",l.n);
                gotoxy(94,c);
                printf("%s",l.due_date);
                c=c+2;
            }
    }
    fclose(ifile);
    getch();
    mainmenu();
}
void class_details()
{
    system("cls");
    FILE *ifile;
    int c=10,class_no;
    char section[10];
    gotoxy(45,2);
    printf("CLASS DETAIL");
    ifile=fopen("Issue.txt","r");
    if(ifile==NULL)
    {
        printf("No Record found");
        fclose(ifile);
        gotoxy(36,6);
		printf("Enter any key to go to main menu: ");
		getch();
		mainmenu();
    }
    gotoxy(44,4);
    printf("Enter Class: ");
    scanf("%d",&class_no);
    gotoxy(44,6);
    printf("Enter section: ");
    scanf("%s",section);
    gotoxy(10,8);
    printf("Student name");
    gotoxy(26,8);
    printf("Student Class");
    gotoxy(43,8);
    printf("Book Number");
    gotoxy(59,8);
    printf("Issued Date");
    gotoxy(75,8);
    printf("Issued for(days)");
    gotoxy(94,8);
    printf("Return date");
    while(fscanf(ifile,"%s %d %s %d %s %d %s",l.student_name,&l.student_class,l.section,&l.book_no,l.date,&l.n,l.due_date)!=EOF)
    {
          if((l.student_class==class_no) && (strcmp(l.section,section)==0))
          {
              gotoxy(10,c);
              printf("%s",l.student_name);
              gotoxy(26,c);
              printf("%d-%s",l.student_class,l.section);
              gotoxy(43,c);
              printf("%d",l.book_no);
              gotoxy(59,c);
              printf("%s",l.date);
              gotoxy(75,c);
              printf("%d",l.n);
              gotoxy(94,c);
              printf("%s",l.due_date);
              c=c+2;
          }
    }
    fclose(ifile);
    fflush(stdin);
    gotoxy(43,c+2);
    printf("Search another class[y/n]: ");
    scanf("%c",&ch);
    if(ch=='y'||ch=='Y')
         class_details();
    else
        mainmenu();

}
void search_book()
{
     system("cls");
     FILE *lfile;
     int ch,b_no,found=0;
     char choice[50];
     gotoxy(43,2);
     printf("SEARCH BOOK");
     lfile=fopen("Books.txt","r");
     gotoxy(43,4);
     if(lfile==NULL)
     {
        printf("No Record found");
        fclose(lfile);
        gotoxy(36,6);
		printf("Enter any key to go to main menu: ");
		getch();
		mainmenu();
     }
    else
    {
        gotoxy(39,4);
        printf("1. Search Book by Book number");
        gotoxy(39,6);
        printf("2. Search Book by Book name");
        gotoxy(39,8);
        printf("3. Search Book by Author name");
        gotoxy(39,10);
        printf("4. Search Book by Genres");
        gotoxy(39,12);
        printf("Enter your choice: ");
        scanf("%d",&ch);
        gotoxy(39,14);
        switch(ch)
        {
            case 1:
                printf("Enter Book Number: ");
                scanf("%d",&b_no);
                break;
            case 2:
                printf("Enter Book Name: ");
                scanf("%s",choice);
                break;
            case 3:
                printf("Enter Author Name: ");
                scanf("%s",choice);
                break;
            case 4:
                printf("Enter Genre: ");
                scanf("%s",choice);
                break;
            default:
                {
                    printf("Wrong Choice: ");
                    fclose(lfile);
                    fflush(stdin);
                    gotoxy(39,16);
                    printf("Search another book[y/n]: ");
                    scanf("%c",&ch);
                    if(ch=='y'||ch=='Y')
                        search_issued_book();
                    else
                        mainmenu();
                }
        }
        system("cls");
        gotoxy(43,2);
        printf("SEARCHED BOOK");
        while(fscanf(lfile,"%s %d %s %s",l.book_name,&l.book_no,l.author_name,l.genres)!=EOF)
        {
            if(l.book_no==b_no|| (strcmpi(l.book_name,choice)==0)|| (strcmpi(l.author_name,choice)==0)|| (strcmpi(l.genres,choice)==0))
            {
                found=1;
                gotoxy(21,7);
                printf("%s",l.book_name);
                gotoxy(36,7);
                printf("%d",l.book_no);
                gotoxy(51,7);
                printf("%s",l.author_name);
                gotoxy(66,7);
                printf("%s",l.genres);
            }
        }
    }
        if(found==1)
        {
           gotoxy(21,4);
           printf("Book Name");
           gotoxy(36,4);
           printf("Book Number");
           gotoxy(51,4);
           printf("Author Name");
           gotoxy(66,4);
           printf("Genres");
           gotoxy(21,10);
        }
        else
        {
            gotoxy(43,4);
            printf("Searched Book not found");
            gotoxy(43,6);
        }
        fclose(lfile);
        fflush(stdin);
        printf("Search another book[y/n]: ");
        scanf("%c",&ch);
        if(ch=='y'||ch=='Y')
            search_book();
        else
            mainmenu();
}
void available()
{
     system("cls");
     FILE *lfile;
     FILE *ifile;
     int id,found=0,found2=0;
     gotoxy(43,2);
     printf("AVAILABILITY");
     lfile=fopen("Books.txt","r");
     gotoxy(43,4);
     if(lfile==NULL)
     {
        printf("No Record found");
        fclose(lfile);
        gotoxy(36,6);
		printf("Enter any key to go to main menu: ");
		getch();
		mainmenu();
     }
     gotoxy(33,4);
     printf("Enter Book No. to check availability for: ");
     scanf("%d",&id);
     while(fscanf(lfile,"%s %d %s %s",l.book_name,&l.book_no,l.author_name,l.genres)!=EOF)
     {
         if(l.book_no==id)
         {
             fclose(lfile);
             found2=1;
             goto C;
         }
     }
     if(found2==0)
     {
         gotoxy(41,6);
         printf("Book not in library");
         fclose(lfile);
         goto D;
     }
     C:
     ifile=fopen("Issue.txt","r");
     if(ifile==NULL)
     {
        printf("No Record found");
        fclose(ifile);
        gotoxy(36,6);
		printf("Enter any key to go to main menu: ");
		getch();
		mainmenu();
     }
     while(fscanf(ifile,"%s %d %s %d %s %d %s",l.student_name,&l.student_class,l.section,&l.book_no,l.date,&l.n,l.due_date)!=EOF)
     {
          if(l.book_no==id)
          {
            gotoxy(20,6);
            found=1;
            printf("This Book is Issued to: %s of %d-%s on %s for %d days till %s",l.student_name,l.student_class,l.section,l.date,l.n,l.due_date);
        }
    }
    if(found==0)
    {
        gotoxy(41,6);
        printf("Book is available");
    }
    fclose(ifile);
    D:
    fflush(stdin);
    gotoxy(33,8);
    printf("Check availability for another book[y/n]: ");
    scanf("%c",&ch);
    if(ch=='y'||ch=='Y')
         available();
    else
        mainmenu();
}
void total_books()
{
    int count;
    system("cls");
    FILE *lfile;
    lfile=fopen("Books.txt","r");
    gotoxy(43,2);
    printf("TOTAL BOOKS IN LIBRARY: ");
    if(lfile==NULL)
    {
        gotoxy(43,4);
        printf("No Record found");
        fclose(lfile);
        gotoxy(36,6);
		printf("Enter any key to go to main menu: ");
		getch();
    }
    else
    {
    count=0;
    while(fscanf(lfile,"%s %d %s %s",l.book_name,&l.book_no,l.author_name,l.genres)!=EOF)
    {
        count++;
    }
    }
    fclose(lfile);
    printf("%d",count);
    gotoxy(43,4);
    printf("Enter any key to go to main menu: ");
    getch();
    mainmenu();
}
void update_password()
{
    FILE *pass;
    FILE *change_pass;
    char *old_pass,new_pass[20],re_new_pass[20];
    pass=fopen("pass.txt","rb+");
    system("cls");
    gotoxy(43,2);
    printf("UPDATE PASSWORD");
    if(pass==NULL)
    {
        gotoxy(43,4);
        printf("No Record found");
        fclose(pass);
        gotoxy(36,6);
		printf("Enter any key to go to password menu: ");
		getch();
		password_menu();
    }
    gotoxy(38,4);
    printf("Enter Old password: ");
    old_pass=get_pass();
    while(fscanf(pass,"%s",l.password)!=EOF)
    {
        if(strcmp(old_pass,l.password)==0)
        {
            gotoxy(38,6);
            printf("Enter new password: ");
            strcpy(new_pass,get_pass());
            gotoxy(38,8);
            printf("Re-Enter new password: ");
            strcpy(re_new_pass,get_pass());
            if(strcmp(new_pass,re_new_pass)==0)
            {
                change_pass=fopen("change_pass.txt","w");
                strcpy(l.password,new_pass);
                fprintf(change_pass,"%s",l.password);
                fclose(pass);//file should be closed in all functions
                fclose(change_pass);
                remove("pass.txt");
                rename("change_pass.txt","pass.txt");
                gotoxy(38,10);
                printf("Password changed!!!");
                gotoxy(38,12);
                printf("Press any key to go to password menu");
                getch();
                password_menu();
            }
            else
            {
                gotoxy(38,10);
                printf("Password mismatched");
                gotoxy(38,12);
                printf("Press any key to go to password menu");
                fclose(pass);
                getch();
                password_menu();
            }
        }
        else
        {
            gotoxy(38,6);
            printf("Wrong password");
            gotoxy(38,8);
            printf("Press any key to go to password menu");
            fclose(pass);
            getch();
            password_menu();
        }
    }
}
