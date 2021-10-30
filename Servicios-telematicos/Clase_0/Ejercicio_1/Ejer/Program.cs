using System;

namespace Ejer
{
    class Program
    {
        static void Main(string[] args){
            int [,] Matriz=new int[3,3];
            int j=0;
            for (int i=0;i<3;i++){
                for(j=0;j<2;j++){
                    Console.WriteLine("Ingrese valor para el componente "+i+", "+j);
                    int numero=Convert.ToInt16(Console.ReadLine());
                    Matriz[i, j]=numero;
                }
                Matriz[i, j] = Matriz[i,j-2] * Matriz[i,j-1];
                j=0;
            }
            for (int i=0;i<3;i++){
                for(int k=0;k<3;k++){
                    Console.Write(" "+Matriz[i, k]);
                }
                Console.WriteLine(" ");
            }
        }
    }
}
