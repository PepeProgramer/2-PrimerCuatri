package ejerciciosjava;

import java.util.ArrayList;

public class Hotel {

    private static int NUM_HOTELES = 0;
    private String nombre;
    private String ciudad;
    private int estrellas;
    private Director director;
    private ArrayList<Reserva> reservas;
    private ArrayList<Empleado> empleados;
    private ArrayList<Habitacion> habitaciones;

    public Hotel(String nombre, String ciudad, int estrellas) {
        this.nombre = nombre;
        this.ciudad = ciudad;
        this.estrellas = estrellas;
        this.director = null;
        this.reservas = new ArrayList<>();
        this.empleados = new ArrayList<>();
        this.habitaciones = new ArrayList<>();
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

    public boolean addEmpleado(Empleado empleado) {
        this.empleados.add(empleado);
        empleado.addTrabajo(this);
        return true;
    }

    public ArrayList<Empleado> getEmpleados() {
        return this.empleados;
    }
    
    /*public void addHabitacion(int numero, int capacidad){
        this.habitaciones.add(new Habitacion(numero, capacidad));
    }*/
    
    public void addHabitacion(Habitacion habitacion){
        this.habitaciones.add(habitacion);
        habitacion.setHotel(this);
    }
    
    public int bucarHabitacionCapacidad(int capacidad){
        for(Habitacion h: this.habitaciones){
            if(h.getCapacidad() == capacidad)
                return h.getNumero();
        }
        return 0;
    }
}
