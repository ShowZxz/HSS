# HSS (partie Développement)

HighScoreSystem
Ce projet comprend quatre programmes développés sous Qt Creator version 6_5_3 MinGW. Chacun de ces programmes joue un rôle spécifique dans la gestion et l'affichage des scores de l'utilisateurs dans  l'environnement de Pinuppoper.
il fonctionne qu'avec les resolutions suivantes
- 1280 x 720
- 1920 x 1080
Veuillez mettre l'ecran ou vous souhaiter affiché dans une des deux résolution sur windows il est préférable d'avoir un Topper pour l'affichage des scores

## Prérequis
Qt Creator version 6_5_3 avec la chaîne d'outils MinGW.
Les DLLs pour la connexion a la base de données qui se trouve dans HSS/Extra/*les_dll
les DLLs sont a mettre dans dans le build du projet Score record et Highscore
PinupPoper https://www.nailbuster.com/wikipinup/doku.php?id=start
VisualPinballX
Un écran de type topper configurer dans Windows a la résolution 1280 x 720
Compte sur [PinemHi](http://www.pinemhi.com/) version 3.6.2

# 1. Config (partie Développement)

Le programme Config permet de fournir à l'utilisateur  :

D'avoir une interface graphique pour la configuration de l'application HighscoreSystem
De sélectionner l'écran sur lequel il souhaite afficher l'application.
D'entrer son pseudo et son code pour s'identifier.
S'inscrire via un bouton si l'utilisateur n'a pas encore de compte, il sera redirigé vers le site internet pour l'inscription.
Bouton test pour vérifier si le bonne écran a été selctionné.
Les informations écrite sur l'interface sera stocké a l'aide d'un bouton SAVE qui enregistrera dans le fichier Config/Setup.ini

### Exemple du fichier Setup.ini:

```Setup.ini
	[USER]
	Username=Me
	Password=mypassword
	
	[SCREEN]
	Display=2
	SerialNumber=000000000000
	Manufacturer=CVT
	Model=HDMI
	
	[PATH]
	Leaderboard=PINemHi/PINemHi LeaderBoard/TOP10_Personal/
	
	[SCALE]
	Size_screen=1280 x 720
```
### Explication du fichier Setup.ini
- Le groupe [User] permet au programme Highscore de récuperer les information pour le login de l'utlisateur
- Le groupe [SCREEN] permet au programme Highscore d'identifier le bon écran a affiché l'application
- Le groupe [Path] permet au programme Highscore d'avoir le chemin par Défault pour la lecture des scores
- Le groupe [Scale] permet au programme Highscore d'avoir la résolution afin de placer les labels au bon endroit

### Image Config.exe

![Image_Alt](https://github.com/ShowZxz/HSS/blob/7a31187895353a5f8fb379d05fa6232c5794faaf/image/uiconfig.png)

# 2. Front
Le programme Front est une interface visuelle qui permet de naviguer dans les jeux tout en affichant le programme Highscore. Il sert à fournir une expérience utilisateur fluide en matière de navigation dans PinuPoper.
![Image_Alt](https://github.com/ShowZxz/HSS/blob/83159ad21d5fa160c30deed3255d78cf49ca25eb/image/Score3.png)

### Explication du programme Front
- Le programme Front va s'affiché une fois la premiére partie sera faite il restera affiché pendant la navigation sur PinupPopperMenu
- Il dispose d'un thread qui vérifie si le programme PinupMenuSetup est fermé c'est a dire que quand PinupPopperMenu se ferme Front se ferme par la suite
- Sans oublier qui lit le fichier Config/Setup.ini pour pouvoir affiché l'application sur le bon écran

# 3. Highscore
Le programme Highscore affiche :

Les scores de l'utilisateur.
Le top 1 des scores mondiaux.
celui qui est devant et derrière lui
Il permet à l'utilisateur de suivre ses performances ainsi que celles des autres joueurs.

### Explication du programme Highscore
Ordre chronologique des évenement
- Le programme va lire le fichier Config/Setup.ini pour récuperer les information sur l'utilisateur et l'écran
- Effectuer une vérification du login de l'utilisateur
- Vérification de l'argument passé par pinupPopper (voir Explication )
- Récupération du titre via le nom de la rom passé en argument avec la lecture du fichier Config/Rom.ini qui permet de traduire le nom de la rom au titre concerné
- Verification si le jeu est supporté par nôtre system
- Fermeture de l'application Front.exe ( pour en place HighscoreSystem)
- Execution des requete SQL pour : Le score de l'utilisateur, le top 1 sur ce jeu ,qui est devant + son score et qui est derriere lui + son score.
- Setup de l'écrans + déplacemnt de l'application vers l'écran selon les informatiuon récuperer precedement dans le fichier Config/Setup.ini
- Mise en place des labels selon la résolution
- Affecter les labels avec les informations récolté
- Affichage de l'application
- Lancement d'un thread qui permet de savoir quand l'utilisateur a finit une partie pour stocké provisoirement dans le fichier Score/Info.ini les information suivante: nom du jeu qu'il a joué,son pseudo, le chemin pour la lecture du score
- Thread : le thread permet aussi executer front afin de donner un visuel au retour de la navigation et executer Score.exe pour enrgistrer le score dans la BDD

### Plus d'info sur Highscore 

j'utilise qui Pinemhi qui stocke les scores a l'adresse suivante : 
```Info.ini
	Leaderboard=PINemHi/PINemHi LeaderBoard/TOP10_Personal/
```
La lecture des scores ce fait sur la BDD.

#### Comment savoir sur quel jeu l'utilisateur joue ?
J'utilise le Lauch script de Pinuppoper qui execute Highscore.exe en passant comme argument le nom de la ROM 

```Launch Script
	cd /d "C:\HighScoreSystem"
	START "" "C:\HighScoreSystem\Highscore.exe" "[?ROM?]"
	cd /d "[DIREMU]"
```
Voir "Explication pour la configuration de PinupPopperSetup" pour affiché [?ROM?]


# 4. Score
Le programme Score enregistre le score d'un utilisateur à la fin d'une session de jeu. Il s'intègre avec PinemHi, un outil qui génère un fichier contenant les scores

### Explication du programme Score
Score.exe sera éxecuté par Highscore a la fin d'une partie
une fois score.exe sera en cours d'execution il va recuperer les valeurs stocké dans le fichier Score/Info.ini
Exemple du fichier Info.ini
```Info.ini
	[Info]
	Path=PINemHi/PINemHi LeaderBoard/TOP10_Personal/afbm.113b.txt
	Table=Attack From Mars
	Username=user
```
- Score.exe va verifier si le jeu existe
- il va lancé un timer qui va lire 5 fois le fichier ou le score est stocké grace au chemin recuperé dans le fichier.ini puis a la fin du timer on enregistre le score dans la BDD
- Le script ce lance en tache de fond il n'y a pas d'interface graphique


# Installation de l'environnement sur QTCreator
Clonez le dépôt depuis GitHub :
bash
Copier le code
```git code
git clone (https://github.com/ShowZxz/HSS.git)
```

- Ouvrez le projet dans Qt Creator pour chaque programme independemment (Score,Lecture score,Config,Highscore).
- Ouvrez le fichier .pro pour chaque projet et configuré le chemin que vous souhaité
- Configurez le projet pour la chaîne d'outils MinGW.
- Compilez et exécutez les programmes depuis l'IDE.

### Test programme
Config : à lancer avant toute autre application pour configurer l'interface et s'authentifier.
Front : utilisé pour montrer un visuel durant la navigation dans PinupPopper .
Highscore : permet de consulter les scores.
Score : s'exécute après une session de jeu pour enregistrer les résultats.
Vous pouvez crée un compte sur pinemhi pour faire les test pour la lecture des fichiers http://www.pinemhi.com/
Pour lancer HighscoreSystem il faut copier ce code dans le launch script de PinupPopper (VisualpinballX)

				cd /d "C:\HighScoreSystem"
				START "" "C:\HighScoreSystem\Highscore.exe" "[?ROM?]" 
				cd /d "[DIREMU]"

# Comment tester les programmes
### Config:
Pour tester Config il suffit juste d'executer le programme depuis L'IDE
### Highscore
C'est plus compliqué car il prends en compte des valeurs precise pour le bon fonctionnement des l'applications vous pouvez remplacer les valeurs par des valeur fictives comme :
```code
	QString rom = "afm_113b"
	QString gameName = "AC-DC";
```
#### Mettre en commentaire si vous passez pas d'argument
```code comm
	/* if (argc < 2){
        QMessageBox::critical(nullptr, "Highscore System Error", "No argument, verify the pinup lauch script use [?ROM?] read the Read Me for more information");
        return 1;
    } */
```

# Explication pour la configuration de PinupPopperSetup 
### Allez dans Games Manager
![Image_Alt](https://github.com/ShowZxz/HSS/blob/fbbec19bdf063000a7970ff5e65c9df2cad52fa7/image/Menu%201.png)
### Allez dans Import pour ajouter les informations de la table une les infos ajouter vous allez voir dans la section rom quel sera remplis
![Image_Alt](https://github.com/ShowZxz/HSS/blob/fbbec19bdf063000a7970ff5e65c9df2cad52fa7/image/import%20rolm.png)
### Allez dans Popper Setup / Emulators / VisualPinball X /Lauch Setup
![Image_Alt](https://github.com/ShowZxz/HSS/blob/fbbec19bdf063000a7970ff5e65c9df2cad52fa7/image/Launch%20setup.png)
### Copié le code suivant dans le Lauch Script :
```code rom
	cd /d "C:\HighScoreSystem"
	START "" "C:\HighScoreSystem\Highscore.exe" "[?ROM?]" 
	cd /d "[DIREMU]"
```
![Image_Alt](https://github.com/ShowZxz/HSS/blob/fbbec19bdf063000a7970ff5e65c9df2cad52fa7/image/rom.png)
Maitenant vous pouvez fournir l'argument rom a Highscore.exe


# Comment tester les applications dans un environnement réel
- Vous allez devoir créer un répertoire dans le disque "C:/HighscoreSystem" et mettre vos .exe dans celui ci 
- Allez dans le répertoire "C:\Qt\6.5.3\mingw_64\bin" et ouvrir un powershell
- Dans le powershell tapez :
  ```powershell code
  	.\windeployqt.exe "C:\HighScoreSystem\Highscore.exe"
  	.\windeployqt.exe "C:\HighScoreSystem\Front.exe"
  	.\windeployqt.exe "C:\HighScoreSystem\Score.exe"
  	.\windeployqt.exe "C:\HighScoreSystem\Config.exe"
  ```
  - Dans Structure/HighscoreSystem vous avez la structure du dossier pour le déploiment de l'application  
  Une fois vos application déployé lancé PinuppoperMenu est joué une table
# Pinemhi Configuration et Fonctionnement avec HSS
Pour lancer le script des scores automatiquement j'ai fais un petit script rapide qui lance pinemhi.rom.monitor au démarrage de l'ordinateur
- 1 Ouvrir l'explorateur de fichier, allez dans la barre de recherche et copié ce code là
```shell
	shell:startup
```
- 2 Coller le shortcut pinemhi dans le dossier démarrer \Start Menu\Programs\Startup
- 3 Allez sur le shorcut et mettre éxecution en tant administrateur
- 4 Creer un fichier dans le même dossier demarrage un .bat Creer un fichier dans le même dossier demarrage.bat

### Fonctionnement avec HSS
Une fois que pinemhi_rom_monitor est lancé automatiquement dés que vous allez jouer une table Pinemhi va génerer le fichier de scores correspondant a la table dans le dossier C:\HighScoreSystem\PINemHi\PINemHi LeaderBoard\TOP10_Personal\nom_rom.txt
Score.exe va lire le fichier de score correspondant au dernier jeu que l'utilisateur a joué grace a l'argument passé par PinupPopper
# Note de fin
Le programme HSS n'a pas un objectif a but lucratif mais a fournir une meilleur experience a la Communauté de VisualPinball a tout public.
Le code est mis a disposition a fin que la communauté puisse améliorer l'application et benificier du meilleur expérience de jeu.

# Build du programme
Vous trouverez l'installateur du programme sur le site internet https://highscoresystem.com/

# Installateur
