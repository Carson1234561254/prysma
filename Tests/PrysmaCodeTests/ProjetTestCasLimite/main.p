include "TestBoucle.p";
include "TestCondition.p";
include "TestFonctionnelVariableBool.p";
include "TestFonctionnelVariableFloat.p";
include "TestFonctionnelVariableInt.p";
include "TestRecursivité.p";
include "TestTableauBool.p";
include "TestTableauFloat.p";
include "TestTableauInt.p";
include "TestMemoireDynamique.p";



fn int64 main() 
{
    call testBoucle();
    call testCondition();
    call testFonctionnelVariableBool();
    call testFonctionnelVariableFloat();
    call testFonctionnelVariableInt();
    call testRecursivite();
    call testTableauBool();
    call testTableauFloat();
    call testTableauInt();
    call testMemoireDynamique();
    
    return 0;
}