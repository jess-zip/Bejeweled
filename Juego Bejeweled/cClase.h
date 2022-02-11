#ifndef CCLASE_H_INCLUDED
#define CCLASE_H_INCLUDED
#include <iostream>

using namespace std;

class Tablero{
protected:
    int primero;
    int segundo;
    int puntos;
    BITMAP *buffer;
    SAMPLE *musica1;//musica del introduccion//musica del introduccion
    SAMPLE *click;//sonido del click
    SAMPLE *GetReady;//sonido get Ready
    SAMPLE *Welcome;//sonido Welcome to bejeweled
    //nuestro buffer
    BITMAP *cursor;//cursor
    BITMAP *load;//cargando
public:
    int x1, x2, y1, y2;
    int tablero[8][8];//tamaño del tablero
    Tablero();//inicializa la tabla con aleatorios del 1 al 6
    void imprimir_tab();//imprime la tabla
    void change(int, int, int, int);//intercambia los valores de la tabla
    bool ren(int, int, int, int);
    bool col(int, int, int, int);
    void validar();//ve si el cambio es valido
};

Tablero::Tablero(){
    primero=segundo=0;
    x1=x2=y1=y2=puntos=0;
    //puntos=200;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            tablero[i][j]=1+rand()%(6-1+1);//llenamos el tablero con numeros aleatorios
            cout<<tablero[i][j]<<" ";
        }
        cout<<endl;
    }
}

void Tablero::imprimir_tab(){
    for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			cout<<tablero[i][j]<<" ";
		}
		cout<<endl;
	}
}

void Tablero::change(int x, int y, int x1, int y1){
	primero=tablero[x][y];
	segundo=tablero[x1][y1];
	cout<<endl<<"Valores a cambiar: ";
	cout<<endl<<primero<<" "<<segundo;
	if(col(x, y, x1, y1)==true || ren(x, y, x1, y1)==true){
		//swap(primero,segundo);//hacemos el swap
		tablero[x][y]=segundo;
        tablero[x1][y1]=primero;
        puntos+=100;
	}


	cout<<endl<<"Como quedaría la tabla: "<<endl;
	imprimir_tab();
	cout<<endl<<"Validando";
	validar();
	cout<<endl<<"Nueva tabla"<<endl;
	imprimir_tab();
}

bool Tablero::ren(int x, int y, int x1, int y1){
	if(primero==tablero[x-1][y] || primero==tablero[x+1][y] || segundo==tablero[x1-1][y1] || segundo==tablero[x1+1][y1]){
		return true;
	}
	else{
		return false;
	}
}

bool Tablero::col(int x, int y, int x1, int y1){
	if(primero==tablero[x1][y1-1] || primero==tablero[x1][y1+1] || segundo==tablero[x-1][y] || segundo==tablero[x][y+1]){
		return true;
	}
	else{
		return false;
	}
}

void Tablero::validar(){
    int sw,n=0,n1;
	for(int p=0; p<3; p++){
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if(tablero[i][j]==tablero[i+1][j] && tablero[i][j]==tablero[i+2][j] ){
					cout<<"fila"<<endl;
					sw=tablero[i][j];
					n=i;
					while(tablero[n][j]==sw){	//contar elemetos iguales
						n++;
					}
					for(int m=j;m>0;m--){//reduce hasta llegar a renglon 0
						for(n1=n-1;n1>=i;n1--){//reduce hasta llegar a columna i
							tablero[n1][m]=tablero[n1][m-1];
						}
					}
					for(int o=i;o<=n;o++){
						tablero[o][0]=1+rand()%(6-1+1);
					}
					imprimir_tab();
				}
				else if(tablero[j][i]==tablero[j][i+1]&&tablero[j][i]==tablero[j][i+2]){
					cout<<"col"<<endl;
					sw=tablero[j][i];
					n=i;
					while(tablero[j][n]){
						n++;
					}
					for(int m=n;m>(n-i);m--){//reduce hasta llegar a renglon 0
						tablero[j][m]=tablero[j][m-(n-i)];//objetos diferentes al obj1/obj2 cayendo
					}
					for(int m=0;m<(n-i);m++){//ingresando objetos en espacios "desocupados"
						tablero[j][m]=1+rand()%(6-1+1);
					}
					imprimir_tab();
				}
			}
		}
	}
}

#endif // CCLASE_H_INCLUDED
