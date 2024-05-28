//
// Created by referencecat on 28.05.24.
//
#include "iostream"
#include "chrono"

int main( )
{  using std::cout;
    using namespace std::chrono;
    setlocale(LC_ALL, "Russian");
    srand((unsigned int)7);      //Пока здесь константа, данные повторяются
//    srand((unsigned int)time(nullptr)); //Разблокировать для случайных данных
    bool debug = true;    //false, чтобы запретить отладочный вывод
    auto MaxMul = 5;
    int middle_power = 0, set_count = 0;
    auto Used = [&] (MyCont & t){ middle_power += t.Power( );
        ++set_count; };
    auto DebOut = [debug] (MyCont & t) { if(debug) { t.Show( ); system("Pause");}};
    auto rand = [ ] (int d) { return std::rand( )%d; }; //Лямбда-функция!
    ofstream fout("in.txt");   //Открытие файла для результатов
    int p = rand(20) + 1;      //Текущая мощность (место для цикла по p)
    //=== Данные ===
    middle_power = 0, set_count = 0;
    MyCont A(p, 'A');
    MyCont B(p, 'B');
    MyCont C(p, 'C');
    MyCont D(p, 'D');
    MyCont E(p, 'E');
    MyCont F(0, 'F');   //Пустая заготовка для Excl
    MyCont G(p, 'G');
    MyCont H(p, 'H');
    MyCont R(p);
    int q_and(rand(MaxMul) + 1);
    PrepareAnd(A, R, q_and);
    if (debug) A.Show( ); Used(A);
    if (debug) R.Show( ); Used(R);
//=== Цепочка операций ===
// (Операция пропускается (skipped!), если аргументы некорректны)
//Идет суммирование мощностей множеств и подсчёт их количества,
// измеряется время выполнения цепочки
    auto t1 = std::chrono::high_resolution_clock::now( );
    if (debug) cout << "\n=== R&=A ===(" << q_and << ") ";
    R&=A;   DebOut(R); Used(R);

    if (debug) B.Show( ); Used(B);
    if (debug) cout << "\n=== R|=B ===";
    R|=B;  DebOut(R); Used(R);

    int e = rand(R.Power( ));
    if (debug) cout << "\n=== R.Change (H, " << e << ") ===";
    H.Show( ); Used(H);
    R.Change(H, e);   DebOut(R);	Used(R);

    int q_sub(rand(MaxMul) + 1);
    PrepareAnd(C, R, q_sub);
    if (debug) R.Show( ), C.Show( ); middle_power += q_sub; Used(C);
    if (debug) cout << "\n=== R-=C ===(" << q_sub << ") ";
    R-=C;  DebOut(R); Used(R);

    int a = rand(R.Power( )), b = rand(R.Power( ));
    if (debug) cout << "\n=== R.Erase (" << a << "," << b << ")===";
    if (a>b) cout << "(skipped!)";
    R.Erase(a, b);   DebOut(R);	Used(R);

    if (debug) cout << "\n=== R.Concat(D) ===";
    D.Show( ); Used(D);
    R.Concat(D);   DebOut(R);	Used(R);

    if (debug) cout << "\n=== R.Merge(E) ===";
    E.Show( ); Used(E);
    R.Merge(E);   DebOut(R);	Used(R);

    if (debug) cout << "\n=== R.Excl(F) ===";
    F.PrepareExcl(R);
    if(debug && !F.Power( )) cout << "(skipped)!";
    F.Show( );  Used(F);
    R.Excl(F);   DebOut(R);	Used(R);
    int d = rand(R.Power( ));
    if (debug) cout << "\n=== R.Subst (G, " << d << ") ===";
    G.Show( ); Used(G);
    R.Subst(G, d);   DebOut(R);	Used(R);
    int c = rand(MaxMul);
    if (debug) cout << "\n=== R.Mul(" << c << ")===";
    if (c < 2) cout << "(skipped!)";
    R.Mul(c);   DebOut(R);	Used(R);
    auto t2 = std::chrono::high_resolution_clock::now( );
    auto dt = duration_cast<duration<double,micro>>(t2-t1).count( );
    middle_power /= set_count;
    fout << p << '  ' << dt << endl; //Выдача в файл
    cout << "\n=== Конец === (" << p << " : " << set_count << " * " <<
         middle_power << " DT=" << dt <<")\n";
    cin.get( );
    return 0;
}
