
package ejerciciosjava;

import java.util.ArrayList;


public class Director {
    private String nombre;
    private long telefono;
    private ArrayList<Hotel> dirige;
    
    public Director(String nombre, long telefono){
        this.nombre = nombre;
        this.telefono = telefono;
        this.dirige = new ArrayList<>();
    }
    
    public String getNombre(){
        return nombre;
    }
    
    public void addHotel(Hotel h){
        this.dirige.add(h);
    }
    
    public ArrayList<Hotel> getHoteles(){
        return this.dirige;
    }
}
