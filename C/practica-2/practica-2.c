#include <stdio.h>
#include <string.h>
#include <conio.h>

typedef struct
{
    int codigo;
    char descripcion[35];
    int puntoDePedido;
    int stock;
    float precioUnitario;
}PRODUCTOS;

typedef struct
{
    int codigo;
    int cantPedida;
    int cliente;
    int dia;
}PEDIDOS;

int validar_rango(int, int, int, int, int);
void fuera_de_rango(int);
void carga_datos(PEDIDOS[], int);
int buscar(PRODUCTOS[], int, int);
void dia_menos_unidades(PEDIDOS[], int);
void mostrar_matriz(float[][31], int, int);
int suma_dias(float[][31], int, int, int);


int main()
{
    int n = 1000; //cantidad de pedidos maxima a cargar.
    PEDIDOS listaPedidos[n];
    int contadorPedidos;

// carga de datos de pedidos
    printf("------------- Ingreso de pedidos del mes ---------");
    carga_datos(listaPedidos, contadorPedidos);

// punto a) actualizar campo stock
    //abro archivo
    FILE *pf;
    pf = fopen("PRODUCTOS.dat", "ab");
    if ( pf == NULL )
    {
        printf("No se puede abrir o crear archivo.\n");
        getch(); 
        exit(1);
    }
    //leo el archivo en un vector hasta el final en un vector
    int cantProductos, i=0;
    PRODUCTOS listaProductos[3500];

    fread(&listaProductos[i], sizeof(PRODUCTOS),1,pf);
    while ( !feof (pf) ) 
    {
        i++;
        fread(&listaProductos[i], sizeof(PRODUCTOS),1,pf);
    }
    cantProductos = i; //acumula la cantidad de productos leidos.
    fclose(pf);

    //resto los pedidos al stock
    int pos;
    for(i=0; i<contadorPedidos ; i++)
    {
        pos = buscar(listaProductos, listaPedidos[i].codigo, cantProductos);
        if (pos != -1)
        {
            listaProductos[pos].stock -= listaPedidos[i].cantPedida;
        }
    }

    // una vez restado, sobreescribo el archivo original con el stock actualizado
    pf = fopen("PRODUCTOS.dat", "wb");
    if ( pf == NULL )
    {
        printf("No se puede abrir o crear archivo.\n");
        getch(); 
        exit(1);
    }
    i=0;
    while(i<cantProductos)
    {
        fwrite(&listaProductos[i], sizeof(PRODUCTOS),1,pf);
        i++;
    }
    
// punto a) genero archivo con productos a reponer.
    pf = fopen("AREPONER.dat", "wb");
    if ( pf == NULL )
    {
        printf("No se puede abrir o crear archivo.\n");
        getch(); 
        exit(1);
    }
    for (i = 0; i < cantProductos; i++)
    {
        if (listaProductos[i].stock <= listaProductos[i].puntoDePedido)
        {
            fwrite(&listaProductos[i], sizeof(PRODUCTOS),1,pf);
        }
    }

// punto b) dias que se pidieron menos unidades
    dia_menos_unidades(listaPedidos, contadorPedidos);

// punto c) imprimir importes por dia por cliente siempre que haya comprado para al menos 3 dias diferentes.
    int cantClientes = 350;
    float matriz_importes[cantClientes][31];
    cargar_matriz(listaPedidos, listaProductos, matriz_importes, cantClientes, contadorPedidos, cantProductos);
    printf("Importes por dia por cliente (para aquellos que pidieron para al menos 3 dias\nCliente/Dia");
    for ( i = 1; i <= 30; i++)
    {
        printf("\t%7d", i);
    }
    printf("\n");
    mostrar_matriz(matriz_importes, cantClientes, 31);

// punto d) informar suma de importes a cobrar del dia 1 al 6.
    float importeTotal;
    importeTotal = suma_dias(matriz_importes, cantClientes, 1, 6);
    printf("\nSuma de importes total del dia 1 al 6: %.2f", importeTotal);

    return 0;
}

int validar_rango(int input, int tipo, int limiteSup, int limiteInf, int condicionSalida)
{  /*
  | tipo 0: valida >=limiteInf y <=limiteSup (retorna "1") y si cumple condSalida retorna "2" 
  | tipo 1: valida limites sin condSalida 
  | tipo 2: valida que solo sea "> 0" 
  | Siempre que no cumpla el caso retorna "0"*/
  
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
    case 2:
            if (input > 0)
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

void fuera_de_rango(int valor)
{ //repite mensaje si el valor es "0"
    while (valor == 0)
        {
            printf("Valor fuera de rango. Ingrese nuevamente. \n");
            valor = 1;
        }
} 

void carga_datos(PEDIDOS vector[], int contadorIngresos)
{
    int cargar=1, i= 0, validacion;
    while (cargar != 0)
    {
        // primer do-while con condicion de salida
        do
        {
            printf("Ingrese codigo ('999' para terminar):"); 
            scanf("%d", vector[i].codigo);
            validacion = validar_rango(vector[i].codigo, 0, 10000, 1000, 999);
            fuera_de_rango(validacion);
            if (validacion == 2) // termina carga: sale del do-while
            {
                cargar = 0;
                break;
            }
        } while (validacion == 0);

        while (validacion == 1) // si el primer do while se cargó, continua.
        {
            do 
            {
                printf("Ingrese cantidad pedida:"); 
                scanf("%d", vector[i].cantPedida);
                validacion = validar_rango(vector[i].cantPedida, 2, 0, 0, 0);
                fuera_de_rango(validacion);
            } while (validacion == 0);
            do 
            {
                printf("Ingrese numero de cliente:"); 
                scanf("%d", vector[i].cliente);
                validacion = validar_rango(vector[i].cliente, 1, 350, 1, 0);
                fuera_de_rango(validacion);
            } while (validacion == 0);
            do 
            {
                printf("Ingrese dia de entrega:"); 
                scanf("%d", vector[i].dia);
                validacion = validar_rango(vector[i].dia, 1, 30, 1, 0);
                fuera_de_rango(validacion);
            } while (validacion == 0);
        i++;
        }
    contadorIngresos += 1;
    }
    printf("\n------------- Terminó la carga de datos ---------");
}

int buscar(PRODUCTOS vector[], int datoBuscado, int tamanoVector) 
{ // busca "datoBuscado" en el vector  hasta la posicion "tamanoVector". Devuelve la posicion en el vector si existe, o "-1" si no existe.
    int i=0, pos=-1;
    while (pos==-1 && i<tamanoVector)
    {
        if (vector[i].codigo == datoBuscado)
            pos = i;
        else
            i++;
    }
    return pos;
}

void dia_menos_unidades(PEDIDOS vector[], int tamanoVector)
{
    int dia, i=0, sumaPorDia[30], min;
    printf("\nDias que se pidieron la menor cantidad de unidades: ");
    // sumo unidades pedidas por dia
    for (dia=1; dia<=30; dia++)
    {
        for (i=0; i<tamanoVector; i++)
        {
            if (vector[i].dia == dia)
            {
                sumaPorDia[dia-1] += vector[i].cantPedida;
            }
        }
    }
    // busco el valor minimo diferente de 0.
    min = 1;
    for (i=0;i<30;i++)
    {
        if (sumaPorDia[i] < min)
        {
            min = sumaPorDia[i];
        }
    }
    // busco el minimo en el vector e imprimo el numero de dia.
    /* SE PODRIA VALIDAR CON IF SI ES EL MINIMO POR DEFAULT O NO??? */
    for ( i = 0; i < 30; i++)
    {
        if (sumaPorDia[i] == min)
        {
            printf("\t%d", (i+1));
        }
    }
    printf(" .");
}

void cargar_matriz(PEDIDOS vPedidos[], PRODUCTOS vProductos[], float matriz[][31], int cantClientes, int cantPedidos, int tamanoVector)
{
    int cliente, dia, registro, pos;
    for ( dia = 1; dia <= 30; dia++)
    {
        for ( cliente = 1; cliente <= cantClientes; cliente++)
        {
            matriz[cliente-1][0] = cliente;
            for ( registro = 0; registro < cantPedidos; registro++)
            {
                while(vPedidos[registro].dia == dia && vPedidos[registro].cliente == cliente)
                {
                    pos = buscar(vProductos, vPedidos[registro].codigo, tamanoVector);
                    if (pos != -1)
                    {
                        matriz[cliente][dia] += (vPedidos[registro].cantPedida * vProductos[pos].precioUnitario);
                    }

                }

            }
            
        }
        
    }
    
}

void mostrar_matriz(float matriz[][31], int cf, int cc)
{
    int f,c, condicion;
    for (f=0;f<cf;f++)
    {
        for (c=0;c<cc;c++)
        {
            if ( matriz[f][c] != 0 && c != 0)
            {
                condicion += 1; // suma cantidad de dias distintos en los que el cliente efectuo compra.
            }
            
        }
        if (condicion >= 3) //si cumple que compro para 3 dias diferentes, imprime el renglon cliente.
        {
            for (c=0;c<cc;c++)
            {
                if (c == 0)
                {
                    printf("%3d\t", (int)(matriz[f][c]));
                }
                else
                {
                    printf("%7.2f",matriz[f][c]);
                }
            }
            printf ("\n");
        }
        
    }
}

int suma_dias(float matriz[][31], int cf, int de, int hasta)
{
    int total, f, c;
    for (f=0;f<cf;f++)
    {
        for (c = de ; c <= hasta ; c++)
        {
            total += matriz[f][c];
        }  
    }
    return total;
}