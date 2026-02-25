
fn bool tableauTestLecture_bool()
{
    dec string[] fonctionnalite = "1.tableauTestLecture : ";
    call print(ref fonctionnalite);
        dec bool[4] tableau = [true, false, true, false];

        if (tableau[0] != true) {
            return false;
        }
        if (tableau[1] != false) {
            return false;  
        }
    if (tableau[2] != true) {
        return false;  
    }
    if (tableau[3] != false) {
        return false;  
    }
    return true;
}

fn bool tableauTestAffectation_bool()
{
    dec string[] fonctionnalite = "2.tableauTestAffectation : ";
    call print(ref fonctionnalite);
        dec bool[4] tableau = [false, false, false, false];

        aff tableau[0] = true;
        aff tableau[1] = true;
        aff tableau[2] = false;
        aff tableau[3] = true;

        if (tableau[0] != true) {
            return false;
        }
        if (tableau[1] != true) {
            return false;  
        }
    if (tableau[2] != false) {
        return false;  
    }
    if (tableau[3] != true) {
        return false;  
    }
    return true;
}

fn bool tableauTestSortieHorsLimite_bool()
{
    dec string[] fonctionnalite = "3.tableauTestSortieHorsLimite : ";
    call print(ref fonctionnalite);
        dec bool[4] tableau = [true, true, true, true];

        aff tableau[4] = false; // Doit générer une erreur de compilation
        return true; // Ne doit pas être atteint
}

fn bool tableauVariableTest_bool()
{
    dec string[] fonctionnalite = "4.tableauVariableTest : ";
    call print(ref fonctionnalite);
    dec bool a = true; 
    dec bool b = false; 
    dec bool[5] tableau = [a, b, true, false, true];

    if (tableau[0] != true) {
        return false;
    }
    if (tableau[1] != false) {
        return false;
    }
    if (tableau[2] != true) {
        return false;
    }
    if (tableau[3] != false) {
        return false;
    }
    if (tableau[4] != true) {
        return false;
    }
    return true;
}

// bug à corriger
// Le compilateur génère un code LLVM incorrect pour l'accès à un tableau avec une expression comme index (ex: t[i + 1]).
// Au lieu de calculer d'abord l'index (i + 1), il semble charger la valeur de t[i] (un booléen)
// puis essaie d'ajouter 1 à ce booléen, ce qui cause une erreur de type dans LLVM (add i1, i32).
// La logique de génération de code pour les équations d'index de tableau doit être corrigée.
//fn bool tableauTestIndexDynamique()
//{
//    dec bool[4] t = [true, false, true, false];
//    dec int32 i = 2;
//    
//    // Test variable
//    if (t[i] != true) { return false; }
//
//    // Test expression mathématique (i + 1)
//    if (t[i + 1] != false) { return false; }
//    
//    return true;
//}

fn bool tableauTestIntegritePile_bool()
{
    dec string[] fonctionnalite = "5.tableauTestIntegritePile : ";
    call print(ref fonctionnalite);
    dec bool a = true;
    dec bool[2] t = [false, false];
    dec bool b = false;

    aff t[0] = true;
    aff t[1] = true;

    // Si le calcul d'index est faux, 'a' ou 'b' pourraient être modifiés
    if (a != true) { return false; }
    if (b != false) { return false; }
    return true;
}

fn bool tableauTestIteration_bool()
{
    dec string[] fonctionnalite = "6.tableauTestIteration : ";
    call print(ref fonctionnalite);
    dec bool[3] t = [false, false, false];
    dec int32 i = 0;

    // Remplissage dynamique
    while (i < 3) {
        aff t[i] = true;
        aff i = i + 1;
    }

    // Lecture et accumulation
    aff i = 0;
    while (i < 3) {
        if(t[i] != true)
        {
            return false;
        }
        aff i = i + 1;
    }

    return true;
}

fn bool[4] tableauTestRetour_bool()
{
    dec string[] fonctionnalite = "7.tableauTestRetour : ";
    call print(ref fonctionnalite);
    dec bool[4] tableau = [true, false, true, false];
    return tableau;
}

fn bool tableauTestRetourLecture_bool()
{
    dec string[] fonctionnalite = "8.tableauTestRetourLecture : ";
    call print(ref fonctionnalite);
    dec bool[4] tableau = call tableauTestRetour_bool();

        if (tableau[0] != true) {
            return false;
        }
        if (tableau[1] != false) {
            return false;  
        }
    if (tableau[2] != true) {
        return false;  
    }
    if (tableau[3] != false) {
        return false;  
    }
    return true;
}

fn bool tableauInjectionArgument_bool(arg bool[3] tableau)
{
    dec string[] fonctionnalite = "9.tableauInjectionArgument : ";
    call print(ref fonctionnalite);
    if (tableau[0] != true) {
            return false;
        }
        if (tableau[1] != false) {
            return false;  
        }
    if (tableau[2] != true) {
        return false;  
    }
    return true;
}

fn bool tableauTestArgument_bool()
{
    dec string[] fonctionnalite = "10.tableauTestArgument : ";
    call print(ref fonctionnalite);
    dec bool[3] tableau = [true, false, true];
    return call tableauInjectionArgument_bool(tableau);
}

fn int32 testTableauBool()
{
    call print(call tableauTestLecture_bool()); call backSlashN();
    call print(call tableauTestAffectation_bool()); call backSlashN();
    //call print(call tableauTestSortieHorsLimite_bool()); true
    call print(call tableauVariableTest_bool()); call backSlashN();
    //call print(call tableauTestIndexDynamique()); // false
    call print(call tableauTestIntegritePile_bool()); call backSlashN();
    call print(call tableauTestIteration_bool()); call backSlashN();
    call print(call tableauTestRetourLecture_bool()); call backSlashN();
    call print(call tableauTestArgument_bool()); call backSlashN();

    return 0; 
}
