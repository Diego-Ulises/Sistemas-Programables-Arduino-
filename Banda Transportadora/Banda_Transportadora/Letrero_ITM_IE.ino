// Programa para mostrar el catalogo de las animaciones MD_PAROLA 

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Se define en numero de dispositivos que nosotros tenemos 
#define  MAX_DEVICES 8
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

// Conexión Hardware SPI 
MD_Parola P = MD_Parola(CS_PIN, MAX_DEVICES);

#define ARRAY_SIZE(x)  (sizeof(x)/sizeof(x[0]))

// Datos globales
typedef struct
{
  textEffect_t  effect;   // text effect to display
  char *        psz;      // text string nul terminated
  uint16_t      speed;    // speed multiplier of library default
  uint16_t      pause;    // pause multiplier for library default
} sCatalog;

sCatalog  catalog[] =
{

  { PA_SCROLL_LEFT, "INSTITUTO  TECNOLOGICO  DE  MORELIA", 5, 1 },
  { PA_FADE, "INGENIERIA", 9, 5 },
  { PA_FADE, "ELECTRICA", 9, 5 }

};


void setup(void)
{
  P.begin();
  P.setInvert(false);

  for (uint8_t i = 0; i < ARRAY_SIZE(catalog); i++)
  {
    catalog[i].speed *= P.getSpeed();
    catalog[i].pause *= 0;
  }
}

void loop(void)
{
  for (uint8_t j = 0; j < 3; j++)
  {
    textPosition_t  just;

    for (uint8_t i = 0; i < ARRAY_SIZE(catalog); i++)
    {
      P.displayText(catalog[i].psz, PA_CENTER, catalog[i].speed, catalog[i].pause, catalog[i].effect, catalog[i].effect);

      while (!P.displayAnimate()); 
      // animates and returns true when an animation is completed

      delay(catalog[i].pause);
    }
  }
}
