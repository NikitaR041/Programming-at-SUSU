fun replace(f: (Int) -> Boolean, x: List<Int>, a: Int): List<Int> = 
    if (x.isEmpty()) x
    else if (f(x.first())) listOf(a) + replace(f, x.drop(1), a)
    else listOf(x.first()) + replace(f, x.drop(1), a)
       
   
// replace({ it % 2 == 0}, listOf(1,2,3,4,5,6), 0)