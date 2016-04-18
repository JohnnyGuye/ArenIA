# ArenIA
Un jeu avec des robots dont l'IA est codée par le joueur.

# RoadMap

► GUI : Halte au terminal, bonjour le jeu ! - CHECK

► Prototype fonctionnel : Deux IAs qui s'affrontent et rien de plus

► Prototype teamplay : Plus de 2 robots et des équipes

► Objectifs : DeathMatch oui, mais aussi King of Hill, CTF, etc...

► Tutoriel : C'est parti pour apprendre à coder !

► Mode histoire : Des IAs oui, mais des IAs badasses !

► Online !

# Comment utiliser git dans le terminal :

récupérer le dépot sur son PC :
	git clone https://github.com/JohnnyGuye/ArenIA.git

ajouter un fichier :
une fois le fichier créer,
	git add <nomFichier>
	
supprimer un fichier :
	git rm <nomFichier>
	
valider des modifications :
	git commit -a -m "Message de commit"
	
envoyer ses modifications :
	git push
	
récupérer les modifications :
	git pull
	
récupérer des informations sur l'état des fichiers :
	git status

revenir à ancien commit
en gardant la copie locale (#le nombre de retour en arrière jusqu'au bon commit)
	git reset --mixed HEAD^# 
Il a deux autres options mais la première est agréablement inutile, et la deuxième terriblement dangereuse

# Liste des dépendendances d'un projet Ogre

J'ai nommé ma variable d'environnement OGRE_HOME.
Du coup en utilisant ce nom de variable et en le mettant à jour pour votre PC, les bons chemins se font tout seuls pour MSVS2010
Normalement pour utiliser les librairies il suffit que chacun les installe sur son PC et mette à jour les variables d'environnement. 
On utilise Gorilla pour le GUI.
pour OGRE : faut DL sur leur site la version précompilée de 1.9 pour MSVS2010 et normalement ça se fait tout seul.

ELLES SONT LA A TITRE INDICATIF, TOUT EST CONFIGURE DANS LE PROJET, N'Y TOUCHEZ PAS ! C'est juste pour pouvoir vérifier au cas où y a un pb de compilation.

• Fichier d'en-tête  
Pour Ogre :  
$(OgreDir)\include  
$(OgreDir)\include\OGRE  

Pour les Inputs/Outputs  
$(OgreDir)\include\OIS  

Pour les Overlays :  
$(OgreDir)\include\OGRE\Overlay  

Pour boost (ça dépend de si vous prenez boost seul ou dans le package Ogre)  
$(OgreDir)\include\boost   

• Libs
$(OgreDir)\boost\lib  
$(OgreDir)\lib\$(Configuration)  

• EDL  
- lib debug    
OgreMain_d.lib  
OIS_d.lib  
OgreOverlay_d.lib  

- lib release  
OgreMain.lib  
OIS.lib  
OgreOverlay.lib  

# Features:

- Maps  
On peut utiliser Tiled pour créer des maps, il suffit ensuite de les ajouter dans le dossier maps pour qu'elle soit chargeables.
Il faut utiliser le tileset fourni.
http://www.mapeditor.org/
Les murs en 2D ont une corrélation directe avec l'affichage 3D.
Objets :  
- Start : créer un robot dans la case

# Répartition des tâches

- Moteur de jeu : Johnny  
- Lua Binding : Clément  
- Son : Clément/Johnny  
- Robot : Alp/Simon  
- GFX-Interface : Johnny/Samory  
- Utilitaires : Alltogether  


#Préceptes et guide de style
- Dans les fichiers tout est en anglais ! 
- Les méthodes commencent par une minuscule  
- Les attributs terminent par un '_' ou commencent par un 'm'. En tout cas, on change pas de style dans une classe ou ses filles et on laisse bien les attributs plus visibles que les autres  
- Pas de classes moitié inline moitié .cpp. Soit on fait tout en inline (exemple GameTimeDuration et GameTimeMoment) soit on fait tout dans un .cpp. Mais on ne mélange pas (lisibilité et puissance du code)  
- Ajouter dans l'en-tête son nom pour les plus gros participants à chaque fichiers. Ca sera plus simple pour déboguer ou discuter d'une faute de conception.  
- Insultez mon anglais, je ne vous en voudrait pas mais dites moi quand vous corrigez comme ça j'aprends !  
- Ne pas oublier de mettre un joli résumé du fonctionnement de la classe, c'est chiant pour les autres de devoir lire tout le code d'une classe quand on a besoin que d'une ou deux méthodes  
- Toujours privilégier du CODE MAINTENABLE au code optimisé as fuck  

Diagramme de classe : https://drive.google.com/file/d/0B7ykpBf0E6UZa0pPaDYyOVpzUVk/view?usp=sharing
