#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "grille.h"
#include "pieces.h"
#include "ini_poyo.h"
#include "jeu.h"
#include "affichage_mlv.h"
#include "destruction.h"

int verif(bouton bouton, int coord_x, int coord_y){
    if((coord_x > bouton.x && coord_x < bouton.x + bouton.largeur) && (coord_y > bouton.y && coord_y < bouton.y + bouton.hauteur)){
        return 1;
    }
    return 0;
}



void cree_bouton(bouton *bouton, char* message, int x, int y, MLV_Font *police){
    int largeur, hauteur;
    MLV_get_size_of_adapted_text_box_with_font(message, police, 10, &largeur, &hauteur);
    bouton -> x = x - largeur/2;
    bouton -> y = y;
    bouton -> hauteur = hauteur;
    bouton -> largeur = largeur;
    strcpy(bouton -> txt, message);    
}

void afficher_text(bouton bouton , MLV_Font *police){
    MLV_draw_adapted_text_box_with_font(bouton.x, bouton.y, bouton.txt, police, 10, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
}



void menu(bouton *t_bouton_menu[]){
    char *nom_bouton[4] = {"start", "save", "score", "exit"};
    int i, text_width, text_height;
    MLV_Font *police;

    MLV_clear_window(MLV_COLOR_BLACK);

    police = MLV_load_font("squaretype_b.ttf", 90);

    MLV_get_size_of_adapted_text_box_with_font("puyo puyo", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, LY / 10 - (text_height / 2), "puyo puyo", police, 10, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    for( i = 0 ; i < 4 ; i++ ){
        cree_bouton(t_bouton_menu[i], nom_bouton[i], LX / 2, 200 + LY / 7 * i, police);
        afficher_text(*t_bouton_menu[i], police);
    }
    MLV_actualise_window();
}



void menu_save(bouton *t_bouton_save[], bouton *t_bouton_retour){
    MLV_Font *police_70, *police_50, *police_30;
    char *nom_bouton_save[4] = {"save_1", "save_2", "save_3", "Retour"/* (renverra 4) */};
    int i, text_width, text_height;
        
    MLV_clear_window(MLV_COLOR_BLACK);

    police_70 = MLV_load_font("squaretype_b.ttf", 70); /* pour titre */
    police_50 = MLV_load_font("squaretype_b.ttf", 50); /* pour save */
    police_30 = MLV_load_font("squaretype_b.ttf", 30); /* pour retour */

    cree_bouton(t_bouton_retour, "Retour", LX / 6 - X, 1, police_30);

    /* Titre */
    MLV_get_size_of_adapted_text_box_with_font("save", police_70, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, LY / 10 - (text_height / 2), "save", police_70, 10, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    /* bouton save */
    for( i = 0 ; i < 3 ; i++){
        cree_bouton(t_bouton_save[i], nom_bouton_save[i], LX / 2, LY / 3 + X * i, police_50);
        afficher_text(*t_bouton_save[i], police_50);
    }

    afficher_text(*t_bouton_retour, police_30);
    
    MLV_actualise_window();
}


int charger_save(char *nom, save *sauvegarde){
    FILE * f;
    int i, j;
    if((f = fopen(nom, "r")) == NULL){
        printf("Erreur ouverture f \n");
        return -1;
    }

    if (fscanf(f, "%s", sauvegarde -> j.pseudo) != 1){
        printf("Erreur : lecture pseudo \n");
        fclose(f);
        return -1;
    }

    if (fscanf(f, "%d", &sauvegarde -> j.score) != 1){
        printf("Erreur : lecture score \n");
        fclose(f);
        return -1;
    }
    
    if(fscanf(f, "%d %d %d", &sauvegarde -> gr.n, &sauvegarde -> gr.m, &sauvegarde -> niveau) != 3){
        printf("Erreur lecture dimension grille \n");
        fclose(f);
        return -1;
    }

    for( i = 0; i < sauvegarde -> gr.n; i++){
        for( j = 0; j < sauvegarde -> gr.m; j++){
            if(fscanf(f, "%d,", &sauvegarde -> gr.mat[i][j]) != 1){
                printf("Erreur lecture case \n");
                fclose(f);
                return 0;
            }
        }
    }
    fclose(f);
    return 1;
}

int save_partie(char *nom, save *partie){
    FILE *f;
    int i, j;
    if((f = fopen(nom, "w")) == NULL){
        return -1;
    }

    fprintf(f, "%s\n", partie -> j.pseudo);
    fprintf(f, "%d\n", partie -> j.score);

    fprintf(f, "%d %d %d\n", partie -> gr.n, partie -> gr.m, partie -> gr.niveau);

    for( i = 0; i < partie -> gr.n; i++){
        for( j = 0; j < partie -> gr.m; j++){
            fprintf(f, "%d ", partie -> gr.mat[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
    return 1;
}


void menu_score(bouton *t_bouton_retour){
    MLV_Font *police_70, *police_40, *police_30;
    bouton ST1, ND2, RD3, TH4, TH5, TH6, TH7, TH8, TH9, TH10;
    bouton *t_bouton_score[10]; /* = {&ST1, &ND2, &RD3, &TH4, &TH5, &TH6, &TH7, &TH8, &TH9, &TH10}; */
    char *nom_bouton_score[10] = {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th"};
    int i, text_width, text_height;

    MLV_clear_window(MLV_COLOR_BLACK);

    /* Police */
    police_70 = MLV_load_font("squaretype_b.ttf", 70); /* pour titre */
    police_40 = MLV_load_font("squaretype_b.ttf", 40); /* pour numéro score */
    police_30 = MLV_load_font("squaretype_b.ttf", 30); /* pour retour */

    cree_bouton(t_bouton_retour, "Retour", LX / 6 - X, 1, police_30);

    /* Titre */
    MLV_get_size_of_adapted_text_box_with_font("meilleurs scores", police_70, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, LY / 10 - (text_height / 2), "meilleurs scores", police_70, 10, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    t_bouton_score[0] = &ST1;
    t_bouton_score[1] = &ND2;
    t_bouton_score[2] = &RD3;
    t_bouton_score[3] = &TH4;
    t_bouton_score[4] = &TH5;
    t_bouton_score[5] = &TH6;
    t_bouton_score[6] = &TH7;
    t_bouton_score[7] = &TH8;
    t_bouton_score[8] = &TH9;
    t_bouton_score[9] = &TH10;

    /* Numéro score */
    for( i = 0 ; i < 10 ; i++ ){
        cree_bouton(t_bouton_score[i], nom_bouton_score[i], LX / 5, 150 /* (150 pour descente du 1st) */ + LY / 14 * i/* (pour espaces entre le 1st et 10th )*/, police_40);
        afficher_text(*t_bouton_score[i], police_40);
    }

    afficher_text(*t_bouton_retour, police_30);
    
    MLV_actualise_window();
}



int clic_bouton(bouton *t_bouton[], int longueur){
    int i, s_x, s_y;

    while (1){
        if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED){
            MLV_get_mouse_position(&s_x, &s_y);
            for( i = 0 ; i < longueur ; i++ ){
                if(verif(*t_bouton[i], s_x, s_y) == 1){
                    while(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED);
                    printf("i = %d sx = %d sy = %d \n", i, s_x, s_y);
                    return i + 1;
                }
            }
        }
    }
}



void menu_jeu(){
    int b_pressed, s_pressed, r_pressed;
    bouton Start, Save, Score, Exit;
    bouton Save_1, Save_2, Save_3;
    bouton Retour_s, Retour_sc;
    bouton *t_bouton_menu[4]; /* = {&Start, &Save, &Score, &Exit}; */
    bouton *t_bouton_save[4]; /* = {&Save_1, &Save_2, &Save_3, &Retour_s}; */
    bouton *t_bouton_retour[2]; /* = {&Retour_s, &Retour_sc}; */
    MLV_Font *police;
    save sauvegarde; /* tableau de sauvegarde */
    int n = 10, m = 8;
    grille gr;
    joueur j;
    c_poyo tpoyo[4];
    
    MLV_create_window("Puyo", "puyo", LX, LY);
    police = MLV_load_font("squaretype_b.ttf", 60);

    t_bouton_menu[0] = &Start;
    t_bouton_menu[1] = &Save;
    t_bouton_menu[2] = &Score;
    t_bouton_menu[3] = &Exit;

    t_bouton_save[0] = &Save_1;
    t_bouton_save[1] = &Save_2;
    t_bouton_save[2] = &Save_3;
    t_bouton_save[3] = &Retour_s;

    t_bouton_retour[0] = &Retour_s;
    t_bouton_retour[1] = &Retour_sc;

    
    while(1){
        menu(t_bouton_menu);
        b_pressed = clic_bouton(t_bouton_menu, 4);
        switch(b_pressed){
        case 1:
            printf("Le jeu commence \n");
            gr = initialisation_grille(n,m);
            ini_poyo_chaine(tpoyo, 4);
            strcpy(j.pseudo, "Moi");
            j.score = 2;
            jeu(&gr, &j, tpoyo);
            break;
        case 2:
            printf("Menu save \n");
            menu_save(t_bouton_save, t_bouton_retour[0]);
            s_pressed = clic_bouton(t_bouton_save, 4);
            switch(s_pressed){
            case 1:
                printf("Save 1 lancée \n");
                if(charger_save("save.txt", &sauvegarde) == 1){
                    printf("sauvegarde chargée avec succès \n");
                    ini_poyo_chaine(tpoyo, 4);
                    gr = sauvegarde.gr;
                    j = sauvegarde.j;
                    jeu(&gr, &j, tpoyo);
                }
                else{
                    printf("La save est corrompue \n");
                }
                break;
            case 2:
                printf("Save 2 lancée \n");
                /* if(charger_save("save.txt", sauvegarde) == 0){ */
                /*     gr = initialisation_grille(n, m); */
                /*     j = sauvegarde[1].j; */
                /*     ini_poyo_chaine(tpoyo, 4); */
                /*     jeu(&gr, &j, tpoyo); */
                /* } */
                /* else{ */
                /*     printf("Erreur 2"); */
                /* } */
                break;
            case 3:
                printf("Save 3 lancée \n");
                /* if(charger_save("save.txt", sauvegarde) == 0){ */
                /*     gr = initialisation_grille(n, m); */
                /*     j = sauvegarde[2].j; */
                /*     ini_poyo_chaine(tpoyo, 4); */
                /*     jeu(&gr, &j, tpoyo); */
                /* } */
                /* else{ */
                /*     printf("Erreur 3"); */
                /* } */
                break;
            case 4:
                menu(t_bouton_menu);
                break;
            }
            break;
        case 3:
            menu_score(t_bouton_retour[1]);
            r_pressed = clic_bouton(t_bouton_retour, 1);
            if(r_pressed == 1){
                menu(t_bouton_menu);
            }
            break;
        case 4:
            printf("Vous avez quitté le jeu \n");
            MLV_free_window();
            exit(EXIT_SUCCESS);
            break;
        }
    }
    MLV_free_font(police);
    MLV_free_window();
    exit(EXIT_SUCCESS);
}