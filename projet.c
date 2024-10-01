#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// structure d'un contact
struct contact {
    char nom[50];
    char numero[20];
    char email[50];
    char id[8];};

// tableau de contacts et nombre de contacts
struct contact contacts[100];
int nb_contacts = 0;
char id_table[10000][8];
int conteur_id = 0;
int i;

// les couleurs
const char *reset = "\033[0m";
const char *vert = "\033[32m";
const char *rouge = "\033[31m";
const char *jaune = "\033[33m";

// la fonction qui verifier le nom 
int nom_verifier(char *nom){

        // Vérification de la longueur de la chaîne saisie pour le nom
    if (strlen(nom) >= 100) {
        printf("%sLe nom est trop long.%s\n",rouge,reset);
        return 0;}
    
    // vérification que le nom contien des lettres
    for (int i = 0; nom[i] != '\0'; i++) {
        if (!isalpha(nom[i]) && nom[i] != ' ') {
            printf("%sle nom ne doit contenir que des lettres et des espaces.%s\n",rouge,reset);
            return 0;}
            }
        return 1;
        }

// la fonction qui verifier le numero de telephone
int numero_valide(const char *numero) {
    int longueur = strlen(numero);

    // Vérifier la longueur
    if (longueur != 10) {
        return 0;}

    // Vérifier les deux premiers chiffres
    if (numero[0] != '0' || (numero[1] != '6' && numero[1] != '7')) {
        return 0;}

    // Vérifier que tous les caractères sont des chiffres
    for (int i = 0; i < longueur; i++) {
        if (numero[i] < '0' || numero[i] > '9') {
            return 0;}}
    
    // Vérifier si déja utiliser ou non
    for (int i = 0; i < nb_contacts; i++) {
        if (strcmp(contacts[i].numero, numero) == 0 ) {
            printf("%sle numero existe deja :%s\n",rouge,reset);
            return 0;} // Le numéro ou l'email existe déjà
    }
    return 1;}

// la fonction qui generer des id
char *generer_id() {
    char *idi = malloc(8);
    int i;
    authre:
    srand(time(NULL));
    int num = rand() % 900000 + 100000; 
    sprintf(idi, "YC%06d", num);
    for (i = 0; i <= conteur_id;i++){
        if (!strcmp(id_table[conteur_id], idi)){
            free(idi);
            goto authre;}}
    strcpy(id_table[conteur_id],idi);
    conteur_id++; 
    return idi;  
}

//1.Ajouter un contact
void ajouter_contact() {
    struct contact nouveau_contact;

    // Vérifier si le tableau est plein
    if (nb_contacts >= 100) {
        printf("%sLe carnet d adresses est plein.%s\n",rouge,reset);
        return;}

    debutnom:
    // Demander les informations à l'utilisateur
    // Ajouter le nom
    getchar();
    {printf("entrer le nom : ");
    fgets(nouveau_contact.nom,100,stdin);
    nouveau_contact.nom[strcspn(nouveau_contact.nom, "\n")] = '\0';}
    //vérification de nom
    if (!nom_verifier(nouveau_contact.nom)){
        goto debutnom;
    }

    debutnumero:
    //ajouter le numero de telephone
    {printf("entrer le numero de telephone : ");
    scanf("%s",&nouveau_contact.numero);
    nouveau_contact.numero[strcspn(nouveau_contact.numero, "\n")] = '\0';}
     
     //vérification de numero de telephone
    if (!numero_valide(nouveau_contact.numero)){
        printf("%sce nomero n\'est pas validie \n%s",rouge,reset);
        goto debutnumero;
    }

    // ajouter l adresse email
    {printf("entrer l\'adresse email : ");
    scanf("%s",&nouveau_contact.email);
    nouveau_contact.email[strcspn(nouveau_contact.email, "\n")] = '\0';}

    // Ajouter un id au nouveau contact
    strcpy(nouveau_contact.id,generer_id());

    // Ajouter le nouveau contact au tableau
    {contacts[nb_contacts] = nouveau_contact;
    nb_contacts++;}

    printf("%sContact ajoute avec succes !%s\n",vert,reset);
}

//2.modifier un contact
void modifier_contact() {
    char nom_a_modifier[50];
    char nouveau_numero[20];
    char nouveau_email[50];

    // Vérifier si le tableau contacts est nul
    if (contacts == NULL) {
        printf("%sErreur : le tableau de contacts est null.%s\n",rouge,reset);
        return;
    }
    
    debutmodi:
    //ecrit le nom à modifier
    getchar();
    {printf(" ecrit le nom a modifier :");
    fgets(nom_a_modifier, sizeof(nom_a_modifier), stdin);
    nom_a_modifier[strcspn(nom_a_modifier, "\n")] = '\0';}

    //verifier le nom à supprimer
    if (!nom_verifier(nom_a_modifier)){
        goto debutmodi;
    }

    // Rechercher le contact
    {int i;
    for (i = 0; i < nb_contacts; i++) {
        if (strcmp(contacts[i].nom, nom_a_modifier) == 0) {
            break;}}

    if (i == nb_contacts) {
        printf("%sContact non trouve.%s\n",rouge,reset);
        return;}}
    
    debutonum:
    // Modifier le numero 
    {printf("entrer le nouveau numero de telephone : ");
    scanf("%s", nouveau_numero);}
    
    // vérifier le nouveau numero
    if (numero_valide(nouveau_numero)==0){
        printf("%sce nomero n est pas validie .%s\n",rouge,reset);
        return;}
    strcpy(contacts[i].numero, nouveau_numero);
    
    // Modifier l email
    {printf("entrer la nouvelle adresse email : ");
    scanf("%s", nouveau_email);
    strcpy(contacts[i].email, nouveau_email);}

    printf("%sContact modifié avec succès.%s\n",vert,reset);}

// 3.supprimer un Contact
void supprimer_contact() {
    char nom_a_supprimer[50];
    int i, j;

    // Vérifier si le tableau contacts est nul
    if (contacts == NULL) {
        printf("%sErreur : le tableau de contacts est null.%s\n",rouge,reset);
        return;
    }
    
    //ecrit le nom à supprimer
    debutsupp:
    getchar();
    {printf(" ecrit le nom a supprimer :\n");
    fgets(nom_a_supprimer, sizeof(nom_a_supprimer), stdin);
    nom_a_supprimer[strcspn(nom_a_supprimer, "\n")] = '\0';}

    //verifier le nom à supprimer
    if (!nom_verifier(nom_a_supprimer)){
        goto debutsupp;
    }

    // Rechercher l'indice du contact à supprimer
    for (i = 0; i < nb_contacts; i++) {
        if (strcmp(contacts[i].nom, nom_a_supprimer) == 0) {
            break;}}
    
    //cas non trouvé
    if (i == nb_contacts) {
        printf("%scontact non trouve.%s\n",rouge,reset);
        return;}

    // Décaler tous les éléments 
    for (j = i; j < nb_contacts - 1; j++) {
        contacts[j] = contacts[j + 1];
    }

    // Décrémenter le nombre de contacts
    (nb_contacts)--;

    printf("contact supprime avec succes.\n");
}

//4.afficher Tous les Contacts
void afficher_contacts() {

     // Vérifier si le tableau contacts est nul
    if (contacts == NULL) {
    printf("%serreur : le tableau de contacts est null.%s\n",rouge,reset);
    return;}

    //affichage de tableau
    {printf("                           %sListe des contacts :%s\n",jaune,reset);
    printf("+----------+----------------------+-----------------+----------------------------------+\n");
    printf("|   %sID%s     |         %sName%s         |   %sPhone Number%s  |              %sEmail%s               |\n",jaune,reset,jaune,reset,jaune,reset,jaune,reset);
    printf("+----------+----------------------+-----------------+----------------------------------+\n");
    for (int i = 0; i < nb_contacts; i++) {
        printf("| %s | %-20s | %-15s | %-32s |\n",contacts[i].id,contacts[i].nom,contacts[i].numero,contacts[i].email);}
    printf("+----------+----------------------+-----------------+----------------------------------+\n");}}

//5.rechercher un Contact
void rechercher_contact( ) {
    char nom_a_rechercher[50];
    int i;
    int trouve = 0;

    // Vérifier si le tableau contacts est nul
    if (contacts == NULL) {
        printf("%sErreur : le tableau de contacts est null.%s\n",rouge,reset);
        return;
    }

    //ecrit le nom à rechercher
    getchar();
    {printf("ecrit le nom a rechercher :");
    fgets(nom_a_rechercher, sizeof(nom_a_rechercher), stdin);
    nom_a_rechercher[strcspn(nom_a_rechercher, "\n")] = '\0';}
    
    //rechercher sur le contact
    for (i = 0; i < nb_contacts; i++) {
        if (!strcmp(contacts[i].nom, nom_a_rechercher)) {
            printf("Contact trouvé :\n");
            printf("ID : %s\n", contacts[i].id);
            printf("Nom : %s\n", contacts[i].nom);
            printf("Numéro : %s\n", contacts[i].numero);
            printf("Email : %s\n", contacts[i].email);
            trouve = 1;
            break;
        }
    }
    
    //si le contact non trouvé
    if (!trouve) {
        printf("%sContact non trouve.%s\n",rouge,reset);}
}

int main() {
    int choix;
    do {
        printf("\n%s**********Menu*********%s\n",jaune,reset);
        printf("1. ajouter un contact\n");
        printf("2. modifier un contact\n");
        printf("3. supprimer un contact\n");
        printf("4. afficher tous les contacts\n");
        printf("5. rechercher un contact\n" );
        printf("6. quitter\n");
        printf("votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouter_contact();
                break;
            case 2:
                modifier_contact();
                break;
            case 3:
                supprimer_contact();
                break;
            case 4:
                afficher_contacts();
                break;
            case 5:
                rechercher_contact();
                break;
            case 6:
                printf("au revoir!\n");
                break;
            default:
                printf("%sChoix invalide.%s\n", rouge, reset);
        }
    } while (choix != 5);

    return 0;
}