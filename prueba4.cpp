#include <iostream>
#include <windows.h>
#include <conio.h>

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
	class enemigo 
	{
	private:
	public:
		void pintar(int, int);
		void mover(int &, int &);
		void borrar(int, int);
		void mapa();
	};
	
	class jugador{
	public:
		void portaviones(int,int,int);
		void dltportaaviones(int,int,int);
		void moveport(int &, int &, int);
	};
	
	
	void enemigo::mapa()
	{
		for(int i=0;i<22;i++)
		{
			cout<<endl;
			for(int j=0;j<22;j++)
				cout<<map[i][j];
		}
	}
	
	
	void enemigo::pintar(int x, int y)
	{
		gotoxy(x,y);cout<<"+";  
	}
	
	void enemigo::borrar(int x, int y)
	{
		gotoxy(x,y);cout<<" ";
	}
	
	void enemigo::mover(int &x,int &y)
	{
		if(kbhit())
		{
			enemigo::borrar(x,y);
			char tecla = getch();
			if(tecla == 'a' && x>2) x=x-2;
			if(tecla == 'd' && x<20) x=x+2;
			if(tecla == 'w' && y>3) y=y-2;
			if(tecla == 's' && y<21) y=y+2;
			enemigo::pintar(x,y);
		}
		
	}
	
	void jugador::portaviones(int x,int y, int k)
	{
		if(k==0)
		{
			gotoxy(x,y);cout<<"P";
			gotoxy(x,y+2);cout<<"P";
			gotoxy(x,y+4);cout<<"P";
			gotoxy(x,y+6);cout<<"P";
			gotoxy(x,y+8);cout<<"P";
		}else
		{
			gotoxy(x,y);cout<<"P";
			gotoxy(x+2,y);cout<<"P";
			gotoxy(x+4,y);cout<<"P";
			gotoxy(x+6,y);cout<<"P";
			gotoxy(x+8,y);cout<<"P";
			
		}
	}
	
	void jugador::dltportaaviones(int x,int y, int k)
	{
		if(k==0)
		{
			gotoxy(x,y);cout<<" ";
			gotoxy(x,y+2);cout<<" ";
			gotoxy(x,y+4);cout<<" ";
			gotoxy(x,y+6);cout<<" ";
			gotoxy(x,y+8);cout<<" ";    
		}else
		{
			gotoxy(x,y);cout<<" ";
			gotoxy(x+2,y);cout<<" ";
			gotoxy(x+4,y);cout<<" ";
			gotoxy(x+6,y);cout<<" ";
			gotoxy(x+8,y);cout<<" ";
			
		}
	}
	
	void jugador::moveport(int &x,int &y, int k)
	{
		if(kbhit())
		{
			jugador::dltportaaviones(x,y,k);
			char tecla = getch();
			if(tecla == 'a' && x>2) x=x-2;
			if(k==0)
			{
				if(tecla == 'd' && x<20) x=x+2;
			}
			if(k==1)
			{
				if(tecla == 'd' && x<12) x=x+2;
			}
			if(tecla == 'w' && y>28) y=y-2;
			if(k==0)
			{
				if(tecla == 's' && y<38) y=y+2;
			}
			if(k==1)
			{
				if(tecla == 's' && y<46) y=y+2;
			}
			
			jugador::portaviones(x,y,k);
		}
	}
	
	int main(){
		jugador e;
		enemigo a;
		int q=2,w=3;
		int q1=2, w1=28;
		
		
		a.mapa();
		gotoxy(0,25);
		a.mapa();
		
		
		while(true)
		{
			e.moveport(q1,w1,0);
		}
		
		
		return 0;
	}
		
