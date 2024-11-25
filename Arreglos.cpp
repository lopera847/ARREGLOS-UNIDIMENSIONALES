#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

struct Cliente {
    int documento;
    string nombre;
    float saldo;
    bool activo;  // El campo activo puede quedarse como booleano
};

class Tienda {
private:
    vector<Cliente> clientes;

    // Función para buscar un cliente por su documento usando búsqueda binaria
    int buscarCliente(int documento) {
        auto it = lower_bound(clientes.begin(), clientes.end(), documento, [](const Cliente &a, int doc) {
            return a.documento < doc;
        });
        if (it != clientes.end() && it->documento == documento) {
            return it - clientes.begin();  // Devuelve el índice
        }
        return -1; // Si no lo encuentra
    }

public:
    // Opción 1: Consultar por documento
    void consultar(int documento) {
        int idx = buscarCliente(documento);
        if (idx != -1) {
            // Mostrar nombre, saldo y documento
            cout << "Cliente encontrado:" << endl;
            cout << "Nombre: " << clientes[idx].nombre << endl;
            cout << "Documento: " << clientes[idx].documento << endl;
            cout << "Saldo: " << clientes[idx].saldo << endl;
        } else {
            cout << "Cliente no encontrado." << endl;
        }
    }

    // Opción 2: Ordenar por documento
    void ordenar() {
        sort(clientes.begin(), clientes.end(), [](const Cliente &a, const Cliente &b) {
            return a.documento < b.documento;
        });
        cout << "Clientes ordenados por documento." << endl;
        mostrarClientes();  // Mostrar los clientes después de ordenar
    }

    // Opción 3: Eliminar un cliente
    void eliminar(int documento) {
        int idx = buscarCliente(documento);
        if (idx != -1) {
            clientes.erase(clientes.begin() + idx);
            cout << "Cliente eliminado." << endl;
        } else {
            cout << "Cliente no encontrado para eliminar." << endl;
        }
    }

    // Opción 4: Ingresar un nuevo cliente
    void ingresar(int documento, string nombre, float saldo) {
        if (buscarCliente(documento) != -1) {
            cout << "Error: El documento ya está registrado." << endl;
        } else {
            Cliente nuevoCliente;
            nuevoCliente.documento = documento;
            nuevoCliente.nombre = nombre;
            nuevoCliente.saldo = saldo;
            nuevoCliente.activo = true;  // Nuevo cliente activo por defecto

            // Insertar el cliente en el lugar correcto para mantener el orden
            auto it = lower_bound(clientes.begin(), clientes.end(), documento, [](const Cliente &a, int doc) {
                return a.documento < doc;
            });

            clientes.insert(it, nuevoCliente);
            cout << "Nuevo cliente ingresado." << endl;
        }
    }

    // Opción 9: Terminar
    void terminar() {
        cout << "El programa ha terminado." << endl;
    }

    // Función para mostrar el menú
    void mostrarMenu() {
        cout << "\n--- Menú de Opciones ---" << endl;
        cout << "1. Consultar" << endl;
        cout << "2. Ordenar" << endl;
        cout << "3. Eliminar" << endl;
        cout << "4. Ingresar" << endl;
        cout << "9. Terminar" << endl;
    }

    // Función para mostrar todos los clientes
    void mostrarClientes() {
        if (clientes.empty()) {
            cout << "No hay clientes registrados." << endl;
            return;
        }
        cout << "\nClientes actuales (ordenados por documento):" << endl;
        for (const auto& cliente : clientes) {
            cout << "Documento: " << cliente.documento 
                 << ", Nombre: " << cliente.nombre 
                 << ", Saldo: " << cliente.saldo << endl;
        }
    }
};

int main() {
    Tienda tienda;
    int opcion;

    while (true) {
        tienda.mostrarMenu();
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if (opcion == 1) {
            // Consultar
            int documento;
            cout << "Ingrese el número de documento a consultar: ";
            cin >> documento;
            tienda.consultar(documento);
        } else if (opcion == 2) {
            // Ordenar
            tienda.ordenar();
        } else if (opcion == 3) {
            // Eliminar
            int documento;
            cout << "Ingrese el número de documento a eliminar: ";
            cin >> documento;
            tienda.eliminar(documento);
        } else if (opcion == 4) {
            // Ingresar
            int documento;
            string nombre;
            float saldo;
            cout << "Ingrese el número de documento: ";
            cin >> documento;
            cin.ignore();  // Limpiar el buffer de entrada
            cout << "Ingrese el nombre del cliente: ";
            getline(cin, nombre);
            cout << "Ingrese el saldo: ";
            cin >> saldo;
            tienda.ingresar(documento, nombre, saldo);
        } else if (opcion == 9) {
            // Terminar
            tienda.terminar();
            break;
        } else {
            cout << "Opción inválida, por favor intente nuevamente." << endl;
        }
    }

    return 0;
}

