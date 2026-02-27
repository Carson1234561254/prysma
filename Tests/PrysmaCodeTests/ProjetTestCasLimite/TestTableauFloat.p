
fn bool tableauTestLecture_float()
{
    dec string[] fonctionnalite = "1.tableauTestLecture : ";
    call print(ref fonctionnalite);
        dec float[4] tableau = [0.0, 1.0, 2.0, 3.0];

        if (tableau[0] != 0.0) {
            return false;
        }
        if (tableau[1] != 1.0) {
            return false;  
        }
    if (tableau[2] != 2.0) {
        return false;  
    }
    if (tableau[3] != 3.0) {
        return false;  
    }
    return true;
}

fn bool tableauTestAffectation_float()
{
    dec string[] fonctionnalite = "2.tableauTestAffectation : ";
    call print(ref fonctionnalite);
        dec float[4] tableau = [0.0, 1.0, 2.0, 3.0];

        aff tableau[0] = 10.0;
        aff tableau[1] = 11.0;
        aff tableau[2] = 12.0;
        aff tableau[3] = 13.0;

        if (tableau[0] != 10.0) {
            return false;
        }
        if (tableau[1] != 11.0) {
            return false;  
        }
    if (tableau[2] != 12.0) {
        return false;  
    }
    if (tableau[3] != 13.0) {
        return false;  
    }
    return true;
}

// Problème actuelle gènère true même si l'affectation est hors limite, bug dans la gestion de l'équation du tableau dans les braquettes []
fn bool tableauTestSortieHorsLimite_float()
{
    dec string[] fonctionnalite = "3.tableauTestSortieHorsLimite : ";
    call print(ref fonctionnalite);
        dec float[4] tableau = [0.0, 1.0, 2.0, 3.0];

        aff tableau[4] = 10.0; // Doit générer une erreur de compilation
        return true; // Ne doit pas être atteint
}

fn bool tableauVariableTest_float()
{
    dec string[] fonctionnalite = "4.tableauVariableTest : ";
    call print(ref fonctionnalite);
    dec float a = 4.0; 
    dec float b = 2.0; 
    dec float[5] tableau = [a, b, 3.0, 4.0, 5.0];

    if (tableau[0] != 4.0) {
        return false;
    }
    if (tableau[1] != 2.0) {
        return false;
    }
    if (tableau[2] != 3.0) {
        return false;
    }
    if (tableau[3] != 4.0) {
        return false;
    }
    if (tableau[4] != 5.0) {
        return false;
    }
    return true;
}

fn bool tableauTestIndexDynamique_float()
{
    dec string[] fonctionnalite = "5.tableauTestIndexDynamique : ";
    call print(ref fonctionnalite);
    dec float[4] t = [10.0, 20.0, 30.0, 40.0];
    dec int32 i = 2;
    
    // Test variable
    if (t[i] != 30.0) { return false; }

    // Test expression mathématique (i + 1)
    if (t[i + 1] != 40.0) { return false; }
    
    return true;
}

fn bool tableauTestIntegritePile_float()
{
    dec string[] fonctionnalite = "6.tableauTestIntegritePile : ";
    call print(ref fonctionnalite);
    dec float a = 100.0;
    dec float[2] t = [1.0, 2.0];
    dec float b = 200.0;

    aff t[0] = 5.0;
    aff t[1] = 6.0;

    // Si le calcul d'index est faux, 'a' ou 'b' pourraient être modifiés
    if (a != 100.0) { return false; }
    if (b != 200.0) { return false; }
    return true;
}

fn bool tableauTestIteration_float()
{
    dec string[] fonctionnalite = "7.tableauTestIteration : ";
    call print(ref fonctionnalite);
    dec float[3] t = [0.0, 0.0, 0.0];
    dec int32 i = 0;
    dec float somme = 0.0;

    // Remplissage dynamique
    while (i < 3) {
        aff t[i] = i + 1;
        aff i = i + 1;
    }

    // Lecture et accumulation
    aff i = 0;
    while (i < 3) {
        aff somme = somme + t[i];
        aff i = i + 1;
    }

    return (somme == 6.0);
}
// Ne fonctionne pas, bug dans la gestion de l'équation du tableau dans les braquettes []
//fn bool testeEquationScopeTableau()
//{
    //  dec float a = 5.0; 
    // dec float[3] tableau = [1.0+(3.0*a)-23.0-2.0, 3.0*4.0*4.0, 42.0-23.0]; 

    // if(tableau[0] != -9.0)
    //{
        // return false;
    // }
    // if(tableau[1] != 48.0)
    //{
        //   return false; 
    //}

    // if(tableau[2] != 19.0)
    //{
        //   return false;
    //}
    //return true; 
//}

fn float[4] tableauTestRetour_float()
{
    dec string[] fonctionnalite = "8.tableauTestRetour : ";
    call print(ref fonctionnalite);
    dec float[4] tableau = [0.0, 1.0, 2.0, 3.0];
    return tableau;
}

fn bool tableauTestRetourLecture_float()
{
    dec string[] fonctionnalite = "9.tableauTestRetourLecture : ";
    call print(ref fonctionnalite);
    dec float[4] tableau = call tableauTestRetour_float();

        if (tableau[0] != 0.0) {
            return false;
        }
        if (tableau[1] != 1.0) {
            return false;  
        }
    if (tableau[2] != 2.0) {
        return false;  
    }
    if (tableau[3] != 3.0) {
        return false;  
    }
    return true;
}

fn bool tableauInjectionArgument_float(arg float[3] tableau)
{
    dec string[] fonctionnalite = "10.tableauInjectionArgument : ";
    call print(ref fonctionnalite);
    if (tableau[0] != 0.0) {
            return false;
        }
        if (tableau[1] != 1.0) {
            return false;  
        }
    if (tableau[2] != 2.0) {
        return false;  
    }
    return true;
}

fn bool tableauTestArgument_float()
{
    dec string[] fonctionnalite = "11.tableauTestArgument : ";
    call print(ref fonctionnalite);
    dec float[3] tableau = [0.0, 1.0, 2.0];
    return call tableauInjectionArgument_float(tableau);
}

fn int32 testTableauFloat()
{
    call print(call tableauTestLecture_float()); call backSlashN();
    call print(call tableauTestAffectation_float()); call backSlashN();
    //call print(call tableauTestSortieHorsLimite_float()); true
    call print(call tableauVariableTest_float()); call backSlashN();
    call print(call tableauTestIndexDynamique_float()); call backSlashN();  
    call print(call tableauTestIntegritePile_float()); call backSlashN();
    call print(call tableauTestIteration_float()); call backSlashN(); 
    //call print(call testeEquationScopeTableau());
    call print(call tableauTestRetourLecture_float()); call backSlashN();
    call print(call tableauTestArgument_float()); call backSlashN();
    return 0; 
}


   