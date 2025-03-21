#include <iostream>
#include <winbgim.h>
#include <string.h>
 
#define MAX 20
 
using namespace std;
 
int TablaDeJoc[MAX][MAX];
int n, jucator;
int piesaAleasa;
int indicePagina=0;
void win(int player)
{
    cleardevice();
   // line(0, 0, 1000, 1000);
    if(player == 1)
    //readimagefile("res/player1Win.jpg", 0, 0, 550, 550);
    outtextxy(200, 200, "JUCATORUL 1 CASTIGA");
   else
   // readimagefile("res/player2Win.jpg", 0, 0, 550, 550);
    outtextxy(200, 200, "JUCATORUL 2 CASTIGA");
    getch();
    closegraph();
}
 
void lose(int player)
{
    cleardevice();
    if(player == 1)
   // readimagefile("res/player1Lose.jpg", 0, 0, 800, 800);
   outtextxy(200, 200, "JUCATORUL 1 PIERDE");
   else
    //readimagefile("res/player2Lose.jpg", 0, 0, 800, 800);
    outtextxy(200, 200, "JUCATORUL 2 PIERDE");
   getch();
   closegraph();
}
 
void initTabla(int n)
{
    int i,j;
    for (i=1; i<=n; i++)
        for (j=1; j<=n; j++)
            TablaDeJoc[i][j]=0;
    TablaDeJoc[1][1] = 1;
    TablaDeJoc[n][n] = -1;
//Bordarea matricei
    for(i = 1; i <= n; i++)
        TablaDeJoc[i][0] = -2;
    for(i = 1; i <= n; i++)
        TablaDeJoc[i][n+1] = -2;
    for(j = 1; j <= n; j++)
        TablaDeJoc[0][j] = -2;
    for(j = 1; j <= n; j++)
        TablaDeJoc[n+1][j] = -2;
 
}
 
void desPiesa(int p, int l, int c)
{
    char numeFisier[10];
    switch (p)
    {
    case 0:
        strcpy(numeFisier,"res/0.jpg");
        break;
    case 1:
        strcpy(numeFisier,"res/1.jpg");
        break;
    case 2:
        strcpy(numeFisier,"res/2.jpg");
        break;
    case 3:
        strcpy(numeFisier,"res/3.jpg");
        break;
    }
    readimagefile(numeFisier, 50 * c, 100 + 50 * l, 50 * (c + 1) - 2, 100 + 50 * (l + 1) - 2);
}
 
void desTabla(int n)
{
    int i,j,p;
    for (i=1; i<=n; i++)
    {
        for (j=1; j<=n; j++)
        {
            p=TablaDeJoc[i][j];
            desPiesa(p,i,j);
        }
    }
}
 
void alegePiesa(int &p)
{
    int x, y;
    p = 0;
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        x = mousex();
        y = mousey();
        if (x >= 50 && x <= 100 && y >= 25 && y <= 75) p = 1;
        if (x >= 150 && x <= 200 && y >= 25 && y <= 75) p = 2;
        if (x >= 250 && x <= 300 && y >= 25 && y <= 75) p = 3;
        if (x >= 350 && x <= 400 && y >= 25 && y <= 75) p = 4;
        if (x >= 450 && x <= 500 && y >= 25 && y <= 75) p = 5;
    }
}
 
void verif(int &directie, int linia, int coloana)
{
    int i = linia;
    int j = coloana;
    while(TablaDeJoc[i][j] != -1 && TablaDeJoc[i][j] != -2 && TablaDeJoc[i][j] != 0)
    {
        if(TablaDeJoc[i][j] == 1)
        {
            if(directie == 1)j++;
            if(directie == 2)j--;
            if(directie == 3)i++;
            if(directie == 4)i--;
            cout << linia << " " << coloana << " *" << directie <<"\n";
        }
        else if(TablaDeJoc[i][j] == 2)
        {
            if(directie == 1)
            {
                i--;
                directie = 4;
            }
 
            else  if(directie == 2)
            {
                directie = 3;
                i++;
            }
 
            else if(directie == 3)
            {
                directie = 2;
                j--;
            }
 
            else if(directie == 4)
            {
                directie = 1;
                j++;
            }
            cout << linia << " " << coloana << " " << directie <<"\n";
 
        }
        else if(TablaDeJoc[i][j] == 3)
        {
            if(directie == 1)
            {
                directie = 3;
                i++;
            }
 
            else if(directie == 2)
            {
                directie = 4;
                i--;
            }
            else if(directie == 3)
            {
                directie = 1;
                j++;
            }
            else if(directie == 4)
            {
                directie = 2;
                j--;
            }
            cout << linia << " " << coloana << " " << directie <<"\n";
        }
 
    }
    if(TablaDeJoc[i][j] == -1)
        win(jucator);
 
    if(TablaDeJoc[i][j] == -2)
        lose(jucator);
}
void directieStart(int &directie, int linia, int coloana, int &ok)
{
    ok = 1;
    if(linia == 2 && coloana == 1 && TablaDeJoc[linia][coloana] != 0 && TablaDeJoc[1][2] == 0)directie = 3;
    else if(linia == 1 && coloana == 2 && TablaDeJoc[linia][coloana] != 0 && TablaDeJoc[2][1] == 0)directie = 1;
    else if(linia == 2 && coloana == 1 && TablaDeJoc[linia][coloana] == 2 && TablaDeJoc[1][2] == 0)
    {
        lose(jucator);
        ok = 0;
    }
    else if(linia == 1 && coloana == 2 && TablaDeJoc[linia][coloana] == 2 && TablaDeJoc[2][1] == 0)
    {
        lose(jucator);
        ok = 0;
    }
    cout << linia << " "<< coloana << " " << directie << "\n";
}
int  directie = 0;
bool punerePiesa(int n)
{
    int linia, coloana, x, y, corect;
    int stanga = 50, sus = 150;
    int dreapta = 50 + 50 * n, jos = 150 + 50 * n;
    bool ok = false;
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        x = mousex();
        y = mousey();
        if (x>=stanga && x<=dreapta && y>=sus&&y<=jos)
        {
            linia=(y-sus)/50+1;
            coloana=(x-stanga)/50+1;
            if(piesaAleasa != 4)
            {
                if(TablaDeJoc[linia][coloana-1] > 0 || TablaDeJoc[linia][coloana+1] > 0 || TablaDeJoc[linia-1][coloana] > 0 || TablaDeJoc[linia+1][coloana] > 0)//punerea pieselor doar in rubrici vecine
                    if (TablaDeJoc[linia][coloana] == 0)
                    {
                        TablaDeJoc[linia][coloana] = piesaAleasa;
                        directieStart(directie, linia, coloana, corect);
                        if(corect == 1)
                            verif(directie, linia, coloana);
                        desPiesa(piesaAleasa,linia,coloana);
                        ok=true;
                    }
            }
            else if(piesaAleasa == 4)
            {
                if(linia != 1 || coloana != 1)
                {
                    TablaDeJoc[linia][coloana] = 0;
                    verif(directie, linia, coloana);
                    desPiesa(0, linia, coloana);
                    ok = true;
                }
 
            }
 
        }
    }
    return ok;
}
void afiseazaMeniul()
{
    readimagefile("res/1.jpg",50,25,100,75);
    readimagefile("res/2.jpg",150,25,200,75);
    readimagefile("res/3.jpg",250,25,300,75);
    readimagefile("res/0.jpg",350,25,400,75);
    readimagefile("res/exit.jpg",450,25,500,75);
}
 
void genMenu()
{
 
    outtextxy(100, 50, "ALEGETI MARIMEA TABLEI DE JOC: ");
    readimagefile("res/8x8.jpg",100, 100, 200, 150);
    readimagefile("res/7x7.jpg",220, 100, 320, 150);
    readimagefile("res/6x6.jpg",100, 170, 200, 220);
    readimagefile("res/5x5.jpg",220, 170, 320, 220);
    readimagefile("res/4x4.jpg",160, 240, 260, 290);
}
 
void alegeMarime(int &p)
{
    int x,y;
    p=0;
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        x=mousex();
        y=mousey();
        if(x >= 100 && x <= 200 && y >= 100 && y <= 150) p = 1;
        if(x >= 220 && x <= 320 && y >= 100 && y <= 150) p = 2;
        if(x >= 100 && x <= 200 && y >= 170 && y <= 220) p = 3;
        if(x >= 220 && x <= 320 && y >= 170 && y <= 220) p = 4;
        if(x >= 160 && x <= 260 && y >= 240 && y <= 290) p = 5;
    }
}
 
void pagina_meniu()
{
    setbkcolor(WHITE);
    indicePagina = 0;
    cleardevice();
    setbkcolor(BLACK);
    settextstyle(8, 0, 15);
    outtextxy(250, 150, "   Coltul Negru   ");
 
    settextstyle(8, 0, 3);
    outtextxy(300, 250, " Start Game ");
    outtextxy(300, 300,"Reguli");
    outtextxy(300, 350, " Exit ");
    setbkcolor(WHITE);
 
 
}
 
void pagina_reguli()
{
    int height=0;
    indicePagina=1;
    setbkcolor(WHITE);
    settextstyle(8, 0 , 1);
    setbkcolor(BLACK);
    outtextxy(50,100,"1.Jocul se incepe obligatoriu cu un jeton cu linii incrucisate.");
    height=100+textheight("a")+5;
    outtextxy(50,height,"2.Plasand asemenea jetoane unul langa altul sa se conduca");
    height=height+textheight("a")+5;
    outtextxy(73,height,"o linie continua din coltul de inceput al tablei in coltul negru.");
     height=height+textheight("a")+5;
    outtextxy(50,height,"3.Castiga jocul cel care pune jetonul cu care ,,linia lunga''");
    height=height+textheight("a")+5;
    outtextxy(73,height,"a jocului ajunge in -se suprapune peste- coltul negru.");
    height=height+textheight("a")+5;
    outtextxy(50,height,"4.Din cele doua linii ale fiecarui cartonas numai una duce");
    height=height+textheight("a")+5;
    outtextxy(73,height,"linia jocului mai departe,dar la mutari urmatoare pot fi cuprinse");
    height=height+textheight("a")+5;
    outtextxy(73,height,"in continuarea liniei si capete ramase pe parcurs.In felul acesta pot aparea");
    height=height+textheight("a")+5;
    outtextxy(73,height,"bucle.");
    height=height+textheight("a")+5;
    outtextxy(50,height,"5.Daca langa primul jeton,al doilea jucator va plasa un jeton cu linii");
    height=height+textheight("a")+5;
    outtextxy(73,height,"incrucisate,linia jocului se continua drept,iar daca va plasa un jeton");
    height=height+textheight("a")+5;
    outtextxy(73,height,"cu linii curbe,linia jocului este intoarsa cu 90 grade la stanga sau");
    height=height+textheight("a")+5;
    outtextxy(73,height,"la dreapta.");
    height=height+textheight("a")+5;
    outtextxy(50,height,"6.Este interzis ca linia principala sa fie condusa la marginea tablei!");
    height=height+textheight("a")+5;
    outtextxy(73,height,"Jucatorul a carui mutare se scoate linia jocului la conturul tablei");
    height=height+textheight("a")+5;
    outtextxy(73,height,"pierde jocul.");
   settextstyle(8,0,3);
    outtextxy(10,50,"Meniu");
    setbkcolor(WHITE);
 
}
 
void pagina_start_game()
{
    indicePagina = 1;
    setbkcolor(0);
    int  marime, marimeaAleasa = 0;
    genMenu();
    do
    {
        alegeMarime(marimeaAleasa);
        switch (marimeaAleasa)
        {
        case 1:
            marime = 8;
            break;
        case 2:
            marime = 7;
            break;
        case 3:
            marime = 6;
            break;
        case 4:
            marime = 5;
            break;
        case 5:
            marime = 4;
            break;
        }
    }
    while(marimeaAleasa == 0);
    cleardevice();
    afiseazaMeniul();
    initTabla(marime);
    desTabla(marime);
    readimagefile("res/null.jpg", 50*marime, 100+50*marime, 50*(marime+1)-2,100+50*(marime+1)-2);
    bool ok;
    jucator = 2;
    do
    {
        if(jucator == 2)
        {
            jucator = 1;
            outtextxy(50, 85, "Randul jucatorului 1");
        }
 
        else if(jucator == 1)
        {
            jucator = 2;
            outtextxy(50, 85, "Randul jucatorului 2");
        }
 
        int i,j;
        cout <<"\n\n";
        for (i=0; i<=marime+1; i++)
        {
            for (j=0; j<=marime+1; j++)
                cout << TablaDeJoc[i][j] << " ";
            cout << endl;
        }
        piesaAleasa=0;
        do
        {
            alegePiesa(piesaAleasa);
            if (piesaAleasa==5)
            {
                closegraph();
 
            }
        }
        while (piesaAleasa==0);
        do
        {
            ok=punerePiesa(marime);
        }
        while (!ok);
    }
    while(1);
}
 
 
void functii()
{
    int x, y;
    bool click;
    while (1)
    {
        x = mousex();
        y = mousey();
        click = ismouseclick(WM_LBUTTONDOWN);
 
        if (click)
        {   cout<<x<<" "<<y;
            if (indicePagina==0)
            {
            clearmouseclick(WM_LBUTTONDOWN);
                settextstyle(8, 0, 15);
                if (x >300 && x < 300 + textwidth(" Reguli ") && y > 300 && y < 300 + textheight(" Reguli ")) // buton reguli din meniu
                {
                    cleardevice();
                    pagina_reguli();
                    cout<<"aoleo";
                }
 
                if (x > 300 && x < 300 + textwidth(" Start game ") && y > 250 && y < 250 + textheight(" Start game "))
                {
                    cleardevice();
                    pagina_start_game();
                }
 
                if (x > 300 && x < 300 + textwidth(" Exit ") && y > 350 && y < 350 + textheight(" Exit "))
                {
                    closegraph();
                    break;
                }
 
 
            }
            settextstyle(8,0,3);
            if (indicePagina!=0 && x>10 && x<10+ textwidth("Meniu") && y>50 && y<50+textheight("Meniu"))
            {
                pagina_meniu();
            }
 
        }
    }
}
 
 
 
 
int main()
{
    initwindow(920, 700);
    pagina_meniu();
    functii();
}
 