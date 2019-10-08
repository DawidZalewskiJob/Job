#-----------------------------Rozwiązanie problemu przepływowego algorytmem NEH-----------------------------

""""
Program rozwiązuje problem przepływowy opisany na tej stronie: http://dominik.zelazny.staff.iiar.pwr.wroc.pl/materialy/Algorytm_NEH_(Metoda_wstawien_w_klasycznych_problemach_szeregowania._Cz._I._Problem_przeplywowy).pdf

Przykładowe dane wejściowe:

3  4
7  88  69
3  75  74
45  17  88
44  86  93

Gdzie 3 oznacza ilość zadań(kolumny) oraz 4 maszyny(wiersze)

"""

import datetime
start = datetime.datetime.now()

def czytanie_z_pliku(plik):
    mega_maszyna = []


    file_handle = open(plik, 'r')

    lines_list = file_handle.readlines()

    zadania, maszyna = (int(val) for val in lines_list[0].split())
    globals()['zadania'] = zadania
    globals()['maszyna'] = maszyna

    mega_kursor = [0]*maszyna
    globals()['mega_kursor'] = mega_kursor

    dane = [[int(val) for val in line.split()] for line in lines_list[1:]]
    globals()['dane'] = dane

    for i in range(1, maszyna + 1):
        mini_maszyna = [0] * zadania
        globals()['M%s' % i] = [0] * zadania
        globals()['K%s' % i] = 0
        j = i
        for i in range(0, zadania):
            mini_maszyna[i] = dane[i][j - 1]
            globals()['M%s' % j][i] = dane[i][j - 1]
        mega_maszyna.append(mini_maszyna)
    globals()['mega_maszyna'] = mega_maszyna

def liczenie_mega_kursora(dane):
    mega_kursor = [0] * maszyna

    for i in range(0, len(dane)):
        mega_kursor[0] = mega_maszyna[0][dane[i]] + mega_kursor[0]


        for j in range(0, maszyna):
            if j != (maszyna - 1):
                if mega_kursor[j] >= mega_kursor[j+1]:
                    mega_kursor[j+1] = mega_kursor[j] + mega_maszyna[j+1][dane[i]]
                else:
                    mega_kursor[j+1] = mega_kursor[j+1] + mega_maszyna[j+1][dane[i]]

        kursor_max = max(mega_kursor)



    globals()['kursor_max'] = kursor_max

def liczenie_czasow():
    tabela_sum = [0] * len(M1)
    bierzace_zadanie = 0
    while bierzace_zadanie != zadania:

        for i in range(0,maszyna):

            zad1=dane[bierzace_zadanie][i]
            i = +1
            tabela_sum[bierzace_zadanie] = zad1 + tabela_sum[bierzace_zadanie]

        bierzace_zadanie += 1
        globals()['tabela_sum'] = tabela_sum

def sortowanie_czasow():

    sortowanie = sorted(tabela_sum)
    sortowanie.reverse()
    globals()['sortowana_tabela'] = sortowanie

def sprwadzanie_kolejnosci():
    temp_tabela_sum = tabela_sum
    kolejnosc = []
    for i in range (0,zadania):
        blokada = 0
        for j in range (0,zadania):
            if blokada == 1:
                break
            if sortowana_tabela[i] == temp_tabela_sum[j]:
                temp_tabela_sum[j]= None
                kolejnosc.append(j)
                blokada = 1
                globals()['kolejnosc'] = kolejnosc

def NEH():

    NEH = []
    blokada = 0

    for iteracja in range (0,(len(kolejnosc))):
        kursory = [0] * (iteracja+1)


        for j in range (0,iteracja+1):
            NEHK=NEH[::]
            NEHK.insert(j,kolejnosc[iteracja])
            liczenie_mega_kursora(NEHK)
            kursory[j]=kursor_max


        for i in range (0,iteracja+1):
            if min(kursory) == kursory[i] and blokada == 0:
                NEH.insert(i, kolejnosc[iteracja])
                liczenie_mega_kursora(NEH)
                blokada = 1

        blokada = 0

    globals()['NEH'] = NEH


def main():
    czytanie_z_pliku("data.txt")
    liczenie_czasow()
    sortowanie_czasow()
    sprwadzanie_kolejnosci()
    NEH()
    print("Kolejnosc NEH'a to:",NEH)
    liczenie_mega_kursora(NEH)
    print("Czas C_MAX to:",kursor_max)
    duration = datetime.datetime.now() - start
    print("Czas obliczen to:", duration)

main()