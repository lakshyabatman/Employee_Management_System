#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>


void returnfunc(void);
void mainmenu(void);
void addemp(void);
void deleteemp(void);
void editemp(void);
void searchemp(void);
void viewemp(void);
void closeapplication(void);
int  getdata();
int  checkid(int);
void Password();
void issuerecord();

FILE *fp,*ft,*fs;


COORD coord = {0, 0};
int s;
char findemp;
char password[10]={"jaypee"};

void gotoxy (int x, int y)
{
coord.X = x; coord.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct D
{
int mm,dd,yy;
};
struct employee
{
	int id;
	char name[20];
	char depart[20];
	struct D DOB;
	struct D DOJ;
};
struct employee a;
int main()
{
	Password();
	getch();
	return 0;

}
void mainmenu()
{
	system("cls");
	int i;
	gotoxy(20,3);
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!MAIN MENU!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	gotoxy(20,5);
	printf("1. Add employee   ");
	gotoxy(20,7);
	printf("2. Delete employee");
	gotoxy(20,9);
	printf("3. Search employee");
	gotoxy(20,11);
	printf("4. View Employee list");
	gotoxy(20,13);
	printf("5. Edit Employee's Record");
	gotoxy(20,15);
	printf("6. Close Application");
	gotoxy(20,20);
	printf("Enter your choice:");
	switch(getch())
		{
			case '1':
			addemp();
			break;
			case '2':
			deleteemp();
			break;
			case '3':
			searchemp();
			break;
			case '4':
			viewemp();
			break;
			case '5':
			editemp();
			break;
			case '6':
				{
					system("cls");
					gotoxy(16,3);
					printf("\tTHANK YOU");
					Sleep(3000);
					exit(0);
				}
default:
{
	gotoxy(10,23);
	printf("Please re-entered correct option");
	if(getch())
	mainmenu();
}

}
}

void addemp(void)
{
	int i;
	system("cls");
	fp=fopen("OP.dat","ab+");
	if(getdata()==1)
	{
		fseek(fp,0,SEEK_END);
		fwrite(&a,sizeof(a),1,fp);
		fclose(fp);
		gotoxy(21,14);
		printf("The record is sucessfully saved");
		gotoxy(21,15);
		printf("Save any more?(Y / N):");
		if(getch()=='n')
		mainmenu();
		else
		system("cls");
        addemp();
	}
	gotoxy(21,35);
	printf("Press Enter Return To Main Menu");
	if(getch()=="")
    {
        mainmenu();
    }
}

void deleteemp()
{
	system("cls");
	int d;
	char another='y';
	while(another=='y')
	{
	system("cls");
	gotoxy(10,5);
	printf("Enter the Employee ID to  delete:");
	scanf("%d",&d);
	fp=fopen("OP.dat","rb+");
	rewind(fp);
	while(fread(&a,sizeof(a),1,fp)==1)
		{
			if(a.id==d)
				{
					gotoxy(10,7);
					printf("The Employee Record Is Available");
					gotoxy(10,8);
					printf("Employee Name is %s",a.name);
					gotoxy(10,9);
					printf("Department %d",a.depart);
					findemp='t';
				}
		}
if(findemp!='t')
{
	gotoxy(10,10);
	printf("No record is found modify the search");
	if(getch())
	mainmenu();
}
if(findemp=='t')
{
	gotoxy(10,9);
	printf("Do you want to delete it?(Y/N):");
	if(getch()=='y')
		{
			ft=fopen("copy.dat","wb+");
			rewind(fp);
			while(fread(&a,sizeof(a),1,fp)==1)
				{
					if(a.id!=d)
						{
							fseek(ft,0,SEEK_CUR);
							fwrite(&a,sizeof(a),1,ft);
						}
				}
	fclose(ft);
	fclose(fp);
	remove("OP.dat");
	rename("test.dat","OP.dat");
	fp=fopen("OP.dat","rb+");
	if(findemp=='t')
		{
			gotoxy(10,10);
			printf("The record is sucessfully deleted");
			gotoxy(10,11);
			printf("Delete another record?(Y/N)");
		}
		}
	else
		mainmenu();
		fflush(stdin);
		another=getch();
}
}
gotoxy(10,15);
mainmenu();
}
void searchemp()
{
	system("cls");
	int d;
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!Search employee!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	gotoxy(20,10);
	printf("1. Search By ID");
	gotoxy(20,14);
	printf("2. Search By Name");
	gotoxy( 15,20);
	printf("Enter Your Choice");
	fp=fopen("OP.dat","rb+");
	rewind(fp);
		switch(getch())
		{
			case '1':
			{
			system("cls");
			gotoxy(25,4);
			printf("****Search Employee By Id****");
			gotoxy(20,5);
			printf("Enter The Employee Id:");
			scanf("%d",&d);
			while(fread(&a,sizeof(a),1,fp)==1)
				{
					if(a.id==d)
						{
							gotoxy(20,7);
							printf("The Employee is available");
							gotoxy(20,9);
							printf("ID:%d",a.id);
							gotoxy(20,10);
							printf("Name:%s",a.name);
							gotoxy(20,11);
							printf("Department:%s ",a.depart);
							findemp='t';
						}
				}
	if(findemp!='t')
		{
			gotoxy(22,9);
			printf("\aNo Record Found");
		}
	gotoxy(20,17);
	printf("Try another search?(Y/N)");
	if(getch()=='y')
	searchemp();
	else
	mainmenu();
	break;
			}
	case '2':
	{
		char s[15];
		system("cls");
		gotoxy(25,4);
		printf("****Search employee By Name****");
		gotoxy(20,5);
		printf("Enter Employee Name:");
		scanf("%s",s);
		int d=0;
		while(fread(&a,sizeof(a),1,fp)==1)
			{
				if(strcmp(a.name,(s))==0)
					{
						gotoxy(20,7);
						printf("The Employee Is Available");
						gotoxy(20,9);
						printf("ID:%d",a.id);
						gotoxy(20,10);
						printf("Name:%s",a.name);
						gotoxy(20,11);
						printf("Depart:%s",a.depart);
						d++;
					}

			}
	if(d==0)
	{
		gotoxy(22,9);printf("\aNo Record Found");
	}
	gotoxy(20,17);
	printf("Try another search?(Y/N)");
	if(getch()=='y')
		searchemp();
	else
	mainmenu();
	break;
	}
	default :
	getch();
	searchemp();
		}
	fclose(fp);
}

void viewemp()
{
    int i=0,j;
    system("cls");
    gotoxy(14,1);
    printf("*********************************Department List*****************************");
    gotoxy(2,2);
    printf("             ID    EMPLOYEE NAME     DEPARTMENT       DOB         DOJ             ");
    j=4;
    fp=fopen("OP.dat","rb");
    while(fread(&a,sizeof(a),1,fp)==1)
    {
        gotoxy(16,j);
        printf("%d",a.id);
        gotoxy(23,j);
        printf("%s",a.name);
        gotoxy(41,j);
        printf("%s",a.depart);
        gotoxy(53,j);
        printf("%d-%d-%d",a.DOB.dd,a.DOB.mm,a.DOB.yy);
        gotoxy(65,j);
        printf("%d-%d-%d",a.DOJ.dd,a.DOJ.mm,a.DOJ.yy);
        printf("\n\n");
        j++;
    }
    fclose(fp);
    gotoxy(35,25);
    returnfunc();
}


void editemp(void)
{
	system("cls");
	int c=0;
	int d,e;
	gotoxy(20,4);
	printf("****Edit Employee Section****");
	char another='y';
	while(another=='y')
		{
			system("cls");
			gotoxy(15,6);
			printf("Enter Employee Id to be edited:");
			scanf("%d",&d);
			fp=fopen("OP.dat","rb+");
			while(fread(&a,sizeof(a),1,fp)==1)
			{
				if(checkid(d)==0)
				{
					gotoxy(15,7);
					printf("The Employee is Availble");
					gotoxy(15,8);
					printf("The Employee ID:%d",a.id);
					gotoxy(15,9);
					printf("Enter New Name:");
					scanf("%s",a.name);
					gotoxy(15,10);
					printf("Enter New Depart:");
					scanf("%s",a.depart);
					gotoxy(15,14);
					printf("The record is modified");
					fseek(fp,ftell(fp)-sizeof(a),0);
					fwrite(&a,sizeof(a),1,fp);
					fclose(fp);
					c=1;
				}
				if(c==0)
				{
					gotoxy(15,9);
					printf("No record found");
				}
			}
	gotoxy(15,16);
	printf("Modify another Record?(Y/N)");
	fflush(stdin);
	another=getch() ;
		}
	returnfunc();
}
void returnfunc(void)
{
	printf(" Press ENTER to return to main menu");
	a:
	if(getch()==13)
	mainmenu();
	else
	goto a;
}

int getdata()
{
	int t;
	gotoxy(20,3);printf("!!!!!!!!!!!!!!!!!!!!Enter the Information Below!!!!!!!!!!!!!!!!!!!!");
	gotoxy(25,6);
	printf("Employee ID:\t");
	gotoxy(37,6);
	scanf("%d",&t);
	if(checkid(t) == 0)
		{
			gotoxy(21,13);
			printf("\aThe Employee Id Already Exists\a");
			getch();
			mainmenu();
			return 0;
		}
	a.id=t;
	gotoxy(25,7);
	printf("Employee Name:");
	gotoxy(39,7);
	scanf("%s",a.name);
	gotoxy(25,8);
	printf("Department:");
	gotoxy(36,8);
	scanf("%s",a.depart);
	gotoxy(25,9);
	printf("Enter DOB(DD\MM\YYYY):");
	gotoxy(48,9);
	scanf("%d %d %d",&a.DOB.dd,&a.DOB.mm,&a.DOB.yy);
	gotoxy(25,10);
	printf("Enter DOJ(DD\MM\YYYY):");
	gotoxy(48,10);
	scanf("%d %d %d",&a.DOJ.dd,&a.DOJ.mm,&a.DOJ.yy);
	return 1;
}

int checkid(int t)
{
	rewind(fp);
	while(fread(&a,sizeof(a),1,fp)==1)
	if(a.id==t)
	return 0;
	return 1;
}
void Password(void)
{
    int i=0;
    system("cls");
    char d[25]="Password Protected";
    char ch,pass[10];
    gotoxy(30,3);
    printf("!!!!!!!!!!!!!!!!!!!!Password Protected!!!!!!!!!!!!!!!!!!!!");
    gotoxy(40,5);
    printf("Enter Password:");
    while(ch!=13)
    {
    ch=getch();
    if(ch!=13 && ch!=8)
        {
            putch('*');
            pass[i] = ch;
            i++;
        }
    }
    pass[i] = '\0';
    if(strcmp(pass,password)==0)
        {
            gotoxy(15,9);
            printf("Password match");
            gotoxy(17,10);
            printf("Press any key to continue.....");
            getch();
            mainmenu();
        }
    else
        {
            gotoxy(15,16);
            printf("\aWarning!! Incorrect Password");
            Password();
        }
    }
