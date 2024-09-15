# HSS

Projet de gestion des scores de jeu
Ce projet comprend quatre programmes développés sous Qt Creator version 6_5_3 MinGW. Chacun de ces programmes joue un rôle spécifique dans la gestion et l'affichage des scores des utilisateurs dans un environnement de jeu.

#Prérequis
Qt Creator version 6_5_3 avec la chaîne d'outils MinGW.
Bibliothèques Qt nécessaires au bon fonctionnement de l'interface graphique.
Programmes
#1. Config
Le programme Config permet à l'utilisateur de :

Sélectionner l'écran sur lequel il souhaite afficher l'application.
Entrer un pseudo et un code pour s'identifier.
S'inscrire via un bouton si l'utilisateur n'a pas encore de compte.
#2. Front
Le programme Front est une interface visuelle qui permet de naviguer dans les jeux tout en affichant le programme Highscore. Il sert à fournir une expérience utilisateur fluide en matière de navigation.

#3. Highscore
Le programme Highscore affiche :

Les scores de l'utilisateur.
Le top 1 des scores mondiaux.
Il permet à l'utilisateur de suivre ses performances ainsi que celles des autres joueurs.

#4. Score
Le programme Score enregistre le score d'un utilisateur à la fin d'une session de jeu. Il s'intègre avec PinemHi, un outil qui génère un fichier contenant les scores pour une gestion et une consultation ultérieures.

Installation
Clonez le dépôt depuis GitHub :
bash
Copier le code
git clone https://github.com/votre-repo/projet-scores.git
Ouvrez le projet dans Qt Creator.
Configurez le projet pour la chaîne d'outils MinGW.
Compilez et exécutez les programmes depuis l'IDE.
Utilisation
Config : à lancer avant toute autre application pour configurer l'interface et s'authentifier.
Front : utilisé pour naviguer dans le menu de sélection des jeux.
Highscore : permet de consulter les meilleurs scores.
Score : s'exécute après une session de jeu pour enregistrer les résultats.
