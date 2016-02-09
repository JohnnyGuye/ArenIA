# ArenIA
Un jeu avec des robots dont l'IA est codée par le joueur.


# Comment utiliser git sur linux :

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
	
# Liste des dépendendances d'un projet Ogre

• Fichier d'en-tête
Pour les fichiers d'Ogre :
$(OgreDir)\include
$(OgreDir)\include\OGRE

Pour les Inputs/Outpus
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

