# Simulare management spital
Ai devenit seful unui spital, construit din mai multe cabinete, fiecare avand o lista doctori, asistenti si administratori. Dar nu ai idee daca cabinetele tale au prea multi sau prea putini angajati. 
Acest program simuleaza o zi in spitalul tau si iti spune ce probleme are un cabinet, daca are, si ce ai putea sa faci ca sa le rezolvi.

Fiecare cabinet are un rol (ex: stomatologie, medic de familie, etc). Acesta primeste pacienti in limita lui, si ii trateaza daca mai exista timp in zi. 
Un cabinet este compus din angajati, care pot fi:
  * Doctori, care trateaza X pacienti pe ora/zi
  * Asistenti, fiecare usurand lucrul unui doctor. Un doctor poate trata de doua ori mai multi pacienti daca este asistat de un asistent.

Spitalul are si:
  * Administratori, fara de care spitalul nu poate redirectiona pacienti catre doctori. Un administrator poate redirectiona un singur pacient in orice moment, ceea ce poate rezulta in cozi lungi daca nu exista destui administratoi.

Cele trei tipuri de angajati au fost implementate ca clase derivate a unei clase abstracta de 'angajat'. Acestea se folosesc de multa functionalitate pe care o au in comun, dar au si functionalitatea lor, indeplinind lucrul lor cu ajutorul functilor virtuale.

Pacientii au:
  * Un nume
  * O varsta
  * O lista de probleme, fiecare problema reprezentand un cabinet prin care trebuie sa treaca pacientul.
Pacientii in varsta (60+) necesita asistenta unui asistent pentru a putea fi tratati.

Programul simuleaza o zi de munca de 8 ore. In fiecare ora:
  * Administratorii redirectioneaza pacienti catre cabinetele necesare
  * Asistentii ajuta doctorii din cabinetul lor
  * Doctorii trateaza pacienti din cabinetul lor

Dupa tratarea unei probleme, pacientul este trimis inapoi in coada principala pentru a fi redirectionat catre urmatorul cabinet necesar. Daca nu mai are probleme, pacientul este considerat complet tratat.

Programul afiseaza:
  * Fiecare pas facut de angajati in cele 8 ore
  * Ce pacienti nu au putut fi tratati
  * Ce cabinete sunt supraincarcate
  * Ce doctori nu au avut suficienti pacienti
  * Cati bani au fost pierduti din salarii neutilizate
  * Recomandari pentru imbunatatirea structurii spitalului

Programul foloseste:
  * O clasa abstracta `Staff`
  * Clase derivate:
      * `Doctor`
      * `Nurse`
      * `Admin`
  * Clasa `Patient`
  * Clasa `Department`

Cele trei tipuri de angajati au fost implementate ca clase derivate ale unei clase abstracte de `Staff`. Acestea folosesc functionalitatea comuna mostenita din clasa de baza, dar isi implementeaza propriul comportament prin functii virtuale.

Afisarea este realizata polimorfic prin operator<< care foloseste o functie virtuala display(...)

Input

Programul foloseste fisiere text pentru datele initiale.

  * doctors.txt

Format:

nume specializare pacienti_pe_zi salariu

Exemplu:

House doctor_familie 5 20000
Doc chirurg 2 40000

  * nurses.txt

Format:

nume specializare salariu

  * admins.txt

Format:

nume salariu

  * patients.txt

Format:

nume varsta lista_cabinete

Exemplu:

Ducu 19 doctor_familie laringolog chirurg

Programul foloseste o ierarhie proprie de exceptii derivata din std::exception. Exceptiile sunt folosite pentru:
  * varste invalide
  * salarii invalide
  * cabinete inexistente
  * fisiere care nu pot fi deschise
Exceptiile sunt aruncate in constructori sau la citirea fisierelor si tratate in main().


Numele temei pt review: Pariuri sportive

Nume coleg review: Bugeac Alexandru

