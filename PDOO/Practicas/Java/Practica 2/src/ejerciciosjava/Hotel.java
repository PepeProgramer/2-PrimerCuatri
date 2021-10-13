package ejerciciosjava;

import java.util.ArrayList;

public class Hotel {

    private static int NUM_HOTELES = 0;
    private String nombre;
    private String ciudad;
    private int estrellas;
    private Director director;
    private ArrayList<Reserva> reservas;

    public Hotel(String nombre, String ciudad, int estrellas) {
        this.nombre = nombre;
        this.ciudad = ciudad;
        this.estrellas = estrellas;
        this.director = null;
        this.reservas = new ArrayList<>();
        NUM_HOTELES++;
    }

    public String getNombre() {
        return nombre;
    }

    static int getNUM_HOTELES() {
        return NUM_HOTELES;
    }

    void setDirector(Director director) {
        this.director = director;
        this.director.addHotel(this);

    }

    Director getDirector() {
        return this.director;
    }

    public void addReserva(Cliente cliente, String fechaEntrada, String fechaSalida) {
        Reserva r = new Reserva(fechaEntrada, fechaSalida, cliente, this);
        reservas.add(r);
        cliente.addReserva(r);
    }

    public ArrayList<Reserva> getReservas() {
        /*Reserva[] reservas = new Reserva[this.reservas.size()];
        for (int i = 0; i < this.reservas.size(); i++) {
            reservas[i] = this.reservas.get(i);
        }*/
        return this.reservas;
    }
}
