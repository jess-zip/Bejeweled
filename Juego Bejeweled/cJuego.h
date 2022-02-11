#ifndef CJUEGO_H_INCLUDED
#define CJUEGO_H_INCLUDED
#include <iostream>
#include <allegro.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include "cClase.h"

using namespace std;



class Juego: public Tablero{//hereda de tablero
protected:
    int Tx, Ty;
    bool ready;//para saber si ya se reprodució welcome
public:
    Juego(){//constructor
        Tx=273;
        Ty=28;
        ready=0;
        musica1 = load_sample("Opening.wav");
        click = load_sample("click_x.wav");
        GetReady = load_sample("getReady.wav");
        Welcome = load_sample("WelcomeToBejeweled.wav");
        buffer = create_bitmap(740,480);
        cursor =  load_bitmap("cursor.bmp",NULL);
        load = load_bitmap("loading.bmp",NULL);
    }
    void intro();//abre el juego
    void menu();
    void game();
    void imprimTab();//imprime los gems
    void elegir();//selecciona los dos que se van a cambiar
    void instrucciones();
    void records();
};

void Juego::intro(){

    BITMAP *Imag1 =  load_bitmap("openingImagen1.bmp",NULL);
    BITMAP *Imag2 =  load_bitmap("openingImagen2.bmp",NULL);
    BITMAP *Imag3 =  load_bitmap("openingImagen3.bmp",NULL);
    BITMAP *Imag4 =  load_bitmap("openingImagen4.bmp",NULL);
    BITMAP *Imag5 =  load_bitmap("openingImagen5.bmp",NULL);
    BITMAP *Imag6 =  load_bitmap("openingImagen6.bmp",NULL);
    BITMAP *Imag7 =  load_bitmap("openingImagen7.bmp",NULL);
    BITMAP *Imag8 =  load_bitmap("openingImagen8.bmp",NULL);
    BITMAP *Imag9 =  load_bitmap("openingImagen9.bmp",NULL);

    int band = 0;
    char c;

    set_volume(230, 200);
    play_sample(musica1,200,150,1000,0);

    blit(Imag1,buffer, 0,0, 0,0, 740,480);
    rest(200);
    blit(buffer,screen, 0,0, 0,0, 740,480);
    blit(Imag2,buffer, 0,0, 0,0, 740,480);
    rest(200);
    blit(buffer,screen, 0,0, 0,0, 740,480);
    blit(Imag3,buffer, 0,0, 0,0, 740,480);
    rest(200);
    blit(buffer,screen, 0,0, 0,0, 740,480);
    blit(Imag4,buffer, 0,0, 0,0, 740,480);
    rest(200);
    blit(buffer,screen, 0,0, 0,0, 740,480);
    blit(Imag5,buffer, 0,0, 0,0, 740,480);
    rest(200);
    blit(buffer,screen, 0,0, 0,0, 740,480);
    blit(Imag6,buffer, 0,0, 0,0,740,480);
    rest(200);
    blit(buffer,screen, 0,0, 0,0, 740,480);
    blit(Imag7,buffer, 0,0, 0,0, 740,480);
    rest(200);
    blit(buffer,screen, 0,0, 0,0, 740,480);
    while(c!=KEY_ENTER){
        for(int i=0; i<5; i++){//hace parpadear las letras
            blit(Imag8,buffer, 0,0, 0,0, 740,480);
            rest(900);
            blit(buffer,screen, 0,0, 0,0, 740,480);
            blit(Imag9,buffer, 0,0, 0,0, 740,480);
            rest(500);
            blit(buffer,screen, 0,0, 0,0, 740,480);
        }
        c= readkey() >>8;//presiona enter
    }
    menu();
    destroy_bitmap(buffer);
}

void Juego::menu(){
    BITMAP *menu = load_bitmap("menu.bmp",NULL);
    BITMAP *menu2 =  load_bitmap("menu2.bmp",NULL);
    BITMAP *menu3 =  load_bitmap("menu3.bmp",NULL);
    BITMAP *menu4 =  load_bitmap("menu4.bmp",NULL);
    BITMAP *menu5 = load_bitmap("menu5.bmp",NULL);

    bool salida=1;
    int band=0;
    if(ready==0){
        play_sample(Welcome,200,150,1000,0);
        ready=1;
    }

    while(salida){
        if(mouse_x>=290&&mouse_x<=442 && mouse_y>=147 && mouse_y<=196){//iniciar
            if(band!=1){//para que haga el sonido una sola vez
                play_sample(click,200,150,1000,0);
                band=1;
            }

            blit(menu2,buffer,0,0,0,0,740,480);

            if(mouse_b&1){//si hace click
                blit(load,buffer,0,0,0,0,740,480);
                //rest(1000);
                //validar();
                game();
            }
        }
        else if(mouse_x>=213&&mouse_x<=532 && mouse_y>=206 && mouse_y<=258){//instrucciones
            if(band!=1){
                play_sample(click,200,150,1000,0);
                band=1;
            }
            blit(menu3,buffer,0,0, 0,0, 740,480);

            if(mouse_b&1){//si hace click
                blit(load,buffer,0,0,0,0,740,480);
                instrucciones();
            }
        }
        else if(mouse_x>=269&&mouse_x<=463 && mouse_y>=266 && mouse_y<=313){//records
            if(band!=1){
                play_sample(click,200,150,1000,0);
                band=1;
            }
            blit(menu4,buffer,0,0, 0,0, 740,480);

            if(mouse_b&1){//si hace click
                blit(load,buffer,0,0,0,0,740,480);
                rest(1000);
                records();
            }
        }
        else if(mouse_x>=305&&mouse_x<=428 && mouse_y>=322 && mouse_y<=367){//salida
            if(band!=1){
                play_sample(click,200,150,1000,0);
                band=1;
            }
            blit(menu5,buffer,0,0, 0,0, 740,480);

            if(mouse_b&1){//si hace click
                salida=false;
            }
        }
        else{
            blit(menu,buffer,0,0,0,0,740,480);
            band=0;
        }
        masked_blit(cursor,buffer,0,0,mouse_x,mouse_y,13,22);
        blit(buffer,screen,0,0,0,0,740,480);
    }
    destroy_bitmap(buffer);
}

void Juego::game(){
    show_mouse(screen);
    bool salida=true;
    play_sample(GetReady,200,150,1000,0);
    int n=0;
    while(salida==true){
        if(mouse_x>=110 && mouse_x<=182 && mouse_y>=360 && mouse_y<=407){
            //blit(fondo2,fondo,0,0,0,0,740,480);
            if(mouse_b&1){//si presiona menú
                salida=false;//se sale del while
            }
        }
        else{
            //validar();
            imprimTab();//imprimimos los gráficos
            //rest(5000);
            elegir();//seleccionamos los gems
            imprimTab();
            game();
        }
        /*masked_blit(cursor,buffer,0,0,mouse_x,mouse_y,13,22);
        blit(buffer,screen,0,0,0,0,740,480);*/
        cout<<"PUNTOS: "<<puntos;
    }
    masked_blit(cursor,buffer,0,0,mouse_x,mouse_y,13,22);
        blit(buffer,screen,0,0,0,0,740,480);
    menu();

    destroy_bitmap(buffer);
}

void Juego::imprimTab(){
    Tx=273;
        Ty=28;
    BITMAP *fondo =  load_bitmap("background.bmp",NULL);
    BITMAP *fondo2 =  load_bitmap("background2.bmp",NULL);
    BITMAP *gem1 = load_bitmap("gem1.bmp",NULL);
    BITMAP *gem2 = load_bitmap("gem2.bmp",NULL);
    BITMAP *gem3 = load_bitmap("gem3.bmp",NULL);
    BITMAP *gem4 = load_bitmap("gem4.bmp",NULL);
    BITMAP *gem5 = load_bitmap("gem5.bmp",NULL);
    BITMAP *gem6 = load_bitmap("gem6.bmp",NULL);
    blit(fondo,buffer,0,0,0,0,740,480);
            for(int i=0; i<8; i++){//col
                for(int j=0; j<8; j++){//ren
                    if(tablero[j][i]==1){
                       draw_sprite(buffer,gem1,Tx+(i*53),Ty+(j*53));
                    }
                    else if(tablero[j][i]==2){
                       draw_sprite(buffer,gem2,Tx+(i*53),Ty+(j*53));
                    }
                    else if(tablero[j][i]==3){
                       draw_sprite(buffer,gem3,Tx+(i*53),Ty+(j*53));
                    }
                    else if(tablero[j][i]==4){
                       draw_sprite(buffer,gem4,Tx+(i*53),Ty+(j*53));
                    }
                    else if(tablero[j][i]==5){
                       draw_sprite(buffer,gem5,Tx+(i*53),Ty+(j*53));
                    }
                    else if(tablero[j][i]==6){
                       draw_sprite(buffer,gem6,Tx+(i*53),Ty+(j*53));
                    }
                }//for j
            }//for i
            masked_blit(cursor,buffer,0,0,mouse_x,mouse_y,13,22);
            blit(buffer,screen,0,0,0,0,740,480);
}

void Juego::elegir(){
    bool band=0;
    bool otro=0;
    //primer valor
    rest(500);
    cout<<endl<<x1<<" "<<y1<<" "<<x2<<" "<<y2;
    while(band==0){//hasta que tengan diferente valor
        if(mouse_y>=28 && mouse_y<=82){//si está en el primer renglón
            if(mouse_x>=272 && mouse_x<=326){
                if(mouse_b&1){
                       x1=0;
                        y1=0;
                        band=1;

                }

            }
            else if(mouse_x>=327 && mouse_x<=377){
                if(mouse_b&1){
                       x1=0;
                        y1=1;
                        band=1;

                }

            }
            else if(mouse_x>=378 && mouse_x<=430){
                if(mouse_b&1){
                       x1=0;
                        y1=2;
                        band=1;

                }

            }
            else if(mouse_x>=431 && mouse_x<=480){
                if(mouse_b&1){
                        x1=0;
                        y1=3;
                        band=1;

                }

            }
            else if(mouse_x>=481 && mouse_x<=534){
                if(mouse_b&1){
                       x1=0;
                        y1=4;
                        band=1;

                }

            }
            else if(mouse_x>=535 && mouse_x<=586){
                if(mouse_b&1){
                       x1=0;
                        y1=5;
                        band=1;

                }

            }
            else if(mouse_x>=587 && mouse_x<=639){
                if(mouse_b&1){
                        x1=0;
                        y1=6;
                        band=1;

                }

            }
            else if(mouse_x>=640 && mouse_x<=690){
                if(mouse_b&1){
                        x1=0;
                        y1=7;
                        band=1;

                }

            }
        }
        else if(mouse_y>=83 && mouse_y<=133){//si está en el 2do renglon
            if(mouse_x>=272 && mouse_x<=326){
                if(mouse_b&1){
                        x1=0;
                        y1=0;
                        band=1;

                }

            }
            else if(mouse_x>=327 && mouse_x<=377){
                if(mouse_b&1){
                        x1=1;
                        y1=1;
                        band=1;

                }

            }
            else if(mouse_x>=378 && mouse_x<=430){
                if(mouse_b&1){
                        x1=1;
                        y1=2;
                        band=1;

                }

            }
            else if(mouse_x>=431 && mouse_x<=480){
                if(mouse_b&1){
                        x1=1;
                        y1=3;
                        band=1;

                }

            }
            else if(mouse_x>=481 && mouse_x<=534){
                if(mouse_b&1){
                        x1=1;
                        y1=4;
                        band=1;

                }

            }
            else if(mouse_x>=535 && mouse_x<=586){
                if(mouse_b&1){
                        x1=1;
                        y1=5;
                        band=1;

                }

            }
            else if(mouse_x>=587 && mouse_x<=639){
                if(mouse_b&1){
                        x1=1;
                        y1=6;
                        band=1;

                }

            }
            else if(mouse_x>=640 && mouse_x<=690){
                if(mouse_b&1){
                        x1=1;
                        y1=7;
                        band=1;

                }

            }
        }
        else if(mouse_y>=134 && mouse_y<=186){//si está en el 3er renglon
            if(mouse_x>=272 && mouse_x<=326){
                if(mouse_b&1){
                        x1=2;
                        y1=0;
                        band=1;

                }

            }
            else if(mouse_x>=327 && mouse_x<=377){
                if(mouse_b&1){
                        x1=2;
                        y1=1;
                        band=1;

                }

            }
            else if(mouse_x>=378 && mouse_x<=430){
                if(mouse_b&1){
                        x1=2;
                        y1=2;
                        band=1;

                }

            }
            else if(mouse_x>=431 && mouse_x<=480){
                if(mouse_b&1){
                        x1=2;
                        y1=3;
                        band=1;

                }

            }
            else if(mouse_x>=481 && mouse_x<=534){
                if(mouse_b&1){
                        x1=2;
                        y1=4;
                        band=1;

                }

            }
            else if(mouse_x>=535 && mouse_x<=586){
                if(mouse_b&1){
                        x1=2;
                    y1=5;
                    band=1;

                }

            }
            else if(mouse_x>=587 && mouse_x<=639){
                if(mouse_b&1){
                            x1=2;
                    y1=6;
                    band=1;

                }

            }
            else if(mouse_x>=640 && mouse_x<=690){
                if(mouse_b&1){
                        x1=2;
                    y1=7;
                    band=1;

                }

            }
        }
        else if(mouse_y>=187 && mouse_y<=238){//si está en el 4to renglon
            if(mouse_x>=272 && mouse_x<=326){
                if(mouse_b&1){
                        x1=3;
                    y1=0;
                    band=1;

                }

            }
            else if(mouse_x>=327 && mouse_x<=377){
                if(mouse_b&1){
                       x1=3;
                    y1=1;
                    band=1;

                }

            }
            else if(mouse_x>=378 && mouse_x<=430){
                if(mouse_b&1){
                        x1=3;
                    y1=2;
                    band=1;

                }

            }
            else if(mouse_x>=431 && mouse_x<=480){
                if(mouse_b&1){
                        x1=3;
                    y1=3;
                    band=1;

                }

            }
            else if(mouse_x>=481 && mouse_x<=534){
                if(mouse_b&1){
                       x1=3;
                    y1=4;
                    band=1;

                }

            }
            else if(mouse_x>=535 && mouse_x<=586){
                if(mouse_b&1){
                        x1=3;
                    y1=5;
                    band=1;

                }

            }
            else if(mouse_x>=587 && mouse_x<=639){
                if(mouse_b&1){
                        x1=3;
                    y1=6;
                    band=1;

                }

            }
            else if(mouse_x>=640 && mouse_x<=690){
                if(mouse_b&1){
                       x1=3;
                    y1=7;
                    band=1;

                }

            }
        }
        else if(mouse_y>=239 && mouse_y<=290){//si está en el 5to renglón
            if(mouse_x>=272 && mouse_x<=326){
                if(mouse_b&1){
                        x1=4;
                    y1=0;
                    band=1;

                }

            }
            else if(mouse_x>=327 && mouse_x<=377){
                if(mouse_b&1){
                       x1=4;
                    y1=1;
                    band=1;

                }

            }
            else if(mouse_x>=378 && mouse_x<=430){
                if(mouse_b&1){
                        x1=4;
                    y1=2;
                    band=1;

                }

            }
            else if(mouse_x>=431 && mouse_x<=480){
                if(mouse_b&1){
                        x1=4;
                    y1=3;
                    band=1;

                }

            }
            else if(mouse_x>=481 && mouse_x<=534){
                if(mouse_b&1){
                        x1=4;
                    y1=4;
                    band=1;

                }

            }
            else if(mouse_x>=535 && mouse_x<=586){
                if(mouse_b&1){
                        x1=4;
                    y1=5;
                    band=1;

                }

            }
            else if(mouse_x>=587 && mouse_x<=639){
                if(mouse_b&1){
                       x1=4;
                    y1=6;
                    band=1;

                }

            }
            else if(mouse_x>=640 && mouse_x<=690){
                if(mouse_b&1){
                        x1=4;
                    y1=7;
                    band=1;

                }

            }
        }
        else if(mouse_y>=291 && mouse_y<=343){//si está en el 6to renglon
            if(mouse_x>=272 && mouse_x<=326){
                if(mouse_b&1){
                        x1=5;
                    y1=0;
                    band=1;

                }

            }
            else if(mouse_x>=327 && mouse_x<=377){
                if(mouse_b&1){
                       x1=5;
                    y1=1;
                    band=1;

                }

            }
            else if(mouse_x>=378 && mouse_x<=430){
                if(mouse_b&1){
                       x1=5;
                    y1=2;
                    band=1;

                }

            }
            else if(mouse_x>=431 && mouse_x<=480){
                if(mouse_b&1){
                        x1=5;
                    y1=3;
                    band=1;

                }

            }
            else if(mouse_x>=481 && mouse_x<=534){
                if(mouse_b&1){
                        x1=5;
                    y1=4;
                    band=1;

                }

            }
            else if(mouse_x>=535 && mouse_x<=586){
                if(mouse_b&1){
                        x1=5;
                    y1=5;
                    band=1;

                }

            }
            else if(mouse_x>=587 && mouse_x<=639){
                if(mouse_b&1){
                        x1=5;
                    y1=6;
                    band=1;

                }

            }
            else if(mouse_x>=640 && mouse_x<=690){
                if(mouse_b&1){
                        x1=5;
                    y1=7;
                    band=1;

                }

            }
        }
        else if(mouse_y>=344 && mouse_y<=395){//si está en el 7mo renglón
            if(mouse_x>=272 && mouse_x<=326){
                if(mouse_b&1){
                        x1=6;
                    y1=0;
                    band=1;

                }

            }
            else if(mouse_x>=327 && mouse_x<=377){
                if(mouse_b&1){
                       x1=6;
                    y1=1;
                    band=1;

                }

            }
            else if(mouse_x>=378 && mouse_x<=430){
                if(mouse_b&1){
                        x1=6;
                    y1=2;
                    band=1;

                }

            }
            else if(mouse_x>=431 && mouse_x<=480){
                if(mouse_b&1){
                        x1=6;
                    y1=3;
                    band=1;

                }

            }
            else if(mouse_x>=481 && mouse_x<=534){
                if(mouse_b&1){
                       x1=6;
                    y1=4;
                    band=1;

                }

            }
            else if(mouse_x>=535 && mouse_x<=586){
                if(mouse_b&1){
                        x1=6;
                    y1=5;
                    band=1;

                }

            }
            else if(mouse_x>=587 && mouse_x<=639){
                if(mouse_b&1){
                        x1=6;
                    y1=6;
                    band=1;

                }

            }
            else if(mouse_x>=640 && mouse_x<=690){
                if(mouse_b&1){
                        x1=6;
                    y1=7;
                    band=1;

                }

            }
        }
        else if(mouse_y>=396 && mouse_y<=446){//si está en el 8vo renglón
            if(mouse_x>=272 && mouse_x<=326){
                if(mouse_b&1){
                      x1=7;
                    y1=0;
                    band=1;

                }

            }
            else if(mouse_x>=327 && mouse_x<=377){
                if(mouse_b&1){
                        x1=7;
                    y1=1;
                    band=1;

                }

            }
            else if(mouse_x>=378 && mouse_x<=430){
                if(mouse_b&1){
                        x1=7;
                    y1=2;
                    band=1;

                }

            }
            else if(mouse_x>=431 && mouse_x<=480){
                if(mouse_b&1){
                        x1=7;
                    y1=3;
                    band=1;

                }

            }
            else if(mouse_x>=481 && mouse_x<=534){
                if(mouse_b&1){
                        x1=7;
                    y1=4;
                    band=1;

                }

            }
            else if(mouse_x>=535 && mouse_x<=586){
                if(mouse_b&1){
                       x1=7;
                    y1=5;
                    band=1;

                }

            }
            else if(mouse_x>=587 && mouse_x<=639){
                if(mouse_b&1){
                        x1=7;
                    y1=6;
                    band=1;

                }

            }
            else if(mouse_x>=640 && mouse_x<=690){
                if(mouse_b&1){
                        x1=7;
                    y1=7;
                    band=1;

                }

            }
        }
    }
    cout<<endl<<"Sali del 1er while";
    cout<<endl<<tablero[x1][y1];
    rest(500);
    band=0;
    //segundo valor
    while(band==0){//hasta que tengan diferente valor
        if(mouse_y>=28 && mouse_y<=82){//si está en el primer renglón
            if(mouse_x>=272 && mouse_x<=326){
                if(mouse_b&1){
                    if(band==0){

                    x2=0;
                    y2=0;
                    band=1;
                }
                }

            }
            else if(mouse_x>=327 && mouse_x<=377){
                if(mouse_b&1){
                    x2=0;
                    y2=1;
                    band=1;
                }

            }
            else if(mouse_x>=378 && mouse_x<=430){
                if(mouse_b&1){
                    x2=0;
                    y2=2;
                    band=1;
                }
                }
            else if(mouse_x>=431 && mouse_x<=480){
                if(mouse_b&1){
                    x2=0;
                    y2=3;

                }

            }
            else if(mouse_x>=481 && mouse_x<=534){
                if(mouse_b&1){
                    x2=0;
                    y2=4;
                }


            }
            else if(mouse_x>=535 && mouse_x<=586){
                if(mouse_b&1){
                    x2=0;
                    y2=5;

                }

            }
            else if(mouse_x>=587 && mouse_x<=639){
                if(mouse_b&1){
                    x2=0;
                    y2=6;
                    band=1;
                }

            }
            else if(mouse_x>=640 && mouse_x<=690){
                if(mouse_b&1){
                    x2=0;
                    y2=7;
                    band=1;

                }

            }
        }
        else if(mouse_y>=83 && mouse_y<=133){//si está en el 2do renglon
            if(mouse_x>=272 && mouse_x<=326){
                if(mouse_b&1){
                    x2=0;
                    y2=0;
                    band=1;
                }

            }
            else if(mouse_x>=327 && mouse_x<=377){
                if(mouse_b&1){
                    x2=1;
                    y2=1;
                    band=1;
                }

            }
            else if(mouse_x>=378 && mouse_x<=430){
                if(mouse_b&1){
                    x2=1;
                    y2=2;
                    band=1;
                }

            }
            else if(mouse_x>=431 && mouse_x<=480){
                if(mouse_b&1){
                    x2=1;
                    y2=3;
                    band=1;
                }

            }
            else if(mouse_x>=481 && mouse_x<=534){
                if(mouse_b&1){
                    x2=1;
                    y2=4;
                    band=1;
                }

            }
            else if(mouse_x>=535 && mouse_x<=586){
                if(mouse_b&1){
                    x2=1;
                    y2=5;
                    band=1;
                }

            }
            else if(mouse_x>=587 && mouse_x<=639){
                if(mouse_b&1){
                    x2=1;
                    y2=6;
                    band=1;
                }

            }
            else if(mouse_x>=640 && mouse_x<=690){
                if(mouse_b&1){
                    x2=1;
                    y2=7;
                    band=1;
                }

            }
        }
        else if(mouse_y>=134 && mouse_y<=186){//si está en el 3er renglon
            if(mouse_x>=272 && mouse_x<=326){
                if(mouse_b&1){
                    x2=2;
                    y2=0;
                    band=1;
                }

            }
            else if(mouse_x>=327 && mouse_x<=377){
                if(mouse_b&1){
                    x2=2;
                    y2=1;
                    band=1;
                }

            }
            else if(mouse_x>=378 && mouse_x<=430){
                if(mouse_b&1){
                    x2=2;
                    y2=2;
                    band=1;
                }

            }
            else if(mouse_x>=431 && mouse_x<=480){
                if(mouse_b&1){
                        x2=2;
                        y2=3;
                    band=1;
                }

            }
            else if(mouse_x>=481 && mouse_x<=534){
                if(mouse_b&1){
                        x2=2;
                        y2=4;
                        band=1;
                }

            }
            else if(mouse_x>=535 && mouse_x<=586){
                if(mouse_b&1){
                    x2=2;
                    y2=5;
                    band=1;
                }

            }
            else if(mouse_x>=587 && mouse_x<=639){
                if(mouse_b&1){
                    x2=2;
                    y2=6;
                    band=1;
                }

            }
            else if(mouse_x>=640 && mouse_x<=690){
                if(mouse_b&1){
                    x2=2;
                    y2=7;
                    band=1;
                }

            }
        }
        else if(mouse_y>=187 && mouse_y<=238){//si está en el 4to renglon
            if(mouse_x>=272 && mouse_x<=326){
                if(mouse_b&1){
                    x2=3;
                    y2=0;
                    band=1;
                }

            }
            else if(mouse_x>=327 && mouse_x<=377){
                if(mouse_b&1){
                    x2=3;
                    y2=1;
                    band=1;
                }

            }
            else if(mouse_x>=378 && mouse_x<=430){
                if(mouse_b&1){
                    x2=3;
                    y2=2;
                    band=1;
                }

            }
            else if(mouse_x>=431 && mouse_x<=480){
                if(mouse_b&1){
                    x2=3;
                    y2=3;
                    band=1;
                }

            }
            else if(mouse_x>=481 && mouse_x<=534){
                if(mouse_b&1){
                    x2=3;
                    y2=4;
                    band=1;
                }

            }
            else if(mouse_x>=535 && mouse_x<=586){
                if(mouse_b&1){
                    x2=3;
                    y2=5;
                    band=1;
                }

            }
            else if(mouse_x>=587 && mouse_x<=639){
                if(mouse_b&1){
                    x2=3;
                    y2=6;
                    band=1;
                }

            }
            else if(mouse_x>=640 && mouse_x<=690){
                if(mouse_b&1){
                    x2=3;
                    y2=7;
                    band=1;
                }

            }
        }
        else if(mouse_y>=239 && mouse_y<=290){//si está en el 5to renglón
            if(mouse_x>=272 && mouse_x<=326){
                if(mouse_b&1){
                    x2=4;
                    y2=0;
                    band=1;
                }

            }
            else if(mouse_x>=327 && mouse_x<=377){
                if(mouse_b&1){
                    x2=4;
                    y2=1;
                    band=1;
                }

            }
            else if(mouse_x>=378 && mouse_x<=430){
                if(mouse_b&1){
                    x2=4;
                    y2=2;
                    band=1;
                }

            }
            else if(mouse_x>=431 && mouse_x<=480){
                if(mouse_b&1){
                    x2=4;
                    y2=3;
                    band=1;
                }

            }
            else if(mouse_x>=481 && mouse_x<=534){
                if(mouse_b&1){
                    x2=4;
                    y2=4;
                    band=1;
                }

            }
            else if(mouse_x>=535 && mouse_x<=586){
                if(mouse_b&1){
                    x2=4;
                    y2=5;
                    band=1;
                }

            }
            else if(mouse_x>=587 && mouse_x<=639){
                if(mouse_b&1){
                    x2=4;
                    y2=6;
                    band=1;
                }

            }
            else if(mouse_x>=640 && mouse_x<=690){
                if(mouse_b&1){
                    x2=4;
                    y2=7;
                    band=1;
                }

            }
        }
        else if(mouse_y>=291 && mouse_y<=343){//si está en el 6to renglon
            if(mouse_x>=272 && mouse_x<=326){
                if(mouse_b&1){
                    x2=5;
                    y2=0;
                    band=1;
                }

            }
            else if(mouse_x>=327 && mouse_x<=377){
                if(mouse_b&1){
                    x2=5;
                    y2=1;
                    band=1;
                }

            }
            else if(mouse_x>=378 && mouse_x<=430){
                if(mouse_b&1){
                    x2=5;
                    y2=2;
                    band=1;
                }

            }
            else if(mouse_x>=431 && mouse_x<=480){
                if(mouse_b&1){
                    x2=5;
                    y2=3;
                    band=1;
                }

            }
            else if(mouse_x>=481 && mouse_x<=534){
                if(mouse_b&1){
                    x2=5;
                    y2=4;
                    band=1;
                }

            }
            else if(mouse_x>=535 && mouse_x<=586){
                if(mouse_b&1){
                    x2=5;
                    y2=5;
                    band=1;
                }

            }
            else if(mouse_x>=587 && mouse_x<=639){
                if(mouse_b&1){
                    x2=5;
                    y2=6;
                    band=1;
                }

            }
            else if(mouse_x>=640 && mouse_x<=690){
                if(mouse_b&1){
                    x2=5;
                    y2=7;
                    band=1;
                }

            }
        }
        else if(mouse_y>=344 && mouse_y<=395){//si está en el 7mo renglón
            if(mouse_x>=272 && mouse_x<=326){
                if(mouse_b&1){
                    x2=6;
                    y2=0;
                    band=1;
                }

            }
            else if(mouse_x>=327 && mouse_x<=377){
                if(mouse_b&1){
                    x2=6;
                    y2=1;
                    band=1;
                }

            }
            else if(mouse_x>=378 && mouse_x<=430){
                if(mouse_b&1){
                    x2=6;
                    y2=2;
                    band=1;
                }

            }
            else if(mouse_x>=431 && mouse_x<=480){
                if(mouse_b&1){
                    x2=6;
                    y2=3;
                    band=1;
                }

            }
            else if(mouse_x>=481 && mouse_x<=534){
                if(mouse_b&1){
                    x2=6;
                    y2=4;
                    band=1;
                }

            }
            else if(mouse_x>=535 && mouse_x<=586){
                if(mouse_b&1){
                    x2=6;
                    y2=5;
                    band=1;
                }

            }
            else if(mouse_x>=587 && mouse_x<=639){
                if(mouse_b&1){
                    x2=6;
                    y2=6;
                    band=1;
                }

            }
            else if(mouse_x>=640 && mouse_x<=690){
                if(mouse_b&1){
                    x2=6;
                    y2=7;
                    band=1;
                }

            }
        }
        else if(mouse_y>=396 && mouse_y<=446){//si está en el 8vo renglón
            if(mouse_x>=272 && mouse_x<=326){
                if(mouse_b&1){
                    x2=7;
                    y2=0;
                    band=1;
                }

            }
            else if(mouse_x>=327 && mouse_x<=377){
                if(mouse_b&1){
                    x2=7;
                    y2=1;
                    band=1;
                }

            }
            else if(mouse_x>=378 && mouse_x<=430){
                if(mouse_b&1){
                    x2=7;
                    y2=2;
                    band=1;
                }

            }
            else if(mouse_x>=431 && mouse_x<=480){
                if(mouse_b&1){
                    x2=7;
                    y2=3;
                    band=1;
                }

            }
            else if(mouse_x>=481 && mouse_x<=534){
                if(mouse_b&1){
                    x2=7;
                    y2=4;
                    band=1;
                }

            }
            else if(mouse_x>=535 && mouse_x<=586){
                if(mouse_b&1){
                    x2=7;
                    y2=5;
                    band=1;
                }

            }
            else if(mouse_x>=587 && mouse_x<=639){
                if(mouse_b&1){
                    x2=7;
                    y2=6;
                    band=1;
                }

            }
            else if(mouse_x>=640 && mouse_x<=690){
                if(mouse_b&1){
                    x2=7;
                    y2=7;
                    band=1;
                }

            }
        }
    }
    cout<<endl<<"Sali del 2do while";
    cout<<endl<<tablero[x2][y2];
    change(x1, y1, x2, y2);//hacemos el cambio
}

void Juego::instrucciones(){
    BITMAP *inst = load_bitmap("instrucciones.bmp",NULL);
    BITMAP *inst2 = load_bitmap("instrucciones2.bmp",NULL);

    bool salida=true;
    int band=0;

    while(salida){
        if(mouse_x>=624 &&mouse_x<=714 && mouse_y>=415 &&mouse_y<=454){
            blit(inst2,buffer,0,0,0,0,740,480);
            if(mouse_b&1){//si hace click
                blit(load,buffer,0,0,0,0,740,480);
                salida=false;
                menu();
            }
        }
        else{
            blit(inst,buffer,0,0,0,0,740,480);
        }
        masked_blit(cursor,buffer,0,0,mouse_x,mouse_y,13,22);
        blit(buffer,screen,0,0,0,0,740,480);
    }
}

void Juego::records(){
    //cout<<endl<<"Entré a records";
    BITMAP *records1 = load_bitmap("records.bmp",NULL);
    BITMAP *records2 = load_bitmap("records2.bmp",NULL);

    bool salida=true;
    /*char nombre[50];
    int band=0;
    int a=90, b=200, c=90, d=270;*/
    //fstream out;
    /*out.open("archRecords.txt",ios::out|ios::app);
    out.seekg(0,ios::end);
    out<<nombre<<" "<<puntos<<endl;
    out.close();*/
    /*fstream file;
    file.open("archRecords.txt",ios::in);
    b+=20;
    d+=20;*/

    while(salida==true){
        //cout<<endl<<"Estoy en el while";
        if(mouse_x>=591 &&mouse_x<=710 && mouse_y>=410 &&mouse_y<=458){
            blit(records2,buffer,0,0,0,0,740,480);
            /*while(file>>nombre>>puntos){
                textprintf_ex(records2,font,c,d,0x42eef4,-1,"%9s %30s",nombre,puntos);
                d+=20;
            }*/
            if(mouse_b&1){//si hace click
                blit(load,buffer,0,0,0,0,740,480);
                salida=false;
                menu();
            }
        }
        else{
            blit(records1,buffer,0,0,0,0,740,480);
            /*while(file>>nombre>>puntos){
                textprintf_ex(records1,font,a,b,0x42eef4,-1,"%9s %30s",nombre,puntos);
                b+=20;
            }*/

        }
        masked_blit(cursor,buffer,0,0,mouse_x,mouse_y,13,22);
        blit(buffer,screen,0,0,0,0,740,480);
    }
    //file.close();
    destroy_bitmap(buffer);
}


#endif // CJUEGO_H_INCLUDED
