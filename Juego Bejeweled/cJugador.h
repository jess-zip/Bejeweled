#ifndef CJUGADOR_H_INCLUDED
#define CJUGADOR_H_INCLUDED

class cJugador{
private:
    int puntos;//puntos del jugador
    char nombre[30];//nombre del jugador
public:
    cJugador();//constructor
    ~cJugador();//destructor
    void set_Jugador(char, int);//le damos los datos al jugador
};

#endif // CJUGADOR_H_INCLUDED
