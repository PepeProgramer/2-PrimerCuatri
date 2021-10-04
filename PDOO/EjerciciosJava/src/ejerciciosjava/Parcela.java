/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ejerciciosjava;

/**
 *
 * @author jordi
 */
public class Parcela {
    private static float FACTORIAL_ALQUILER_CALLE = 1.0f;
    private static float FACTORIAL_ALQUILER_CASA = 1.0f;
    private static float FACTORIAL_ALQUILER_HOTEL = 4.0f;
    
    private static int MAX_CASAS = 2;
    
    private String nombre;
    private float precioCompra, precioEdificar, PrecioBaseAlquiler;
    private int numCasas, numHoteles, maxCasas;

    public Parcela(String nombre, float precioCompra, float precioEdificar, float PrecioBaseAlquiler, int maxCasas) {
        this.nombre = nombre;
        this.precioCompra = precioCompra;
        this.PrecioBaseAlquiler = PrecioBaseAlquiler;
        this.precioEdificar = precioEdificar;
        this.numCasas = this.numHoteles = 0;
        this.maxCasas = maxCasas;

    }

    public String getNombre() {
        return nombre;
    }

    public float getPrecioCompra() {
        return precioCompra;
    }

    public static int getMAX_CASAS() {
        return MAX_CASAS;
    }
    

    public float getPrecioEdificar() {
        return precioEdificar;
    }

    public int getNumCasas() {
        return numCasas;
    }

    public int getNumHoteles() {
        return numHoteles;
    }

    public float getPrecioAlquilerCompleto() {
        float precioAlquiler = this.PrecioBaseAlquiler * (FACTORIAL_ALQUILER_CALLE + this.numCasas*FACTORIAL_ALQUILER_CASA + this.numHoteles * FACTORIAL_ALQUILER_HOTEL);
        return precioAlquiler;
    }

    public boolean construirCasa() {
        /*if (this.numCasas < maxCasas) {
            this.numCasas++;
            return true;
        }*/
        if (this.numCasas < MAX_CASAS) {
            this.numCasas++;
            return true;
        }
        return false;
    }

    public boolean construirHotel() {
        this.numHoteles++;
        return true;
    }

    public boolean IgualdadIdentidad(Parcela otraParcela) {
        return this == otraParcela;
    }
    
    public boolean igualdadEstado(Parcela otraParcela){
        boolean mismoEstado = false;
        if(this.nombre.equals(otraParcela.getNombre()))
            if(this.precioCompra == otraParcela.getPrecioCompra())
                if(this.precioEdificar == otraParcela.getPrecioEdificar())
                    if(getPrecioAlquilerCompleto() == otraParcela.getPrecioAlquilerCompleto())
                        if(this.numCasas == otraParcela.getNumCasas())
                            if(this.numHoteles == otraParcela.getNumHoteles())
                                mismoEstado = true;
        return mismoEstado;
    }
    
    
}