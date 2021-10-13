
package ejerciciosjava;

/**
 * @author antonio
 */
public class Parcela {
    
    private String nombre;
    private float precioCompra, precioEdificar, precioBaseAlquiler;
    private int numCasas, numHoteles, maxCasas;
    
    private static float FACTORALQUILERCALLE = 1.0f;
    private static float FACTORALQUILERCASA = 1.0f;
    private static float FACTORALQUILERHOTEL = 4.0f;
    
    Parcela(String s, float precioCompra, float precioEdificar, float precioBaseAlquiler, int maxCasas){
        nombre = s;
        this.precioCompra = precioCompra;
        this.precioBaseAlquiler = precioBaseAlquiler;
        this.precioEdificar = precioEdificar;
        this.maxCasas = maxCasas;
        
        //por defecto
        numCasas = 0;
        numHoteles = 0;
    }

    public String getNombre() {
        return nombre;
    }

    public float getPrecioCompra() {
        return precioCompra;
    }

    public float getPrecioEdificar() {
        return precioEdificar;
    }

    public int getNumCasas() {
        return numCasas;
    }
    
    public int getMaxCasas(){
        return maxCasas;
    }

    public int getNumHoteles() {
        return numHoteles;
    }
    
    public float getPrecioAlquilerCompleto(){
        
        //float precioAlquiler = precioBaseAlquiler * (1 + numCasas + 
        //     numHoteles*4);
        float precioAlquiler = precioBaseAlquiler * (1 + numCasas*FACTORALQUILERCASA + 
                numHoteles*FACTORALQUILERHOTEL);
        return precioAlquiler;
    }
    
    public boolean construirCasa(){
        if(numCasas < maxCasas){
            numCasas++;
            return false;
        }else{
            return true;
        }
    } 
    
    public boolean construirHotel(){
        numHoteles++;
        return true;
    }
    
    boolean igualdadIdentidad(Parcela otraParcela){
        return this == otraParcela;
        
    }
    
    boolean igualdadEstado (Parcela otraParcela){
        
        boolean igual = false;
        
        if(this.nombre.equals(otraParcela.getNombre()))
                if(this.precioCompra == otraParcela.getPrecioCompra())
                    if(this.precioEdificar == otraParcela.getPrecioEdificar())
                        if(this.numCasas == otraParcela.getNumCasas())
                            if(this.numHoteles == otraParcela.getNumHoteles())
                                if(this.maxCasas == otraParcela.getMaxCasas())
                                    igual = true;
        
        return igual;
    }
}
