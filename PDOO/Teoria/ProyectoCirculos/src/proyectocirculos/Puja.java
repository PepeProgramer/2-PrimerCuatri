/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package proyectocirculos;

/**
 *
 * @author jordi
 */
public class Puja {
   private float precio;
   private Comprador comprador;
   private Cuadro cuadro;

    public Puja(float precio, Comprador comprador, Cuadro cuadro) {
        this.precio = precio;
        this.comprador = comprador;
        this.cuadro = cuadro;
        
        cuadro.addPuja(this);
        comprador.addPuja(this);
    }

    public float getPrecio() {
        return precio;
    }

    public Comprador getComprador() {
        return comprador;
    }

    public Cuadro getCuadro() {
        return cuadro;
    }
    
    
}
