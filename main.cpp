#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <binario.h>
#include <encriptar.h>
#include <desencriptar.h>
#include <math.h>


using namespace std;

void escribir(string, string);

string leer(string);

bool ingreso (string,string);

void signin(string, string, int);

bool login(string,string);

bool verificar_exist(string user);

void saldo(string user);

void retiro(string user);

//1001111000111011001100100100011010010001000001010110111001101101011011001101010101101111011011110110111101101111a
/*
admin
123
juan
123
lisa
12
pola
1
*/

int main()
{

    int problema = 1;

    while (problema != 0){

        cout<<"·___________________________________________·"<<endl;
        cout<<"|           Menu de la practica 3           |"<<endl;
        cout<<"º-------------------------------------------º"<<endl;
        cout<<"|Para crear un archivo presione 1 (1)       |"<<endl;
        cout<<"|Para desencriptar un archivo presione 2 (2)|"<<endl;
        cout<<"|Para Usar el banco presione 3 (3)          |"<<endl;
        cout<<"|Para salir presione (0)                    |"<<endl;
        cout<<"---------------------------------------------"<<endl;
        cin>>problema;
        cin.ignore();

        switch (problema) {
            case 1:{
                string contenido = "",nombre_out = "",nombre_in = "", bin="", bin_en="";
                binario txtbin(0);
                encriptar _out(0,0,"");
                int cemilla = 0, metodo=0;

                cout<<"Por favor ingrese un nombre para el archivo de texto sin codificar: ";
                getline(cin,nombre_in);

                cout<<"Por favor ingrese un nombre para el archivo de texto codificado: ";
                getline(cin,nombre_out);

                cout<<"Por favor ingrese el contenido del texto: ";
                getline(cin,contenido);

                cout<<"Por favor ingrese la cemilla de encriptacion: ";
                cin>>cemilla;

                cout<<"Por favor ingrese el metodo de encriptacion: ";
                cin>>metodo;
                cin.ignore();

                for (int i = 0 ; i < contenido.length() ; i++){
                    bin += txtbin.ascii_bin(contenido[i]); // bin = contenido en binario.
                }

                escribir(nombre_in,bin);

                bin_en =_out.encriptado(cemilla, metodo, bin);

                escribir(nombre_out, bin_en);

                break;

            }

            case 2:{
                string nombre_out = "", contenido= "", traduccion = "", desencr="",desencr2="";
                int cemilla=0;
                cout << "Ingrese el nombre del archivo que quiere desencriptar: ";
                getline(cin,nombre_out);
                cout<<"Ingrese la cemilla con la que encripto el archivo "<<nombre_out<<": ";
                cin>>cemilla;
                cin.ignore();

                contenido = leer(nombre_out);

                desencriptar _in(cemilla,contenido);
                binario _traduccion(contenido);

                desencr=_in.desencriptado(cemilla,contenido);

                cout<<"El archivo desencriptado es: "<<desencr<<endl;

                for(int i=0; i<contenido.length() ; i+=8){
                    for(int j =0; j<8 ; j++){
                        desencr2 += desencr[i+j];
                    }
                    traduccion+=_traduccion.bin_ascii(desencr2);
                    desencr2="";
                }
                cout<<"Traduciendolo a lenguaje alfabetico: "<<traduccion<<endl;
                break;


            }

            case 3:{

            string user="", password="";
            cout<<"Autentifiquese como administrador para usar el banco."<<endl;
            cout<<"Ingrese su usuario: ";
            cin>>user;
            cout<<"Ingrese su contraseña: ";
            cin>>password;

            if (ingreso (user,password)){
                cout<<"·________________·"<<endl;
                cout<<"|   BIENVENIDO   |"<<endl;
                cout<<"º----------------º"<<endl;

                int problemabanco = 1;

                while (problemabanco != 0){

                    cout<<"·___________________________________________·"<<endl;
                    cout<<"|               Menu del Banco              |"<<endl;
                    cout<<"º-------------------------------------------º"<<endl;
                    cout<<"|Iniciar sesion (1)                         |"<<endl;
                    cout<<"|Registrarse (2)                            |"<<endl;
                    cout<<"|Para salir presione (0)                    |"<<endl;
                    cout<<"---------------------------------------------"<<endl;
                    cin>>problemabanco;
                    cin.ignore();

                    switch (problemabanco) {
                        case 1:{
                        string User="",Password="";
                        cout<<"Ingrese un nombre: ";
                        cin>>User;
                        cout<<"Ingrese una contraseña: ";
                        cin>>Password;
                        if(login(User,Password)){
                            int problema = 1;

                            while (problema != 0){

                                cout<<"·___________________________________________·"<<endl;
                                cout<<"|              Menu de usuario              |"<<endl;
                                cout<<"º-------------------------------------------º"<<endl;
                                cout<<"|Para consultar saldo pulse 1 (1)           |"<<endl;
                                cout<<"|Para retirar dinero pulse 2 (2)            |"<<endl;
                                cout<<"|Para salir pulse (0)                       |"<<endl;
                                cout<<"---------------------------------------------"<<endl;
                                cin>>problema;
                                cin.ignore();

                                switch (problema) {
                                    case 1:{
                                        saldo(User);

                                    break;}
                                    case 2:{
                                        retiro(User);

                                    break;}
                                }
                            }
                        }
                        else
                            cout<<"Usuario o contraseña incorrectos."<<endl;

                        break;}
                        case 2:{
                        string User="",Password="";
                        int Money=250;
                        cout<<"Ingrese un nombre: ";
                        cin>>User;
                        cout<<"Ingrese una contraseña: ";
                        cin>>Password;
                        if(!verificar_exist(User)){
                            signin(User, Password, Money);
                            cout<<"Su cuenta se creara con 250 pesos."<<endl;
                            cout<<"Registrado exitosamente."<<endl;
                        }
                        else
                            cout<<"El usuario "<<"'"<<User<<"' ya existe."<<endl;


                        break;
                        }
                    }
                    }
            }
            else{
                cout<<"contraseña o usuario incorrecto."<<endl;
            }


            break;
            }
        }
    }




    return 0;
}




void escribir(string nombre, string bin){
    ofstream archivo_w;

    archivo_w.open(nombre, ios::out );

    if (archivo_w.fail()){
        cout<<"No se pudo abrir el archivo."<<endl;
        exit(1);
    }
    archivo_w<<bin;
    archivo_w<<"\n";

    archivo_w.close();

}

string leer(string nombre_out){
    ifstream archvo_r;
    string texto1="",texto2="";
    archvo_r.open(nombre_out, ios::in);

    if (archvo_r.fail()){
        cout<<"No se pudo abrir el archivo."<<endl;
        exit(1);
    }

    while(!archvo_r.eof()){
        getline(archvo_r,texto1);
        texto2 += texto1;
    }

    archvo_r.close();

    return (texto2);


}

bool ingreso (string user, string passwor){
    ifstream leer ("sudo.txt", ios::in);
    if (leer.fail()){
        cout<<"No se pudo abrir el archivo."<<endl;
        exit(1);
    }
    string usuario="",clave="",bina="",desencr="",desencr2="",traduccion="";
    leer>>bina;
    desencriptar _in(4,bina);
    binario _traduccion(bina);
    desencr=_in.desencriptado(4,bina);

    for(int i=0; i<bina.length() ; i+=8){
        for(int j =0; j<8 ; j++){
            desencr2 += desencr[i+j];
        }
        traduccion+=_traduccion.bin_ascii(desencr2);
        desencr2="";
    }

    usuario = traduccion.substr(0,traduccion.find(" "));

    traduccion.erase(0,traduccion.find(" ")+1);

    clave = traduccion.substr(0,traduccion.find(" "));


    if (usuario == user && passwor == clave){
        return true;
        leer.close();}
    else{
        return false;
        leer.close();}
}

void signin(string User, string Password, int money){

    string bin="";
    binario txtbin(0);
    encriptar txten(4,1,"");
    ofstream archivo_w;
    archivo_w.open("sudo.txt", ios::out | ios::app);

    for (int i = 0 ; i < User.length() ; i++){
        bin += txtbin.ascii_bin(User[i]); // bin = contenido en binario.
    }
    bin+="00100000";
    for (int i = 0 ; i < Password.length() ; i++){
        bin += txtbin.ascii_bin(Password[i]); // bin = contenido en binario.
    }
    bin+="00100000";

    bin+= txtbin.ascii_bin(money);

    archivo_w<<txten.encriptado(4,1,bin)<<endl;

    archivo_w.close();
}

bool verificar_exist(string user){
    ifstream archvo_r;
    string texto_encrip="",texto_desencrip="", alfabeto ="",acomulador="",usuario="";
    desencriptar t_des(4,"");
    binario txt("");
    bool conf = false;
    archvo_r.open("sudo.txt", ios::in);

    if (archvo_r.fail()){
        cout<<"No se pudo abrir el archivo."<<endl;
        exit(1);
    }

    while(!archvo_r.eof()){
        getline(archvo_r,texto_encrip);

        if(texto_encrip == "")
            break;

        texto_desencrip = t_des.desencriptado(4,texto_encrip);

        for(int i=0; i<texto_encrip.length() ; i+=8){
            for(int j =0; j<8 ; j++){
                acomulador += texto_desencrip[i+j];
            }
            alfabeto+=txt.bin_ascii(acomulador);

            acomulador="";
        }
        usuario = alfabeto.substr(0,alfabeto.find(" "));

        if (usuario == user){
            conf = true;
        }

        alfabeto = "";

    }

    archvo_r.close();
    return conf;
}

bool login(string user,string password){
    ifstream archvo_r;
    string texto_encrip="",texto_desencrip="", alfabeto ="",acomulador="",usuario="",clave="";
    desencriptar t_des(4,"");
    binario txt("");

    bool conf = false;
    archvo_r.open("sudo.txt", ios::in);///home/juan/practica03/sudo

    if (archvo_r.fail()){
        cout<<"No se pudo abrir el archivo."<<endl;
        exit(1);
    }

    while(!archvo_r.eof()){
        getline(archvo_r,texto_encrip);

        if(texto_encrip == "")
            break;

        texto_desencrip = t_des.desencriptado(4,texto_encrip);

        for(int i=0; i<texto_encrip.length() ; i+=8){
            for(int j =0; j<8 ; j++){
                acomulador += texto_desencrip[i+j];
            }
            alfabeto+=txt.bin_ascii(acomulador);

            acomulador="";
        }
        usuario = alfabeto.substr(0,alfabeto.find(" "));

        alfabeto.erase(0,alfabeto.find(" ")+1);

        clave = alfabeto.substr(0,alfabeto.find(" "));

        if (usuario == user && password == clave){
            conf = true;
        }

        alfabeto = "";

    }

    archvo_r.close();
    return conf;

}

void saldo(string user){
    ifstream archvo_r;
    ofstream temp;

    int money=0,c=0,letter=0;
    vector <string> bill;
    string texto_encrip="",texto_desencrip="", alfabeto ="",acomulador="",usuario="",clave="",moneystr="",textoout="",moneybin="",bin="";
    desencriptar t_des(4,"");
    encriptar out(4,1,"");
    binario txt(""),plata(0),plataout(0),txtbin(0);

    archvo_r.open("sudo.txt", ios::in); //para leer
    temp.open("temp.txt", ios::out); //para escribir

    if (archvo_r.fail()){
        cout<<"No se pudo abrir el archivo."<<endl;
        exit(1);
    }

    while(!archvo_r.eof()){
        getline(archvo_r,texto_encrip);

        if(texto_encrip == "")
            break;



        texto_desencrip = t_des.desencriptado(4,texto_encrip);

        for(int i=0; i<texto_encrip.length() ; i+=8){
            for(int j =0; j<8 ; j++){
                acomulador += texto_desencrip[i+j];
            }
            alfabeto+=txt.bin_ascii(acomulador);

            acomulador="";
        }
        bill.push_back(texto_desencrip.substr(texto_desencrip.length()-8,8));

        usuario = alfabeto.substr(0,alfabeto.find(" "));
        alfabeto.erase(0,alfabeto.find(" ")+1);
        textoout+=usuario;
        textoout+=" ";

        clave = alfabeto.substr(0,alfabeto.find(" "));
        alfabeto.erase(0,alfabeto.find(" ")+1);
        textoout+=clave;
        textoout+=" ";

        moneystr=bill[money];

        for (int i = 7 ; i>=0 ; i--){
            if(moneystr[i] == '1')
                letter += pow(2,c);
            else
                letter+=0;

            c++;

        }



        if (user == usuario){

            cout<<"su dinero actual es: "<<letter<<endl;
            letter= letter-5;
            moneybin=plataout.ascii_bin(letter);

            for (int i = 0 ; i < textoout.length() ; i++){
                bin += txtbin.ascii_bin(textoout[i]); // bin = contenido en binario.
            }
            bin+=moneybin;

            temp<<out.encriptado(4,1,bin)<<endl;

        }
        else{
            temp<<texto_encrip<<endl;
            textoout="";
        }

        alfabeto = "";
        money++;
        c=0;
        letter=0;

    }

    cout<<"Transaccion realizada exitosamente."<<endl;
    archvo_r.close();
    temp.close();
    remove("sudo.txt");
    rename("temp.txt","sudo.txt");

}

void retiro(string user){
    ifstream archvo_r;
    ofstream temp;

    int money=0,c=0,letter=0, retiro=0;
    vector <string> bill;
    string texto_encrip="",texto_desencrip="", alfabeto ="",acomulador="",usuario="",clave="",moneystr="",textoout="",moneybin="",bin="";
    desencriptar t_des(4,"");
    encriptar out(4,1,"");
    binario txt(""),plata(0),plataout(0),txtbin(0);

    archvo_r.open("sudo.txt", ios::in); //para leer
    temp.open("temp.txt", ios::out); //para escribir

    if (archvo_r.fail()){
        cout<<"No se pudo abrir el archivo."<<endl;
        exit(1);
    }

    while(!archvo_r.eof()){
        getline(archvo_r,texto_encrip);

        if(texto_encrip == "")
            break;



        texto_desencrip = t_des.desencriptado(4,texto_encrip);

        for(int i=0; i<texto_encrip.length() ; i+=8){
            for(int j =0; j<8 ; j++){
                acomulador += texto_desencrip[i+j];
            }
            alfabeto+=txt.bin_ascii(acomulador);

            acomulador="";
        }
        bill.push_back(texto_desencrip.substr(texto_desencrip.length()-8,8));

        usuario = alfabeto.substr(0,alfabeto.find(" "));
        alfabeto.erase(0,alfabeto.find(" ")+1);
        textoout+=usuario;
        textoout+=" ";

        clave = alfabeto.substr(0,alfabeto.find(" "));
        alfabeto.erase(0,alfabeto.find(" ")+1);
        textoout+=clave;
        textoout+=" ";

        moneystr=bill[money];

        for (int i = 7 ; i>=0 ; i--){
            if(moneystr[i] == '1')
                letter += pow(2,c);
            else
                letter+=0;

            c++;

        }



        if (user == usuario){

            cout<<"Su dinero actual es "<<letter;
            cout<<"$ ¿cuanto dinero desea retirar?: "<<endl;
            cin>>retiro;
            cin.ignore();
            letter= letter-retiro;
            moneybin=plataout.ascii_bin(letter);

            for (int i = 0 ; i < textoout.length() ; i++){
                bin += txtbin.ascii_bin(textoout[i]); // bin = contenido en binario.
            }
            bin+=moneybin;

            temp<<out.encriptado(4,1,bin)<<endl;

        }
        else{
            temp<<texto_encrip<<endl;
            textoout="";
        }

        alfabeto = "";
        money++;
        c=0;
        letter=0;

    }

    cout<<"Transaccion realizada exitosamente."<<endl;
    archvo_r.close();
    temp.close();
    remove("sudo.txt");
    rename("temp.txt","sudo.txt");

}
