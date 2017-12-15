# arduino-LED-MATRIX
Cirstoiu Andreea-Ioana
351
Documentatie proiect 1

-Jocul pe care intentionati sa-l faceti pe matrice
SpaceShips adaptare

-DESCRIEREA JOCULUI
    Jocul de fapt, presupune o nava(Ship) care se poate misca doar in stanga sau in dreapta, avand pozitie verticala fixata pe ultima linie a matricei de LED-uri, care trebuie sa impuste toate obstacolele existente(predefinite in matrice) si sa nu depaseasca un anumit interval de timp.
    Conceptele OOP le-am folosit pentru a:
      -refolosi codul;
      -da jocului autenticitate
      -usura ideea de a crea elemente noi(gloantele - pe care, la un moment dat, trebuie sa le sterg).
    Jocul se termina in momentul in care toate obstacolele sunt eliminate nedepasind timpul limita, respectiv in momentul in care timpul expira chiar daca obstacolele nu sunt eliminate.
     

-Cum acopera toate punctele necesare din document
		Folosesc concepte OOP - nava si gloantele sunt clase pe care le instantiez.
    Obstacolele sunt de fapt reprezentarile unor matrice alea caror elemente sunt 1 pe anumite pozitii.
Gloantele sunt alocate dinamic folosind ArduinoSTL, pentru ca atunci cand unul loveste un inamic, acesta sa se stearga si sa elibereze memorie.
-Evolutia lui in timp (niveluri, dificultate, scor etc)
		Jocul se desfasoara momentan pe 2 niveluri de dificultate.
Exista scor - care reprezinta numarul de obstacole impuscate pana in momentul de fata(incluzandu-le si pe cele din nivelul anterior). In plus,jucatorul trebuie sa il finalizeze intr-un interval de timp, iar daca acesta este depasit, jocul trebuie reluat.
		Pe LCD se afiseaza timpul scurs si numarul ramas de inamici.
    
-Cum se joaca, adica metodele de control (de exemplu, joystick pt control,
 buton pt o actiune specifica etc)
  Startul se da apasand pe butonul joystick-ului.
  Impuscarea inamicilor se face prin indreptarea joystickului spre UP.
  Atata timp cat joystick-ul este tinut in starea UP se vor genera gloante care vor fi automat adaugate in vectorul bullets, dar in momentul in care ies din ecran sau ating vreun led a carui valoare in matricea prestabilita este 1 si de asemenea, matricea este actualizata: practic, cand pozitia unui glont coincide cu un astfel de element, in matrice acesta va lua valoarea 0, iar apoi se va stinge.
-Ce alte elemente conexe vreti sa folositi: display etc.
		Folosesc joystick si display
