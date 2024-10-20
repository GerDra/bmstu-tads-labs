using System.Numerics;
using System.IO;
using System.Diagnostics;
using System.Linq;
using System.Collections;
using System.Diagnostics.Metrics;
using System.Collections.Generic;


int counter = 0;
double alfa, beta, ro, tmax, Q;
alfa = 0.5;
ro = 0.1;
tmax = 100;
beta = 1 - alfa;
Q = 1;
/*
Console.WriteLine("Input alfa, ro and lifetime of colony");
alfa=Convert.ToDouble(Console.ReadLine());
ro = Convert.ToDouble(Console.ReadLine());
tmax = Convert.ToInt32(Console.ReadLine());
*/
String line;
double probability(int to, Ant ant, Rebro [,]matrix, int vertex)
{
    // если вершина уже посещена, возвращаем 0
    for (int i = 0; i < ant.towns.Count; i++) 
        if (to == ant.towns.ElementAt(i)) 
            return 0;
    double rand;
    double sum = 0.0;
    int from = ant.towns.ElementAt(ant.towns.Count-1);
    // считаем сумму в знаминателе
    for (int j = 0; j < vertex; j++)
    {
        int flag = 1;
        // проверяем, посещал ли муравей j вершину
        for (int i = 0; i < ant.towns.Count; i++) if (j == ant.towns[i]) flag = 0;
        // если нет, тогда прибавляем к общей сумме
        if (flag==1) sum += Math.Pow(matrix[from,j].ferom, alfa) * Math.Pow(matrix[from, j].nu, beta);
    }

    // возвращаем значение вероятности
    rand = Math.Pow(matrix[from, to].ferom, alfa) * Math.Pow(matrix[from, to].nu, beta) / sum;

    return rand;
}
try
{
        //Pass the file path and file name to the StreamReader constructor
    StreamReader sr = new StreamReader("matr1.txt");
        //Read the first line of text
    line = sr.ReadLine();
        //Continue to read until you reach end of file
while (line != null)
    {
            //write the line to console window
            Console.WriteLine(line);
            //Read the next line
            line = sr.ReadLine();
            counter++;
    }
        //close the file
        sr.Close();
        Console.ReadLine();
    }
    catch (Exception e)
    {
        Console.WriteLine("Exception: " + e.Message);
    }
    finally
    {
        Console.WriteLine("Executing finally block.");
    }

string[] lines = File.ReadAllLines(@"matr1.txt").ToArray();

Rebro[,] matrix;
matrix = new Rebro[counter, counter];


for (int i = 0; i < counter; i++)
{
    int[] row = lines[i].Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries).Select(Int32.Parse).ToArray();
    for (int j = 0; j < counter; j++)
    {
        matrix[i, j].dist = row[j]; 
    }
}
for (int i = 0; i < counter; i++)
{
    for (int j = 0; j < counter; j++)
    {
        Console.WriteLine(" \t", +matrix[i, j].dist);
    }
}

List<int> towns = new List<int>();
for (int i = 0;i<counter; i++)
    towns.Add(i);


var results = new List<List<int>>();
Permute(towns, new List<int>(), results); //method of full permute

int S;
// Output results if needed
Put[] put = new Put[results.Count];
int min=0;

for (int i = 0; i < results.Count; i++)
{
    S = 0;
    var result = results[i];
    for (int j = 0; j < result.Count-1; j++)
    {
        //Console.WriteLine(result[j]);
        if (matrix[result[j], result[j + 1]].dist != -1)
            S += matrix[result[j],result[j + 1]].dist;
    }
    //Console.WriteLine($"{i} S={S}");
    if (i == 0 || min > S) 
        min = S;

    put[i].dist = S;
}

for (int i = 0; i < results.Count; i++)
{
    var result = results[i];
    if (min == put[i].dist)
    {
        //minPut[m].dist = put[i].dist;
        //minPut[m].number = put[i].number;
        //minPut[m].list = put[i].list;
        Console.WriteLine($"№{i} path " + String.Join(" ", result) + $" dist ={min}");
        //m++;
        //Array.Resize(ref minPut, m);
    }
}

for (int i = 0; i < counter; i++)
{
    for (int j = 0;j < counter; j++)
    {
        matrix[i, j].ferom = 0;
        matrix[i, j].nu = 1 / matrix[i, j].dist;
    }
}

Put[] minAput = new Put[counter];

for (int i = 0;i < minAput.Length; i++) {
    Console.WriteLine($"\n{i}-s probe search of solution");
    minAput[i].dist = AntColonyOptimization(matrix, counter);
    //Console.WriteLine($"Minimal path {minAput[i].dist}");
}

 int AntColonyOptimization(Rebro[,] matrix, int counter)
{
        // инициализация данных о лучшем маршруте
    Put way;
    way.dist = -1;
    way.list = new List<int>();

    // инициализация данных о расстоянии и количестве феромона
    for (int i = 0; i < counter; i++)
    {
        for (int j = 0; j < counter; j++)
        {
            matrix[i,j].ferom = 1.0 / counter;
            if (i != j) matrix[i, j].nu = 1.0 / matrix[i, j].dist;
        }
    }
    Ant[] ants = new Ant[counter];
    for(int k=0; k < counter; k++)
    {
        ants[k] = new Ant() ;
        ants[k].length = 0;
        ants[k].towns.Add(k);
        put[k].dist = -1;
        put[k].list = new List<int>();
    }
    
    //цикл по дням
    for(int t = 0; t < tmax; t++)
    {
        // цикл по муравьям
        for (int k=0;k<counter; k++) 
        {
            //цикл посещения всех городов
            do
            {
                int j_max = -1;
                double prob = 0.0;
                Random random = new Random();
                double randChs = random.NextDouble();

                for (int j = 0; j < counter; j++)
                {
                    // Проверка вероятности перехода в вершину j
                    if (ants[k].towns.ElementAt(ants[k].towns.Count() - 1) != j)
                    {
                        double p = probability(j, ants[k], matrix, counter);
                        
                        if (p!=0 && randChs > prob && randChs <= prob + p)
                        {
                            j_max = j;
                        }
                        prob += p;
                    }
                }

                //накопление длинны пути: рассчитать длину L(t)
                ants[k].length += matrix[ants[k].towns.ElementAt(ants[k].towns.Count()-1),j_max].dist;
                ants[k].towns.Add(j_max); //накопление посещенных городов: Построить маршрут Tk(t) по правилу(1)
            } while (ants[k].towns.Count() != counter);

            // проверка на лучшее решение
            if (ants[k].length < put[k].dist || put[k].dist < 0)
            {
                put[k].dist = ants[k].length; //запомнить новый оптимальный длинну для k-го муравья
                put[k].list.Clear();
                put[k].list.AddRange(ants[k].towns);
            }

            // проверка на лучшее решение
            if (ants[k].length < way.dist || way.dist < 0)
            {
                way.dist = ants[k].length;  //запомнить новый оптимальный длинну 
                way.list.Clear();
                way.list.AddRange(ants[k].towns);
            }
            /*
            //распыление фермона k-м муравьем в день t
            for (int i = 0; i < ants[k].towns.Count() - 1; i++)
            {
                int from = ants[k].towns.First() / ants[k].towns.Count();
                int to = ants[k].towns.Last();
                matrix[from,to].ferom += Q / ants[k].length;
                matrix[to,from].ferom = matrix[from,to].ferom;
            }
            // обновление муравьев
            //ants[k].itabu = 1;
            //ants[k].towns2 = ants[k].towns;
            ants[k].towns.Clear();
            ants[k].towns.Add(k);
            ants[k].length = 0;*/
        }

        // цикл по ребрам
        for (int i = 0; i < counter; i++)
            for (int j = 0; j < counter; j++)
                // обновление феромона для ребра (i, j)
                if (i != j) matrix[i,j].ferom *= (1 - ro);
        
        for(int k = 0;  k < counter; k++)
        {
            //распыление фермона k-м муравьем в день t
            for (int i = 0; i < ants[k].towns.Count() - 1; i++)
            {
                int from = ants[k].towns.First() / ants[k].towns.Count();
                int to = ants[k].towns.Last();
                matrix[from, to].ferom += Q / ants[k].length;
                matrix[to, from].ferom = matrix[from, to].ferom;
            }
            // обновление муравьев
            ants[k].towns.Clear();
            ants[k].towns.Add(k);
            ants[k].length = 0;
        }
    }

    for (int k = 0; k<ants.Length; k++)
        Console.WriteLine($"Minimal path for {k}'s ants " + String.Join("-", put[k].list) + $" with lenght {put[k].dist}");
    
    Console.WriteLine($"Minimal path " + String.Join("-", way.list) + $" with lenght {way.dist}");
    //Console.WriteLine($"№{minPut[i].number} path " + String.Join(" ", minPut[i].list) + $" dist ={minPut[i].dist}");
    return way.dist;
}
// возвращаем кратчайший маршрут

    

static void Permute(List<int> arr, List<int> memo, List<List<int>> results)
{
    if (arr.Count == 0)
    {
        results.Add(new List<int>(memo));
        return;
    }

    for (int i = 0; i < arr.Count; i++)
    {
        var cur = arr[i];
        arr.RemoveAt(i);
        memo.Add(cur);

        Permute(arr, memo, results);

        memo.RemoveAt(memo.Count - 1);
        arr.Insert(i, cur);
    }
}

public class Ant
{
    public List<int> towns;
    public int length;
    public Rebro matrix;

    public Ant()
    {
        towns = new List<int>();
        length = 0;
        matrix = new Rebro();
    }

    public Ant(Rebro amatrix, int numTown, int counter)
    {
        towns = new List<int>();
        matrix = amatrix;
        length = 0;
    }
}

public struct Rebro{
    public int dist;
    public double ferom;
    public double nu;
    public int townCount;
    public double probability;
}
struct Put
{
    public int dist;
    public int number;
    public List<int> list;
}
