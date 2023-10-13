#include <iostream>
using namespace std;

const char *nombre_archivo="archivo.dat";
struct Estudiante{
    int codigo;
    char nombres[50];
    char apellidos[50];
    int telefono;

};
//instanciar metodos
void Leer();
void Crear();
void Borrar();
void Actualizar();

main(){

    //Archivos
    Leer();
    Crear();
    // Actualizar();
    Borrar();

   system("pause") ;
}
void Leer(){
    system("cls");
    //abrir un archivo
    FILE* archivo = fopen(nombre_archivo,"rb");
    if (!archivo){        
        FILE* archivo = fopen(nombre_archivo,"w+b");
    }
     Estudiante estudiante;
     int id=0; //indice o posicion dentro del archivo

     //leer el archivo
     fread(&estudiante,sizeof(Estudiante),1,archivo);
     cout<<"________________________________"<<endl;
     cout<<"ID"<<"|"<<"Codigo"<<"|"<<"Nombres"<<"|"<<"Apellidos"<<"|"<<"Telefono"<<endl;
     do
     {
        cout<<id<<"|"<<estudiante.codigo<<"|"<<estudiante.nombres<<"|"<<estudiante.apellidos<<"|"<<estudiante.telefono<<endl;
        //para que cambie de registro
        fread(&estudiante,sizeof(Estudiante),1,archivo);
        id+=1;
     } while (feof(archivo)==0);
     fclose(archivo);
}

void Crear(){
    FILE* archivo = fopen(nombre_archivo,"a+b");
    char res;
    Estudiante estudiante;
    do
    {
        fflush(stdin);
        cout<<"Ingrese codigo: "<<endl;
        cin>>estudiante.codigo;
        cin.ignore();
        cout<<"Ingrese nombres: "<<endl;
        cin.getline(estudiante.nombres,50);
        cout<<"Ingrese apellidos: "<<endl;
        cin.getline(estudiante.apellidos,50);
        cout<<"Ingrese telefono: "<<endl;
        cin>>estudiante.telefono;

        //almacenamiento de datos
        fwrite(&estudiante,sizeof(Estudiante),1,archivo);

        cout<<"Desea ingresar otro estudiante (s/n)"<<endl;
        cin>>res;
    } while (res=='s'||res=='S');
    
    fclose(archivo);
    Leer();
}

void Actualizar(){
    FILE* archivo = fopen(nombre_archivo,"r+b");
    char res;
    Estudiante estudiante;
    int id=0;
    cout<<"Ingrese ID a modificar: "<<endl;
    cin>>id;  

        //posicionar el puntero
        fseek(archivo,id * sizeof(Estudiante),SEEK_SET);
        cout<<"Ingrese codigo: "<<endl;
        cin>>estudiante.codigo;
        cin.ignore();
        cout<<"Ingrese nombres: "<<endl;
        cin.getline(estudiante.nombres,50);
        cout<<"Ingrese apellidos: "<<endl;
        cin.getline(estudiante.apellidos,50);
        cout<<"Ingrese telefono: "<<endl;
        cin>>estudiante.telefono;

        //almacenamiento de datos
        fwrite(&estudiante,sizeof(Estudiante),1,archivo);

    fclose(archivo);
    Leer();
}

void Borrar(){
    const char *nombre_archivo_temp = "archivo_temp.dat";
    FILE* archivo_temp = fopen(nombre_archivo_temp,"w+b");
    FILE* archivo = fopen(nombre_archivo,"rb");

    //especificar el elemento a eliminar
    Estudiante estudiante;
    int id=0,id_n=0;

    cout<<"Ingrese el ID a eliminar: "<<endl;
    cin>>id;

    while (fread(&estudiante,sizeof(Estudiante),1,archivo)){
        if (id_n!=id)
        {
            fwrite(&estudiante,sizeof(Estudiante),1,archivo_temp);
        }
        id_n++;        
    }
    
    fclose(archivo);
    fclose(archivo_temp);

        //Crear archivo desde el temporal sin el id que se desea eliminar
        archivo_temp = fopen(nombre_archivo_temp,"rb");
        archivo = fopen(nombre_archivo,"wb");

        while (fread(&estudiante,sizeof(Estudiante),1,archivo_temp)){
        if (id_n!=id)
        {
            fwrite(&estudiante,sizeof(Estudiante),1,archivo);
        }
        id_n++;        
        }

        fclose(archivo);
        fclose(archivo_temp);
        Leer();
}
