/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package proyectocirculos;

import java.util.ArrayList;

/**
 *
 * @author jordi
 */
public class Comprador {
    private String nombre;
    private ArrayList<Puja> pujas;

    public Comprador(String nombre) {
        this.nombre = nombre;
        this.pujas = new ArrayList<>();
    }

    public String getNombre() {
        return nombre;
    }
    
    public void addPuja(Puja puja){
        this.pujas.add(puja);
    }
    
}
