#include <stdio.h>

void lista_vendedores(float[*][*], int);
void fuera_de_rango(int);
int validar_rango(int, int, int, int, int);
int cargar_datos(float[*][*], int[], int[], int);
void suma_por_filas(float[*][*], int, int);
void imprimir_cabecera(float[*][*],int[], int, int, int, int);
void imprimir_global(float[*][*],int[], int, int);
int minimo(float[*][*], int, int);
void imprimir_vector(int[], int);
void ordenar_por_burbujeo(float[*][*], int, int);
void imprimir_lista(float[*][*], int, int);



int main() {
    int n, dd, mm, aa, min, valida, artVendidos[20] = {0}, transacciones[15] = {0};
    n = 300;
    float global[15][22] = {{0}};

    printf("REdA 2 - Elementos de Programación - Lucas Zonta - UNLaM 2020\n\n");

//punto a)
    printf("Bienvenido al sistema. \n\nIngrese la fecha\n");
    do
    {
        printf("\nDia: ");
        scanf("%d", &dd);
        valida = validar_rango(dd, 1, 31, 1, 0);
        fuera_de_rango(valida);
    } while (valida == 0);
    do
    {
        printf("\nMes: ");
        scanf("%d", &mm);
        valida = validar_rango(mm, 1, 12, 1, 0);
        fuera_de_rango(valida);
    } while (valida == 0);
     do
    {
        printf("\nAnio: ");
        scanf("%d", &aa);
        valida = validar_rango(aa, 1, 2020, 1900, 0);
        fuera_de_rango(valida);
    } while (valida == 0);
    
    lista_vendedores(global, 15);
    cargar_datos(global, transacciones, artVendidos, n); //carga datos y devuelve cant de transacciones en el dia
    suma_por_filas(global, 15, 21); //suma totales de cada vendedor
    imprimir_cabecera(global, artVendidos, 20, dd, mm, aa);
    imprimir_global(global, artVendidos, 15, 22);

//punto b)
    min = minimo(global, 15, 21);
    printf("\n\n---- El numero de vendedor con menor recaudacion es: %d ----\n", min);

//punto c)
    printf("\n\nCANTIDAD DE TRANSACCIONES POR VENDEDOR\n");
    printf(" VENDEDOR \t VENTAS\n");
    imprimir_vector(transacciones, 15);
    
//punto d)
    ordenar_por_burbujeo(global, 15, 11);
    printf("\n\nMONTOS RECAUDADOS DEL ARTICULO 11\n");
    printf(" VENDEDOR \t MONTO\n");
    imprimir_lista(global, 15, 11);

    return 0;
}

void lista_vendedores(float global[][22], int a){ //llena la primera columna de la matriz con numeros del 1 hasta 'a', siendo 'a' la cant de filas de la matriz.
    int i;
    for ( i = 0; i < a; i++)
    {
        global[i][0] = (i+1);
    }
}

int cargar_datos (float global[][22], int transacciones[], int vendidos[], int n){ //carga datos en matriz global, vector de cantidad de registros por numero de fila, y vector si se vendio o no un articulo. n: maximo de iteracion
  int i, valida, cantidad_transacciones, vendedor, cantidad, articulo;
  float precio;
  for ( i = 0; i < n; i++)
  {
        do //ingresa y valida vendedor
        {
            printf("\n\nIngrese numero de vendedor: ");
            scanf("%d", &vendedor);
            valida = validar_rango(vendedor, 0, 15, 1, 0);
            fuera_de_rango(valida);

            if (valida == 2) // termina carga: sale del do-while
            {
                break; 
            }

        } while (valida == 0);

        if (valida == 2) //termina carga: sale del for
        {
            printf("\n--------Termino carga de datos.\n\n\n");
            break; 
        }
      
        do //ingresa y valida articulo
        {
            printf("Ingrese numero de articulo: ");
            scanf("%d", &articulo);
            valida = validar_rango(articulo, 1, 20, 1, 0);
            fuera_de_rango(valida);

        } while (valida == 0);
    
        printf("Ingrese cantidad vendida: ");
        scanf("%d", &cantidad);

        printf("Ingrese precio de unidad: ");
        scanf("%f", &precio);

        vendidos[articulo-1] = 1;
        global[vendedor-1][articulo] += (cantidad * precio);
        transacciones[vendedor-1] += 1;
  }

  cantidad_transacciones = i;
  return cantidad_transacciones;
}

void suma_por_filas(float global[][22], int cf, int cc){ //suma valor de filas en la ultima columna, exceptua la primera columna de la matriz.
    int f,c;
    float suma;
    for (f=0;f<cf;f++)
    {
        suma=0;
        for (c=1;c<cc;c++)
        {
            suma += global[f][c];
        }
        global[f][21]= suma;
    }
}

int validar_rango(int input, int tipo, int limiteSup, int limiteInf, int condicionSalida){ //valida el input a >= y <= a los limites + condicion de salida si es tipo 0 ( si cumple retorna: 2)
    switch (tipo)
    {
    case 0:
            if (input >= limiteInf && input <= limiteSup)
            {
                return 1;
            }
            else if (input == condicionSalida)
            {
                return 2;
            }
            else
            {
                return 0;
            }
        break;

    case 1:
            if (input >= limiteInf && input <= limiteSup)
            {
                return 1;
            }
            else
            {
                return 0;
            }

    default: return 0;
        break;
    }
}

void fuera_de_rango(int valor){ //repite mensaje si el valor no es válido
    while (valor == 0)
        {
            printf("Valor fuera de rango. Ingrese nuevamente. \n");
            valor = 1;
        }
}

void imprimir_cabecera(float global[][22], int v[], int count, int dd, int mm, int aa){ //dd, mm, aa: formato de fecha.
    int i;

    //imprime cabecera
    printf("\t\t\t\t------- RECAUDACIONES TOTALES POR VENDEDOR -------\t %d / %d / %d \n", dd, mm, aa);
    printf("Vendedor\t");
    for ( i = 0; i < count; i++)
    {
        printf("Art-%d\t", i+1);
    }
    
    printf("Total\n");
}

void imprimir_global(float global[][22], int v[], int cf, int cc){ //imprime tabla de cantidades
    int f, c;
    for (f=0;f<cf;f++)
    {
        for (c=0;c<cc;c++)
        {
            if (c == 0)
            {
                printf("%2d\t\t", (int)(global[f][c]));
            }
            else
            {
                printf("%7.2f\t", global[f][c]);
            }
            
        }
        printf ("\n");
    }
}


int minimo (float global[][22], int n, int num_c){ //devuelve la posicion del valor minimo de la columna numero "num_c"
    int i, fila_min = 0;
    float min = 99999999;
    for ( i = 0; i < n; i++)
    {

        if (global[i][num_c]< min && global[i][num_c] != 0)
        {
            min = global[i][num_c];
            fila_min = i+1;
        }
    }
    return fila_min;
}

void imprimir_vector(int v[], int count){
    int i;
    for ( i = 0; i < count; i++)
    {
        printf("   %d \t\t    %d\n", (i+1), v[i]);
    }
    
}

void ordenar_por_burbujeo(float mat[][22], int n, int c){ //ordena la columna 'c' de menor a mayor y la columna 0 de forma paralela a la anterior.
    int j, cota, desordenado;
    float aux, aux2;
    cota = n-1;
    desordenado =1;
        while (desordenado !=0)
        {
            desordenado=0;
            for (j=0;j<cota;j++)
            {

                if (mat[j][c]>mat[j+1][c])
                {
                    aux = mat[j][c];
                    mat[j][c]=mat[j+1][c];
                    mat[j+1][c] = aux;

                    aux2 = mat[j][0];
                    mat[j][0]=mat[j+1][0];
                    mat[j+1][0] = aux2;
                    
                    desordenado = j;
                }
            }
            cota = desordenado;
        }
}

void imprimir_lista(float mat[][22], int count, int col){ 
    int i; 
    for ( i = 0; i < count; i++)
    {
        printf("   %2d\t      %8.2f\n", (int)(mat[i][0]), mat[i][col]);
    }
}
