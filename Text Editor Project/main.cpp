#include <iostream>
#include <fstream>
#include <graphics.h>
using namespace std;
struct Node
{
    int Char;
    int Lin;
    int Col;
    int Semn;
    struct Node *Next;
    struct Node *Prev;
};

int Colour;
void WhichColour()
{
    settextstyle(10,12,0);
    setcolor(WHITE);
    bar(1184,54,1600,94);
    setcolor(Colour);
    if(Colour==0)
        outtextxy(1191,57,"NEGRU");
    if(Colour==1)
        outtextxy(1191,57,"ALBASTRU");
    if(Colour==2)
        outtextxy(1191,57,"VERDE");
    if(Colour==3)
        outtextxy(1191,57,"ALBASTRU");
    if(Colour==4)
        outtextxy(1191,57,"ROSU");
    if(Colour==5)
        outtextxy(1191,57,"MAGENTA");
    if(Colour==6)
        outtextxy(1191,57,"MARO");
    if(Colour==7)
        outtextxy(1191,57,"GRI DESCHIS");
    if(Colour==8)
        outtextxy(1191,57,"GRI INCHIS");
    if(Colour==10)
        outtextxy(1191,57,"VERDE DESCHIS");
    if(Colour==11)
        outtextxy(1191,57,"ALBASTRU DESCHIS");
    if(Colour==12)
        outtextxy(1191,57,"ROSU DESCHIS");
    if(Colour==13)
        outtextxy(1191,57,"MAGENTA DESCHIS");
    if(Colour==14)
        outtextxy(1191,57,"GALBEN");
    settextstyle(8,12,2);
}

int NullVerify(struct Node **Head,int x,int y);
int LinVerify(struct Node **Head,int y);
void MakePage(int x,int y);
void PrintPage(struct Node **Head);
int FirstNodeLine(struct Node **Head,int x,int y);

bool FirstNodeVerify(struct Node **Head,int Col,int Lin)
{
    struct Node *e;
    bool Val = 0;

    for(e=*Head; e!=NULL&&!Val; e=e->Next)
    {
        if(e->Lin == Lin && e->Col == Col)
        {
            if(e->Prev == NULL)
                Val=1;
        }
    }

    return Val;
}


bool LastNodeVerify(struct Node **Head,struct Node **Last,int Col,int Lin)
{
    struct Node *e;
    bool Val = 0;

    for(e=*Head; e!=NULL&&!Val; e=e->Next)
    {
        if(e->Lin == Lin && e->Col == Col)
        {
            if(e->Next == *Last)
                Val = 1;
        }
    }

    return Val;
}


bool IfNextNode(struct Node **Head,int Col,int Lin)
{
    struct Node *e;
    bool LastElem=0;

    for(e=*Head; e!=NULL&&!LastElem; e=e->Next)
    {
        if(e->Lin > Lin && e->Col >= Col)
            LastElem = 1;
    }

    return LastElem;
}

///CTRL+V
void Add2(struct Node **Head2,struct Node **Last2,int Char)
{
    struct Node *New =(struct Node*) malloc(sizeof(struct Node));
    New->Char = Char;
    New->Lin = 0;
    New->Col = 0;

    if(*Head2 == NULL)
    {
        New->Next = NULL;
        New->Prev = NULL;
        *Head2 = *Last2 = New;
    }
    else
    {
        New->Next = NULL;
        New->Prev = *Last2;
        (*Last2)->Next = New;
        *Last2 = New;
    }
}

///CTRL+V
void Add(struct Node **Head,struct Node **Last,int Char,int Lin,int Col)
{
    struct Node *e;
    struct Node *f;


    struct Node *New =(struct Node*) malloc(sizeof(struct Node));
    New->Char = Char;
    New->Lin = Lin;
    New->Col = Col;
    New->Semn = 0;

    if(*Head == NULL)
    {
        New->Next = NULL;
        New->Prev = NULL;
        *Head = *Last = New;
    }
    else if(FirstNodeVerify(Head,Col,Lin)==1)
    {
        for(e=*Head; e!=NULL; e=e->Next)
        {
            if(e->Lin == Lin && e->Col == Col)
            {
                New->Prev = NULL;
                New->Next = *Head;
                New->Next = e;
                e->Prev = New;
                *Head = New;

                break;
            }
        }

        for(e=*Head; e!=NULL; e=e->Next)
        {
            if(e!=*Head && e->Lin == Lin && e->Col >= Col)
                e->Col = e->Col+20;
        }

    }

    else if(IfNextNode(Head,Col,Lin)==1)
    {
        New->Prev = NULL;
        New->Next = *Head;
        (*Head)->Prev = New;
        *Head = New;
    }

    else if(LastNodeVerify(Head,Last,Col,Lin)!=1) ///Daca nu este ultimul nod
    {
        struct Node *e;

        for(e=*Head; e!=NULL; e=e->Next)
        {
            if(e->Lin == Lin && e->Col == Col-20)
            {
                if(e == *Last)
                {
                    New->Next = NULL;
                    New->Prev = *Last;
                    (*Last)->Next = New;
                    *Last = New;
                }
                else
                {
                    struct Node *g;

                    for(g=*Head; g!=NULL; g=g->Next)
                    {
                        if(g->Lin == Lin && g->Col >= Col && g != *Head)
                        {
                            g->Col = g->Col+20;
                        }
                    }

                    New->Next = e->Next;
                    e->Next = New;
                    New->Prev = e;
                    e->Next->Prev = New;

                }
            }
            else if(e->Col == Col && LinVerify(Head,Lin)==0 && IfNextNode(Head,Col,Lin)!=1)
            {
                New->Next = NULL;
                New->Prev = *Last;
                (*Last)->Next = New;
                *Last = New;
            }
            else if(IfNextNode(Head,Col,Lin)==1 && LinVerify(Head,Lin)==0)
            {
                for(f=*Head; f!=NULL; f=f->Next)
                {
                    if(f->Lin < Lin && f->Next->Lin >Lin)
                        break;
                }

                New->Next = f->Next;
                f->Next = New;
                f->Next->Prev = New;
                New->Prev = f;

                break;
            }
        }
    }
    else
    {
        for(e=*Head; e!=NULL; e=e->Next)
        {
            if(e->Lin == Lin && e->Col == Col)
            {
                if(e->Prev == NULL)
                {
                    e->Prev = New;
                    New->Next = e;
                    *Head = New;
                    e->Col = e->Col+20;
                }
                else
                {
                    e->Prev->Next = New;
                    New->Prev = e->Prev;
                    e->Prev = New;
                    New->Next = e;
                    e->Col = e->Col+20;
                }
            }
            else if(e->Lin == Lin && e->Col >= Col)
                e->Col= e->Col+20;
            else {}
        }
    }
}



///CTRL+X
void Delete(struct Node **Head,struct Node **Last,int Lin,int Col)
{
    struct Node *Target;
    int Contor = 0;

    for(Target = *Head ; Target!=NULL ; Target=Target->Next)
        Contor++;

    for(Target = *Head ; Target != NULL ; Target=Target->Next)
    {
        if(Target->Lin == Lin && Target->Col == Col)
        {
            if(Target == *Last)
            {
                if(Contor == 1)
                    *Head = *Last = NULL;

                else
                {
                    Target->Prev->Next = NULL;
                    *Last = (*Last)->Prev;
                    Contor--;
                }
            }
            else if(Target == *Head)
            {
                Target->Next->Prev = NULL;
                *Head = (*Head) -> Next;
                Contor--;
            }
            else
            {
                struct Node *f;
                struct Node *BackUpNode;

                if(NullVerify(Head,Col+20,Lin)==0)
                {
                    for(f=*Head; f!=NULL; f=f->Next)
                    {
                        if(f->Lin == Lin && f->Col == Col-20 && LinVerify(Head,Lin)!=70)
                        {
                            BackUpNode = f->Next->Next;
                            f->Next->Next->Prev = f;
                            f->Next = BackUpNode;
                        }
                        else if(f->Lin == Lin && LinVerify(Head,Lin)==70)
                        {
                            if(f->Lin == Lin && f->Col == 70)
                            {
                                f->Prev->Next = f->Next;
                                f->Next->Prev = f->Prev;
                            }
                        }
                    }
                }
                else
                {
                    Target->Prev->Next = Target->Next;
                    Target->Next->Prev = Target->Prev;
                }
                Contor--;
                break;
            }
        }
    }

    free(Target);
}


void Edit(struct Node **Head,int Col,int Lin)
{
    struct Node *Rest;

    for(Rest = *Head; Rest!=NULL; Rest=Rest->Next)
    {
        if(Rest->Lin == Lin && Rest->Col > Col)
            Rest->Col = Rest->Col-20;
    }
}


void Edit2(struct Node **Head,int Col,int Lin)
{
    struct Node *e;
    int Seq=50;

    for(e=*Head; e!=NULL; e=e->Next)
    {
        if(e->Lin == Lin && e->Col > Col)
            e->Col = e->Col+20;

        if(e->Col >= 1800)
        {
            e->Lin = e->Lin+20;
            e->Col = Seq;
            Seq=Seq+20;
        }
    }
}


void Solve(struct Node **Head,int x,int y)
{
    setfillstyle(1,15);
    setcolor(15);
    bar(x,y,1810,y+20);
    rectangle(x,y,1810,y+20);
}


void Solve2(struct Node **Head,int x,int y)
{
    setfillstyle(1,15);
    setcolor(15);
    bar(x,y,x+20,y+20);
    rectangle(x,y,x+20,y+20);
}


void Print(struct Node **Head,int x,int y)
{
    struct Node *e;

    for(e=*Head; e!=NULL; e=e->Next)
    {
        if(e->Lin == y && e->Col > x)
        {
            char Char[2] = {e->Char,'\0'};
            setcolor(Colour);

            if(y < 980)
                outtextxy(e->Col-20,e->Lin,Char);
            else
                outtextxy(e->Col-20,980,Char);
        }
    }
}
///Verificare pt. cursorul liniutza
///Verifica daca suntem la prima linie, daca nu suntem ne putem deplasa in sus
int LinVerify(struct Node **Head,int y)
{
    struct Node *e;
    int Val = 0;

    for (e=(*Head); e!=NULL; e=e->Next)
    {
        if(e->Lin == y)
            Val=e->Col;
    }

    return Val;
}


int CharControl(struct Node **Head,int x,int y)
{
    struct Node *e;
    int Val = 0;

    for(e=*Head; e!=NULL; e=e->Next)
    {
        if(e->Col == x && e->Lin == y)
        {
            Val = e->Lin;
            break;
        }
    }

    return Val;
}


int NullVerify(struct Node **Head,int x,int y)
{
    struct Node *e;
    int Val = 0;

    for (e=(*Head); e!=NULL; e=e->Next)
    {
        if(e->Col == x && e->Lin == y)
            Val=e->Lin;
    }

    return Val;
}


int NextLin(struct Node **Head,int x,int y)
{
    struct Node *e;
    int Val = 0;

    for (e=(*Head); e!=NULL; e=e->Next)
    {
        if(e->Col == x && e->Lin == y)
            Val=e->Next->Lin;
    }

    return Val;
}


int NextCol(struct Node **Head,int x,int y)
{
    struct Node *e;
    int Val = 0;

    for (e=(*Head); e!=NULL; e=e->Next)
    {
        if(e->Col == x && e->Lin == y)
            Val=e->Next->Col;
    }

    return Val;
}


int FirstNodeLine(struct Node **Head,int x,int y)
{
    struct Node *e;
    int Val = 0;

    for (e=(*Head); e!=NULL; e=e->Next)
    {
        if(e->Col == x && e->Lin == y)
        {
            Val=e->Col;
            break;
        }
    }

    return Val;
}


int LastNodeLine(struct Node **Head,int x,int y)
{
    struct Node *e;
    int Val = 0;

    for (e=(*Head); e!=NULL; e=e->Next)
    {
        if(e->Col == x && e->Lin == y)
            Val=e->Col;
    }

    if(Val == 0)
        return 50;
    else
        return Val;
}


void AddTopLine(struct Node **Head,int Col,int Lin)
{
    struct Node *e;
    int Seq=20;
    int Seq2=20;

    for(e=*Head; e!=NULL; e=e->Next)
    {
        if(e->Lin == Lin+20)
        {
            e->Lin = e->Lin-20;
            e->Col = LastNodeLine(Head,Col,Lin)+Seq;
            Seq = Seq+20;

            if(e->Col >= 1810)
            {
                e->Lin = e->Lin+20;
                e->Col = 50+Seq2;
                Seq2=Seq2+20;
            }
        }
    }
}


void LastLine(struct Node **Head,int y,int Go)
{
    struct Node *e;

    for(e=*Head; e!=NULL; e=e->Next)
    {
        if(e->Lin > y && e->Lin <= Go)
            e->Lin = e->Lin-20;
    }
}


void AddLastLine(struct Node **Head,int Col,int Lin)
{
    struct Node *e;
    int Seq = 20;

    for(e=*Head; e!=NULL; e=e->Next)
    {
        if(e->Lin > Lin)
            e->Lin = e->Lin+20;
    }

    for(e=*Head; e!=NULL; e=e->Next)
    {
        if(e->Col > Col && e->Lin == Lin)
        {
            e->Lin = e->Lin+20;
            e->Col = 50+Seq;
            Seq=Seq+20;
        }
    }
}


void MakePage(int x,int y)
{
    setfillstyle(1,15);
    setcolor(15);
    bar(50,100,1810,1000);
    rectangle(50,100,1810,1000);
}


void PrintPage(struct Node **Head,int Diff)
{
    struct Node *e;

    for(e=*Head; e!=NULL; e=e->Next)
    {
        char Char[2] = {e->Char,'\0'};
        setcolor(Colour);

        if(Diff <= 0 && e->Lin <=980)
            outtextxy(e->Col-20,e->Lin,Char);
        else
        {
            if(e->Lin-Diff >= 100 && e->Lin-Diff <= 980)
                outtextxy(e->Col-20,e->Lin-Diff,Char);
            else {}
        }
    }
}


void PrintPage2(struct Node **Head,int Lin,int Diff)
{
    struct Node *e;

    for(e=*Head; e!=NULL; e=e->Next)
    {
        char Char[2] = {e->Char,'\0'};
        setcolor(Colour);

        if(e->Lin > Lin)
        {
            if(Diff <= 0)
                outtextxy(e->Col-20,e->Lin,Char);
            else
            {
                if(e->Lin-Diff >= 100 && e->Lin-Diff <= 980)
                    outtextxy(e->Col-20,e->Lin-Diff,Char);
                else {}
            }

        }
    }
}


void PageEdit(struct Node **Head,int Col,int Lin)
{
    struct Node *Rest;
    int Seq2=0;

    for(Rest = *Head; Rest!=NULL; Rest=Rest->Next)
    {
        if( Rest->Lin == Lin+20)
            Rest->Lin = Rest->Lin-20;

        else if(Rest->Lin == Lin+40)
        {
            Rest->Col = 70+Seq2;
            Seq2 = Seq2 +20;
        }
    }

    for(Rest = *Head; Rest!=NULL; Rest=Rest->Next)
    {
        if( Rest->Col >= 1800)
        {
            Rest->Lin = Rest->Lin+20;
            Rest->Col = Rest->Col-1750;
        }
    }
}


void LastColEdit(struct Node **Head)
{
    struct Node *e;
    struct Node *f;

    for(e=*Head; e!=NULL; e=e->Next)
    {
        if(e->Col > 1810)
        {
            for(f=*Head; f!=NULL; f=f->Next)
            {
                if(f->Lin == e->Lin+20)
                    f->Col = f->Col+20;
            }

            e->Lin = e->Lin+20;
            e->Col = 70;
        }
    }

    MakePage(0,0);
    PrintPage(Head,0);
}


void LastLinePrint(struct Node **Head,int Col,int Lin,int Diff)
{
    struct Node *e;

    for(e=*Head; e!=NULL; e=e->Next)
    {
        char Char[2] = {e->Char,'\0'};
        setcolor(Colour);

        if(e->Lin-Diff>=100)
            outtextxy(e->Col-20,e->Lin-Diff,Char);
    }
}


void DeleteField(struct Node **Head,int x,int y,int Lastx,int Lasty,int Colour,int Diff) ///CTRL+X
{
    setfillstyle(1,Colour);
    setcolor(15);

    if(Diff<=0)
        Diff=0;

    bar(x,y-Diff,Lastx,Lasty-Diff);
    rectangle(x,y-Diff,Lastx,Lasty-Diff);
}


void MakeSelection(struct Node **Head,int x,int y,int Lastx,int Lasty,int Diff)
{
    struct Node *e;

    if(Diff<=0)
        Diff=0;

    for(e=*Head; e!=NULL; e=e->Next)
    {
        if(e->Lin >= y && e->Lin < Lasty && e->Col > x && e->Col <= Lastx)
        {
            char Char[2] = {e->Char,'\0'};

            if(e->Semn == 0)
            {
                DeleteField(Head,x,y,Lastx,Lasty,9,Diff);
                setcolor(Colour);
                setbkcolor(9);
                e->Semn = 1;

                if(y-Diff >=100 && y-Diff <= 980)
                    outtextxy(x,y-Diff,Char);
            }
            else
            {
                DeleteField(Head,x,y,Lastx,Lasty,15,Diff);
                setcolor(Colour);
                setbkcolor(15);
                e->Semn = 0;

                if(y-Diff >=100 && y-Diff <= 980)
                    outtextxy(x,y-Diff,Char);
            }
        }
    }
}


void VerifySelection2(struct Node **Head,int x,int y,int Lastx,int Lasty,int Diff)
{
    struct Node *e;

    for(e=*Head; e!=NULL; e=e->Next)
    {
        if(e->Lin == y && e->Col >= x)
            MakeSelection(Head,e->Col,e->Lin,e->Col+20,e->Lin+20,Diff);

        if(e->Lin == Lasty && e->Col <= Lastx)
            MakeSelection(Head,e->Col-20,e->Lin,e->Col,e->Lin+20,Diff);

        if(e->Lin == y && x == 50)
            MakeSelection(Head,50,e->Lin,70,e->Lin+20,Diff);
    }
}


void VerifySelection3(struct Node **Head,int x,int y,int Lastx,int Lasty,int Tx,int Diff)
{
    struct Node *e;

    for(e=*Head; e!=NULL; e=e->Next)
    {
        if(e->Lin == y && e->Col >= x)
            MakeSelection(Head,e->Col,e->Lin,e->Col+20,e->Lin+20,Diff);

        if(e->Lin == Lasty && e->Col <= x)
            MakeSelection(Head,e->Col-20,e->Lin,e->Col,e->Lin+20,Diff);

        if(e->Lin == y && x == 50)
            MakeSelection(Head,50,e->Lin,70,e->Lin+20,Diff);
    }
}


void VerifySelection(struct Node **Head,int x,int y,int Lastx,int Lasty,int Diff)//colorare
{
    struct Node *e;

    if(Diff<=0)
        Diff=0;

    for(e=*Head; e!=NULL; e=e->Next)
    {
        if(e->Lin >= y && e->Lin < e->Lin+20 && e->Col > x )
        {
            char Char[2] = {e->Char,'\0'};

            if(e->Semn == 0)
            {
                setcolor(Colour);
                setbkcolor(9);

                if(y-Diff >=100 && y-Diff <= 980)
                    outtextxy(e->Col-20,y-Diff,Char);

                e->Semn = 1;
            }
            else
            {
                setcolor(Colour);
                setbkcolor(15);

                if(y-Diff >=100 && y-Diff <= 980)
                    outtextxy(e->Col-20,y-Diff,Char);

                e->Semn = 0;
            }
        }
        if(e->Lin >= Lasty && e->Lin < Lasty+20 && e->Col <=Lastx)
        {
            char Char[2] = {e->Char,'\0'};

            if(e->Semn == 0)
            {
                setcolor(Colour);
                setbkcolor(9);
                if(y-Diff >=100 && y-Diff <= 980)
                    outtextxy(e->Col-20,Lasty-Diff,Char);

                e->Semn = 1;
            }
            else
            {
                setcolor(Colour);
                setbkcolor(15);

                if(y-Diff >=100 && y-Diff <= 980)
                    outtextxy(e->Col-20,Lasty-Diff,Char);

                e->Semn = 0;
            }
        }


    }
}


void MakePage2()//new year new me
{
    setfillstyle(1,15);
    setcolor(15);
    bar(50,100,1810,120);
    rectangle(50,100,1810,120);
}


void PrintArr(char Storage[],int x,int TLast)
{
    struct Node *Head3=NULL;
    struct Node *Last3=NULL;
    int Seq=50;
    int i;

    for(i=0; i<TLast; i++)
    {
        struct Node *New =(struct Node*) malloc(sizeof(struct Node));
        New->Char = Storage[i];

        if(Head3 == NULL)
        {
            New->Next = NULL;
            New->Prev = NULL;
            Head3 = Last3 = New;
        }
        else
        {
            New->Next = NULL;
            New->Prev = Last3;
            (Last3)->Next = New;
            Last3 = New;
        }
    }

    struct Node *e;

    for(e=Head3; e!=NULL; e=e->Next)
    {
        char OneChar[2] = {e->Char,'\0'};
        setcolor(Colour);
        outtextxy(Seq,100,OneChar);
        Seq=Seq+20;
    }

}


void DeleteSolve(int left,int top,int right,int bottom)
{
    setfillstyle(1,15);
    setcolor(15);
    bar(left,top,right,bottom);
    rectangle(left,top,right,bottom);
}


void SolveNr(int Go,int Diff)
{
    int i;
    char a;
    char as[4];
    setfillstyle(1,15);
    setcolor(15);
    bar(0,100,45,1000);
    rectangle(0,100,45,1000);

    for(i=0; i <= (Go-100)/20 ; i++)
    {
        setcolor(Colour);
        setbkcolor(15);
        itoa(i+1,as,10);

        if(Diff <0 && i <= 45)
            outtextxy(15,100+(20*i),as);
        else
        {
            if(100+(20*i)-Diff>=100 && 100+(20*i)-Diff <=980)
                outtextxy(15,100+(20*i)-Diff,as);
            else {}
        }
    }
}


int main()
{ //1500,900
    //cout<<getmaxwidth()<<" "<<getmaxheight()<<'\n';
    int MainScreen = initwindow(getmaxwidth(),getmaxheight(),"Notepad");
    struct Node *Head = NULL;
    struct Node *Last = NULL;
    struct Node *Head2 = NULL;
    struct Node *Last2 = NULL;

    char c;
    char h;
    char ReadArr[10005];
    char ReadArr2[10005];

    int x = 50;
    int y = 100;
    int indexy = 100;
    int KeyVal = 0;
    int Tx;
    int Ty;
    int Go = 0;
    int Diff = 100+Go-980;
    int Diff2;
    int Td=0;
    int Lin2;
    int Col2;
    int Read;
    int Wx=50;
    int Wy=100;
    int Exit=0;
    int Buffer[10005];
    int i=0;
    int j=0;
    int ReadGo;
    int k;
    int Readx=70;
    int Ready=100;
    int EditTx;
    int SaveNewFile;
    int y2;

    FILE *CrtFile;


    floodfill(0,0,WHITE);

    Colour = 0;

    setcolor(Colour);
    setbkcolor(15);

    line(0,99,getmaxx(),99);
    line(48,99,48,getmaxy());
    line(0,1001,getmaxx(),1001);
    line(1811,99,1811,getmaxy());


    setcolor(4);
    outtextxy(0,0,"");
    settextstyle(10,12,0);
    outtextxy(20,3 ,"Deschide fisier => F2");
    outtextxy(20,30,"Salveaza fisier => F3");
    outtextxy(20,57,"Selectie => F1");
    outtextxy(480,3 ,"Copiere selectie => CTRL+C");
    outtextxy(480,30,"Lipire selectie  => CTRL+V");
    outtextxy(480,57,"Sterge selectie  => CTRL+X");
    outtextxy(1035,3,"Culoare - => F4");
    outtextxy(1035,30,"Culoare + => F5");
    outtextxy(1035,57,"CULOARE:");
    setcolor(Colour);
    outtextxy(1191,57,"NEGRU");

    settextstyle(8,12,2);
    outtextxy(15,100,"1");

 while(1)
{
    if(y<=980)
        y2=y;
    else
        y2=980;
    while(!kbhit())  ///Functie pt. cursor
    {
        setcolor(Colour);
        line(x,indexy,x,indexy+20);
        delay(100);
        setcolor(15);
        line(x,indexy,x,indexy+20);
        setcolor(Colour);
        delay(100);
    }

    if(Diff <= 0)
        Diff=0;

    setbkcolor(15);

    c = (char) getch();
    char cs[2] = {c,'\0'};

    if (c != 0)
    {
        if (c=='z')
        {
            c=' ';
             if(KeyVal%2 != 1) ///verificam sa nu fie selectie
            {
                struct Node *e;

                if(x>=1800)
                {
                    x=50;
                    y=y+20;
                    indexy=indexy+20;
                    Go=Go+20;
                }

                Solve2(&Head,x,indexy);
                setcolor(Colour);
                setbkcolor(15);
                outtextxy(x,indexy,cs);
                x=x+20;
                Add(&Head,&Last,c,y,x);

                for(e=Head; e!=NULL; e=e->Next)
                {
                    if(e->Col > 1810)
                        LastColEdit(&Head);
                }

                Solve2(&Head,x,indexy);
                Solve(&Head,x,indexy);
                Print(&Head,x,y);
            }
                if(Diff<=0)
                    Diff=0;

                if(KeyVal%2 == 1)
                {
                    if(NullVerify(&Head,x+20,y)!=0)
                    {
                        if(Tx > x)
                        {
                            DeleteField(&Head,x,y,x+20,y+20,15,Diff+Td);
                            MakeSelection(&Head,x,y,x+20,y+20,Diff+Td);
                        }
                        else
                        {
                            DeleteField(&Head,x,y,x+20,y+20,9,Diff+Td);
                            MakeSelection(&Head,x,y,x+20,y+20,Diff+Td);
                        }
                    }
                }
                if(Head == NULL) {}
                else if(x>=1800 && NullVerify(&Head,50,y+20)==0) {}
                else if(x>=1800 && NullVerify(&Head,50,y+20)!=0)
                {
                    x=50;
                    y=y+20;

                    if(indexy < 980)
                        indexy=indexy+20;
                }
                else if(x<=1800)
                {
                    if(NullVerify(&Head,x+20,y)==0 && Last->Lin == y && Last->Col == x) {}
                    else if(NullVerify(&Head,x+20,y)==0 && (Last->Lin != y || Last->Col != x))
                    {
                        if(LinVerify(&Head,y+20)==0)
                        {
                            y=y+20;

                            if(indexy < 980)
                                indexy=indexy+20;

                            x=50;
                        }
                        else
                        {
                            y=y+20;

                            if(indexy < 980)
                                indexy=indexy+20;

                            x=50;
                        }
                    }
                    else
                        x=x+20;
                }
            if(x<=50 && y<=100)
            {
                x=50;
                y=100;
                indexy=100;
            }
            else if(x<=50)
            {
                y=y-20;
                indexy=indexy-20;
                Go=Go-20;

                if(Last != NULL && Last->Lin==y)
                    x=Last->Col;

                else if (y>=100 && LinVerify(&Head,y)==0)
                {
                    if(LinVerify(&Head,y+20)!=0)
                    {
                        LastLine(&Head,y,140+Go);
                        MakePage(x,y);
                        Diff = 100+Go-980;
                        PrintPage(&Head,Diff+Td);
                    }
                    else if(LinVerify(&Head,y+20)==0)
                    {
                        LastLine(&Head,y,140+Go);
                        MakePage(x,y);
                        Diff = 100+Go-980;
                        PrintPage(&Head,Diff+Td);
                    }

                    x=50;
                }
                else if (y>=100 && LinVerify(&Head,y)!=0)
                {
                    x=LinVerify(&Head,y);

                    if(LinVerify(&Head,y+20)!=0)
                    {
                        Diff = 100+Go-980;
                        AddTopLine(&Head,x,y);
                        MakePage(x,y);
                        PrintPage(&Head,Diff+Td);

                        if(LinVerify(&Head,y+20)==0)
                        {
                            LastLine(&Head,y,140+Go);
                            MakePage(x,y);
                            PrintPage(&Head,Diff+Td);
                        }

                    }
                    else
                    {
                        LastLine(&Head,y,140+Go);
                        MakePage(x,y);
                        PrintPage(&Head,Diff+Td);
                    }

                    MakePage(x,y);
                    PrintPage(&Head,Diff+Td);
                }
                else
                    x=50;
                PageEdit(&Head,x,y);
            }
            else
            {
                setfillstyle(1,15);
                setcolor(15);
                bar(x-20,y,x,y+20);
                rectangle(x-20,y,x,y+20);
                x=x-20;
                setcolor(Colour);
                Delete(&Head,&Last,y,x+20);
                Edit(&Head,x,y);
                Solve(&Head,x,indexy);
                Print(&Head,x,y);
            }
        } else
        if(c == 8 && KeyVal%2 != 1)///daca e backspace, stergem caracter daca nu suntem in selectie (F1 mode)
        {
            if(x<=50 && y<=100)
            {
                x=50;
                y=100;
                indexy=100;
            }
            else if(x<=50)
            {
                y=y-20;
                indexy=indexy-20;
                Go=Go-20;

                if(Last != NULL && Last->Lin==y)
                    x=Last->Col;

                else if (y>=100 && LinVerify(&Head,y)==0)
                {
                    if(LinVerify(&Head,y+20)!=0)
                    {
                        LastLine(&Head,y,140+Go);
                        MakePage(x,y);
                        Diff = 100+Go-980;
                        PrintPage(&Head,Diff+Td);
                    }
                    else if(LinVerify(&Head,y+20)==0)
                    {
                        LastLine(&Head,y,140+Go);
                        MakePage(x,y);
                        Diff = 100+Go-980;
                        PrintPage(&Head,Diff+Td);
                    }

                    x=50;
                }
                else if (y>=100 && LinVerify(&Head,y)!=0)
                {
                    x=LinVerify(&Head,y);

                    if(LinVerify(&Head,y+20)!=0)
                    {
                        Diff = 100+Go-980;
                        AddTopLine(&Head,x,y);
                        MakePage(x,y);
                        PrintPage(&Head,Diff+Td);

                        if(LinVerify(&Head,y+20)==0)
                        {
                            LastLine(&Head,y,140+Go);
                            MakePage(x,y);
                            PrintPage(&Head,Diff+Td);
                        }

                    }
                    else
                    {
                        LastLine(&Head,y,140+Go);
                        MakePage(x,y);
                        PrintPage(&Head,Diff+Td);
                    }

                    MakePage(x,y);
                    PrintPage(&Head,Diff+Td);
                }
                else
                    x=50;
                PageEdit(&Head,x,y);
            }
            else
            {
                setfillstyle(1,15);
                setcolor(15);
                bar(x-20,y,x,y+20);
                rectangle(x-20,y,x,y+20);
                x=x-20;
                setcolor(Colour);
                Delete(&Head,&Last,y,x+20);
                Edit(&Head,x,y);
                Solve(&Head,x,indexy);
                Print(&Head,x,y);
            }
        }
        else if(c == 3)///!!EOF
        {
            struct Node *c;
            Head2 = NULL;
            Last2 = NULL;

            for(c=Head; c!=NULL; c=c->Next)
            {
                if(c->Semn == 1)
                {
                    Add2(&Head2,&Last2,c->Char);
                    c->Semn = 0;
                }
            }

            Diff2=Diff;

            if(Diff2<=0)
                Diff2=0;

            MakePage(x,y);
            setbkcolor(15);
            PrintPage(&Head,Diff2+Td);
            DeleteSolve(1825,180,1920,260);
            setcolor(Colour);
            KeyVal++;
        }
        else if(c == 22)  ///asigurare ca nu face poc programul daca este in idle/sync
        {
            struct Node *v;
            Lin2=y;
            Col2=x;

            for(v=Head2; v!=NULL; v=v->Next)
            {
                Col2=Col2+20;

                if(Col2 >= 1800)
                {
                    Col2=50;
                    Lin2=Lin2+20;
                }

                Add(&Head,&Last,v->Char,Lin2,Col2);
            }

            Diff2=Diff;

            if(Diff2<=0)
                Diff2=0;

            MakePage(x,y);
            setbkcolor(15);
            PrintPage(&Head,Diff2+Td);
        }
        else if(c == 24)
        {
            struct Node *c;
            Head2 = NULL;
            Last2 = NULL;
            EditTx = Tx;

            for(c=Head; c!=NULL; c=c->Next)
            {
                if(c->Semn == 1)
                    Add2(&Head2,&Last2,c->Char);
            }

            for(c=Head; c!=NULL; c=c->Next)
            {
                if(c->Semn == 1)
                {
                    Delete(&Head,&Last,c->Lin,c->Col);

                    if(x<EditTx)
                        Edit(&Head,x,y);
                    else
                    {
                        Edit(&Head,EditTx,y);
                        x=EditTx;
                    }
                }
            }

            Diff2=Diff;

            if(Diff2<=0)
                Diff2=0;

            MakePage(x,y);
            setbkcolor(15);
            PrintPage(&Head,Diff2+Td);
            KeyVal++;
        }
        else if(c == 13 && KeyVal%2 != 1)  ///facem ENTER pt. o noua linie daca nu suntem in selectie
        {
            Go=Go+20;

            if(indexy >= 980)
            {
                Diff = 100+Go-980;  ///nevoie de modificare diferenta

                AddLastLine(&Head,x,y);
                MakePage(x,y);
                LastLinePrint(&Head,x,y,Diff);
            }
            else
            {
                AddLastLine(&Head,x,y);
                MakePage(x,y);
                Diff2=Diff;

                if(Diff2<=0)
                    Diff2=0;

                PrintPage(&Head,Diff2+Td);
                Diff = 100+Go-980;

                if(Diff==0)
                    Td=0;

            }

            y=y+20;

            if(indexy < 980)
                indexy=indexy+20;

            x=50;
        }
        else if(c == 27) {} ///ESC nu face nmk in fereastra principala
        else
        { ///daca e orice alta tasta >:3
            if(KeyVal%2 != 1) ///verificam sa nu fie selectie
            {
                struct Node *e;

                if(x>=1800)
                {
                    x=50;
                    y=y+20;
                    indexy=indexy+20;
                    Go=Go+20;
                }

                Solve2(&Head,x,indexy);
                setcolor(Colour);
                setbkcolor(15);
                outtextxy(x,indexy,cs);
                x=x+20;
                Add(&Head,&Last,c,y,x);

                for(e=Head; e!=NULL; e=e->Next)
                {
                    if(e->Col > 1810)
                        LastColEdit(&Head);
                }

                Solve2(&Head,x,indexy);
                Solve(&Head,x,indexy);
                Print(&Head,x,y);
            }
        }
    }
    else
    {
        c = (char) getch();
///SWITCH PT CAZURILE F1/F2/F3/F4/F5
    switch (c)
    {
            case KEY_F5: ///CULOARE IN SUS

                Colour++;

                if(Colour < 0)
                    Colour = 14-Colour;

                if(Colour == 15)
                    Colour = 0;

                if(Colour == 9)
                    Colour=10;

                Diff2=Diff;

                if(Diff2<=0)
                    Diff2=0;

                MakePage(x,y);
                setbkcolor(15);
                PrintPage(&Head,Diff2+Td);
                DeleteSolve(1820,310,1920,360);
                setcolor(Colour);
                ///CULORI!!! :)
                WhichColour();
                break;

            case KEY_F4: ///CULOARE IN JOS

                Colour--;

                if(Colour < 0)
                    Colour = 14-Colour;

                if(Colour == 15)
                    Colour = 14;

                if(Colour == 9)
                    Colour=8;

                Diff2=Diff;

                if(Diff2<=0)
                    Diff2=0;

                MakePage(x,y);
                setbkcolor(15);
                PrintPage(&Head,Diff2+Td);
                DeleteSolve(1820,310,1920,360);
                setcolor(Colour);
                ///CULORI!!! :)
                WhichColour();
                break;

            case KEY_F3:   ///SALVEAZA FISIER

                if(getcurrentwindow()!=1)
                    Read = initwindow(1030,200,"Salvare",250,400,false,false);

                floodfill(0,0,WHITE);
                setcolor(4);
                rectangle(45,99,985,121);
                setbkcolor(15);
                outtextxy(50,130,"Salvare fisier = ENTER");
                outtextxy(50,150,"Inchide fereastra = ESC");
                Exit = 0;
                ReadGo = 50;
                Wx=50;

                for(j=0; j<100; j++) ///Sters selectie precedenta
                    ReadArr[j]=NULL;

                setbkcolor(15);
                outtextxy(50,50,"Salveaza fisierul indicand locatia din calculator: C:\\...\\test.txt");
                setcolor(Colour);

                while(1)
                {
                    while(!kbhit())  ///Cursorul liniutza care palpaie
                    {
                        setcolor(Colour);
                        line(Wx,Wy,Wx,Wy+20);
                        delay(100);
                        setcolor(15);
                        line(Wx,Wy,Wx,Wy+20);
                        setcolor(Colour);
                        delay(100);
                    }

                    if(Exit != 1)
                        h = (char) getch();

                    char hs[2] = {h,'\0'};

                    if(Exit!=1 && h != 0 )
                    {
                        if(h == 8)
                        {
                            if(Wx>50)
                            {
                                Wx=Wx-20;
                                ReadGo=ReadGo-20;
                            }

                            if(ReadArr[((Wx-50)/20)+1] == NULL)
                            {
                                i--;
                                Solve2(&Head,Wx,Wy);
                                ReadArr[((Wx-50)/20)]=NULL;
                            }
                            else if(ReadArr[((Wx-50)/20)-1] == NULL)
                            {
                                for(j=0; j<=i; j++)
                                {
                                    if(j > (Wx-50)/20 )
                                    {
                                        ReadArr[j-1]=ReadArr[j];

                                        if(j == i)
                                            ReadArr[i]=NULL;
                                    }
                                }

                                MakePage2();
                                PrintArr(ReadArr,100,i);
                            }
                            else
                            {
                                if(ReadArr[((Wx-50)/20)-1] != NULL)
                                {
                                    i--;

                                    for(j=0; j<=i; j++)
                                    {
                                        if(j > (Wx-50)/20 )
                                        {
                                            ReadArr[j-1]=ReadArr[j];

                                            if(j == i)
                                                ReadArr[i]=NULL;
                                        }
                                    }

                                    MakePage2();
                                    PrintArr(ReadArr,100,i);
                                }
                            }
                        }
                        else if(h == 13)
                            Exit = 1;

                        else if(h == 27)
                        {
                            for(j=0; j<100; j++) ///E bun de editat
                                ReadArr[j]=NULL;
                            Exit = 1;
                        }
                        else
                        {
                            if(ReadArr[((Wx-50)/20)+1] != NULL)
                            {
                                k=0;

                                for(j=0; j<=i; j++)
                                {
                                    if(j >= (Wx-50)/20)
                                    {
                                        ReadArr2[k]=ReadArr[j];
                                        k++;
                                    }
                                }

                                ReadArr[((Wx-50)/20)]= h;

                                for(j=1; j<k; j++)
                                    ReadArr[((Wx-50)/20)+j] = ReadArr2[j-1];

                                MakePage2();
                                PrintArr(ReadArr,100,i+1);
                                i++;
                                Wx=Wx+20;
                                ReadGo=ReadGo+20;
                            }
                            else
                            {
                                setcolor(Colour);
                                setbkcolor(15);
                                outtextxy(Wx,Wy,hs);
                                ReadArr[(Wx-50)/20]=h;
                                Buffer[i]=h;
                                i++;
                                Wx=Wx+20;
                                ReadGo=ReadGo+20;
                            }
                        }
                    }
                    else
                    {
                        if(Exit != 1)
                            h = (char) getch();

                        switch(h)
                        {
                        case KEY_RIGHT:

                            if(ReadArr[((Wx-50)/20)] != NULL || ReadArr[((Wx-50)/20)+1] != NULL )
                                Wx=Wx+20;

                            break;

                        case KEY_LEFT:

                            if(Wx>50)
                                Wx=Wx-20;

                            break;
                        }
                    }

                    if(Exit == 1)
                        break;
                }

                struct Node *e;
                closegraph(Read);
                setcurrentwindow(MainScreen);

                CrtFile = fopen(ReadArr,"w");

                if(CrtFile != NULL)
                {
                    for(e=Head; e!=NULL; e=e->Next)
                    {
                        fprintf(CrtFile,"%c",e->Char);

                        if(e->Next != NULL && e->Lin < e->Next->Lin)
                            fputs("\n",CrtFile);
                    }

                    setcolor(Colour);
                    PrintPage(&Head,0);
                    x=Readx-20;
                    y=Ready;

                    SaveNewFile = initwindow(420,100,"Salvare",600,450,false,false);
                    floodfill(0,0,WHITE);
                    setcolor(4);
                    setbkcolor(15);
                    settextstyle(10,12,0);
                    outtextxy(410,65,"Fisier salvat cu succes!");
                    delay(1000);
                    settextstyle(8,12,2);
                    closegraph(SaveNewFile);
                    setcurrentwindow(MainScreen);
                    setcolor(Colour);
                }
                else
                    printf("Eroare! Nu s-a salvat fisierul!\n");

                fclose(CrtFile);

                break;
///Deschide fisier
            case KEY_F2 :

                if(getcurrentwindow()!=1)
                    Read = initwindow(1030,200,"Deschide",250,400,false,false);

                floodfill(0,0,WHITE);
                setcolor(4);
                rectangle(45,99,985,121);
                Exit = 0;
                ReadGo = 50;
                Wx=50;

                for(j=0; j<100; j++) ///Sters selectie precedenta
                    ReadArr[j]=NULL;

                setbkcolor(15);
                outtextxy(50,50,"Deschide fisierul indicand locatia din calculator: C:\\...\\test.txt");
                outtextxy(50,130,"Deschide fisier = ENTER");
                outtextxy(50,150,"Inchide fereastra = ESC");
                setcolor(Colour);

                while(1)
                {
                    while(!kbhit())  ///Cursorul liniutza
                    {
                        setcolor(Colour);
                        line(Wx,Wy,Wx,Wy+20);
                        delay(100);
                        setcolor(15);
                        line(Wx,Wy,Wx,Wy+20);
                        setcolor(Colour);
                        delay(100);
                    }

                    if(Exit != 1)
                        h = (char) getch();

                    char hs[2] = {h,'\0'};

                    if(Exit!=1 && h != 0 )
                    {
                        if(h == 8)
                        {
                            if(Wx>50)
                            {
                                Wx=Wx-20;
                                ReadGo=ReadGo-20;
                            }

                            if(ReadArr[((Wx-50)/20)+1] == NULL)
                            {
                                i--;
                                Solve2(&Head,Wx,Wy);
                                ReadArr[((Wx-50)/20)]=NULL;
                            }
                            else if(ReadArr[((Wx-50)/20)-1] == NULL)
                            {
                                for(j=0; j<=i; j++)
                                {
                                    if(j > (Wx-50)/20 )
                                    {
                                        ReadArr[j-1]=ReadArr[j];

                                        if(j == i)
                                            ReadArr[i]=NULL;
                                    }
                                }

                                MakePage2();
                                PrintArr(ReadArr,100,i);
                            }
                            else
                            {
                                if(ReadArr[((Wx-50)/20)-1] != NULL)
                                {
                                    i--;

                                    for(j=0; j<=i; j++)
                                    {
                                        if(j > (Wx-50)/20 )
                                        {
                                            ReadArr[j-1]=ReadArr[j];

                                            if(j == i)
                                                ReadArr[i]=NULL;
                                        }

                                    }

                                    MakePage2();
                                    PrintArr(ReadArr,100,i);
                                }
                            }
                        }
                        else if(h == 13)
                            Exit = 1;

                        else if(h == 27)
                        {
                            for(j=0; j<100; j++) ///Se produce o schimbare
                                ReadArr[j]=NULL;

                            Exit = 1;
                        }
                        else
                        {
                            if(ReadArr[((Wx-50)/20)+1] != NULL)
                            {
                                k=0;

                                for(j=0; j<=i; j++)
                                {
                                    if(j >= (Wx-50)/20)
                                    {
                                        ReadArr2[k]=ReadArr[j];
                                        k++;
                                    }
                                }

                                ReadArr[((Wx-50)/20)]= h;

                                for(j=1; j<k; j++)
                                    ReadArr[((Wx-50)/20)+j] = ReadArr2[j-1];

                                MakePage2();
                                PrintArr(ReadArr,100,i+1);
                                i++;
                                Wx=Wx+20;
                                ReadGo=ReadGo+20;
                            }
                            else
                            {
                                setcolor(Colour);
                                setbkcolor(15);
                                outtextxy(Wx,Wy,hs);
                                ReadArr[(Wx-50)/20]=h;
                                Buffer[i]=h;
                                i++;
                                Wx=Wx+20;
                                ReadGo=ReadGo+20;
                            }
                        }
                    }
                    else
                    {
                        if(Exit != 1)
                            h = (char) getch();

                        switch(h)
                        {
                        case KEY_RIGHT:

                            if(ReadArr[((Wx-50)/20)] != NULL || ReadArr[((Wx-50)/20)+1] != NULL )
                                Wx=Wx+20;

                            break;

                        case KEY_LEFT:

                            if(Wx>50)
                                Wx=Wx-20;

                            break;
                        }

                    }

                    if(Exit == 1)
                        break;

                }

                closegraph(Read);
                setcurrentwindow(MainScreen);
                char Word[10005];
                CrtFile = fopen(ReadArr,"r");

                if(CrtFile != NULL)
                {
                    Head = NULL;
                    Last = NULL;
                    while(!feof(CrtFile))
                    {
                        fscanf(CrtFile,"%c",&Word[i]);

                        if(feof(CrtFile))
                            break;

                        if(Readx >= 1800)
                            Ready=Ready+20;

                        Add(&Head,&Last,Word[i],Ready,Readx);
                        Readx = Readx+20;
                    }

                    setcolor(Colour);
                    PrintPage(&Head,0);
                    x=Readx-20;
                    y=Ready;
                }
                else
                    printf("Eroare! Nu s-a deschis fisierul!\n");

                fclose(CrtFile);

                break;
////////////
            case KEY_F1 : ///SELECTIE
////////////
                KeyVal++;

                if(KeyVal%2 == 1)
                {
                    Tx=x;
                    Ty=y;
                    DeleteSolve(1825,180,1920,260);
                    setcolor(Colour);
                }
                else
                {
                    struct Node *c;

                    Head2=NULL;
                    Last2=NULL;
                    DeleteSolve(1825,180,1920,260);
                    setcolor(Colour);

                    for(c=Head; c!=NULL; c=c->Next)
                    {
                        if(c->Semn == 1)
                            c->Semn = 0;
                    }

                    Diff2=Diff;

                    if(Diff2<=0)
                        Diff2=0;

                    MakePage(x,y);
                    setbkcolor(15);
                    PrintPage(&Head,Diff2+Td);
                }

                break;
////////////
            case KEY_UP: ///mergem in sus cu cursorul liniutza
////////////
                if(KeyVal%2 == 1 && LinVerify(&Head,y-20)!=0)
                {
                    ///Verifica daca suntem la prima linie, daca nu suntem ne putem deplasa in sus
                    if(Ty < y)
                        VerifySelection2(&Head,x,y-20,x,y,Diff+Td);
                    else
                        VerifySelection2(&Head,x,y-20,x,y,Diff+Td);
                }

                if(indexy == 100)
                {
                    if(Td <= -1*Diff)
                        Td=-1*Diff;

                    if(Td > -1*Diff)
                    {
                        Td=Td-20;
                        MakePage(x,y);
                        PrintPage(&Head,Diff+Td);
                    }

                }

                if(y<=100)
                {
                    y=100;
                    indexy=100;
                }
                else if(LinVerify(&Head,y-20)==0)
                {
                    y=y-20;

                    if(indexy > 100)
                        indexy=indexy-20;

                    x=50;
                }
                else if(LinVerify(&Head,y-20)>= x) ///Verificam daca suntem la prima linie
                {
                    y=y-20;

                    if(indexy >= 100)
                        indexy=indexy-20;

                }
                else if(LinVerify(&Head,y-20)< x)///Verificam daca suntem sub prima linie
                {
                    y=y-20;

                    if(indexy > 100)
                        indexy=indexy-20;

                    x=LinVerify(&Head,y);
                }


                break;
////////////
            case KEY_DOWN: ///mergem in jos cu cursorul liniutza
////////////
                if(KeyVal%2 == 1 && LinVerify(&Head,y+20)!=0)
                {
                    if(Ty > y)
                        VerifySelection3(&Head,x,y,x,y+20,Tx,Diff+Td);
                    else
                        VerifySelection3(&Head,x,y,x,y+20,Tx,Diff+Td);

                }
                if(indexy == 980)
                {
                    if(Td > 0)
                        Td=0;

                    if(Td <= -20)
                    {
                        Td=Td+20;
                        MakePage(x,y);
                        PrintPage(&Head,Diff+Td);
                    }
                }

                if(Head == NULL) {}
                else if(NullVerify(&Head,x+20,y)==0 && Last->Lin == y && Last->Col == x) {}
                else if(y < 100+Go && LinVerify(&Head,y+20)==0)
                {
                    y=y+20;

                    if(indexy < 980)
                        indexy=indexy+20;

                    x=50;
                }
                else if(NullVerify(&Head,x+20,y)==0 && (Last->Lin != y || Last->Col != x))
                {
                    if(LinVerify(&Head,y+20)==0)
                    {
                        y=y+20;

                        if(indexy < 980)
                            indexy=indexy+20;

                        x=50;
                    }
                    else if(LinVerify(&Head,y+20)>= x)
                    {
                        y=y+20;

                        if(indexy < 980)
                            indexy=indexy+20;
                    }
                    else if(LinVerify(&Head,y+20)< x)
                    {
                        y=y+20;

                        if(indexy < 980)
                            indexy=indexy+20;

                        x=LinVerify(&Head,y);
                    }
                    else
                    {
                        y=y+20;

                        if(indexy < 980)
                            indexy=indexy+20;

                        x=LinVerify(&Head,y);
                    }
                }
                else if (LinVerify(&Head,y+20)!=0)
                {
                    y=y+20;

                    if(indexy < 980)
                        indexy=indexy+20;
                }

                break;
////////////
            case KEY_LEFT: ///MUTARE CURSOR LINIUTZA STANGA PE COLOANA
////////////
                if(KeyVal%2 == 1)
                {
                    if(Tx < x)
                        MakeSelection(&Head,x-20,y,x,y+20,Diff+Td);

                    else
                        MakeSelection(&Head,x-20,y,x,y+20,Diff+Td);

                }
                if(x<=50 && y<=100)
                {
                    x=50;
                    y=100;
                    indexy=100;
                }
                else if(x<=50)
                {
                    y=y-20;
                    indexy=indexy-20;

                    if(LinVerify(&Head,y)==0)
                        x=50;
                    else
                        x=LinVerify(&Head,y);
                }
                else
                    x=x-20;

                break;
////////////
            case KEY_RIGHT: ///MUTARE CURSOR LINIUTZA DREAPTA PE COLOANA
////////////
                if(Diff<=0)
                    Diff=0;

                if(KeyVal%2 == 1)
                {
                    if(NullVerify(&Head,x+20,y)!=0)
                    {
                        if(Tx > x)
                        {
                            DeleteField(&Head,x,y,x+20,y+20,15,Diff+Td);
                            MakeSelection(&Head,x,y,x+20,y+20,Diff+Td);
                        }
                        else
                        {
                            DeleteField(&Head,x,y,x+20,y+20,9,Diff+Td);
                            MakeSelection(&Head,x,y,x+20,y+20,Diff+Td);
                        }
                    }
                }
                if(Head == NULL) {}
                else if(x>=1800 && NullVerify(&Head,50,y+20)==0) {}
                else if(x>=1800 && NullVerify(&Head,50,y+20)!=0)
                {
                    x=50;
                    y=y+20;

                    if(indexy < 980)
                        indexy=indexy+20;
                }
                else if(x<=1800)
                {
                    if(NullVerify(&Head,x+20,y)==0 && Last->Lin == y && Last->Col == x) {}
                    else if(NullVerify(&Head,x+20,y)==0 && (Last->Lin != y || Last->Col != x))
                    {
                        if(LinVerify(&Head,y+20)==0)
                        {
                            y=y+20;

                            if(indexy < 980)
                                indexy=indexy+20;

                            x=50;
                        }
                        else
                        {
                            y=y+20;

                            if(indexy < 980)
                                indexy=indexy+20;

                            x=50;
                        }
                    }
                    else
                        x=x+20;
                }

                break;
////////////
            default:
                break;
    }
}

    /// if(Diff<=0)
    ///    indexy=(100+Go);

    Diff2=Diff;

    if(Diff2<=0)
        Diff2=0;

    SolveNr(100+Go,Diff+Td);

    if(x >= 1790)
        line(1811,99,1811,getmaxy());

}

    closegraph();
    return 0;
}
