/*



*/


#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

//Esta funcion nos permite manipular la posición en la pantalla de lo que nuestra aplicación envie de salida
void gotoxy(int x, int y){
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;     
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}
	
	//esta matriz bidimencional nos sirve para dibujar el tablero que deja un espacio en blanco para posicionar las naves o piezas
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
	
	//esta estructura nos da una coordenada con la que nos podremos mover por el teclado 
	struct coordenada{
		int x, y;
	};
	 
	struct pieza{
		coordenada in;     // aqui al llamar a "in" de "inicial" ya tendra 2 datos, corresponde a la primera pieza de un barco, que es la que se movera
		coordenada pe[4];  // esta funcion nos permite formar un barco de hasta 5 posiciones y que sigan a la pieza "in"
		char D;            // este dato "D" nos dara el tipo de caracter que se mostrara por consola
		char d ='*';       // esto lo uso mas adelante para reemplar las piezas de los barcos antes de imprimirlos en pantalla
		coordenada lugar(int n);
	};
	
	//esto se encarga de adicionar los lugares que requieren los barcos
	coordenada pieza::lugar(int n)
	{
		coordenada retorno = {in.x, in.y};
		if(n!=0)
		{
			retorno.x += pe[n-1].x; 
			retorno.y += pe[n-1].y;
		}
		return retorno;
		
	}

	//esta funcion nos permite definir el numero de piezas que tendra cada uno de los barcos, e indica en la coordenada que se debe posicionar
	coordenada per[6][4] ={
		{{2,0},{4,0},{6,0},{8,0}},
		{{2,0},{4,0},{6,0},{   }} ,
		{{2,0},{4,0},{   },{   }},
		{{2,0},{4,0},{   },{   }},
		{{2,0},{   },{   },{   }},
		{{   },{   },{   },{   }}, // esta matriz correspondera al puntero de ataque
	};
	
	
	// P= PortaAviones A= Acorazado C= Crucero S= Submarino D= Destructor
	char barcos[5]={'P','A','C','S','D'};
	
	
    //estos son tableros a parte que usare mas tarde, dejare el del inicio como una declaracion 
	char map2[22][22];       //map2= mapa del jugador 
	char m[22][22];         // mapa de disparos
	char m2[22][22];       //m2= mapa del enemigo
	
	class jugador
	{
		
	private:
		int turno = 0;
		int turno1;
		int ganajugador = 0, ganaIA = 0;
		
		
	public:
		// & = operador de referencia de punteros, y declarador de referencia.    
		// al usarlo pasamos un valor por referencia estamos pasando una direccion 
		// la ventaja de usar esto es que como pasamos una direccion y no un valor, se puede modificar

		int rganajugador(){return ganajugador;}
		int rganaIA(){return ganaIA;}   

		void pintar(pieza &, int);
		void mover(pieza &, int &);
		void rotar(pieza &);    
		coordenada rotar(coordenada &);           
		void seleccionar(pieza &, int);        
		bool limite(pieza &, int);            
		void borrar(pieza &);
		void cambiarmapa();
		void mostrarmap2();
		int getxy();
		void seleccionarmapa(pieza &, int, int);
		void disparo(pieza &, int);
		int verificar(pieza &);
		void IA(pieza &, int &, int);
		void cambioturno(pieza &, int &, int);
	};
	
	//esta funcion nos posiciona la pieza inicial de los barcos en las coordenadas y,x
	void jugador::pintar(pieza &P, int r)
	{
		for(int i=0;i<5;i++)
		{	
			coordenada c = P.lugar(i);
			if(r==1)map2[c.y][c.x] = P.d;
			else map2[c.y][c.x] = P.D;
		}
		
	}


	void jugador::mover(pieza &P, int &r)
	{
		if(kbhit()) // kbhit permite detectar que tecla se esta presionando.
		{
			pieza copia = P; 
			char tecla = getch();
			if(tecla == 'a' ) P.in.x -=2; //el incremento y decremento en '2' es para que nos movamos dentro de los espacios de la matriz
			if(tecla == 'd' ) P.in.x +=2;
			if(tecla == 'w' ) P.in.y -=2;
			if(tecla == 's' ) P.in.y +=2;
			
			if(tecla == 'b')
			{
				jugador::rotar(P);
			}
			if(jugador::limite(P,1))
			{
				P = copia;
			}
			jugador::borrar(copia);
			jugador::pintar(P,1);
			
			if(tecla == 'c')
			{
				jugador::pintar(P,2);
				r++;
				jugador::seleccionarmapa(P,r,1);
			}
		}
	}
	
	
	// esta funcion nos ayuda a rotar a vertical y horizontal las pieza ya definidas "pe" con anterioridad 
	coordenada jugador::rotar(coordenada &c)
	{
		coordenada re ={c.y,c.x};
		return re;
	}
	 //esto hace que al momento de mostrar la piezas en consola deje el lugar con un espacio en blanco
	void jugador::borrar(pieza &P)
	{
		
		for(int i=0;i<5;i++)
		{
			coordenada c = P.lugar(i);
			map2[c.y][c.x] = ' ';
		}
	}
	
	//esta funcion toma los valores que regresa la funcion de arriba y los reescribe
	void jugador::rotar(pieza &P)
	{
		for(int i=0;i<4;i++)
		{
			P.pe[i]=jugador::rotar(P.pe[i]);
		}
	}
	
	void jugador::seleccionar(pieza &P, int r)
	{
		P.in.x = jugador::getxy();     //getxy nos permite generar el barco de manera aleartoria en el mapa 
		P.in.y = jugador::getxy();
		P.D = barcos[r];              //esto indica el valor para poder identificar el barco
		
		for(int i=0;i<4;i++)
		{
			P.pe[i] = per[r][i];	//esto toma el tipo de letra asignado al barco y le da sus piezas dentro de la matriz
		}
	}


	//esta funcion mientras nos regrese un false nos permitira movernos por la matriz
	//tambien hara que en la matriz no se borren los barcos
	bool jugador::limite(pieza &P, int q)
	{
		for(int i=0;i<5;i++)   //aqui pasamos las posiciones de los barcos
		{
			coordenada c = P.lugar(i); 
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
	

	void jugador::cambiarmapa()
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
	
	
	//esto nos da un numero aleartorio dentro de la matriz
	//tambien nos evita que el numero sea impar 
	int jugador::getxy()
	{
		while(true)
		{
			int x= rand()%19+2;
			if(x%2 == 0)return x;
		}
	}


	//esta funcion impide que se cree un barco en pociones donde ya se encuentra otro
	void jugador::seleccionarmapa(pieza &P, int r,int q)
	{
		while(true)
		{
			jugador::seleccionar(P,r);
			if(!jugador::limite(P,q)) break;
		}	
	}
	
	//esta funcion nos permite saber si disparamos a un barco o al agua, si le dimos al barco se marca 'O' caso contrario 'X'
	void jugador::disparo(pieza &P, int q)
	{
		for(int i=0;i<5;i++)
		{
			coordenada c=P.lugar(i);
			if(q == 1)
			{
				if(m2[c.y][c.x]== 'P' || m2[c.y][c.x]=='A' || m2[c.y][c.x]=='C' || m2[c.y][c.x]=='S' || m2[c.y][c.x]=='D')
				{
					m[c.y][c.x] = 'O';
					ganajugador++;
					
				}
				if(m2[c.y][c.x]== ' ') m[c.y][c.x]='X';
			}
			if(q == 2)
			{
				if(map2[c.y][c.x]== 'P' || map2[c.y][c.x]=='A' || map2[c.y][c.x]=='C' || map2[c.y][c.x]=='S' || map2[c.y][c.x]=='D') 
				{
					if(map2[c.y][c.x] == 'P') P.D = 'P';          //esto hace que la maquina busque las letras definidas en el mapa
						if(map2[c.y][c.x] == 'A') P.D = 'A';
					if(map2[c.y][c.x] == 'C') P.D = 'C';
					if(map2[c.y][c.x] == 'S') P.D = 'S';
					if(map2[c.y][c.x] == 'D') P.D = 'D';
					map2[c.y][c.x] = 'O';
					turno1  = 1;
					ganaIA++;
				}
				if(map2[c.y][c.x]== ' ') map2[c.y][c.x]='X';	
			}	
		}
	}
	
	// esta funcion es pa que la IA detecte las piezas de parco de derribo
	int jugador::verificar(pieza &P)
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
	
	
	void jugador::cambioturno(pieza &P, int &t, int r)
	{
		jugador::seleccionarmapa(P,r,2);
		jugador::disparo(P,2);
		t=1;
	}
	
	
	void jugador::IA(pieza &P, int &t, int r)
	{
		if(turno1 == 0) turno = 0;
		if(turno1 == 1) turno = 1;
		if(turno == 0)
		{
			jugador::cambioturno(P,t,r);
		}
		if(turno == 1)
		{
			if(jugador::verificar(P) == 1)
			{
				jugador::disparo(P,2);
				t=1;
			}
			if(jugador::verificar(P) == 2)
			{
				jugador::cambioturno(P,t,r);
				turno1=0;
			}
		}
	}
	
	
	class enemigo : public jugador
	{
	public:
		void pintar(pieza &, int);
		void mover(pieza &,int &, int &);
		bool limite(pieza &, int);
		void borrar(pieza &);
		void mostrarm();
		void seleccionarmapa(pieza &, int);
		void iniciarbarco(pieza &);
		int obtdirc();
	};
	
	//esta funcion permite poner cada uno de los barcos en el mapa
	void enemigo::pintar(pieza &P,int r)
	{
		
		for(int i=0;i<5;i++)
		{
			coordenada c = P.lugar(i);
			if(r==1) m[c.y][c.x] = P.d;
			else m2[c.y][c.x] = P.D;
		}
		
	}
	
	
	void enemigo::borrar(pieza &P)
	{
		for(int i=0;i<5;i++)
		{
			coordenada c = P.lugar(i);
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
	
	
	void enemigo::mover(pieza &P,int &r, int &c)
	{
		if(kbhit())
		{
			pieza copia = P;	
			char tecla = getch();
			if(tecla == 'a' ) P.in.x -=2;
			if(tecla == 'd' ) P.in.x +=2;
			if(tecla == 'w' ) P.in.y -=2;
			if(tecla == 's' ) P.in.y +=2;
			if(enemigo::limite(P,2))
			{
				P = copia;
			}
			
			enemigo::borrar(copia);
			enemigo::pintar(P,1);
			if(tecla =='v')
			{
				enemigo::disparo(P,1);
				enemigo::seleccionarmapa(P,r);
				c = 2;
				copia = P;
			}
		}
	}
	
	bool enemigo::limite(pieza &P, int q)
	{
		for(int i=0;i<5;i++)
		{
			coordenada c = P.lugar(i);
			if(c.x <2 || c.x>20)return true;
			if(c.y <2 || c.y>20)return true;
			if(q == 1) //esto verifiqua la inicialiacion de barcos en el mapa enemigo
			{
				if(m2[c.y][c.x] == 'P' || m2[c.y][c.x] == 'A' || m2[c.y][c.x] == 'C' || m2[c.y][c.x] == 'S' || m2[c.y][c.x] == 'D') return true;
			}
			if(q == 2)  //esto verifica la funcion disparo, para que el disparo no se genere donde hay una X u O
			{
				if(m[c.y][c.x] == 'X' || m[c.y][c.x] == 'O') return true;
			}
			
		}
		return false;
	}
	
	void enemigo::seleccionarmapa(pieza &P, int r)
	{
		while(true)
		{
			enemigo::seleccionar(P,r);
			if(!enemigo::limite(P,2)) break;
		}
	}
	

	int enemigo::obtdirc()
	{
		int x = rand()%2;
		return x;
	}
	
	
	void enemigo::iniciarbarco(pieza &P)
	{
		for(int i = 0;i<6;i++)
		{
			while(true)
			{
				enemigo::seleccionar(P,i);
				if(enemigo::obtdirc() == 0) enemigo::rotar(P);
				if(!enemigo::limite(P,1))
				{
					enemigo::pintar(P,2);                               //"por si no lo explico arriba 2 representa a los caracteres a imprimir y 1 al asteriscos"
					break;
				}
			}
		}
	}
	
	
	
	int main()
	{
		//system("cls");
		
		srand(time(NULL));
		
		jugador e;
		enemigo b;
		
		pieza s,s1;    //estos datos resiben valores diferentes "para la clase jugadores" y s1 para la "clase enemigo"
		int r=0;       
		int c=0;
		
		e.cambiarmapa();
		e.seleccionar(s,r);
		b.iniciarbarco(s1);
		
		bool finjuego = true;
		
		while(finjuego) 
		{
			gotoxy(0,25); e.mostrarmap2();   // muestra el mapa en esa coordenada (este vendria siendo el mapa inferior)
			gotoxy(0,0); b.mostrarm();		// (mapa superior)  
			
			if(c == 0 )
			{
				e.mover(s,r);
				if(r==5)c=1;
			}
			if(c==1)
			{
				b.mover(s1,r,c);
			}
			if(c==2)
			{
				b.IA(s,c,r);
			}
			if(b.rganajugador() == 17)
			{
				finjuego = false;
				system("cls");
				
				cout<<"Ganaste"<<endl;
				Sleep(2000);
			}
			if(b.rganaIA() == 17)
			{
				finjuego = false;
				system("cls");
				cout<<"Perdiste"<<endl;
				Sleep(2000);
			}
			Sleep(30);
		}
		
		return 0;
	}
	
	
	
