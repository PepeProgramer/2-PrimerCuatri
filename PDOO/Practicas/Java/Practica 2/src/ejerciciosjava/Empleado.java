/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package ejerciciosjava;

import java.util.ArrayList;

/**
 *
 * @author jordi
 */
public class Empleado {
    private static int MAX_TRABAJOS = 2;
    private String nombre;
    private ArrayList<Hotel> trabajos;
    public Empleado(String nombre) {
        this.nombre = nombre;
        this.trabajos = new ArrayList<>();
    }

    public String getNombre() {
        return nombre;
    }
    
    public boolean addTrabajo(Hotel hotel){
        if(trabajos.size() >= MAX_TRABAJOS)
           return false;
        trabajos.add(hotel);
        return true;
    }
    
}
