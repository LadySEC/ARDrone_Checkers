Pour compiler : 
~/.../Embedded/Sources/Detect/Build/ cmake ..
~/.../Embedded/Sources/Detect/Build/ make

Pour lancer l'executable créé :
~/.../Embedded/Sources/Detect/Build/ ./Detect

Note 0 :
Quand on compilera ce code dans le drone il faudra enlever la compilation du main (on veut compiler que detect.h et detect.cpp).
=> dans le CMakeLists.txt : enlever "main.cpp


Note 1 :
J'ai mis un main pour montrer comment on utilise tout ça.
Le main : 
	On place dans "form" et "color" la forme et la couleur qu'on veut détecter
	Ouvre une cam
	utilise detect_tag
	retourne structure Position{found, Abscisse, Ordonnée}
	Si (found = 1) { printf (form_color, abs = x, ord = y) ; }
	

Note 2 :
Pour pouvoir afficher form et color (des std::string) il faut les convertir avec form.c_str() et color.c_str().


Note 3 :
La fonction detect peut prendre :
	comme form : "triangle", "circle", "rectangle"
	comme color : "red", "green", "blue"
