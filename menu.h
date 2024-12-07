#ifndef MENU_H
#define MENU_H

int verif(bouton bouton, int coord_x, int coord_y);

void cree_bouton(bouton *bouton, char* message, int x, int y, MLV_Font *police);

void afficher_text(bouton bouton , MLV_Font *police);

void menu(bouton t_bouton_menu[4]);

void menu_save(bouton t_bouton_save[5]);

int charger_save(char *nom, joueur *j, grille *gr, c_poyo tpoyo[4], c_poyo * ptmp);

int save_partie(char *nom, joueur *jr, grille *gr, c_poyo tpoyo[4], c_poyo *ptmp);

int ecrasement_save();

void gestion_save_pause(bouton t_bouton_save[5], joueur *j, grille *gr, c_poyo tpoyo[4], c_poyo *ptmp);

void menu_score(bouton *retour);

void menu_pause(bouton t_bouton_pause[3]);

int clic_bouton(bouton t_bouton[], int longueur);

void fonctionnement();

#endif
