//Menu
#include <iostream>
#include <allegro.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include "cClase.h"
#include "cJuego.h"

//Prototipos
void inicio();

using namespace std;
//SAMPLE *sonido1 = load_sample("click_x.wav");//sonido del click

int puntos=0;


int main()
{
    allegro_init();
    install_keyboard();
    install_mouse();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, 0);
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 740, 480, 0, 0);

    Juego j;//objeto del tipo juego

    //j.registro();
    j.intro();//abre el titulo
    //j.game();
    //j.menu();


    return 0;

}
END_OF_MAIN();
