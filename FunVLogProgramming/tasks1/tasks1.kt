fun delete(s: List<Int>, k: Int): List<Int> =
   if (s.isEmpty()) s
   else if (k == 1) s.drop(1)
   else listOf(s.first()) + delete(s.drop(1), k - 1)