/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package ejerciciosjava;
import java.util.ArrayList;

/**
 *
 * @author antonio
 */
public class Cliente {
    private String dni;
    private String nombre;
    private ArrayList<Reserva> reservas;
    
    
    public Cliente(String dni, String nombre){
        this.dni = dni;
        this.nombre = nombre;
        reservas = new ArrayList<>();
    }
    
    public String getNombre(){
        return nombre;
    }
    
    public void addReserva(Reserva reserva){
        reservas.add(reserva);
    }
    
    public ArrayList<Reserva> getReservas(){
        /*Reserva [] reservas = new Reserva[this.reservas.size()];
        for (int i = 0; i < this.reservas.size(); i++) {
            reservas[i] = this.reservas.get(i);
        }*/
        return this.reservas;
    }
}
