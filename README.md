# [EN] TweenGen
Inbetween frames generator for animation.

-- ABOUT --

TweenGen is a personnal inbetween frame generator to be used for animation projects. The program uses interpolation methods to calculate the coordinates of a point between two frames, and constructs an inbetween according to the armature of the object to be animated.

-- INSTALL --

You can get the source code by using the command ``git clone https://github.com/Lysandre-M/TweenGen.git`` in your shell.
Make sure that you get **all** the files, especially the sample images.
Before making the exe file, you'll have to install the MLV library if not already done. Check this link for more informations : http://www-igm.univ-mlv.fr/~boussica/mlv/api/English/html/index.html
After that, you can create the exe file by entering the command ``make`` in the root folder of the project.

If ``make`` doesn't work change the line 7 of the Makefile to ``CC = gcc`` and remove the line 4 of the main.c file.
(And if it still doesn't work please contact me at lysandre.macke@gmail.com)

-- USE --

This program isn't ready for use.

# [FR] TweenGen
Générateur d'images transitoires pour l'animation.

-- A PROPOS --

TweenGen est un générateur d'images personnel permettant de créer des images transitoires en animation. Le programme utilise des méthodes d'interpolation afin de calculer les coordonnées d'un point entre deux images, et construit l'image intermédiaire en prenant en compte l'armature/le squelette de l'objet qui doit être animé.

-- INSTALLATION --

Le code source du projet est accessible en tapant la commande ``git clone https://github.com/Lysandre-M/TweenGen.git`` dans votre terminal.
Vérifiez bien que vous avez récupéré **tous** les fichiers, notemment les images du dossier "sample".
Avant de pouvoir créer l'exécutable, il vous faudra installer la lib MLV si ce n'est pas déjà fait. Pour plus d'informations référez vous ici : http://www-igm.univ-mlv.fr/~boussica/mlv/api/French/html/index.html
Après ça, vous pouvez créer le .exe en entrant la commande ``make`` dans le dossier principal du projet.

Si ``make`` ne fonctionne pas, modifiez la ligne 7 du Makefile en ``CC = gcc`` et supprimez la ligne 4 du fichier main.c.
(Et si cela ne fonctionne toujours pas vous pouvez me contacter via l'adresse lysandre.macke@gmail.com)

-- UTILISATION --

Ce programme n'est pas prêt à être utilisé.
