; ModuleID = 'output'
source_filename = "output"
target triple = "x86_64-pc-linux-gnu"

declare i32 @printInt(i32)

declare float @printFloat(float)

declare i1 @printBool(i1)

define i32 @main() {
entry:
  %b = alloca i1, align 1
  %addtmp = fadd float 1.000000e+00, 5.000000e+01
  %cmptmp = fcmp ule float 1.000000e+01, %addtmp
  store i1 %cmptmp, ptr %b, align 1
  %b1 = load i1, ptr %b, align 1
  %resultat_appel = call i1 @printBool(i1 %b1)
  br i1 %resultat_appel, label %if, label %else

if:                                               ; preds = %entry
  %b2 = load i1, ptr %b, align 1
  %resultat_appel3 = call i1 @printBool(i1 %b2)
}
