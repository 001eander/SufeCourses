#import "./homework.typ": config

#show: config.with(
  "概率论与数理统计",
  "第二次作业",
  "",
  "陶唐",
  "2024111155",
)

= 习题 1-3

== 2

根据概率的可列可加性 $ P(A union B) = P(A) + P(B) - P(A B) $ 可得

$ P(A B) = P(A) + P(B) - P(A union B) = p + q - r $

$ P(overline(A) B) = P(B) - P(A B) = r - p $

$ P(A overline(B)) = P(A) - P(A B) = r - q $

$ P(overline(A) overline(B)) = P(overline(A union B))) = 1 - P(A union B) = 1 - r $

== 3

1-100 中能够被 5 整除的数有 20 个，能够被 9 整除的数有 11 个，既能被 5 整除又能被 9 整除的数有 2 个。

记 A 为“从1-100中任取一个数，能被 5 整除”，B 为“从1-100中任取一个数，能被 9 整除”，则

$ P(A) = 20 / 100 = 0.2, P(B) = 11 / 100 = 0.11, P(A B) = 2 / 100 = 0.02 $

可以得到

$ P(A union B) = P(A) + P(B) - P(A union B) = 0.29 $

= 习题 1-4

== 1

=== (1)

记 A 表示“有一件是废品”，B 表示“两件都是废品”，则

$
  P(A) = 1 - P(overline(A)) = 1 - binom(M - m, 2) / binom(M, 2) = 1 - ((M - m)(M - m - 1)) / (M (M - 1)) = -(m (m - 2 M + 1))/(M (M - 1))
$

$
  P(A B) = binom(m, 2) / binom(M, 2) = (m (m - 1)) / (M (M - 1))
$

$
  P(B | A) = P(A B) / P(A) = (m - 1)/(2 M - m - 1)
$

=== (2)

$
  P(A overline(B) | overline(B)) = P(A overline(B)) / P(overline(B)) = ((binom(M - m, 1) binom(m, 1)) / binom(M, 2)) / (1 - P(B)) = (2m)/(M + m - 1)
$

=== (3)

$
  P(A) = -(m (m - 2 M + 1))/(M (M - 1))
$
