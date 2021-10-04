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
public class EjerciciosJava {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Parcela par = new Parcela("calle pepe", 100, 50, 55, 1);
        /*Parcela igual = par;
        Parcela estado = new Parcela("calle pepe", 100, 50, 55, 1);
        Parcela par2 = new Parcela("calle pepe", 100, 50, 55, 2);
        for (int i = 0; i < 2; i++) {
            par.construirCasa();
            par.construirHotel();
            par2.construirCasa();
        }
        
        par.IgualdadIdentidad(igual);
        par.igualdadEstado(estado);
        
        System.out.println("El precio del alquiler es de: " + par.getPrecioAlquilerCompleto() + "€");
        System.out.println(par.igualdadEstado(estado));*/
        Parcela.getMAX_CASAS();
        System.out.println("Máximo de casas: " + Parcela.getMAX_CASAS());
    }
    
};
