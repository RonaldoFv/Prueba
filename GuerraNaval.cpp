#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;


void gotoxy(int x, int y){
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;     
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}
	
	
	char map[22][22] =  {{' ',' ','0',' ','1',' ','2',' ','3',' ','4',' ','5',' ','6',' ','7',' ','8',' ','9',' '},
	{' ',' ','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_',' '},
	{'A','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
	{' ','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|'},
	{'B','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
	{' ','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|'},
	{'C','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
	{' ','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|'},
	{'D','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
	{' ','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|'},
	{'E','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
	{' ','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|'},
	{'F','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
	{' ','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|'},
	{'G','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
	{' ','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|'},
	{'H','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
	{' ','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|'},
	{'I','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
	{' ','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|','-','|'},
	{'J','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
	{' ',' ','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',' '},};
	
	
	struct cda{
		int x, y;
	};
	

	struct barco{
		cda in; 
		cda pe[4];
		char D;
		char d ='*';
		cda lugar(int n);
	};
	
	cda barco::lugar(int n)
	{
		cda retorno = {in.x, in.y};
		if(n!=0)
		{
			retorno.x += pe[n-1].x;
			retorno.y += pe[n-1].y;
		}
		return retorno;
		
	}
	cda per[6][4] ={
					{{2,0},{4,0},{6,0},{8,0}},
					{{2,0},{4,0},{6,0},{   }} ,
					{{2,0},{4,0},{   },{   }},
					{{2,0},{4,0},{   },{   }},
					{{2,0},{   },{   },{   }},
					{{   },{   },{   },{   }},
	};
	
	
	char barcos[5]={'P','A','C','S','D'};
		
	
	char map2[22][22];
	char m[22][22];
	char m2[22][22];

	class jugador
	{
	
	private:
		int turno = 0;
		int turno1;
		int winP1 = 0, winIA = 0;
		
		
	public:
		int rwinP1(){return winP1;}
		int rwinIA(){return winIA;}
		void pintar(barco &, int);
		void direc(barco &);
		cda direc(cda &);
		void selc(barco &, int);
		void move(barco &, int &);
		bool limite(barco &, int);
		void dlt(barco &);
		void cbmap();
		void mostrarmap2();
		int getxy();
		void selcmap(barco &, int, int);
		void disparo(barco &, int);
		int very(barco &);
		void IA(barco &, int &, int);
		void cambioturno(barco &, int &, int);
	};
	
	void jugador::cbmap()
	{
		for(int i=0;i<22;i++)
		{
			cout<<endl;
			for(int j=0;j<22;j++)
			{
				map2[i][j] = map[i][j];
				m[i][j] = map[i][j];
				m2[i][j] = map[i][j];
			}
		}
	}
	void jugador::mostrarmap2()
	{
		for(int i=0;i<22;i++)
		{
			cout<<endl;
			for(int j=0;j<22;j++)
			{
				cout<<map2[i][j];
			}
		}
	}
	
	bool jugador::limite(barco &P, int q)
	{
		for(int i=0;i<5;i++)
		{
			cda c = P.lugar(i);
			if(c.x <2 || c.x>20)return true;
			if(c.y <2 || c.y>20)return true;
			if(q == 1)
			{
				if(map2[c.y][c.x] == 'P' || map2[c.y][c.x] == 'A' || map2[c.y][c.x] == 'C' || map2[c.y][c.x] == 'S' || map2[c.y][c.x] == 'D	') return true;
			}
			if(q==2)
			{
				if(map2[c.y][c.x] == 'X' || map2[c.y][c.x] == 'O') return true;
			}
			
		}
		return false;
	}
	
	void jugador::move(barco &P, int &r)
	{
		if(kbhit())
		{
			barco cop = P;	
			char tecla = getch();
			if(tecla == 'a' ) P.in.x -=2;
			if(tecla == 'd' ) P.in.x +=2;
			if(tecla == 'w' ) P.in.y -=2;
			if(tecla == 's' ) P.in.y +=2;
			
			if(tecla == 'b')
			{
				jugador::direc(P);
			}
			if(jugador::limite(P,1))
			{
				P = cop;
			}
			jugador::dlt(cop);
			jugador::pintar(P,1);
			
			if(tecla == 'c')
			{
				jugador::pintar(P,2);
				r++;
				jugador::selcmap(P,r,1);
			}
		}
	}
	
	void jugador::pintar(barco &P, int r)
	{
		for(int i=0;i<5;i++)
		{	
			cda c = P.lugar(i);
			if(r==1)map2[c.y][c.x] = P.d;
			else map2[c.y][c.x] = P.D;
		}
			
			
	}
	

	void jugador::dlt(barco &P)
	{
		
		for(int i=0;i<5;i++)
		{
			cda c = P.lugar(i);
			map2[c.y][c.x] = ' ';
		}
	}
		
		
	cda jugador::direc(cda &c)
	{
		cda re ={c.y,c.x};
		return re;
	}
	
	
	void jugador::direc(barco &P)
	{
		for(int i=0;i<4;i++)
		{
			P.pe[i]=jugador::direc(P.pe[i]);
		}
	}
	
	void jugador::selc(barco &P, int r)
	{
		P.in.x = jugador::getxy();
		P.in.y = jugador::getxy();
		P.D = barcos[r];
		
		for(int i=0;i<4;i++)
		{
			P.pe[i] = per[r][i];		
		}
	}
	
	int jugador::getxy()
	{
		while(true)
		{
		int x= rand()%19+2;
		if(x%2 == 0)return x;
		}
	}
		
	void jugador::selcmap(barco &P, int r,int q)
	{
		while(true)
		{
			jugador::selc(P,r);
			if(!jugador::limite(P,q)) break;
		}	
	}
	
	
	void jugador::disparo(barco &P, int q)
	{
		for(int i=0;i<5;i++)
		{
			cda c=P.lugar(i);
			if(q == 1)
			{
				if(m2[c.y][c.x]== 'P' || m2[c.y][c.x]=='A' || m2[c.y][c.x]=='C' || m2[c.y][c.x]=='S' || m2[c.y][c.x]=='D')
				{
					m[c.y][c.x] = 'O';
					winP1++;
					
				}
				if(m2[c.y][c.x]== ' ') m[c.y][c.x]='X';
			}
			if(q == 2)
			{
				if(map2[c.y][c.x]== 'P' || map2[c.y][c.x]=='A' || map2[c.y][c.x]=='C' || map2[c.y][c.x]=='S' || map2[c.y][c.x]=='D') 
				{
					if(map2[c.y][c.x] == 'P') P.D = 'P';
					if(map2[c.y][c.x] == 'A') P.D = 'A';
					if(map2[c.y][c.x] == 'C') P.D = 'C';
					if(map2[c.y][c.x] == 'S') P.D = 'S';
					if(map2[c.y][c.x] == 'D') P.D = 'D';
					map2[c.y][c.x] = 'O';
					turno1  = 1;
					winIA++;
				}
				if(map2[c.y][c.x]== ' ') map2[c.y][c.x]='X';	
			}	
		}
	}
	
	
	int jugador::very(barco &P)
	{
		for(int i=2;i<22;i++)
		{
			for(int j=2;j<22;j++)
			{
				if(map2[i][j] == P.D)
				{
					P.in.x =j;
					P.in.y =i;
					return 1;
				}
			}
		}
		return 2;
	}
	
	
	void jugador::cambioturno(barco &P, int &t, int r)
	{
		jugador::selcmap(P,r,2);
		jugador::disparo(P,2);
		t=1;
	}
	
	
	void jugador::IA(barco &P, int &t, int r)
	{
		if(turno1 == 0) turno = 0;
		if(turno1 == 1) turno = 1;
		if(turno == 0)
		{
			jugador::cambioturno(P,t,r);
		}
		if(turno == 1)
		{
			if(jugador::very(P) == 1)
			{
				jugador::disparo(P,2);
				t=1;
			}
			if(jugador::very(P) == 2)
			{
				jugador::cambioturno(P,t,r);
				turno1=0;
			}
		}
	}
	
	
	class enemigo : public jugador
	{
		public:
		void pintar(barco &, int);
		void move(barco &,int &, int &);
		bool limite(barco &, int);
		void dlt(barco &);
		void mostrarm();
		void selcmap(barco &, int);
		void inbarco(barco &);
		int obtdirc();
	};
	
	
	void enemigo::pintar(barco &P,int r)
	{
		
		for(int i=0;i<5;i++)
		{
			cda c = P.lugar(i);
			if(r==1) m[c.y][c.x] = P.d;
			else m2[c.y][c.x] = P.D;
		}
		 
	}
	
	
	void enemigo::dlt(barco &P)
	{
		for(int i=0;i<5;i++)
		{
			cda c = P.lugar(i);
			m[c.y][c.x] = ' ';
		}
	}
	
	
	void enemigo::mostrarm()
	{
		for(int i=0;i<22;i++)
		{
			cout<<endl;
			for(int j=0;j<22;j++)
			{
				cout<<m[i][j];
			}
		}
	}
	
	
	void enemigo::move(barco &P,int &r, int &c)
	{
		if(kbhit())
		{
			barco cop = P;	
			char tecla = getch();
			if(tecla == 'a' ) P.in.x -=2;
			if(tecla == 'd' ) P.in.x +=2;
			if(tecla == 'w' ) P.in.y -=2;
			if(tecla == 's' ) P.in.y +=2;
			if(enemigo::limite(P,2))
			{
				P = cop;
			}
				
			enemigo::dlt(cop);
			enemigo::pintar(P,1);
			if(tecla =='v')
			{
				enemigo::disparo(P,1);
				enemigo::selcmap(P,r);
				c = 2;
				cop = P;
			}
		}
	}
	
	bool enemigo::limite(barco &P, int q)
	{
		for(int i=0;i<5;i++)
		{
			cda c = P.lugar(i);
			if(c.x <2 || c.x>20)return true;
			if(c.y <2 || c.y>20)return true;
			if(q == 1)
			{
				if(m2[c.y][c.x] == 'P' || m2[c.y][c.x] == 'A' || m2[c.y][c.x] == 'C' || m2[c.y][c.x] == 'S' || m2[c.y][c.x] == 'D') return true;
			}
			if(q == 2)
			{
				if(m[c.y][c.x] == 'X' || m[c.y][c.x] == 'O') return true;
			}
			   
		}
		return false;
	}
	void enemigo::selcmap(barco &P, int r)
	{
		while(true)
		{
			enemigo::selc(P,r);
			if(!enemigo::limite(P,2)) break;
		}
	}
	
	int enemigo::obtdirc()
	{
		int x = rand()%2;
		return x;
	}
	
	
	void enemigo::inbarco(barco &P)
	{
		for(int i = 0;i<6;i++)
		{
			while(true)
			{
				enemigo::selc(P,i);
				if(enemigo::obtdirc() == 0) enemigo::direc(P);
				if(!enemigo::limite(P,1))
				{
					enemigo::pintar(P,2);
					break;
				}
			}
		}
	}
	
	
	int main()
	{
		system("cls");
		//randomizer
		srand(time(NULL));
		
		jugador e;
		enemigo b;
		
		barco s,s1;
		int r=0;
		int c=0;
		
		e.cbmap();
		e.selc(s,r);
		b.inbarco(s1);
		
		bool finjuego = true;
		while(finjuego)
		{
			gotoxy(0,25); e.mostrarmap2();
			gotoxy(0,0); b.mostrarm();		
			
			if(c == 0 )
			{
				e.move(s,r);
				if(r==5)c=1;
			}
			if(c==1)
			{
				b.move(s1,r,c);
			}
			if(c==2)
			{
				b.IA(s,c,r);
			}
			if(b.rwinP1() == 17)
			{
				finjuego = false;
				system("cls");
				cout<<"Perdiste"<<endl;
				Sleep(1000);
			}
			if(b.rwinIA() == 17)
			{
				finjuego = false;
				system("cls");
				cout<<"Ganaste"<<endl;
				Sleep(1000);
			}
			Sleep(30);
		}
		/*int g;
		system("cls");
		cout<<"Continuar?    Si= 1  No= 2"<<endl;
		cin>>g;
		switch(g)
		{
		case 1: main();
		break;
		case 2: return 0;
		break;
		}*/
		return 0;
	}
		
		
