Projekt na programowanie ewolucyjne

Celem projektu jest znalezienie układu żywych komórek w Conway's game of life na planszy o ograniczonych wymiarach (aby dokonać symulacji) które maksymalizują liczbę żywych komórek po określonej liczbie tur (np. 10, 20,...). Po angielsku funkcjonuje określenie density, określające jaki ułamek komórek w danym momencie jest żywych.

Według https://conwaylife.com/wiki/Density "The maximum density of an n × n still life is greater than or equal to 1/2 for all finite n>1", zawsze da się osiągnąć co najmniej 1/2 zapełnienia planszy żywymi komórkami, jeżeli jest to wzór będący "still life", czyli nie zmieniający się.

Według https://conwaylife.com/ref/lexicon/lex_d.htm#density:
"In 1994 Noam Elkies proved that the maximum density of a stable pattern is 1/2, which had been the conjectured value. See the paper listed in the bibliography. Marcus Moore provided a simpler proof in 1995, and in fact proves that a still life with an m × n bounding box has at most (mn+m+n)/2 cells.

But what is the maximum average density of an oscillating pattern? The answer is conjectured to be 1/2 again, but this remains unproved. The best upper bound so far obtained is 8/13 (Hartmut Holzwart, September 1992). "

W poniższych obliczeniach dzięki algorytmowi SGA udało się osiągnąć wyniki, gdzie density jest zbliżone do 1/2. Obliczenia przeprowadziłem dla umiarkowanie małych plansz (10x10 oraz 20x20), ponieważ już dla nich symulacja game of life zajmowała już około 20-30 minut dla małej liczby tur (10, 20) i około godziny dla większej (50, 100).


SGAsquarecross - algorytm SGA ze zmienionym sposobem crossover, polegającym na wymianie losowo wybranego prostokąta między dwoma osobnikami. Rozumowanie stojące za tym: możliwe że lepszym rozwiązaniem, niż dzielenie
na pół chromosomu, jest wymiana kwadratu z planszy, gdzie u jednego osobnika na tym kwadracie przetrwało zdecydowanie więcej komórek


Symulowane wyżarzanie jest dużo szybsze w obliczeniach, ale jak widać na poniższych wykresach osiąga gorsze wyniki już dla małych plansz i małej liczby tur.

Algorytm SGA dosyć dobrze sprawdza się dla tego zadania, na poniższym wykresie dla gry 10x10 przy 100 turach widać wynik mocno odbiegający od 1/2 * 100, jednak wynika to głównie z faktu, że dla dłuższych gier ciężej jest znaleźć układ który na długo zachowuje dużo żywych komórek (mają one tendencje do umierania z czasem). Najlepsze rozwiązania dla długiego przebiegu gry to "still life", jednak ciężko oczekiwać, ze SGA uda się wylosować bardzo rzadko występujący układ który się nigdy nie zmienia.