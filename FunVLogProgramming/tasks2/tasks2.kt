   fun replace(f: (Int) -> Boolean, x: List<Int>, a: Int): List<Int> = 
    if (x.isEmpty()) x
    else {
         val x1 = replace(f, x.drop(1), a)
         if (f(x.first())) listOf(a) + x1
         else listOf(x.first()) + x1
   }
// replace({ it % 2 == 0}, listOf(1,2,3,4,5,6), 0)