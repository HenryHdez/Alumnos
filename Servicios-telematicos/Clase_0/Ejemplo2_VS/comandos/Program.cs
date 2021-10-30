using System;
using System.IO;

namespace comandos
{
    class Program
    {
        static void Main(string[] args)
        {
            //Comentario
            /*Comentario de múltiples líneas*/
            Console.Clear();        //Eliminar información del terminal
            //Tipos de variable
            string Cadena = "Hola";
            int numero_entero = 0;
            double numero_con_punto = 1.0;
            char caracter = 'a';
            int [] vector = new int[3]; //Lista vacía
            int [] lista  = {1,2,3,4};  //Lista Llena
            string [,] Matriz = new String [4, 3]; //Matriz vacía
            //Editar posiciones de los arreglos
            vector[0]=numero_entero;
            vector[1]=Convert.ToInt32(caracter); //Convertir de char a entero
            Matriz[1,2]=Convert.ToString(numero_con_punto); //Convertir cualquier cosa a String
            Console.WriteLine("El valor de la MA es: "+Matriz[1,2]+" Digite algo");
            //Leer Cadena de caracteres desde el teclado
            Cadena=Console.ReadLine();
            Console.WriteLine("Es = "+Cadena);

            //Estructuras de control de flujo
            int condicion=Convert.ToInt16(Console.Read());
            //Condicional if
            if(condicion<3){Console.WriteLine("Se cumple");}
            else{Console.WriteLine("No se cumple");}
            //Condicional else-if
            if(condicion<1){Console.WriteLine("Haga esto");}
            else if(condicion==2){Console.WriteLine("Haga esto otro");} //...
            else{Console.WriteLine("Haga esto finalmente");}
            //Switch
            switch(condicion){
                case 0:
                Console.WriteLine("Caso 0");
                break;

                case 1: //...
                Console.WriteLine("Caso 1");
                break;

                default:
                Console.WriteLine("Ninguno de los anteriores");
                break;
            }

            //Estructuras de control de flujo
            int veces=3;
            //for
            for(int i=0;i<veces;i++){
                Console.WriteLine(i);
            }
            //while
            int j=0;
            while(j<veces){
                Console.WriteLine(j);
                j++;
            }

        }
    }
}
