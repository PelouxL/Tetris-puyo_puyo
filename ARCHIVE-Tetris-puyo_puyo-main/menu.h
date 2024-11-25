#ifndef MENU_H
#define MENU_H

int verif(bouton bouton, int coord_x, int coord_y);

void cree_bouton(bouton *bouton, char* message, int x, int y, MLV_Font *police);

void afficher_text(bouton bouton , MLV_Font *police);

void menu(bouton *t_bouton_menu[]);

void menu_save(bouton *t_bouton_save[], bouton *t_bouton_retour);

int charger_save(char *nom, tsave t);

int save_partie(char *nom, tsave t, int n);

void menu_score(bouton *t_bouton_retour);

int clic_bouton(bouton *t_bouton[], int longueur);

void menu_jeu();

#endif