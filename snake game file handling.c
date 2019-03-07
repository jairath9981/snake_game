#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
COORD coord={0,0};
void gotoxy(int x,int y)
{
coord.X=x;
coord.Y=y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void hidecursor()
{
HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO info;
info.dwSize = 100;
info.bVisible = FALSE;
SetConsoleCursorInfo(consoleHandle, &info);
}
struct food
{
int xf,yf;
char valuef;
};
struct poison
{
int xp,yp;
char valuep;
};
struct snake
{
int xs,ys;
char values;
struct snake *next;
};
struct snake *head=NULL;
struct food*CreateFoodNode(int x1,int y1,char value)
{
struct food *fo;
fo=(struct food*)malloc(1*sizeof(struct food));
fo->xf=x1;
fo->yf=y1;
fo->valuef=value;
return fo;
}
struct poison *CreatePoisonNode(int xs,int ys,char value)
{
struct poison *po;
po=(struct poison*)malloc(1*sizeof(struct poison));
po->xp=xs;
po->yp=ys;
po->valuep=value;
return po;
}
struct snake* Construct_Snake_Node(int x1,int y1,char value1)
{
struct snake *n;
n=(struct snake*)malloc(1*sizeof(struct snake));
n->xs=x1;
n->ys=y1;
n->values=value1;
n->next=NULL;
return n;
}
int* GenerateCordinates(int c,struct food *f1,struct poison *p1)
{
int x1,y1,x2=0,y2=0,i=0;
int *a;
a=(int*)malloc(2*sizeof(int));
struct snake *sn=head;
struct food *fo=f1;
struct poison *po=p1;
if(c==1 && p1!=NULL) /// generate coordinates for food
{
x2=po->xp;
y2=po->yp;
}
if(c==2 && f1!=NULL) /// generate coordinates for poison
{
x2=fo->xf;
y2=fo->yf;
}
srand(time(0));  /// Use current time as seed for random generator
while(1)
{
x1=rand()%20;
y1=rand()%80;
if(x1==0)
{
x1++;
}
if(x1==20)
{
x1--;
}
if(y1==0)
{
y1++;
}
if(y1==80)
{
y1--;
}
sn=head;
if(x1!=x2 && y1!=y2)
{
while(sn!=NULL)
{
if(sn->xs==x1 && sn->ys==y1)
{
break;
}
sn=sn->next;
}
}
if(sn==NULL)
{
a[i]=x1;
i++;
a[i]=y1;
break;
}
}
return a;
}
void insertAtTail1(int xs,int ys,char value)
{
struct snake *temp,*t;
temp=Construct_Snake_Node(xs,ys,value);
if(head==NULL)
{
head=temp;
}
else
{
t=head;
while(t->next!=NULL)
{
t=t->next;
}
t->next=temp;
}
}
void Insert_In_Snake_Body_Vertical(int x1,int y1)
{
if(x1==0)
x1++;
if(y1==0)
y1++;
int i,flagd=0;
struct snake*n, *temp;
n=head;
if(x1>=16)  /// head is on top vertical
{
temp=Construct_Snake_Node(x1,y1,'T');
flagd=1; /// i will do  x-- to move vertical upward in matrix so head come on top
}
else   /// head is in bottom vertical
{
temp=Construct_Snake_Node(x1,y1,'H'); /// i will do  x++ to move vertical downward in matrix so tail come in bottom
}
if(n==NULL)
{
head=temp;
}
for(i=1;i<4;i++)
{
if(flagd==1)
{
x1--;
if(i!=3)
{
temp=Construct_Snake_Node(x1,y1,'#');
}
else
{
temp=Construct_Snake_Node(x1,y1,'H');  /// x-- head come on top vertical
}
}
else
{
x1++;
if(i!=3)
{
temp=Construct_Snake_Node(x1,y1,'#');
}
else
{
temp=Construct_Snake_Node(x1,y1,'T');
}
}
n=head;
while(n->next!=NULL)
{
n=n->next;
}
n->next=temp;
}
}
void Insert_In_Snake_Body_Horizontal(int x1,int y1)
{
if(x1==0)
x1++;
if(y1==0)
y1++;
int i;
struct snake*n,*temp;
temp=Construct_Snake_Node(x1,y1,'H'); ///H##T
if(head==NULL)
{
head=temp;
}
for(i=1;i<4;i++)
{
y1++;
if(i!=3)
{
temp=Construct_Snake_Node(x1,y1,'#');
}
else
{
temp=Construct_Snake_Node(x1,y1,'T');
}
n=head;
while(n->next!=NULL)
{
n=n->next;
}
n->next=temp;
}
}
void Move_Snake_Head(int x1,int y1)
{
struct snake *temp,*t;
temp=Construct_Snake_Node(x1,y1,'H');
temp->next=head;
head=temp;
}
void ShortTail()
{
struct snake*sn1,*sn2,*temp;
sn1=head;
sn2=sn1;
while(sn1->next!=NULL)
{
sn2=sn1;
sn1=sn1->next;
}
sn2->values=sn1->values;
sn2->next=NULL;
}
void Increase_Tail()
{
int x1,y1;
struct snake*sn1,*sn2,*temp;
sn1=head;
sn2=sn1;
while(sn1->next!=NULL)
{
sn2=sn1;
sn1=sn1->next;
}
if(sn2->xs==sn1->xs) /// tail is horizontal
{
x1=sn1->xs;
y1=sn1->ys;
if(sn2->ys>y1) ///left horizontal insertion T##H
{
sn1->values='#';
y1--;
temp=Construct_Snake_Node(x1,y1,'T');
sn1->next=temp;
}
else /// right horizontal insertion   H##T
{
sn1->values='#';
y1++;
temp=Construct_Snake_Node(x1,y1,'T');
sn1->next=temp;
}
}
else if(sn2->ys==sn1->ys) ///tail is vertical
{
x1=sn1->xs;
y1=sn1->ys;
if(sn2->xs<x1) ///bottom vertical insertion
{
sn1->values='#';
x1++;
temp=Construct_Snake_Node(x1,y1,'T');
sn1->next=temp;
}
else /// up vertical insertion
{
sn1->values='#';
x1--;
temp=Construct_Snake_Node(x1,y1,'T');
sn1->next=temp;
}
}
}
int Snake_Ate_Something(struct food *f1,struct poison *p1)
{
int x1,y1,count=0;
struct food *fo=f1;
struct poison *po=p1;
struct snake*sn1;
sn1=head;
if(sn1->xs==fo->xf && sn1->ys==fo->yf)
{
return 1;
}
if(sn1->xs==po->xp && sn1->ys==po->yp)
{
return 2;
}
x1=sn1->xs;
y1=sn1->ys;
sn1=sn1->next;
while(sn1!=NULL)
{
if(x1==sn1->xs && y1==sn1->ys)
{
return 3;
}
else
{
count++;
sn1=sn1->next;
}
}
if(count==2)
{
return 3;
}
return 0;
}
int Generate_Point()
{
int x;
srand(time(0));  /// Use current time as seed for random generator
x=rand()%20;
return x;
}
void SetMatrix(char a[][80],struct food *f1,struct poison *p1,int row,int col)
{
int i,j;
for(i=0;i<=row;i++)
{
for(j=0;j<=col;j++)
{
if(i==0 || i==row)
{
a[i][j]='!';
}
else if(j==0 || j==col)
{
a[i][j]='!';
}
else
{
a[i][j]=' ';
}
}
}
struct snake *sn=head;
struct food *fo=f1;
struct poison *po=p1;
while(sn!=NULL)
{
a[sn->xs][sn->ys]=sn->values;
sn=sn->next;
}
a[fo->xf][fo->yf]=fo->valuef;
a[po->xp][po->yp]=po->valuep;
}
void DisplayMatrix(char a[][80],int row,int col)
{
int i,j;
for(i=0;i<=row;i++)
{
for(j=0;j<=col;j++)
{
printf("%c",a[i][j]);
}
printf("\n");
}
}
void Valid_Key(int *flagr,int *flagl,int *flagu,int *flagd)
{
int x1,y1;
struct snake *sn1,*sn2;
sn1=head;
sn2=sn1->next;
if(sn2->xs==sn1->xs) /// head is horizontal
{
x1=sn1->xs;
y1=sn1->ys;
if(sn2->ys-y1==1) /// initially moving left H#
{
*flagr=0;
}
else if(y1-sn2->ys==1) /// initially moving right #H
{
*flagl=0;
}
else if(y1==1)
{
*flagl=0;
}
else  if(y1==79)
{
*flagr=0;
}
}
else if(sn2->ys==sn1->ys) ///head is vertical
{
x1=sn1->xs;
y1=sn1->ys;
if(x1-sn2->xs==1) /// initially moving down
{
*flagu=0;
}
else  if(sn2->xs-x1==1)   ///initially moving  up
{
*flagd=0;
}

else if(x1==19)
{
*flagd=0;
}
else if(x1==1)
{
*flagu=0;
}
}
}
void shifter(char val)
{
int x1,y1;
struct snake *sn1,*sn2,*sn3;
sn1=head;
sn3=sn1;
sn2=sn1->next;
x1=sn1->xs;
y1=sn1->ys;
while(sn1->next!=NULL)
{
sn1->values=sn2->values;
sn1=sn1->next;
if(sn2->next!=NULL)
{
sn3=sn2;
sn2=sn2->next;
}
}
sn3->next=NULL;
if(val=='d')
{
if(y1==80)
y1=1;
else
y1++;
Move_Snake_Head(x1,y1);
}
else if(val=='a')
{
if(y1==0)
y1=79;
else
y1--;
Move_Snake_Head(x1,y1);
}
else if(val=='s')
{
if(x1==20)
x1=1;
else
x1++;
Move_Snake_Head(x1,y1);
}
else if(val=='w')
{
if(x1==0)
x1=19;
else
x1--;
Move_Snake_Head(x1,y1);
}
}
void WriteInFile(struct food *f1,struct poison *p1,int score,int opt)
{
int i=0;
struct snake *sn=head;
struct food *fo=f1;
struct poison *po=p1;
char buffer[100],dataw[2000],ch[10];
FILE *fp,*fps;
if(opt==2)
{
fp=fopen("Snake4.txt","w");
fps=fopen("Score.txt","w");
fclose(fps);
fclose(fp);
}
if(opt==1)
{
fp=fopen("Snake4.txt","w");
fps=fopen("Score.txt","w");
fprintf(fps,"%d",score);
fclose(fps);
itoa(fo->xf,buffer,10);
strcpy(dataw,buffer);
strcat(dataw,",");
itoa(fo->yf,buffer,10);
strcat(dataw,buffer);
strcat(dataw,",");
i=0;
ch[i]=fo->valuef;
i++;
ch[i]='\0';
strcat(dataw,ch);
strcat(dataw,"$");
itoa(po->xp,buffer,10);
strcat(dataw,buffer);
strcat(dataw,",");
itoa(po->yp,buffer,10);
strcat(dataw,buffer);
strcat(dataw,",");
i=0;
ch[i]=po->valuep;
i++;
ch[i]='\0';
strcat(dataw,ch);
strcat(dataw,"$");
while(sn!=NULL)
{
itoa(sn->xs,buffer,10);
strcat(dataw,buffer);
strcat(dataw,",");
itoa(sn->ys,buffer,10);
strcat(dataw,buffer);
strcat(dataw,",");
i=0;
ch[i]=sn->values;
i++;
ch[i]='\0';
strcat(dataw,ch);
strcat(dataw,"$");
sn=sn->next;
}
fputs(dataw,fp);
fclose(fp);
}
}
void Read(struct food **f2,struct poison **p2,int **s2) /// we are taking addresses of pointers thats why **
{
int i=0,xs=0,ys=0,j=0,flagx=0,flagy=0,sco;
struct food *fo=NULL;
struct poison *po=NULL;
char buffer[100],dataw[2000],value;
FILE *fp,*fps;
fps=fopen("Score.txt","r");
fscanf(fps,"%d",&sco);
fclose(fps);
**s2=sco;  /// I have to update score of main which is pointed by s and s is pointed by s2 so concept of pointer to pointer thats why
           /// **s2
fp=fopen("Snake4.txt","r");
while(!feof(fp))
{
fgets(dataw,2000,fp);
while(dataw[i]!='\0')
{
i++;
}
if(i>1)
{
i=0;
while(dataw[i]!='\0')
{
while(dataw[i]!=',' && dataw[i]!='$' && xs==0)
{
buffer[j]=dataw[i];
j++;
i++;
flagx=1;
}
if(flagx==1)
{
buffer[j]='\0';
xs=atoi(buffer);
j=0;
flagx=0;
}
while(dataw[i]!=',' && dataw[i]!='$' && ys==0)
{
buffer[j]=dataw[i];
j++;
i++;
flagy=1;
}
if(flagy==1)
{
buffer[j]='\0';
ys=atoi(buffer);
j=0;
flagy=0;
}
if(dataw[i]!=',' && dataw[i]!='$' && xs!=0 && ys!=0)
{
value=dataw[i];
if(value=='@')
{
fo=CreateFoodNode(xs,ys,value); /// f2= means address of f1 as f2 is pointing to f1
*f2=fo; ///*f2 is value of f1 which is NULL previously so updating is value by address of heap food
}
else if(value=='P')
{
po=CreatePoisonNode(xs,ys,value);
*p2=po;
}
else if(value=='H' || value=='#' || value=='T')
{
insertAtTail1(xs,ys,value);
}
xs=0;ys=0;
}
i++;
}
}
else
return;
}
}
void Input(char a[][80],struct food *f1,struct poison *p1,int row,int col,int score,int opt)
{
int gm=1,x=0,*a1,i=0,xs,ys;
a1=(int*)malloc(2*sizeof(int));
int flagr=1,flagl=1,flagu=1,flagd=1;
char choice,cc;
while(gm)
{
SetMatrix(a,f1,p1,20,80);
gotoxy(0,0);
DisplayMatrix(a,20,80);
hidecursor();
gotoxy(1,25);
printf("score =  %d",score);

if(kbhit())
{
choice=getch();
}
Sleep(70);
Valid_Key(&flagr,&flagl,&flagu,&flagd);
if(choice=='d' && flagr==1)
{
cc=choice;  /// TO store correct choice so on random choice game flow do not disturb
shifter(choice);
}
if(choice=='a' && flagl==1)
{
cc=choice;
shifter(choice);
}
if(choice=='w' && flagu==1)
{
cc=choice;
shifter(choice);
}
if(choice=='s' && flagd==1)
{
cc=choice;
shifter(choice);
}
if(choice=='u')
{
WriteInFile(f1,p1,score,1);
gotoxy(16,28);
printf("DO NOT WORRY YOUR GAME IS SAVED\n");
gm=0;
}
else
{
choice=cc;
}
x=Snake_Ate_Something(f1,p1);
if(x==1)
{
score+=1;
a1=GenerateCordinates(1,f1,p1);
xs=a1[i];
i++;
ys=a1[i];
i=0;
f1=CreateFoodNode(xs,ys,'@');
Increase_Tail();
}
if(x==2)
{
score-=1;
a1=GenerateCordinates(2,f1,p1); /// it is sending value of f1 which stores addresses in itself so to receive this there is a pointer
                               ///  in argument of function
xs=a1[i];
i++;
ys=a1[i];
i=0;
p1=CreatePoisonNode(xs,ys,'P');
ShortTail();
}
if(x==3)
{
gm=0;
if(opt==2)
{
WriteInFile(f1,p1,score,2);
}
}
flagr=1;
flagl=1;
flagu=1;
flagd=1;
}
}
int main()
{
int x,xs,ys,*a1,i=0,score=0,*s;
s=&score;
a1=(int*)malloc(2*sizeof(int));
char a[20][80],choice;
struct food *f1=NULL;
struct poison *p1=NULL;
printf("PRESS 1 TO START NEW GAME\n");
printf("PRESS 2 TO LOAD SAVED GAME\n");
scanf("%c",&choice);
system("cls");
if(choice=='1')
{
score=0;
x=Generate_Point();
if(x%2==1) /// if x is odd then vertical
{
xs=Generate_Point();
ys=Generate_Point();
Insert_In_Snake_Body_Vertical(xs,ys);
}
else     /// else x is even then horizontal
{
xs=Generate_Point();
ys=Generate_Point();
Insert_In_Snake_Body_Horizontal(xs,ys);
}
a1=GenerateCordinates(1,f1,p1);
xs=a1[i];
i++;
ys=a1[i];
i=0;
f1=CreateFoodNode(xs,ys,'@');
a1=GenerateCordinates(2,f1,p1);
xs=a1[i];
i++;
ys=a1[i];
p1=CreatePoisonNode(xs,ys,'P');
Input(a,f1,p1,20,80,score,1);
}
if(choice=='2')
{
Read(&f1,&p1,&s);
if(f1==NULL)
{
printf("Sorry no saved game exist please start new game\n");
}
else
{
Input(a,f1,p1,20,80,score,2);
}
}
}

