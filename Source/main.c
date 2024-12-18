#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "menu.h"

int main(){
  srand(time(NULL));
  MLV_create_window("Puyo","puyo", LX, LY);
  fonctionnement();  
  MLV_free_window();
  exit(EXIT_SUCCESS);
}
