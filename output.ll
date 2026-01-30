; ModuleID = 'PrysmaModule'
source_filename = "PrysmaModule"
target triple = "x86_64-pc-linux-gnu"

define i32 @main() {
entry:
  %a = alloca float, align 4
  store float 1.300000e+01, ptr %a, align 4
  %b = alloca float, align 4
  store float 1.300000e+01, ptr %b, align 4
  %c = alloca float, align 4
  store float 1.300000e+01, ptr %c, align 4
  %resultInt = fptosi ptr %c to i32
  ret i32 %resultInt
}
