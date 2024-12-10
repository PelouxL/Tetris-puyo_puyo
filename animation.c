#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include "types.h"

int main(){
  MLV_Image* croix;
  MLV_Animation* animation;
  MLV_Image* images[3];
  MLV_Keyboard_button key;
  MLV_Animation_player *animation_player;
  const char* file_path_of_cross = "./animation/croix_anime1.png";
  int nb_frames, nb_layer, nb_channels, w, h, running = 1;

  MLV_create_window( "advanced - 9 animation", "animation", 900, 800 );
  
  croix = MLV_load_image(file_path_of_cross );
  if( croix == NULL ){
    fprintf(stderr, "erreur animation %s\n ",file_path_of_cross);
    exit(0);
  }
  
  nb_frames = 3;
  nb_layer = 1;
  nb_channels = 1;
  w = 16;
  h = 16;

  images[0] = MLV_copy_partial_image( croix, 0, 0, w, h );
  images[1] = MLV_copy_partial_image( croix, w, 0, w, h );
  images[2] = MLV_copy_partial_image( croix, 0, h, w, h );
  images[3] = MLV_copy_partial_image( croix, w, 0, w, h );

  animation = MLV_create_animation( nb_frames, nb_layer, nb_channels );

  MLV_add_frame_in_animation( images, NULL, 10, animation);
  MLV_add_frame_in_animation( images + 1, NULL, 10, animation);
  MLV_add_frame_in_animation( images + 2, NULL, 10, animation);

  
  animation_player = MLV_create_animation_player(animation);

  MLV_play_animation_player(animation_player);
  MLV_change_frame_rate(12);

  while( running ){
  
    if(MLV_get_event(&key, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL) != MLV_NONE) {
      if (key == MLV_KEYBOARD_ESCAPE) {
	running = 0;
      }
    }

    MLV_update_animation_player(animation_player);

    MLV_clear_window(MLV_COLOR_BLACK);

    MLV_draw_image_from_animation_player(animation_player, 0, 400, 300);

    MLV_actualise_window();

    MLV_delay_according_to_frame_rate();
  }
  MLV_free_window();
  exit(1);
}
