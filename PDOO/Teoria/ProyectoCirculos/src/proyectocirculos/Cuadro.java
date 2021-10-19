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
public class Cuadro {
    private String titulo;
    private ArrayList<Circulo> circulos;
    private ArrayList<Puja> pujas;

    public Cuadro(String titulo) {
        this.titulo = titulo;
        this.circulos = new ArrayList<>();
        this.pujas = new ArrayList<>();
    }

    public String getTitulo() {
        return titulo;
    }

    public ArrayList<Circulo> getCirculos() {
        return circulos;
    }
    
    public void addCirculo(float radio, float x, float y){
        this.circulos.add(new Circulo(radio,x,y));
    }
    
    public double area() {
        double suma = 0;
        for(Circulo c : circulos){
            suma += c.area();
        }
        return suma;
    }
    
    public void addPuja(Puja puja){
        this.pujas.add(puja);
    }
    
    public Comprador ganadorSubasta(){
        Comprador ganador = null;
        float max = 0;
        for(Puja p: this.pujas){
            if(p.getPrecio() > max){
                ganador = p.getComprador();
                max = p.getPrecio();
            }
        }
        return ganador;
    }
}
