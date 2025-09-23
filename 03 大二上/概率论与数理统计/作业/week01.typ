#import "./homework.typ": config
#import "@preview/physica:0.9.5": dd
#show: config.with(
  "概率论与数理统计",
  "第一周作业",
  "",
  "陶唐",
  "2024111155",
)

= 习题 1-1

== 1

+ $Omega = {1, 2, 3, ..., 9, 10}$
+ $Omega = {t in RR | t >= 0}$
+ $Omega = {(i, j) in NN^2 | i, j in {1, 2, 3, ..., 9, 10} }$
+ $Omega = {(i, j) in NN^2 | i, j in {1, 2, 3, ..., 9, 10}, i != j }$
+ $Omega = {(a, b, 1 - a - b) in RR^3 | a > 0, b > 0, a + b < 1}$


== 2

+ $A B overline(C)$ 意味着“该学生*是*男生，*来自*少数民族，*不是*学生干部”。
+ 所有的学生干部都是来自少数民族的男生，也就是 $C in A B$。
+ 所有的学生干部都来自少数民族。
+ 所有的少数民族都是女生，且所有的女生都来自少数民族。

== 3

+ $A overline(B) overline(C)$
+ $A B overline(C) + A overline(B) C + overline(A) B C + A B C$
+ $A B overline(C) + A overline(B) C + overline(A) B C$
+ $A overline(B) overline(C) + overline(A) B overline(C) + overline(A) overline(B) C + overline(A) overline(B) overline(C)$

= 习题 1-2

== 1

$ P = 3 / binom(5, 2) = 3 / 10 $

== 2

$ P = 6 / (5 + 6) times 5 / (5 + 5) times 5 / (4 + 5) = 5 / 33 $

== 3

$ P_1 = binom(N, n) / N^n $

令 $P_m$ 表示某间特定的房恰有 $m$ 个人的概率，则

$ P_m = (binom(n, m) times (N - 1)^(n - m)) / N^n $

== 4

$ P = (1/2 times (24 - 4)^2 + 1/2 times (24 - 3)^2) / 24^2 = 841/1152 $

== 5

$ P_1 = 1 - (1/2 times (1 - 0.2)^2) / 1^2 = 0.68 $

$ P_2 = 1/4 + integral_(1/4)^1 1/x dd(x) = 1/4 + ln 4 $
