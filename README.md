# HSS

HighScoreSystem
Ce projet comprend quatre programmes développés sous Qt Creator version 6_5_3 MinGW. Chacun de ces programmes joue un rôle spécifique dans la gestion et l'affichage des scores de l'utilisateurs dans  l'environnement de Pinuppoper.
il fonctionne qu'avec les resolutions suivantes
- 1280 x 720
- 1920 x 1080
Veuillez mettre l'ecran ou vous souhaiter affiché dans une des deux résolution sur windows il est préférable d'avoir un Topper pour l'affichage des scores

# Prérequis
Qt Creator version 6_5_3 avec la chaîne d'outils MinGW.
Les DLLs pour la connexion a la base de données qui se trouve dans HSS/Extra/*les_dll
les DLLs sont a mettre dans dans le build du projet Score record et Highscore
PinupPoper https://www.nailbuster.com/wikipinup/doku.php?id=start
VisualPinballX

# 1. Config

Le programme Config permet à l'utilisateur de :

D'avoir une interface graphique pour la configuration
Sélectionner l'écran sur lequel il souhaite afficher l'application.
Entrer son pseudo et son code pour s'identifier.
S'inscrire via un bouton si l'utilisateur n'a pas encore de compte.
Bouton test pour vérifier le bonne écran


# 2. Front
Le programme Front est une interface visuelle qui permet de naviguer dans les jeux tout en affichant le programme Highscore. Il sert à fournir une expérience utilisateur fluide en matière de navigation dans PinuPoper.

# 3. Highscore
Le programme Highscore affiche :

Les scores de l'utilisateur.
Le top 1 des scores mondiaux.
celui qui est devant et derrière lui
Il permet à l'utilisateur de suivre ses performances ainsi que celles des autres joueurs.

# 4. Score
Le programme Score enregistre le score d'un utilisateur à la fin d'une session de jeu. Il s'intègre avec PinemHi, un outil qui génère un fichier contenant les scores pour une gestion et une consultation ultérieures.

# Installation
Clonez le dépôt depuis GitHub :
bash
Copier le code
git clone (https://github.com/ShowZxz/HSS.git)
Ouvrez le projet dans Qt Creator.
Configurez le projet pour la chaîne d'outils MinGW.
Compilez et exécutez les programmes depuis l'IDE.
Utilisation
Config : à lancer avant toute autre application pour configurer l'interface et s'authentifier.
Front : utilisé pour montrer un visuel durant la navigation dans PinupPopper .
Highscore : permet de consulter les scores.
Score : s'exécute après une session de jeu pour enregistrer les résultats.
Vous pouvez crée un compte sur pinemhi pour faire les test pour la lecture des fichiers http://www.pinemhi.com/
Pour lancer HighscoreSystem il faut copier ce code dans le launch script de PinupPopper (VisualpinballX)
cd /d "C:\HighScoreSystem"
				START "" "C:\HighScoreSystem\Highscore.exe" "[?ROM?]" 
				cd /d "[DIREMU]"


# Comment HSS fonctionne
j'utilise le projet 
# Build du programme
Vous trouverez l'installateur du programme sur le site internet https://highscoresystem.com/
